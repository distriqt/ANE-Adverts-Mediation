//
//  TJPrivacyPolicy.h
//  Tapjoy
//
//  Copyright © 2020 Tapjoy. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <Tapjoy/TJStatus.h>
#define TJC_DEPRECATION_WARNING(VERSION) __attribute__((deprecated("Go to dev.tapjoy.com for instructions on how to fix this warning")))
NS_ASSUME_NONNULL_BEGIN

@interface TJPrivacyPolicy : NSObject

/**
 * This is used for sending User's consent to behavioral advertising such as in the context of GDPR
 * The consent value can be "0" (User has not provided consent), "1" (User has provided consent) or
 * a daisybit string as suggested in IAB's Transparency and Consent Framework
 *
 * userConsent = "0" (User has not provided consent), "1" (User has provided consent) or a daisybit string as suggested in IAB's Transparency and Consent Framework
 */
@property (assign, nonatomic) TJStatus userConsentStatus;
/**
 * In the US, the Children’s Online Privacy Protection Act (COPPA) imposes certain requirements on operators of online services that (a)
 * have actual knowledge that the connected user is a child under 13 years of age, or (b) operate services (including apps) that are
 * directed to children under 13.
 *
 * Similarly, the GDPR imposes certain requirements in connection with data subjects who are below the applicable local minimum age for
 * online consent (ranging from 13 to 16, as established by each member state).
 *
 * For applications that are not directed towards children under 13 years of age, but still have a minority share of users known to be
 * under the applicable minimum age, utilize this method to access Tapjoy’s monetization capability. This method will set
 * ad_tracking_enabled to false for Tapjoy which only shows the user contextual ads. No ad tracking will be done on this user.
 *
 * belowConsentAge = YES if the user is affected by COPPA, NO if they are not.
 */
@property (assign, nonatomic) TJStatus belowConsentAgeStatus;
/**
 * This can be used by the integrating App to indicate if the user falls in any of the GDPR applicable countries
 * (European Economic Area). The value should be set to YES when User (Subject) is applicable to GDPR regulations
 * and NO when User is not applicable to GDPR regulations. In the absence of this call, Tapjoy server makes the
 * determination of GDPR applicability.
 *
 * subjectToGDPR = YES if the user is affected by GDPR, NO if they are not.
 */
@property (assign, nonatomic) TJStatus subjectToGDPRStatus;
/**
 * This is used for sending US Privacy value to behavioral advertising such as in the context of GDPR
 * The value can be in IAB's US Privacy String Format consists of specification version to encode the string in number, explicit notice or opportunity to opt out in enum, opt-out sale in enum, LSPA covered transaction in enum .
 * eg. "1YNN" where 1 is char in string for the version, Y = YES, N = No, - = Not Applicable
 * See: IAB suggested US Privacy String Format : https://github.com/InteractiveAdvertisingBureau/USPrivacy/blob/master/CCPA/Version%201.0/US%20Privacy%20String.md#us-privacy-string-format
 *
 * USPrivacy = The us privacy value string
 */
@property (strong, nonatomic, nullable) NSString *USPrivacy;


/**
* Deprecated since 13.1.0
* This is used for sending User's consent to behavioral advertising such as in the context of GDPR
* The consent value can be "0" (User has not provided consent), "1" (User has provided consent) or
* a daisybit string as suggested in IAB's Transparency and Consent Framework
*
* @param value "0" (User has not provided consent), "1" (User has provided consent) or a daisybit string as suggested in IAB's Transparency and Consent Framework
**/
- (void)setUserConsent:(NSString *)value TJC_DEPRECATION_WARNING(13.1.0);

/**
* Deprecated since 13.1.0
* This can be used by the integrating App to indicate if the user falls in any of the GDPR applicable countries
* (European Economic Area). The value should be set to YES when User (Subject) is applicable to GDPR regulations
* and NO when User is not applicable to GDPR regulations. In the absence of this call, Tapjoy server makes the
* determination of GDPR applicability.
*
* @param gdprApplicability YES if the user is affected by GDPR, NO if they are not.
* userConsent = "0" (User has not provided consent), "1" (User has provided consent) or a daisybit string as suggested in IAB's Transparency and Consent Framework
*/
- (void)setSubjectToGDPR:(BOOL)gdprApplicability TJC_DEPRECATION_WARNING(13.1.0);

/**
* Deprecated since 13.1.0
* In the US, the Children’s Online Privacy Protection Act (COPPA) imposes certain requirements on operators of online services that (a)
* have actual knowledge that the connected user is a child under 13 years of age, or (b) operate services (including apps) that are
@@ -42,19 +29,29 @@ NS_ASSUME_NONNULL_BEGIN
* under the applicable minimum age, utilize this method to access Tapjoy’s monetization capability. This method will set
* ad_tracking_enabled to false for Tapjoy which only shows the user contextual ads. No ad tracking will be done on this user.
*
* @param isBelowConsentAge YES if the user is affected by COPPA, NO if they are not.
* belowConsentAge = YES if the user is affected by COPPA, NO if they are not.
*/
- (void)setBelowConsentAge:(BOOL)isBelowConsentAge TJC_DEPRECATION_WARNING(13.1.0);

+ (instancetype)sharedInstance;

@end;

NS_ASSUME_NONNULL_END
