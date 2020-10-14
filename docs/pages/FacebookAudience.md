
This guide is intended for publishers who want to use the Google Mobile Ads SDK to load and display ads from Facebook Audience Network via mediation. 



## Step 1: Set up Facebook Audience Network 

The Google documentation contains a very detailed guide as to the process to setup your properties and Facebook account to display adverts.

Make sure you follow this guide closely.

- Android: https://developers.google.com/admob/android/mediation/facebook#step_1_set_up_facebook_audience_network
- iOS: https://developers.google.com/admob/ios/mediation/facebook#step_1_set_up_facebook_audience_network


## Step 2: Configure mediation settings for your AdMob ad unit

You need to add Facebook to the mediation configuration for your ad unit.

- Android: https://developers.google.com/admob/android/mediation/facebook#step_2_configure_mediation_settings_for_your_ad_unit
- iOS: https://developers.google.com/admob/ios/mediation/facebook#step_2_configure_mediation_settings_for_your_ad_unit


## Step 3: Import the Facebook Audience Network SDK and adapter ANE

The `com.distriqt.admob.FacebookAudience` ANE includes the Facebook Audience SDK and the AdMob Facebook mediation adapter. This is everything you need to get Facebook mediation working in your application.

To add the ANE download it from the repository and add it to your application:

- [com.distriqt.admob.FacebookAudience.ane](https://github.com/distriqt/ANE-Adverts-Mediation/raw/master/lib/facebookaudience/com.distriqt.admob.FacebookAudience.ane)

Add the extension id to your application descriptor:

```xml
<extensions>
    <!-- OTHER EXTENSIONS -->

    <extensionID>com.distriqt.admob.FacebookAudience</extensionID>
</extensions>
```

More information on adding ANEs in this [tutorial](https://airnativeextensions.github.io/tutorials/getting-started)




## Step 4: Additional code required

There is no additional code required just a few additional configuration options and files that need to be packaged with your application.


### Android

Add the `audience_network.dex` file to the root of your application package. (This file is located in the repository, this must be the same version as the extension).

Add the following to your manifest additions inside the `application` tag. You must replace `YOUR_APPLICATION_PACKAGE` with your AIR application's Java package name, something like `air.com.distriqt.test`. Generally this is your AIR application id prefixed by `air.` unless you have specified no air flair in your build options.


```xml
<activity
    android:name="com.facebook.ads.AudienceNetworkActivity"
    android:configChanges="keyboardHidden|orientation|screenSize"
    android:exported="false"
    android:theme="@android:style/Theme.Translucent.NoTitleBar" />

<provider
    android:name="com.facebook.ads.AudienceNetworkContentProvider"
    android:authorities="YOUR_APPLICATION_PACKAGE.AudienceNetworkContentProvider"
    android:exported="false" />

<activity
    android:name="com.facebook.ads.internal.ipc.RemoteANActivity"
    android:configChanges="keyboardHidden|orientation|screenSize"
    android:exported="false"
    android:process=":adnw"
    android:theme="@android:style/Theme.Translucent.NoTitleBar" />

<service
    android:name="com.facebook.ads.internal.ipc.AdsProcessPriorityService"
    android:exported="false" />
<service
    android:name="com.facebook.ads.internal.ipc.AdsMessengerService"
    android:exported="false"
    android:process=":adnw" />
```


### iOS


Add the `Frameworks` folder to your application package, ensuring the dynamic `FBAudienceNetwork.framework` is included along with the swift libraries (`dylib` files).

**You will need to resign your application following the guide below otherwise your build will likely fail signing validation.**



## Step 5: Test your implementation 

When testing always make sure you are adding your test device id to the request to ensuring AdMob do not block your account for policy violations:

```as3
new AdRequestBuilder()
    .addTestDevice( "XXXXXXXXXXXXXXXXXX" )
    .build()
```

See the Adverts docs for more details.



### Facebook Testing 

You will need to enable testing in your Facebook account, by adding your test device and enabling an test advert type to serve the device.

See the [Testing Audience Network Implementation guide](https://developers.facebook.com/docs/audience-network/testing) for detailed instructions on how to enable Facebook test ads.



### Forcing Mediation Network

The easiest way we have found to force a mediation network during testing is to disable automatic optimisations and set the eCPM manually. 

Doing this you can give the mediation network you are wanting to test a high eCPM value ( eg $1000) and all others (including AdMob) a very low eCPM (eg $0.01).







# Signing your iOS application

With AIR 27 Adobe partially added the ability to use dynamic frameworks in your iOS application, which works fine with frameworks you control however still has issues with third party frameworks.

Everything will work up to a point, however AIR will incorrectly sign your IPA and it will fail AppStore submission with an error from the Application Loader tool and installing development builds with a signature validation error.

**Please vote to resolve this issue here: [https://tracker.adobe.com/#/view/AIR-4198407](https://tracker.adobe.com/#/view/AIR-4198407)**



To get around this, before you upload or install your application you will need to run a script to resign your IPA. 
This script is available in the repository alongside the ANE in the `scripts` directory.

>
> **This script will only work on a macOS machine with Xcode installed and your certificate installed in Keychain**
>

Copy this script to a directory in your development environment.

Firstly edit the script to change the details of the IPA, provisioning profile and signing identity for your application. These details are located at the top of the script.


```
#####################################
## CONFIG

# You need to set the values below for your application
# We suggest they are full paths to the files. 

# The path to the ipa generated from your AIR application packaging
IPA="/path/to/yourApp.ipa"

# The distribution provisioning profile for your application
PROVISIONING_PROFILE="/path/to/profile.mobileprovision"

# The name of the signing identity. You get this by running the following in a terminal 
# and selecting the name of your distribution certificate:
# 
# security find-identity -v -p codesigning
SIGNING_IDENTITY="iPhone Distribution: XXXXXXXXX (XXXXX)"
```


Now open a Terminal at the script location. *You will need to run the script from this directory.*

```
./resign
```

This should output a few informational items to the console and then once complete you should have a new IPA file in the directory named: `yourApp_resigned.ipa`. If there were any errors or warnings displayed, make sure the information above is all correct.

This resigned IPA is the file you should use.












