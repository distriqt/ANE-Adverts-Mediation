//
//  TJSegment.h
//  Tapjoy
//
//  Created by Luke Bowman on 27/06/2023.
//  Copyright © 2023 Tapjoy. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, TJSegment) {
    TJSegmentNonPayer = 0,
    TJSegmentPayer = 1,
    TJSegmentVIP = 2,
    TJSegmentUnknown = -1
};
