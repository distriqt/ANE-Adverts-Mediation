//
//  TJEntryPoint.h
//  Tapjoy
//
//  Created by Dmytro Dovgoshliubnyi on 09/08/2023.
//  Copyright © 2023 Tapjoy. All rights reserved.
//

#ifndef _TJEntryPoint
#define _TJEntryPoint

#ifdef __cplusplus
typedef enum TJEntryPoint {
    TJEntryPointUnknown = 0,
    TJEntryPointOther,
    TJEntryPointMainMenu,
    TJEntryPointHud,
    TJEntryPointExit,
    TJEntryPointFail,
    TJEntryPointComplete,
    TJEntryPointInbox,
    TJEntryPointInitialisation,
    TJEntryPointStore
} TJEntryPoint;
#else
typedef NS_ENUM(NSUInteger, TJEntryPoint) {
    TJEntryPointUnknown = 0,
    TJEntryPointOther,
    TJEntryPointMainMenu,
    TJEntryPointHud,
    TJEntryPointExit,
    TJEntryPointFail,
    TJEntryPointComplete,
    TJEntryPointInbox,
    TJEntryPointInitialisation,
    TJEntryPointStore
};
#endif // __cplusplus
#endif // _TJEntryPoint

#ifdef __cplusplus

extern "C" {
const char* StringFromTJEntryPoint(TJEntryPoint entryPoint);
TJEntryPoint TJEntryPointFromString(const char* entryPoint);
}

#else

NS_ASSUME_NONNULL_BEGIN

NSString * _Nullable NSStringFromTJEntryPoint(TJEntryPoint entryPoint);
TJEntryPoint TJEntryPointFromNSString(NSString *entryPoint);

NS_ASSUME_NONNULL_END

#endif // __cplusplus

