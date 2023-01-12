// (c) Meta Platforms, Inc. and affiliates. Confidential and proprietary.

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FBDisplayAdController;

@protocol FBAdCompanionViewDelegate;

NS_ASSUME_NONNULL_BEGIN

/**
 This class is experimental and should not be used in production versions of your application
 */
@interface FBAdCompanionView : UIView

@property (nonatomic, weak, nullable) id<FBAdCompanionViewDelegate> delegate;

@end

/**
 Methods declared by the FBAdCompanionViewDelegate protocol are experimental
 and should not be used in production versions of your application
 */
@protocol FBAdCompanionViewDelegate <NSObject>

@optional

/**
 This method is experimental and should not be used in production versions of your application
 */
- (void)companionViewDidLoad:(FBAdCompanionView *)companionView;

/**
 This method is experimental and should not be used in production versions of your application
 */
- (void)companionViewWillClose:(FBAdCompanionView *)companionView;
@end

NS_ASSUME_NONNULL_END
