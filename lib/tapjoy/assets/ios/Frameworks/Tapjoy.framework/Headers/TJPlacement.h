// Copyright (C) 2014 by Tapjoy Inc.
//
// This file is part of the Tapjoy SDK.
//
// By using the Tapjoy SDK in your software, you agree to the terms of the Tapjoy SDK License Agreement.
//
// The Tapjoy SDK is bound by the Tapjoy SDK License Agreement and can be found here: https://www.tapjoy.com/sdk/license

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <Tapjoy/TJEntryPoint.h>

#define TJC_DEPRECATION_WARNING(VERSION) __attribute__((deprecated("Go to dev.tapjoy.com for instructions on how to fix this warning")))

NS_ASSUME_NONNULL_BEGIN

typedef enum TJCActionRequestTypeEnum {
	TJActionRequestInAppPurchase = 1,
	TJActionRequestVirtualGood,
	TJActionRequestCurrency,
	TJActionRequestNavigation
} TJCActionRequestType;


/**
 A request for an app to take an action, triggered by TJPlacement content.

 */
@interface TJActionRequest : NSObject

/**
 * The type of the request
 */
@property (nonatomic, assign) TJCActionRequestType type;

/**
 * Called by your app to indicate that the request was processed successfully.
 */
- (void)completed;

/**
 * Called by your app to indicate that the request was cancelled or otherwise not successfully completed.
 */
- (void)cancelled;

@property (nullable, nonatomic, copy) id callback;

/**
 * The identifier associated with the request.
 */
@property (nullable, nonatomic, copy) NSString *requestId;

/**
 * The identifier associated with the request.
 */
@property (nullable, nonatomic, copy) NSString *token;

@end

@class TJPlacement;

/**
  The Tapjoy placement Delegate protocol. Adopt this protocol in order to handle responses that send are received upon sending a TJPlacement.
 
  The methods to prepare are:
 
  - requestDidSucceed: Called when a placement request is sent successfully
  - requestDidFail:error: Called when an error occurs while sending the placement request
  - contentIsReady: Called when content for a placement is loaded and ready to display
  - contentDidAppear: Called when placement content did appear
  - contentDidDisappear: Called when placement content did disappear
  - placement:didRequestPurchase:productId: Called when the user has successfully completed a purchase request
  - placement:didRequestReward:itemId:quantity:(int)quantity: Called when the user successfully requests a reward

 */
@protocol TJPlacementDelegate <NSObject>

@optional

/**
 * Callback issued by TJ to publisher to state that placement request is successful
 * @param placement The TJPlacement that was sent
 */
- (void)requestDidSucceed:(TJPlacement *)placement;

/**
 * Called when an error occurs while sending the placement
 * @param placement The TJPlacement that was sent
 * @error error code
 */
- (void)requestDidFail:(TJPlacement *)placement error:(nullable NSError *)error;

/**
 * Called when content for an placement is successfully cached
 * @param placement The TJPlacement that was sent
 */
- (void)contentIsReady:(TJPlacement *)placement;

/**
 * Called when placement content did appear
 * @param placement The TJPlacement that was sent
 */
- (void)contentDidAppear:(TJPlacement *)placement;

/**
 * Called when placement content did disappear
 * @param placement The TJPlacement that was sent
 */
- (void)contentDidDisappear:(TJPlacement *)placement;

/**
 * Called when a click event has occurred
 * @param placement The TJPlacement that was sent
 */
- (void)didClick:(TJPlacement *)placement;


/**
 * Callback issued by TJ to publisher when the user has successfully completed a purchase request
 * @param request - The TJActionRequest object
 * @param productId - the id of the offer that sent the request
 */
- (void)placement:(TJPlacement *)placement
didRequestPurchase:(nullable TJActionRequest *)request
        productId:(nullable NSString *)productId;

/**
 * Callback issued by TJ to publisher when the user has successfully requests a reward
 * @param placement - The TJPlacement that triggered the action request
 * @param request   - The TJActionRequest object
 * @param itemId    - The itemId for whose reward has been requested
 * @param quantity  - The quantity of the reward for the requested itemId
 */

- (void)placement:(TJPlacement *)placement
 didRequestReward:(nullable TJActionRequest *)request
           itemId:(nullable NSString *)itemId
         quantity:(int)quantity;


@end

/**
 * Deprecated since 13.2.0
 * Delegate used to receive video events from TJPlacement
 */
TJC_DEPRECATION_WARNING(13.2.0)
@protocol TJPlacementVideoDelegate <NSObject>

@optional

/**
 * Deprecated since 13.2.0
 * Called when a placement video starts playing.
 *
 */
- (void)videoDidStart:(TJPlacement *)placement TJC_DEPRECATION_WARNING(13.2.0);

/**
 * Deprecated since 13.2.0
 * Called when a placement video has completed playing.
 *
 */
- (void)videoDidComplete:(TJPlacement *)placement TJC_DEPRECATION_WARNING(13.2.0);

/**
 * Deprecated since 13.2.0
 * Called when a placement video related error occurs.
 *
 * @param errorMsg Error message.
 */
- (void)videoDidFail:(TJPlacement *)placement error:(nullable NSString *)errorMsg TJC_DEPRECATION_WARNING(13.2.0);
@end

/**
  The Tapjoy placement-Based Framework allows one to identify key placements within their application during development,
  and then reconfigure them on the dashboard as desired to help maximize monetization and engagement, without the need to update or resubmit the application.
  
  Use the TJPlacement class to define placement points in your application where ads and other content can be served.
  placements could include launching the application, completing an achievement, finishing a level, or any other moment conducive to communicating with your users.
 
  During your application development process, the key steps are to:
 
  1. Create and configure each placement as a TJPlacement
 
        TJPlacement *placement = [TJPlacement placementWithName: @"level_complete" delegate: self];
 
  2. Request content
 
        [placement requestContent];
 
  3. Present any content that is returned by the placement callbacks defined in TJPlacementDelegate
 */
@interface TJPlacement : NSObject

/** The TJPlacementDelegate used to handle responses that are received upon sending this placement*/
@property (nullable, nonatomic, weak) id<TJPlacementDelegate> delegate;

/**
 * Deprecated since 13.2.0
 * The delegate that implements the TJPlacementVideoDelegate protocol
 */
@property (nullable, nonatomic, weak) id<TJPlacementVideoDelegate> videoDelegate TJC_DEPRECATION_WARNING(13.2.0);

/** The name of the placement */
@property (nonatomic, copy) NSString *placementName;

/** Whether content has been loaded and is ready to be presented */
@property (nonatomic, assign, readonly, getter=isContentReady) BOOL contentReady;

/** Whether content is available for this placement */
@property (nonatomic, assign, readonly, getter=isContentAvailable) BOOL contentAvailable;

/** The UIViewController to show the content in */
@property (nullable, nonatomic, retain) UIViewController* presentationViewController;

/** Allows plugins to specify a topViewController class (currently only used by Unity) */
@property (nullable, nonatomic, copy) NSString *topViewControllerClassName;

@property (readonly, nonatomic) NSString *beaconId;

/** The point where Offerwall content is being presented. */
@property (nonatomic, assign) TJEntryPoint entryPoint;

/**
 * Creates a new instance of TJPlacement
 * @param placementName The name of the placement
 * @param delegate The class that implements the TJPlacementDelegate protocol
 */
+ (nullable instancetype)placementWithName:(NSString *)placementName delegate:(nullable id<TJPlacementDelegate>)delegate;

/**
 * Sends the placement request to the server
 *
 */
- (void)requestContent;

/**
 * Shows the content that was received from the server after sending this placement
 */
- (void)showContentWithViewController:(nullable UIViewController *)viewController;

/**
 * Dismiss the content
 */
+ (void)dismissContent;

/**
 * Deprecated since 13.2.0
 * Mediation params(used by mediation adapters only)
 *
 */
@property (nullable, nonatomic, copy) NSString *mediationAgent TJC_DEPRECATION_WARNING(13.2.0);
@property (nullable, nonatomic, copy) NSString *mediationId TJC_DEPRECATION_WARNING(13.2.0);

+ (nullable instancetype)placementWithName:(NSString *)placementName
                   mediationAgent:(nullable NSString *)mediationAgent
                      mediationId:(nullable NSString *)mediationId
                         delegate:(nullable id<TJPlacementDelegate>)delegate TJC_DEPRECATION_WARNING(13.2.0);

@property (nullable, nonatomic, copy) NSString *adapterVersion TJC_DEPRECATION_WARNING(13.2.0);

/**
 * Deprecated since 13.2.0
 * Programmatic mediation
 */
@property (nullable, nonatomic, copy) NSDictionary *auctionData TJC_DEPRECATION_WARNING(13.2.0);

/**
 * Deprecated since 13.2.0
 * Used by limited SDK request Only
 */
@property (nonatomic, assign) BOOL isLimited TJC_DEPRECATION_WARNING(13.2.0);

/**
 * Deprecated since 13.2.0
 */
+ (nullable instancetype)limitedPlacementWithName:(NSString *)placementName
                          mediationAgent:(nullable NSString *)mediationAgent
                                delegate:(nullable id<TJPlacementDelegate>)delegate TJC_DEPRECATION_WARNING(13.2.0);
@end

@interface TJPlacement (Currency)

/**
 * Sets the currency balance. Only the balance of self-managed currencies can be set in this way.
 *
 * @param balance the amount of the currency.  Must be greater than or equal to 0.
 * @param currencyId the ID of the currency.
 * @param completion block notifies that the currency balance has been set locally. Error parameter is nil if successful.
 */
- (void)setBalance:(NSInteger)balance
     forCurrencyId:(NSString *)currencyId
    withCompletion:(void (^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Gets the currency balance.
 *
 * @param currencyId the ID of the currency. If set to nil, will return the balance of Tapjoy-manaet currency.
 * @return the amount of the currency balance, -1 if not available.
 */
- (NSInteger)getBalanceForCurrencyId:(nullable NSString *)currencyId;

/**
 * Sets the currency amount required
 *
 * @param requiredAmount The amount of currency the user needs. Must be greater than 0.
 * @param currencyId the ID of the currency.
 * @param completion block notifies that required amount of currency has been set locally. Error parameter is nil if successful.
 */
- (void)setRequiredAmount:(NSInteger)requiredAmount
                    forCurrencyId:(NSString *)currencyId
                   withCompletion:(void (^ _Nullable)(NSError * _Nullable error))completion;

/**
 * Gets the currency amount required.
 *
 * @param currencyId the ID of the currency.
 * @return The amount of currency the user needs. -1 if not available.
 */
- (NSInteger)getRequiredAmountForCurrencyId:(NSString *)currencyId;
@end


NS_ASSUME_NONNULL_END
