#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#include <QObject>
#include <QString>
#include <QVariantMap>

enum class SubscriptionTier {
    FREE = 0,
    PREMIUM_MONTHLY = 1,
    PREMIUM_LIFETIME = 2
};

struct SubscriptionDetails {
    SubscriptionTier tier;
    QString price;
    QString displayName;
    QString description;
};

class PaymentProvider;

class SubscriptionManager : public QObject
{
    Q_OBJECT

public:
    explicit SubscriptionManager(QObject *parent = nullptr);
    ~SubscriptionManager();

    SubscriptionTier getCurrentTier() const;
    QString getCurrentTierName() const;
    QList<SubscriptionDetails> getAvailableSubscriptions() const;

    bool purchaseSubscription(SubscriptionTier tier);
    bool validateReceipt(const QString &platform, const QVariantMap &receiptData);
    void setPaymentProvider(PaymentProvider *provider);
    PaymentProvider *paymentProvider() const;

    static QString tierToString(SubscriptionTier tier);
    static QString tierToDisplayName(SubscriptionTier tier);
    static QString tierToPrice(SubscriptionTier tier);
    static SubscriptionTier stringToTier(const QString &tierStr);

signals:
    void subscriptionActive(SubscriptionTier tier);
    void subscriptionExpired();
    void purchaseSuccess(SubscriptionTier tier, const QString &receiptId);
    void purchaseFailed(const QString &error);
    void receiptValidated(bool valid, const QString &platform);

private:
    SubscriptionTier currentTier;
    SubscriptionTier pendingTier;
    PaymentProvider *provider;
    static QList<SubscriptionDetails> s_availableSubscriptions;
};

class PaymentProvider : public QObject
{
    Q_OBJECT

public:
    enum class Platform {
        Unknown,
        Steam,
        AppStore,
        GooglePlay,
        Stripe,
        Custom
    };

    explicit PaymentProvider(QObject *parent = nullptr) = default;
    virtual ~PaymentProvider() = default;

    virtual QString providerName() const = 0;
    virtual Platform platform() const = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;

    virtual bool startPurchase(SubscriptionTier tier) = 0;
    virtual bool validateReceipt(const QVariantMap &receiptData) = 0;
    virtual QVariantMap getPurchaseMetadata(SubscriptionTier tier) const = 0;

    virtual QString getCurrencyCode() const { return "USD"; }
    virtual QString getLocale() const { return "en_US"; }

signals:
    void purchaseCompleted(bool success, const QString &receiptId, const QString &error);
    void receiptValidated(bool valid, const QString &receiptId);
    void providerError(const QString &error);
};

class SteamPaymentProvider : public PaymentProvider
{
    Q_OBJECT

public:
    explicit SteamPaymentProvider(QObject *parent = nullptr);
    ~SteamPaymentProvider() override;

    QString providerName() const override;
    Platform platform() const override;
    bool initialize() override;
    void shutdown() override;

    bool startPurchase(SubscriptionTier tier) override;
    bool validateReceipt(const QVariantMap &receiptData) override;
    QVariantMap getPurchaseMetadata(SubscriptionTier tier) const override;

private slots:
    void onMicroTxnAuthResponse(int authId, bool success);
    void onMicroTxnResult(int authId, const QString &orderId, bool successful);

private:
    void *m_steamAPI; // Platform-specific handle
    int m_pendingAuthId;
    SubscriptionTier m_pendingTier;
};

class AppStorePaymentProvider : public PaymentProvider
{
    Q_OBJECT

public:
    explicit AppStorePaymentProvider(QObject *parent = nullptr);
    ~AppStorePaymentProvider() override;

    QString providerName() const override;
    Platform platform() const override;
    bool initialize() override;
    void shutdown() override;

    bool startPurchase(SubscriptionTier tier) override;
    bool validateReceipt(const QVariantMap &receiptData) override;
    QVariantMap getPurchaseMetadata(SubscriptionTier tier) const override;

private slots:
    void onStoreKitResponse(const QVariantMap &response);
    void onReceiptVerificationComplete(const QByteArray &receiptData, bool valid);

private:
    QString m_appStoreSharedSecret;
    QVariantMap m_pendingReceipt;
};

class GooglePlayPaymentProvider : public PaymentProvider
{
    Q_OBJECT

public:
    explicit GooglePlayPaymentProvider(QObject *parent = nullptr);
    ~GooglePlayPaymentProvider() override;

    QString providerName() const override;
    Platform platform() const override;
    bool initialize() override;
    void shutdown() override;

    bool startPurchase(SubscriptionTier tier) override;
    bool validateReceipt(const QVariantMap &receiptData) override;
    QVariantMap getPurchaseMetadata(SubscriptionTier tier) const override;

private slots:
    void onBillingResponse(const QVariantMap &response);
    void onPurchaseVerified(const QByteArray &purchaseData, const QString &signature, bool valid);

private:
    QString m_googlePlayPublicKey;
    QVariantMap m_pendingPurchase;
};

class StripePaymentProvider : public PaymentProvider
{
    Q_OBJECT

public:
    explicit StripePaymentProvider(const QString &apiKey, QObject *parent = nullptr);
    ~StripePaymentProvider() override;

    QString providerName() const override;
    Platform platform() const override;
    bool initialize() override;
    void shutdown() override;

    bool startPurchase(SubscriptionTier tier) override;
    bool validateReceipt(const QVariantMap &receiptData) override;
    QVariantMap getPurchaseMetadata(SubscriptionTier tier) const override;

    void setApiKey(const QString &apiKey);
    void setWebhookSecret(const QString &secret);

private slots:
    void onCheckoutComplete(const QString &sessionId, bool success);
    void onPaymentIntentComplete(const QString &paymentIntentId, bool succeeded);

private:
    QString m_apiKey;
    QString m_webhookSecret;
    QVariantMap m_activeSession;
};

#endif // SUBSCRIPTIONMANAGER_H
