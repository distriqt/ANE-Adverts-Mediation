

This guide is intended for publishers who want to use the Google Mobile Ads SDK to load and display ads from ironSource through mediation.


## Step 1: Set up ironSource

The Google documentation contains a very detailed guide as to the process to setup your properties and IronSource account to display adverts:

Make sure you follow this guide closely.

- Android: https://developers.google.com/admob/android/mediation/ironsource#step_1_set_up_ironsource
- iOS: https://developers.google.com/admob/ios/mediation/ironsource#step_1_set_up_ironsource



## Step 2: Configure mediation settings for your AdMob ad unit

You need to add ironSource to the mediation configuration for your ad unit:

- Android: https://developers.google.com/admob/android/mediation/ironsource#step_2_configure_mediation_settings_for_your_ad_unit
- iOS: https://developers.google.com/admob/ios/mediation/ironsource#step_2_configure_mediation_settings_for_your_ad_unit



## Step 3: Import the ironSource SDK and adapter ANE


The `com.distriqt.admob.IronSource` ANE includes the IronSource SDK and the AdMob IronSource mediation adapter. This is everything you need to get IronSource mediation working in your application.

To add the ANE download it from the repository and add it to your application:

- [com.distriqt.admob.IronSource.ane](https://github.com/distriqt/ANE-Adverts-Mediation/raw/master/lib/ironsource/com.distriqt.admob.IronSource.ane)

Add the extension id to your application descriptor:

```xml
<extensions>
    <!-- OTHER EXTENSIONS -->

    <extensionID>com.distriqt.admob.IronSource</extensionID>
</extensions>
```

More information on adding ANEs in this [tutorial](https://airnativeextensions.github.io/tutorials/getting-started)


## Step 4: Additional code required

You should call `IronSource.init();` in your code before you intend to display ads. This ensures the internal sdk is initialised correctly.
 

### Android

Add the following to your manifest additions inside the `application` tag:


```xml
<!-- IRONSOURCE -->
<activity
    android:name="com.ironsource.sdk.controller.ControllerActivity"
    android:configChanges="orientation|screenSize"
    android:hardwareAccelerated="true" />
<activity
    android:name="com.ironsource.sdk.controller.InterstitialActivity"
    android:configChanges="orientation|screenSize"
    android:hardwareAccelerated="true"
    android:theme="@android:style/Theme.Translucent" />
<activity
    android:name="com.ironsource.sdk.controller.OpenUrlActivity"
    android:configChanges="orientation|screenSize"
    android:hardwareAccelerated="true"
    android:theme="@android:style/Theme.Translucent" />
```


### iOS

No specific additions required here.



## Step 5: Test your implementation

You should run the IronSource `validateIntegration()` function to ensure the extension and manifest additions have been added correctly.


```as3
IronSource.instance.validateIntegration();
```

This will output information to the [native device log](https://airnativeextensions.github.io/tutorials/device-logs).



You can then follow the Google guides to add a test device to receive test ads:

- Android: https://developers.google.com/admob/android/mediation/ironsource#step_5_test_your_implementation
- iOS: https://developers.google.com/admob/ios/mediation/ironsource#step_5_test_your_implementation




## Optional Steps

### EU consent and GDPR

Under the Google EU User Consent Policy, you must ensure that certain disclosures are given to, and consents obtained from, users in the European Economic Area (EEA) regarding the use of device identifiers and personal data. This policy reflects the requirements of the EU ePrivacy Directive and the General Data Protection Regulation (GDPR). When seeking consent, you must identify each ad network in your mediation chain that may collect, receive, or use personal data and provide information about each network's use. Google currently is unable to pass the user's consent choice to such networks automatically.

The code below shows you how to enable or disable personalized ads for ironSource.


```as3
IronSource.instance.setConsent( true ); 
```

>
> If you choose to call this method, it is recommended that you do so prior to requesting ads via the Adverts extension.
>
