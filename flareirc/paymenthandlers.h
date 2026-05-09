#ifndef PAYMENTHANDLERS_H
#define PAYMENTHANDLERS_H

#include "subscriptionmanager.h"

/**
 * @class StripePaymentProvider
 * @brief Payment provider implementation using Stripe
 *
 * Handles subscription purchases via Stripe Checkout/Subscription API.
 * Validates receipts using Stripe's webhook signature verification.
 */
class StripePaymentProvider : public PaymentProvider
{
    Q_OBJECT
public:
    explicit StripePaymentProvider(const QString &apiKey, QObject *parent = nullptr);
    ~StripePaymentProvider();

    // PaymentProvider interface
    void purchaseSubscription(SubscriptionTier tier) override;
    bool validateReceipt(const QString &receiptData) override;
    SubscriptionTier getCurrentTier() const override;
    double getPrice(SubscriptionTier tier) const override;
    QString getPlatformName() const override;

    /**
     * @brief Sets the API key for Stripe
     * @param apiKey The secret API key
     */
    void setApiKey(const QString &apiKey);

    /**
     * @brief Gets the customer ID for the current user
     * @return Stripe customer ID, or empty if not set
     */
    QString getCustomerId() const;

    /**
     * @brief Sets the customer ID
     * @param customerId The Stripe customer ID
     */
    void setCustomerId(const QString &customerId);

signals:
    /**
     * @brief Emitted when a Stripe webhook is received
     * @param eventType The type of webhook event
     * @param data Event payload
     */
    void webhookReceived(const QString &eventType, const QVariantMap &data);

private:
    QString m_apiKey;
    QString m_customerId;
    SubscriptionTier m_tier;
    bool m_hasActiveSubscription;

    // Stripe price IDs for each tier
    QMap<SubscriptionTier, QString> m_priceIds;

    // Helper methods
    bool verifyWebhookSignature(const QByteArray &payload, const QString &signature) const;
    void handleCheckoutSessionComplete(const QVariantMap &session);
    void handleInvoicePaid(const QVariantMap &invoice);
};

/**
 * @class ApplePaymentProvider
 * @brief Payment provider implementation for Apple App Store
 *
 * Handles in-app purchases through Apple's StoreKit framework.
 * Validates receipts using Apple's verification server.
 */
class ApplePaymentProvider : public PaymentProvider
{
    Q_OBJECT
public:
    explicit ApplePaymentProvider(QObject *parent = nullptr);
    ~ApplePaymentProvider();

    // PaymentProvider interface
    void purchaseSubscription(SubscriptionTier tier) override;
    bool validateReceipt(const QString &receiptData) override;
    SubscriptionTier getCurrentTier() const override;
    double getPrice(SubscriptionTier tier) const override;
    QString getPlatformName() const override;

    /**
     * @brief Sets the shared secret for App Store receipt validation
     * @param sharedSecret The app shared secret (for auto-renewable subs)
     */
    void setSharedSecret(const QString &sharedSecret);

    /**
     * @brief Sets the product IDs for each subscription tier
     * @param tier The subscription tier
     * @param productId The Apple App Store product identifier
     */
    void setProductId(SubscriptionTier tier, const QString &productId);

    /**
     * @brief Gets the product ID for a tier
     * @param tier The subscription tier
     * @return The Apple product identifier
     */
    QString getProductId(SubscriptionTier tier) const;

private:
    QString m_sharedSecret;
    QMap<SubscriptionTier, QString> m_productIds;
    SubscriptionTier m_tier;

    // Apple's verification endpoints
    static const QString APPLE_VERIFY_URL_SANDBOX;
    static const QString APPLE_VERIFY_URL_PRODUCTION;

    // Helper methods
    QByteArray sendAppleVerifyRequest(const QByteArray &receiptData, bool useSandbox) const;
    bool parseAppleResponse(const QByteArray &response, SubscriptionTier &tier, QDateTime &expirationDate) const;
};

/**
 * @class GooglePaymentProvider
 * @brief Payment provider implementation for Google Play Billing
 *
 * Handles in-app subscriptions through Google Play Billing Library.
 * Validates purchases using Google's Developer API.
 */
class GooglePaymentProvider : public PaymentProvider
{
    Q_OBJECT
public:
    explicit GooglePaymentProvider(const QString &packageName, QObject *parent = nullptr);
    ~GooglePaymentProvider();

    // PaymentProvider interface
    void purchaseSubscription(SubscriptionTier tier) override;
    bool validateReceipt(const QString &receiptData) override;
    SubscriptionTier getCurrentTier() const override;
    double getPrice(SubscriptionTier tier) const override;
    QString getPlatformName() const override;

    /**
     * @brief Sets the OAuth2 access token for Google Play Developer API
     * @param accessToken The access token
     */
    void setAccessToken(const QString &accessToken);

    /**
     * @brief Sets the product IDs for each subscription tier
     * @param tier The subscription tier
     * @param productId The Google Play product identifier (SKU)
     */
    void setProductId(SubscriptionTier tier, const QString &productId);

    /**
     * @brief Gets the product ID for a tier
     * @param tier The subscription tier
     * @return The Google Play product identifier
     */
    QString getProductId(SubscriptionTier tier) const;

private:
    QString m_packageName;
    QString m_accessToken;
    QMap<SubscriptionTier, QString> m_productIds;
    SubscriptionTier m_tier;

    // Google Play API endpoint
    static const QString GOOGLE_PURCHASES_URL;

    // Helper methods
    QByteArray sendGoogleVerifyRequest(const QString &purchaseToken, const QString &productId) const;
    bool parseGoogleResponse(const QByteArray &response, SubscriptionTier &tier, QDateTime &expirationDate) const;
};

/**
 * @class TestPaymentProvider
 * @brief Mock payment provider for testing/development
 *
 * Simulates purchase flows without real payment processing.
 * Useful for unit testing and development without API keys.
 */
class TestPaymentProvider : public PaymentProvider
{
    Q_OBJECT
public:
    explicit TestPaymentProvider(QObject *parent = nullptr);
    ~TestPaymentProvider();

    // PaymentProvider interface
    void purchaseSubscription(SubscriptionTier tier) override;
    bool validateReceipt(const QString &receiptData) override;
    SubscriptionTier getCurrentTier() const override;
    double getPrice(SubscriptionTier tier) const override;
    QString getPlatformName() const override;

    /**
     * @brief Sets whether purchases should auto-succeed
     * @param succeed true to simulate successful purchase, false for failure
     */
    void setPurchaseSucceeds(bool succeed);

    /**
     * @brief Sets whether receipt validation should auto-succeed
     * @param succeed true to validate all receipts, false to reject
     */
    void setValidationSucceeds(bool succeed);

private:
    SubscriptionTier m_tier;
    bool m_purchaseSucceeds;
    bool m_validationSucceeds;
};

#endif // PAYMENTHANDLERS_H
