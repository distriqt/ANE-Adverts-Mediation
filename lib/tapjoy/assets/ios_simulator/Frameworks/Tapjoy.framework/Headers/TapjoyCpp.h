//
// Copyright (c) 2015 - 2018 Tapjoy, Inc.
// All rights reserved.
//

/**
 * @file TapjoyCpp.h
 * @brief C++ API header file of the Tapjoy SDK
 */

#ifndef TapjoyCpp_h
#define TapjoyCpp_h

#include <stdint.h>
#include <map>
#define TJC_DEPRECATION_WARNING(VERSION) __attribute__((deprecated("Go to dev.tapjoy.com for instructions on how to fix this warning")))

#include "TJEntryPoint.h"

#if defined(ANDROID)
#include <jni.h>
#endif
#if defined(__APPLE__) && defined(__OBJC__)
#import <UIKit/UIKit.h>
#endif

namespace tapjoy {

class TJConnectListener;
class TJGetCurrencyBalanceListener;
class TJSpendCurrencyListener;
class TJAwardCurrencyListener;
class TJEarnedCurrencyListener;
class TJSetUserIDListener;
class TJVideoListener;
class TJPlacementListener;

/**
 * @brief C++ API class of the Tapjoy SDK.
 */
class Tapjoy {
public:
    
#if defined(ANDROID) && defined(TAPJOY_STATIC)
    /**
     * @brief Sets the JavaVM instance to interoperate with Java for Android only.
     *        This method is equivalent to Tapjoy.initStaticLibrary() in Java.
     * @param vm
     *        a pointer to JavaVM instance
     */
    static jint setJavaVM(JavaVM* vm);
#endif
    
#if defined(ANDROID)
    /*
     * @brief Set common context for Android
     * @param context
     *        a context
     */
    static void setContext(jobject context);
#endif
    
    /**
     * @brief Returns the name of the library linked.
     */
    static const char* getLibraryName();
    
    /**
     * @brief Returns the version name of the SDK.
     * @return a string which represents the version name
     */
    static const char* getVersion();
    
    /**
     * @brief Enables the debug mode of the SDK.
     * @param enable
     *        true to enable
     */
    static void setDebugEnabled(bool enable);
    
    
#if defined(ANDROID)
    /**
     * @brief Connects to the Tapjoy Server
     * @param context
     *        a Java object of the application context.
     * @param sdkKey
     *        Your Tapjoy SDK Key.
     * @param listener
     *        listener for connect success/failure
     */
    static bool connect(jobject context, const char* sdkKey, TJConnectListener* listener = NULL);
#endif
    
    /**
     * @brief Connects to the Tapjoy Server
     * @param sdkKey
     *        Your Tapjoy SDK Key.
     * @param listener
     *        listener for connect success/failure
     */
    static bool connect(const char* sdkKey, TJConnectListener* listener = NULL);
    
    /**
      * @brief Connects to the Tapjoy Server
      * @param sdkKey
      *        Your Tapjoy SDK Key.
      * @param flags
      *        Connect flags.
      * @param listener
      *        listener for connect success/failure
      */
     static bool connect(const char* sdkKey,const std::map<const char*, const char*>& flags, TJConnectListener* listener = NULL);
    
    /**
     * @brief Gets the virtual currency data from the server for this device. The data
     *        will be returned in a callback to onCurrencyBalanceResponse() to the
     *        class implementing the listener.
     *
     * @param listener
     *        the class implementing the TapjoyCurrencyBalanceListener
     *        callback
     */
    static void getCurrencyBalance(TJGetCurrencyBalanceListener* listener);
    
    /**
     * @brief Spends virtual currency. This can only be used for currency managed by
     *        Tapjoy. The data will be returned in a callback to
     *        onSpendCurrencyResponse() to the class implementing the listener.
     *
     * @param listener
     *        the class implementing the TapjoySpendCurrencyListener
     *        callback
     */
    static void spendCurrency(int amount, TJSpendCurrencyListener* listener);
    
    /**
     * @brief Awards virtual currency. This can only be used for currency managed by
     *        Tapjoy. The data will be returned in a callback to
     *        onAwardCurrencyResponse() to the class implementing the listener.
     *
     * @param listener
     *        the class implementing the TJAwardCurrencyListener
     *        callback
     */
    static void awardCurrency(int amount, TJAwardCurrencyListener* listener);
    
    /**
     * @brief Sets the listener which gets informed whenever virtual currency is
     *        earned.
     *
     * @param listener
     *        class implementing TJEarnedCurrencyListener
     */
    static void setEarnedCurrencyListener(TJEarnedCurrencyListener* listener);
    
    /**
     * @brief Tracks a purchase
     *
     * @param productId
     *        the product identifier
     * @param currencyCode
     *        the currency code of price as an alphabetic currency code
     *        specified in ISO 4217, i.e. "USD", "KRW"
     * @param price
     *        the price of product
     * @param campaignId
     *        the campaign id of the Purchase Action Request if it
     *        initiated this purchase, can be null
     */
    static void trackPurchase(const char* productId, const char* currencyCode, double price, const char* campaignId);
    
#if defined(ANDROID)
    /**
     * @brief Tracks a purchase with JSON data from the Google Play store.
     *        Also performs In-app Billing validation if purchaseData and dataSignature are given.
     *
     * @param skuDetails
     *        a String in JSON Object format that contains product item
     *        details (according to <a href=
     *        "http://developer.android.com/google/play/billing/billing_reference.html#product-details-table"
     *        >Specification on Google Play</a>)
     * @param purchaseData
     *        a String in JSON format that contains details about the purchase order.
     *        Use null not to use validation.
     * @param dataSignature
     *        String containing the signature of the purchase data that the developer signed with their private key.
     *        Use null not to use validation.
     * @param campaignId
     *        the campaign id of the Purchase Action Request if it initiated
     *        this purchase, can be null
     */
    static void trackPurchaseInGooglePlayStore(const char* skuDetails, const char* purchaseData, const char* dataSignature, const char* campaignId);
#endif
#if defined(__APPLE__)
    /**
     * @brief Tracks a purchase from the Apple App Store.
     *
     * @param productId
     *        the identifier of product
     * @param currencyCode
     *        the currency code of price as an alphabetic currency code specified in ISO 4217, i.e. "USD", "KRW"
     * @param price
     *        the price of product
     * @param transactionId
     *        the identifier of iap transaction,
     *        if this is given, we will check receipt validation. (Available in iOS 7.0 and later)
     * @param campaignId
     *        the campaign id of the purchase request which initiated this purchase, can be null
     */
    static void trackPurchaseInAppleAppStore(const char* productId, const char* currencyCode, double price, const char* transactionId, const char* campaignId);
#endif
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given name without category
     */
    static void trackEvent(const char* name) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given name without category, with a value.
     *
     * @param name
     *        the name of event
     * @param value
     *        the value of event
     */
    static void trackEvent(const char* name, int64_t value) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given category and name, with a value.
     */
    static void trackEvent(const char* category, const char* name, int64_t value) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given category and name, with two parameters.
     */
    static void trackEvent(const char* category, const char* name, const char* parameter1, const char* parameter2) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given category and name, with two parameters and a
     *        value.
     */
    static void trackEvent(const char* category, const char* name, const char* parameter1, const char* parameter2, int64_t value) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given category and name, with two parameters and a
     *        named values.
     */
    static void trackEvent(const char* category, const char* name, const char* parameter1, const char* parameter2, const char* valueName, int64_t value) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Tracks an event of the given category and name, with two parameters and
     *        two named values.
     */
    static void trackEvent(const char* category, const char* name, const char* parameter1, const char* parameter2, const char* value1Name, int64_t value1, const char* value2Name, int64_t value2) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     */
    static void trackEvent(const char* category, const char* name, const char* parameter1, const char* parameter2, const char* value1Name, int64_t value1, const char* value2Name, int64_t value2, const char* value3Name, int64_t value3) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @brief Manual session tracking. Notifies the SDK that new session of your
     *        application has been started.
     */
    static void startSession();
    
    /**
     * @brief Manual session tracking. Notifies the SDK that the session of your
     *        application has been ended.
     */
    static void endSession();
    
    /**
     * @brief Assigns a user ID for this user/device. This is used to identify the user
     *        in your application.
     *
     *        This is REQUIRED for NON-MANAGED currency apps.
     *
     * @param userID
     *        user ID you wish to assign to this device
     */
    static void setUserID(const char* userID);
    
    /**
     * @brief Assigns a user ID for this user/device. This is used to identify the user
     *        in your application.
     *
     *        This is REQUIRED for NON-MANAGED currency apps.
     *
     * @param userID
     *        user ID you wish to assign to this device
     *
     * @param listener
     *        class implementing TJUserIdListener
     */
    static void setUserID(const char* userID, TJSetUserIDListener* listener);
    
    /**
     * @brief Assign a custom parameter associated with any following placement requests that contains an ad type. We will return this value on the currency callback.
     *        Only applicable for publishers who manage their own currency servers. This value does NOT get unset with each subsequent placement request.
     *
     * @param customParam
     *         The custom parameter to assign to this device
     */
    static void setCustomParameter(const char* customParam);
    
    /**
     * @brief Returns the currently set custom parameter.
     *
     * @return the value of the currently set custom parameter
     */
    static const char* getCustomParameter();
    
    /**
     * @brief Sets the level of the user.
     *
     * @param userLevel
     *        the level of the user
     */
    static void setUserLevel(int userLevel);
    
    /**
     * @brief Gets the segment of the user
     *
     * @return userSegment 0 (non-payer), 1 (payer), 2 (VIP), -1 (unknown).
     */
    static int getUserSegment();
    
    /**
     * @brief Sets the segment of the user
     *
     * @param userSegment  0 (non-payer), 1 (payer), 2 (VIP), -1 (unknown).
     */
    static void setUserSegment(int userSegment);
    
    /**
     * This method sets the maximum level of the user.
     *
     * @param maxLevel
     *        the maximum possible level
     */
    static void setMaxLevel(int maxLevel);
    
    /**
     * @brief Gets the maximum level of the user.
     *
     * @return the max level
     */
    static int getMaxLevel();
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Sets the friends count of the user.
     *
     * @param friendCount
     *        the number of friends
     */
    static void setUserFriendCount(int friendCount) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @deprecated Deprecated since 13.2.0
     * @brief Sets a variable of user for the cohort analysis.
     *
     * @param variableIndex
     *        the index of the variable to set, must be in the range 1 to 5
     * @param value
     *        the value of the variable to set, or null to unset
     */
    static void setUserCohortVariable(int variableIndex, const char* value) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @brief Removes all tags from the user.
     */
    static void clearUserTags();
    
    /**
     * @brief Adds the given tag to the user if it is not already present.
     *
     * @param tag
     *        the tag to be added
     */
    static void addUserTag(const char* tag);
    
    /**
     * @brief Removes the given tag from the user if it is present.
     *
     * @param tag
     *        the tag to be removed
     */
    static void removeUserTag(const char* tag);
    
    /**
     * @brief Sets the video listener. Use this to receive callbacks for on video
     *        start, complete and error.
     *
     * @param listener
     *        video to receive start/complete/error callbacks
     *
     * @deprecated Deprecated since 13.2.0.
     */

    static void setVideoListener(TJVideoListener* listener) TJC_DEPRECATION_WARNING(13.2.0);
    
    /**
     * @brief Informs the Tapjoy server that the specified Pay-Per-Action was
     *        completed. Should be called whenever a user completes an in-game action.
     *
     * @param actionID
     *        The action ID of the completed action.
     */
    static void actionComplete(const char* actionID);
    
#if defined(ANDROID)
    /**
     * @deprecated Deprecated since 13.2.0.
     * @brief Returns true if the push notification is disabled.
     */
    static bool isPushNotificationDisabled();

    /**
     * @deprecated Deprecated since 13.2.0.
     * @brief Sets whether the push notification is disabled.
     * @param disabled
     *        true to disable the push notification
     */
    static void setPushNotificationDisabled(bool disabled);

    /**
     * @deprecated Deprecated since 13.2.0.
     * @brief Set Firebase Token to initiate Firebase messaging for your application.
     *        Call this method when the Firebase token service callback is triggered to update the token.
     *
     * @param deviceToken
     *           deviceToken is a registration token for firebase senderID and AppID to register in Tapjoy Server.
     *           It is updated through Firebase token service callback triggered everytime Firebase update the token.
     */
    static void setDeviceToken(const char* deviceToken);

    /**
     * @deprecated Deprecated since 13.2.0.
     * @brief Sets the context and RemoteMessage data so that our SDK can display the push notification.
     *        Call this when a message is received from Firebase
     *
     * @param context: The Application context (jobject)
     * @param remoteMessage: The message(jobject) received from Firebase
     */
    static void setReceiveRemoteNotification(jobject context,jobject remoteMessage);
    
    /**
     * @brief This is to opt out passing advertising_id param in the subsequent network requests
     * @param context: The Application context (jobject)
     * @param optOut: Set to true to opt out advertising_id in the subsequent requests, false to disable
     */
    static void optOutAdvertisingID(jobject context, bool optOut);
#endif
    
    /**
     * @brief Helper function to check if SDK is initialized
     */
    static bool isConnected();
};

#if defined(ANDROID)
typedef jobject TJActionRequestHandle;
typedef jobject TJPlacementHandle;
typedef jobject TJPrivacyPolicyHandle;
#else
typedef void* TJActionRequestHandle;
typedef void* TJPlacementHandle;
typedef void* TJPrivacyPolicyHandle;
#endif

class TJConnectListener {
public:
    virtual ~TJConnectListener() {}
    
    virtual void onConnectSuccess() {}
    virtual void onConnectFailure(int code, const char* error) {}
    virtual void onConnectWarning(int code, const char* error) {}
};

class TJAwardCurrencyListener {
public:
    virtual ~TJAwardCurrencyListener() {}
    
    virtual void onAwardCurrencyResponse(const char* currencyName, int balance) {}
    virtual void onAwardCurrencyResponseFailure(const char* error) {}
};

class TJEarnedCurrencyListener {
public:
    virtual ~TJEarnedCurrencyListener() {}
    
    virtual void onEarnedCurrency(const char* currencyName, int amount) {}
};

class TJGetCurrencyBalanceListener {
public:
    virtual ~TJGetCurrencyBalanceListener() {}
    
    virtual void onGetCurrencyBalanceResponse(const char* currencyName, int balance) {}
    virtual void onGetCurrencyBalanceResponseFailure(const char* error) {}
};

class TJSpendCurrencyListener {
public:
    virtual ~TJSpendCurrencyListener() {}
    
    virtual void onSpendCurrencyResponse(const char* currencyName, int balance) {}
    virtual void onSpendCurrencyResponseFailure(const char* error) {}
};

class TJSetCurrencyBalanceListener {
public:
    virtual ~TJSetCurrencyBalanceListener() {}
    
    virtual void onSetCurrencyBalanceSuccess() {}
    virtual void onSetCurrencyBalanceFailure(int code, const char* error) {}
};

class TJSetCurrencyAmountRequiredListener {
public:
    virtual ~TJSetCurrencyAmountRequiredListener() {}

    virtual void onSetCurrencyAmountRequiredSuccess() {}
    virtual void onSetCurrencyAmountRequiredFailure(int code, const char* error) {}
};

class TJSetUserIDListener {
public:
    virtual ~TJSetUserIDListener() {}
    
    virtual void onSetUserIDSuccess() {}
    virtual void onSetUserIDFailure(const char* error) {}
};

class TJC_DEPRECATION_WARNING(13.2.0) TJVideoListener {
public:
    virtual ~TJVideoListener() {}
    
    virtual void onVideoStart() {}
    virtual void onVideoClose() {}
    virtual void onVideoError(int statusCode) {}
    virtual void onVideoComplete() {}
};

class TJPlacementListener {
public:
    virtual ~TJPlacementListener() {}
    
    virtual void onRequestSuccess(TJPlacementHandle placementHandle, const char* placementName) {}
    virtual void onRequestFailure(TJPlacementHandle placementHandle, const char* placementName, int errorCode, const char* errorMessage) {}
    virtual void onContentReady(TJPlacementHandle placementHandle, const char* placementName) {}
    virtual void onContentShow(TJPlacementHandle placementHandle, const char* placementName) {}
    virtual void onContentDismiss(TJPlacementHandle placementHandle, const char* placementName) {}
    virtual void onClick(TJPlacementHandle placementHandle, const char* placementName) {}
    virtual void onPurchaseRequest(TJPlacementHandle placementHandle, const char* placementName, TJActionRequestHandle requestHandle, const char* requestId, const char* requestToken, const char* productId) {}
    virtual void onRewardRequest(TJPlacementHandle placementHandle, const char* placementName, TJActionRequestHandle requestHandle, const char* requestId, const char* requestToken, const char* itemId, int quantity) {}
};

class TJActionRequest {
public:
    static void completed(TJActionRequestHandle actionRequestHandle);
    static void cancelled(TJActionRequestHandle actionRequestHandle);
};

class TJPlacement {
public:
#if defined(ANDROID)
    static TJPlacementHandle create(jobject activityContext, const char* placementName, TJPlacementListener* listener);
#endif
    static TJPlacementHandle create(const char* placementName, TJPlacementListener* listener);
    static void release(TJPlacementHandle placementHandle);
    static bool isContentReady(TJPlacementHandle placementHandle);
    static bool isContentAvailable(TJPlacementHandle placementHandle);
    static void requestContent(TJPlacementHandle placementHandle);
    static void showContent(TJPlacementHandle placementHandle);
    static void setCurrencyBalance(TJPlacementHandle handle, const char* currencyId, int amount, TJSetCurrencyBalanceListener* listener);
    static void setCurrencyAmountRequired(TJPlacementHandle handle, const char* currencyId, int amount, TJSetCurrencyAmountRequiredListener* listener);
    static int getCurrencyBalance(TJPlacementHandle handle, const char* currencyId);
    static int getCurrencyAmountRequired(TJPlacementHandle handle, const char* currencyId);
    static void setEntryPoint(TJPlacementHandle placementHandle, TJEntryPoint entryPoint);
    static TJEntryPoint getEntryPoint(TJPlacementHandle placementHandle);
#if defined(__APPLE__) && defined(__OBJC__)
    static void showContentWithViewController(TJPlacementHandle placementHandle, UIViewController* viewController);
#endif
    static void dismissContent();
};

enum class TJStatusCpp : size_t {
    TJStatusFalse = 0,
    TJStatusTrue = 1,
    TJStatusUnknown = 2
};

class TJPrivacyPolicy {
public:
    /**
     * @brief Returns the TJPrivacyPolicy instance for calling methods to set GDPR, User's consent, below consent age ,and US Privacy policy flags
     *
     * @return TJPrivacyPolicy singleton instance
     */
    static TJPrivacyPolicyHandle getPrivacyPolicy();
    
    /**
     * Deprecated since 13.1.0
     * @brief This can be used by the integrating App to indicate if the user falls in any of the GDPR applicable countries
     *        (European Economic Area). The value should be set to TRUE when User (Subject) is applicable to GDPR regulations
     *        and FALSE when User is not applicable to GDPR regulations. In the absence of this call, Tapjoy server makes the
     *        determination of GDPR applicability.
     *
     * @param gdprApplicable
     *        true if GDPR applies to this user, false otherwise
     */
    static void setSubjectToGDPR(TJPrivacyPolicyHandle handle, bool gdprApplicable);
    
    /**
     * @brief This can be used by the integrating App to indicate if the user falls in any of the GDPR applicable countries
     *        (European Economic Area). The value should be set to TRUE when User (Subject) is applicable to GDPR regulations
     *        and FALSE when User is not applicable to GDPR regulations. In the absence of this call, Tapjoy server makes the
     *        determination of GDPR applicability.
     *
     * @param gdprStatus
     *        True if GDPR applies to this user, False if not or Unknown otherwise.
     */
    static void setSubjectToGDPRStatus(TJPrivacyPolicyHandle handle, TJStatusCpp gdprStatus);
    
    /**
     * Deprecated since 13.1.0
     * @brief This is used for sending User's consent to behavioral advertising such as in the context of GDPR
     * The consent value can be "0" (User has not provided consent), "1" (User has provided consent) or
     * a daisybit string as suggested in IAB's Transparency and Consent Framework
     *        
     *@param consent "0" (User has not provided consent), "1" (User has provided consent) or a daisybit string as suggested in IAB's Transparency and Consent Framework
     */
    static void setUserConsent(TJPrivacyPolicyHandle handle, const char* consent);
    
    /**
     * @brief This is used for sending User's consent to behavioral advertising such as in the context of GDPR
     * The consent value can be "0" (User has not provided consent), "1" (User has provided consent) or
     * a daisybit string as suggested in IAB's Transparency and Consent Framework
     *
     * @param userConsentStatus False (User has not provided consent), True (User has provided consent) or a daisybit string as suggested in IAB's Transparency and Consent Framework, Uknown otherwise.
     */
    static void setUserConsentStatus(TJPrivacyPolicyHandle handle, TJStatusCpp userConsentStatus);
    
    /**
     * Deprecated since 13.1.0
     * @brief In the US, the Children’s Online Privacy Protection Act (COPPA) imposes certain requirements on operators of online
     *        services that (a) have actual knowledge that the connected user is a child under 13 years of age, or (b) operate services
     *        (including apps) that are directed to children under 13.
     *
     *        Similarly, the GDPR imposes certain requirements in connection with data subjects who are below the applicable local
     *        minimum age for online consent (ranging from 13 to 16, as established by each member state).
     *
     *        For applications that are not directed towards children under 13 years of age, but still have a minority share of users known
     *        to be under the applicable minimum age, utilize this method to access Tapjoy’s monetization capability. This method will set
     *        ad_tracking_enabled to false for Tapjoy which only shows the user contextual ads. No ad tracking will be done on this user.
     * @param isBelowConsentAge True if below consent age (COPPA) applies to this user, false otherwise
     */
    static void setBelowConsentAge(TJPrivacyPolicyHandle handle, bool isBelowConsentAge);
    
    /**
     * @brief In the US, the Children’s Online Privacy Protection Act (COPPA) imposes certain requirements on operators of online
     *        services that (a) have actual knowledge that the connected user is a child under 13 years of age, or (b) operate services
     *        (including apps) that are directed to children under 13.
     *
     *        Similarly, the GDPR imposes certain requirements in connection with data subjects who are below the applicable local
     *        minimum age for online consent (ranging from 13 to 16, as established by each member state).
     *
     *        For applications that are not directed towards children under 13 years of age, but still have a minority share of users known
     *        to be under the applicable minimum age, utilize this method to access Tapjoy’s monetization capability. This method will set
     *        ad_tracking_enabled to false for Tapjoy which only shows the user contextual ads. No ad tracking will be done on this user.
     *@param belowConsentAgeStatus True if below consent age (COPPA) applies to this user, false if not, Unknown otherwise.
     */
    static void setBelowConsentAgeStatus(TJPrivacyPolicyHandle handle, TJStatusCpp belowConsentAgeStatus);
    
    /**
     * @brief This is used for sending US Privacy value to behavioral advertising such as in the context of GDPR
     *        The value can be in IAB's US Privacy String Format consists of specification version to encode the string in number, explicit notice or opportunity to opt out in enum, opt-out sale in enum, LSPA covered transaction in enum .
     *        eg. "1YNN" where 1 is char in string for the version, Y = YES, N = No, - = Not Applicable
     *
     *        See: IAB suggested US Privacy String Format: https://github.com/InteractiveAdvertisingBureau/USPrivacy/blob/master/CCPA/Version%201.0/US%20Privacy%20String.md#us-privacy-string-format
     *
     * @param privacyValue The us privacy value string
     */
    static void setUSPrivacy(TJPrivacyPolicyHandle handle, const char* privacyValue);
};

}

#endif // TapjoyCpp_h
