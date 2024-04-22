//
//  TJOfferwallDiscoverView.h
//  Tapjoy
//
//  Created by Dominic Roberts on 20/06/2022.
//  Copyright © 2022 Tapjoy. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class TJOfferwallDiscoverView;

@protocol TJOfferwallDiscoverDelegate <NSObject>

@optional

/**
 * Callback issued by TJ to publisher to state that content has been received
 */
- (void)requestDidSucceedForView:(TJOfferwallDiscoverView *)view;
/**
 * Called when an no content has been returned
 * @error error code
 */
- (void)requestDidFailForView:(TJOfferwallDiscoverView *)view error:(nullable NSError *)error;

/**
 * Called when content has been rendered
 */
- (void)contentIsReadyForView:(TJOfferwallDiscoverView *)view;

/**
 * Call when an error occurs with the webview content
 * @error error code
 */
- (void)contentErrorForView:(TJOfferwallDiscoverView *)view error:(nullable NSError *)error;

@end

@interface TJOfferwallDiscoverView : UIView
@property (nullable, nonatomic, weak) id<TJOfferwallDiscoverDelegate> delegate;

- (void)request:(NSString *)placementName;
- (void)clear;

@end

NS_ASSUME_NONNULL_END
