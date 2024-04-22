#import <Foundation/Foundation.h>
#define TJC_DEPRECATION_WARNING(VERSION) __attribute__((deprecated("Go to dev.tapjoy.com for instructions on how to fix this warning")))

// Auction constants
// Price of winning auction bid
extern NSString *const TJ_AUCTION_CLEARING_PRICE TJC_DEPRECATION_WARNING(13.2.0);

// Auction data
extern NSString *const TJ_AUCTION_DATA TJC_DEPRECATION_WARNING(13.2.0);

// Type of auction
extern NSString *const TJ_AUCTION_TYPE TJC_DEPRECATION_WARNING(13.2.0);

// Auction id
extern NSString *const TJ_AUCTION_ID TJC_DEPRECATION_WARNING(13.2.0);

// Auction type values
extern const NSInteger TJ_AUCTION_TYPE_FIRST_PRICE TJC_DEPRECATION_WARNING(13.2.0);
extern const NSInteger TJ_AUCTION_TYPE_SECOND_PRICE TJC_DEPRECATION_WARNING(13.2.0);
