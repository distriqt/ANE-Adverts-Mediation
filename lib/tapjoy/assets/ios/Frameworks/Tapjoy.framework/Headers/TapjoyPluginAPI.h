//
//  TapjoyPluginAPI.h
//  Tapjoy
//
//  Created by Dominic Roberts on 23/06/2022.
//  Copyright © 2022 Tapjoy. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Tapjoy/TJOfferwallDiscoverView.h>

NS_ASSUME_NONNULL_BEGIN

@interface TapjoyPluginAPI : NSObject
- (void)requestOfferwallDiscover:(NSString *)placementName height:(CGFloat)height delegate:(nullable id<TJOfferwallDiscoverDelegate>)delegate;
- (void)requestOfferwallDiscover:(NSString *)placementName left:(CGFloat)left top:(CGFloat)top width:(CGFloat)width height:(CGFloat)height delegate:(nullable id<TJOfferwallDiscoverDelegate>)delegate;

- (void)showOfferwallDiscover:(UIView *)view;
- (void)destroyOfferwallDiscover;
@end

NS_ASSUME_NONNULL_END
