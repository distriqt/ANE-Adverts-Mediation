
## Android X 

> 
> AndroidX is a major improvement to the original Android Support Library, which is no longer maintained. androidx packages fully replace the Support Library by providing feature parity and new libraries.
>

As there will be no further updates to the Android Support libraries we are migrating all our extensions to AndroidX. Importantly Android Support libraries are not compatible with AndroidX so applications have to migrate all functionality from the support libraries to AndroidX together.

**This means you cannot use older extensions that rely on the Android Support libraries with the latest builds of our extensions and you must upgrade all of our extensions simultaneously.** 

Generally migrating is fairly simple. 

Simply use the table below to swap the extensions you currently have in your application.


| Android Support | Android X |
| --- | --- |
| `com.distriqt.androidsupport.V4` | `androidx.core` |
| `com.distriqt.androidsupport.AppCompatV7` | `androidx.appcompat` |
| `com.distriqt.androidsupport.CardViewV7` | `androidx.cardview` |
| `com.distriqt.androidsupport.CustomTabs` | `androidx.browser` |
| `com.distriqt.androidsupport.Design` | `com.google.android.material` |
| `com.distriqt.androidsupport.InstallReferrer` | `com.android.installreferrer` |
| `com.distriqt.androidsupport.RecyclerView` | `androidx.recyclerview` |


We have included all these extensions in the existing Android Support repository and will continue to use this repository to hold any common Google provided Android libraries that aren't dependent on the Google Play Services. 


**When migrating we also suggest you check the manifest additions and "Add the Extension" documentation. Some of the extensions will require changes to the manifest, where references to the Android Support libraries were being used. And there may be additional extensions required.**



