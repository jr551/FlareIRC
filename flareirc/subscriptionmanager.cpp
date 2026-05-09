#include "subscriptionmanager.h"
#include <QSettings>
#include <QDebug>

// Static instance definition
SubscriptionManager* SubscriptionManager::s_instance = nullptr;

SubscriptionManager* SubscriptionManager::instance()
{
    if (!s_instance) {
        s_instance = new SubscriptionManager();
    }
    return s_instance;
}

SubscriptionManager::SubscriptionManager(QObject *parent)
    : QObject(parent)
    , m_currentTier(SubscriptionTier::FREE)
    , m_paymentProvider(nullptr)
{
    // Initialize pricing in USD
    m_tierPrices[SubscriptionTier::FREE] = 0.0;
    m_tierPrices[SubscriptionTier::PREMIUM_MONTHLY] = 5.0;
    m_tierPrices[SubscriptionTier::PREMIUM_LIFETIME] = 50.0;

    // Load saved subscription state
    loadState();
}

SubscriptionManager::~SubscriptionManager()
{
    shutdown();
    delete s_instance;
    s_instance = nullptr;
}

void SubscriptionManager::initialize(PaymentProvider *provider)
{
    if (!provider || m_paymentProvider) {
        qWarning() << "SubscriptionManager::initialize: Invalid provider or already initialized";
        return;
    }

    m_paymentProvider = provider;
    m_paymentProvider->setParent(this);

    // Connect payment provider signals
    connect(m_paymentProvider, &PaymentProvider::purchaseCompleted,
            this, &SubscriptionManager::onPurchaseCompleted);
    connect(m_paymentProvider, &PaymentProvider::receiptValidated,
            this, &SubscriptionManager::onReceiptValidated);
    connect(m_paymentProvider, &PaymentProvider::tierChanged,
            this, &SubscriptionManager::tierUpdated);

    qInfo() << "SubscriptionManager initialized with provider:" << m_paymentProvider->getPlatformName();
}

void SubscriptionManager::shutdown()
{
    if (m_paymentProvider) {
        m_paymentProvider->deleteLater();
        m_paymentProvider = nullptr;
    }
    saveState();
    qInfo() << "SubscriptionManager shutdown";
}

void SubscriptionManager::purchaseSubscription(SubscriptionTier tier)
{
    if (!m_paymentProvider) {
        qWarning() << "Cannot purchase: no payment provider initialized";
        emit purchaseCompleted(tier, false, QString(), "Payment system not available");
        return;
    }

    if (tier == SubscriptionTier::FREE) {
        qWarning() << "Cannot purchase FREE tier";
        emit purchaseCompleted(tier, false, QString(), "FREE tier does not require purchase");
        return;
    }

    emit purchaseStarted(tier);
    m_paymentProvider->purchaseSubscription(tier);
}

bool SubscriptionManager::validateReceipt(const QString &receiptData)
{
    if (!m_paymentProvider) {
        qWarning() << "Cannot validate receipt: no payment provider";
        return false;
    }

    return m_paymentProvider->validateReceipt(receiptData);
}

SubscriptionTier SubscriptionManager::getCurrentTier() const
{
    return m_currentTier;
}

bool SubscriptionManager::isPremium() const
{
    return m_currentTier != SubscriptionTier::FREE;
}

QString SubscriptionManager::getTierDisplayName(SubscriptionTier tier) const
{
    return formatTierDisplayName(tier);
}

bool SubscriptionManager::isPremiumTier(SubscriptionTier tier) const
{
    return tier != SubscriptionTier::FREE;
}

bool SubscriptionManager::isSubscriptionActive() const
{
    switch (m_currentTier) {
    case SubscriptionTier::PREMIUM_MONTHLY:
        if (m_expirationDate.isValid()) {
            return m_expirationDate > QDateTime::currentDateTime();
        }
        return false;
    case SubscriptionTier::PREMIUM_LIFETIME:
        return true;
    case SubscriptionTier::FREE:
    default:
        return false;
    }
}

int SubscriptionManager::getRemainingDays() const
{
    if (m_currentTier != SubscriptionTier::PREMIUM_MONTHLY || !m_expirationDate.isValid()) {
        return -1;
    }

    QDateTime now = QDateTime::currentDateTime();
    if (m_expirationDate <= now) {
        return 0;
    }

    QDate expDate = m_expirationDate.date();
    QDate currentDate = now.date();
    return currentDate.daysTo(expDate);
}

void SubscriptionManager::loadState()
{
    QSettings settings;

    int tierValue = settings.value("subscription/tier", static_cast<int>(SubscriptionTier::FREE)).toInt();
    m_currentTier = static_cast<SubscriptionTier>(tierValue);

    m_purchaseDate = settings.value("subscription/purchaseDate").toDateTime();
    m_expirationDate = settings.value("subscription/expirationDate").toDateTime();

    // Check if monthly subscription has expired
    if (m_currentTier == SubscriptionTier::PREMIUM_MONTHLY && m_expirationDate.isValid()) {
        if (m_expirationDate <= QDateTime::currentDateTime()) {
            qInfo() << "Subscription expired, downgrading to FREE";
            m_currentTier = SubscriptionTier::FREE;
            m_expirationDate = QDateTime();
            saveState();
        }
    }

    qDebug() << "Subscription state loaded:" << formatTierDisplayName(m_currentTier);
}

void SubscriptionManager::saveState()
{
    QSettings settings;
    settings.setValue("subscription/tier", static_cast<int>(m_currentTier));
    settings.setValue("subscription/purchaseDate", m_purchaseDate);
    settings.setValue("subscription/expirationDate", m_expirationDate);

    qDebug() << "Subscription state saved";
}

QString SubscriptionManager::formatTierDisplayName(SubscriptionTier tier) const
{
    switch (tier) {
    case SubscriptionTier::FREE:
        return QString("Free");
    case SubscriptionTier::PREMIUM_MONTHLY:
        return QString("Premium Monthly ($5/month)");
    case SubscriptionTier::PREMIUM_LIFETIME:
        return QString("Premium Lifetime ($50)");
    default:
        return QString("Unknown");
    }
}

void SubscriptionManager::onPurchaseCompleted(SubscriptionTier tier, bool success, const QString &receiptData, const QString &errorMessage)
{
    Q_UNUSED(receiptData);
    Q_UNUSED(errorMessage);

    if (success) {
        if (tier != m_currentTier) {
            m_currentTier = tier;
            m_purchaseDate = QDateTime::currentDateTime();

            if (tier == SubscriptionTier::PREMIUM_MONTHLY) {
                m_expirationDate = m_purchaseDate.addMonths(1);
            } else if (tier == SubscriptionTier::PREMIUM_LIFETIME) {
                m_expirationDate = QDateTime(); // No expiration
            } else {
                m_expirationDate = QDateTime();
            }

            saveState();
            emit tierUpdated(m_currentTier);
            emit subscriptionActivated(isSubscriptionActive());

            qInfo() << "Purchase successful:" << formatTierDisplayName(m_currentTier);
        }
    } else {
        qWarning() << "Purchase failed:" << errorMessage;
    }

    emit purchaseCompleted(tier, success, errorMessage);
}

void SubscriptionManager::onReceiptValidated(bool valid, SubscriptionTier tier)
{
    if (valid && tier != SubscriptionTier::FREE) {
        m_currentTier = tier;
        m_purchaseDate = QDateTime::currentDateTime();

        if (tier == SubscriptionTier::PREMIUM_MONTHLY) {
            m_expirationDate = m_purchaseDate.addMonths(1);
        } else if (tier == SubscriptionTier::PREMIUM_LIFETIME) {
            m_expirationDate = QDateTime();
        } else {
            m_expirationDate = QDateTime();
        }

        saveState();
        emit tierUpdated(m_currentTier);
        emit subscriptionActivated(true);

        qInfo() << "Receipt validated, tier updated to:" << formatTierDisplayName(tier);
    } else if (!valid) {
        qWarning() << "Receipt validation failed";
    }

    emit receiptValidated(valid, tier);
}
