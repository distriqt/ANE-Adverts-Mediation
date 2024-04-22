class TapjoyConnectFlag
{
public:
    /**
     * Sets the service URL for the connect call.
     */
    static const char* SERVICE_URL;
    /**
     * Sets the URL for the placement request call.
     */
    static const char* PLACEMENT_URL;
    /**
     * Enables logging to the console.
     */
    static const char* ENABLE_LOGGING;
    /**
     * Sets the user ID for the connect call.
     */
    static const char* USER_ID;
#if defined(ANDROID)
    /**
     * @deprecated Deprecated since 13.2.0
     * Sets the app to use a different market/app store other than Google Play.  If not set, Google Play will be used.
     * Use the store name as the flag value.
     */
    static const char* STORE_NAME;
    /**
     * Disables the check for the advertising ID.
     */
    static const char* DISABLE_ADVERTISING_ID_CHECK;
    /**
     * Disables the collection of the advertising ID.
     */
    static const char* DISABLE_ADVERTISING_ID;
    /**
     * Persistent ids will make your analytics data more accurate; using this flag can cause inaccuracies in your analytics data. See https://dev.tapjoy.com for more information.
     */
    static const char* DISABLE_ANDROID_ID_AS_ANALYTICS_ID;

    /**
     * New in Android SDK 12.2.1, which defaults against fallback use of persistent identifiers for advertising. Allows fallback to using persistent identifiers when no Android Advertising ID exists,
     * such as when using an older device that does not support Google Play Services
     */
    static const char* ALLOW_LEGACY_ID_FALLBACK;

    /**
     * Turns off automatic session tracking.
     * Automatic session tracking is only effective for the devices &gt;= API level 14 (ICS).
     * To use session tracking for the devices under API level 14, you have two ways. Use one of ways in the application's main activity.:<br>
     *  - Tapjoy#onActivityStart(android.app.Activity), Tapjoy#onActivityStop(android.app.Activity)<br>
     *  - Tapjoy#startSession(), Tapjoy#endSession()<br>
     * Use "true" to disable automatic session tracking.
     */
    static const char* DISABLE_AUTOMATIC_SESSION_TRACKING;

    //--------------------------------------------------------------------------------
    // Use these values when using the STORE_NAME flag.
    //--------------------------------------------------------------------------------
    /**
     * @deprecated Deprecated since 13.2.0
     * Gfan store in China.<br>
     */
    static const char* STORE_GFAN;

    /**
     * @deprecated Deprecated since 13.2.0
     * T-store in Korea.<br>
     */
    static const char* STORE_SKT;
    
#else //iOS
    
    /**
     * Clears the Shared URL Cache.
     */
    static const char* SHARED_URL_CACHE;
    
    /**
     * Disables the default error dialogs
     */
    static const char* DISABLE_GENERIC_ERROR_ALERT;
    
    /**
     * Sets the Placement Response Timeout value.
     */
    static const char* PLACEMENT_TIMEOUT;
    
    /**
     * Disables the Vendor ID param.
     */
    static const char* DISABLE_VENDOR_ID;
#endif
    


};


const char* TapjoyConnectFlag::SERVICE_URL = "TJC_OPTION_SERVICE_URL";
const char* TapjoyConnectFlag::PLACEMENT_URL = "TJC_OPTION_PLACEMENT_SERVICE_URL";
const char* TapjoyConnectFlag::ENABLE_LOGGING = "TJC_OPTION_ENABLE_LOGGING";
const char* TapjoyConnectFlag::USER_ID = "TJC_OPTION_USER_ID";

#if defined(ANDROID)
const char* TapjoyConnectFlag::STORE_NAME = "TJC_OPTION_STORE_NAME";
const char* TapjoyConnectFlag::DISABLE_ADVERTISING_ID_CHECK = "TJC_OPTION_DISABLE_ADVERTISING_ID_CHECK";
const char* TapjoyConnectFlag::DISABLE_ADVERTISING_ID = "TJC_OPTION_DISABLE_ADVERTISING_ID";
const char* TapjoyConnectFlag::DISABLE_ANDROID_ID_AS_ANALYTICS_ID = "TJC_OPTION_DISABLE_ANDROID_ID_AS_ANALYTICS_ID";
const char* TapjoyConnectFlag::ALLOW_LEGACY_ID_FALLBACK = "TJC_OPTION_ALLOW_LEGACY_ID_FALLBACK";
const char* TapjoyConnectFlag::DISABLE_AUTOMATIC_SESSION_TRACKING = "TJC_OPTION_DISABLE_AUTOMATIC_SESSION_TRACKING";
const char* TapjoyConnectFlag::STORE_GFAN = "gfan";
const char* TapjoyConnectFlag::STORE_SKT = "skt";

#else //iOS
const char* TapjoyConnectFlag::SHARED_URL_CACHE = "TJC_OPTION_CLEAR_SHARED_URL_CACHE";
const char* TapjoyConnectFlag::DISABLE_GENERIC_ERROR_ALERT = "TJC_OPTION_DISABLE_GENERIC_ERROR_ALERT";
const char* TapjoyConnectFlag::PLACEMENT_TIMEOUT = "TJC_OPTION_PLACEMENT_TIMEOUT";
const char* TapjoyConnectFlag::DISABLE_VENDOR_ID = "TJC_OPTION_DISABLE_VENDOR_ID";


#endif

