#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QMap>

/**
 * @enum SubscriptionTier
 * @brief Enum representing available subscription tiers
 */
enum class SubscriptionTier {
    FREE = 0,              // Free tier with basic features
    PREMIUM_MONTHLY = 1,   // $5/month subscription
    PREMIUM_LIFETIME = 2   // $50 one-time lifetime purchase
};

/**
 * @class PaymentProvider
 * @brief Abstract base class for payment processing platform implementations
 *
 * PaymentProvider defines the interface for handling subscription purchases,
 * receipt validation, and tier management across different payment platforms
 * (Stripe, Apple App Store, Google Play, etc.).
 */
class PaymentProvider : public QObject
{
    Q_OBJECT
public:
    explicit PaymentProvider(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~PaymentProvider() {}

    /**
     * @brief Initiates a subscription purchase
     * @param tier The subscription tier to purchase
     */
    virtual void purchaseSubscription(SubscriptionTier tier) = 0;

    /**
     * @brief Validates a receipt from a purchase
     * @param receiptData The receipt data to validate (platform-specific format)
     * @return true if the receipt is valid and corresponds to a valid subscription
     */
    virtual bool validateReceipt(const QString &receiptData) = 0;

    /**
     * @brief Gets the currently active subscription tier
     * @return The current SubscriptionTier based on validated purchases
     */
    virtual SubscriptionTier getCurrentTier() const = 0;

    /**
     * @brief Gets the price for a given tier
     * @param tier The subscription tier
     * @return Price in USD
     */
    virtual double getPrice(SubscriptionTier tier) const = 0;

    /**
     * @brief Gets the platform name (e.g., "Stripe", "Apple", "Google")
     * @return Platform identifier string
     */
    virtual QString getPlatformName() const = 0;

signals:
    /**
     * @brief Emitted when a purchase is completed
     * @param tier The purchased tier
     * @param success Whether the purchase succeeded
     * @param receiptData The receipt data if successful, empty if failed
     * @param errorMessage Error message if failed, empty if success
     */
    void purchaseCompleted(SubscriptionTier tier, bool success, const QString &receiptData, const QString &errorMessage);

    /**
     * @brief Emitted when receipt validation finishes
     * @param valid Whether the receipt is valid
     * @param tier The tier associated with the receipt (FREE if invalid)
     */
    void receiptValidated(bool valid, SubscriptionTier tier);

    /**
     * @brief Emitted when the active tier changes
     * @param newTier The new current tier
     */
    void tierChanged(SubscriptionTier newTier);
};

/**
 * @class SubscriptionManager
 * @brief Singleton manager for subscription state and payment processing
 *
 * SubscriptionManager provides a unified interface for managing subscriptions
 * across different payment platforms. It maintains the current subscription
 * state, handles purchase flows, and persists subscription data.
 */
class SubscriptionManager : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Gets the singleton instance
     * @return The global SubscriptionManager instance
     */
    static SubscriptionManager* instance();

    /**
     * @brief Destroys the singleton instance
     */
    ~SubscriptionManager();

    /**
     * @brief Initializes the subscription system with a payment provider
     * @param provider The platform-specific payment provider to use
     *
     * Sets up the payment provider and loads saved subscription state.
     * Can only be called once; subsequent calls are ignored.
     */
    void initialize(PaymentProvider* provider);

    /**
     * @brief Shuts down the subscription system
     *
     * Cleans up the payment provider and saves current state.
     */
    void shutdown();

    /**
     * @brief Initiates a subscription purchase
     * @param tier The tier to purchase
     *
     * Delegates to the configured PaymentProvider.
     */
    void purchaseSubscription(SubscriptionTier tier);

    /**
     * @brief Validates a receipt
     * @param receiptData The receipt data from the platform
     * @return true if valid
     *
     * Validates through the PaymentProvider and updates tier on success.
     */
    bool validateReceipt(const QString &receiptData);

    /**
     * @brief Gets the current subscription tier
     * @return The active SubscriptionTier
     */
    SubscriptionTier getCurrentTier() const;

    /**
     * @brief Checks if the user has an active premium subscription
     * @return true if PREMIUM_MONTHLY or PREMIUM_LIFETIME
     */
    bool isPremium() const;

    /**
     * @brief Gets the price for a tier
     * @param tier The subscription tier
     * @return Price in USD
     */
    double getPrice(SubscriptionTier tier) const;

    /**
     * @brief Gets display name for a tier
     * @param tier The subscription tier
     * @return Human-readable name with price
     */
    QString getTierDisplayName(SubscriptionTier tier) const;

    /**
     * @brief Checks if a tier is a premium (paid) tier
     * @param tier The subscription tier
     * @return true if premium, false if FREE
     */
    bool isPremiumTier(SubscriptionTier tier) const;

    /**
     * @brief Checks if the current subscription is active (not expired)
     * @return true if subscription is active
     *
     * For PREMIUM_MONTHLY, checks expiration date.
     * For PREMIUM_LIFETIME, always true.
     * For FREE, returns false.
     */
    bool isSubscriptionActive() const;

    /**
     * @brief Gets subscription expiration date (if applicable)
     * @return Expiration date, or invalid QDateTime if not applicable
     */
    QDateTime getExpirationDate() const;

    /**
     * @brief Gets remaining days on monthly subscription
     * @return Days remaining, or -1 if not applicable
     */
    int getRemainingDays() const;

signals:
    /**
     * @brief Emitted when subscription state changes
     * @param active Whether subscription is now active
     */
    void subscriptionActivated(bool active);

    /**
     * @brief Emitted when tier changes
     * @param newTier The new tier
     */
    void tierUpdated(SubscriptionTier newTier);

    /**
     * @brief Emitted when a purchase starts
     * @param tier The tier being purchased
     */
    void purchaseStarted(SubscriptionTier tier);

    /**
     * @brief Emitted when a purchase completes
     * @param tier The purchased tier
     * @param success Whether it succeeded
     * @param errorMessage Error message if failed, empty if success
     */
    void purchaseCompleted(SubscriptionTier tier, bool success, const QString &errorMessage);

    /**
     * @brief Emitted when receipt validation completes
     * @param valid Whether the receipt was valid
     * @param tier The resulting tier (FREE if invalid)
     */
    void receiptValidated(bool valid, SubscriptionTier tier);

public slots:
    /**
     * @brief Slot called by PaymentProvider when purchase completes
     * @param tier The purchased tier
     * @param success Whether the purchase succeeded
     * @param receiptData The receipt data if successful
     * @param errorMessage Error message if failed
     *
     * Internal slot connected to PaymentProvider signals.
     */
    void onPurchaseCompleted(SubscriptionTier tier, bool success, const QString &receiptData, const QString &errorMessage);

    /**
     * @brief Slot called by PaymentProvider when receipt validation completes
     * @param valid Whether the receipt is valid
     * @param tier The validated tier
     */
    void onReceiptValidated(bool valid, SubscriptionTier tier);

private:
    explicit SubscriptionManager(QObject *parent = nullptr);
    static SubscriptionManager* s_instance;

    // Current subscription state
    SubscriptionTier m_currentTier;
    QDateTime m_purchaseDate;
    QDateTime m_expirationDate;

    // Payment provider
    PaymentProvider* m_paymentProvider;

    // Pricing configuration
    QMap<SubscriptionTier, double> m_tierPrices;

    // State persistence
    void loadState();
    void saveState();

    // Helper to format tier name with price
    QString formatTierDisplayName(SubscriptionTier tier) const;
};

inline bool SubscriptionManager::isPremium() const
{
    return m_currentTier != SubscriptionTier::FREE;
}

inline bool SubscriptionManager::isPremiumTier(SubscriptionTier tier) const
{
    return tier != SubscriptionTier::FREE;
}

inline double SubscriptionManager::getPrice(SubscriptionTier tier) const
{
    return m_tierPrices.value(tier, 0.0);
}

inline QDateTime SubscriptionManager::getExpirationDate() const
{
    return m_expirationDate;
}

#endif // SUBSCRIPTIONMANAGER_H
