//
//  TJSdkStatus.h
//  Tapjoy
//
//  Created by Dmytro Dovgoshliubnyi on 31/01/2024.
//  Copyright © 2024 Tapjoy. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, TJSdkStatus) {
    TJSdkStatusNotConnected = -1,
    TJSdkStatusFailed,
    TJSdkStatusConnected,
    TJSdkStatusConnecting
} NS_SWIFT_NAME(Tapjoy.Status);
