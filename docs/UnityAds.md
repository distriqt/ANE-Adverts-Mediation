
This guide is intended for publishers who want to use the Google Mobile Ads SDK to load and display ads from Unity Ads via mediation. 



## Step 1: Set up Unity ads

The Google documentation contains a very detailed guide as to the process to setup your properties and Unity Ads account to display adverts.

Make sure you follow this guide closely.

https://developers.google.com/admob/android/mediation/unity#step_1_set_up_unity_ads




## Step 2: Configure mediation settings for your AdMob ad unit

You need to add Unity Ads to the mediation configuration for your ad unit.

- Android: https://developers.google.com/admob/android/mediation/unity#step_2_configure_mediation_settings_for_your_ad_unit
- iOS: https://developers.google.com/admob/ios/mediation/unity#step_2_configure_mediation_settings_for_your_ad_unit





## Step 3: Import the Unity Ads SDK and adapter ANE

The `com.distriqt.admob.UnityAds` ANE includes the Unity Ads SDK and the AdMob Unity Ads mediation adapter. This is everything you need to get Unity Ads mediation working in your application.

To add the ANE download it from the repository and add it to your application:

- [com.distriqt.admob.UnityAds.ane](https://github.com/distriqt/ANE-Adverts-Mediation/raw/master/lib/unityads/com.distriqt.admob.UnityAds.ane)

Add the extension id to your application descriptor:

```xml
<extensions>
    <!-- OTHER EXTENSIONS -->

    <extensionID>com.distriqt.admob.UnityAds</extensionID>
</extensions>
```

More information on adding ANEs in this [tutorial](https://airnativeextensions.github.io/tutorials/getting-started)




## Step 4: Additional code required

There is no additional code required just a few additional configuration options.


### Android

Add the following to your manifest additions inside the `application` tag. You must replace `YOUR_APPLICATION_PACKAGE` with your AIR application's Java package name, something like `air.com.distriqt.test`. Generally this is your AIR application id prefixed by `air.` unless you have specified no air flair in your build options.


```xml
<!-- UNITY ADS -->
<activity
    android:name="com.unity3d.services.ads.adunit.AdUnitActivity"
    android:configChanges="fontScale|keyboard|keyboardHidden|locale|mnc|mcc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode|touchscreen"
    android:hardwareAccelerated="true"
    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" />
<activity
    android:name="com.unity3d.services.ads.adunit.AdUnitTransparentActivity"
    android:configChanges="fontScale|keyboard|keyboardHidden|locale|mnc|mcc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode|touchscreen"
    android:hardwareAccelerated="true"
    android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" />
<activity
    android:name="com.unity3d.services.ads.adunit.AdUnitTransparentSoftwareActivity"
    android:configChanges="fontScale|keyboard|keyboardHidden|locale|mnc|mcc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode|touchscreen"
    android:hardwareAccelerated="false"
    android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" />
<activity
    android:name="com.unity3d.services.ads.adunit.AdUnitSoftwareActivity"
    android:configChanges="fontScale|keyboard|keyboardHidden|locale|mnc|mcc|navigation|orientation|screenLayout|screenSize|smallestScreenSize|uiMode|touchscreen"
    android:hardwareAccelerated="false"
    android:theme="@android:style/Theme.NoTitleBar.Fullscreen" />
```


### iOS

No additional configuration required.




## Step 5: Test your implementation 

When testing always make sure you are adding your test device id to the request to ensuring AdMob do not block your account for policy violations:

```as3
new AdRequestBuilder()
    .addTestDevice( "XXXXXXXXXXXXXXXXXX" )
    .build()
```

See the Adverts docs for more details.




## Optional Steps

### EU consent and GDPR

Under the Google EU User Consent Policy, you must ensure that certain disclosures are given to, and consents obtained from, users in the European Economic Area (EEA) regarding the use of device identifiers and personal data. This policy reflects the requirements of the EU ePrivacy Directive and the General Data Protection Regulation (GDPR). When seeking consent, you must identify each ad network in your mediation chain that may collect, receive, or use personal data and provide information about each network's use. Google currently is unable to pass the user's consent choice to such networks automatically.

Follow the instructions below to enable or disable personalized ads for Unity Ads.

Unity Ads provides a GDPR Compliance guide that describes both automatic and manual solutions for user consent.

The following sample code shows how to pass consent information to the Unity Ads SDK manually. Should you choose to pass consent information to the Unity Ads SDK manually, it is recommended that this code is called prior to requesting ads via the Google Mobile Ads SDK.


```as3
AdMobUnityAds.instance.setConsent(true);
```

