// Copyright (C) 2016 by Tapjoy Inc.
//
// This file is part of the Tapjoy SDK.
//
// By using the Tapjoy SDK in your software, you agree to the terms of the Tapjoy SDK License Agreement.
//
// The Tapjoy SDK is bound by the Tapjoy SDK License Agreement and can be found here: https://www.tapjoy.com/sdk/license

#ifndef _TAPJOY__H
#define _TAPJOY__H

#import "Tapjoy.h"

@class TJTracking;

@interface Tapjoy ()
@property (weak) UIViewController *defaultViewController;
@property (nonatomic, readonly) TJTracking *tracking;

+ (void)enableLoggingInternal:(BOOL)enable;

@end


#endif
