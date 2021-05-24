/**
 *        __       __               __ 
 *   ____/ /_ ____/ /______ _ ___  / /_
 *  / __  / / ___/ __/ ___/ / __ `/ __/
 * / /_/ / (__  ) / / /  / / /_/ / / 
 * \__,_/_/____/_/ /_/  /_/\__, /_/ 
 *                           / / 
 *                           \/ 
 * http://distriqt.com
 *
 * @author 		"Michael Archbold (ma&#64;distriqt.com)"
 * @created		08/01/2016
 * @copyright	http://distriqt.com/copyright/license.txt
 */
package com.distriqt.test.unityads
{
	import com.distriqt.extension.admob.unityads.AdMobUnityAds;
	import com.distriqt.extension.adverts.AdvertPlatform;
	import com.distriqt.extension.adverts.AdvertisingIdInfo;
	import com.distriqt.extension.adverts.Adverts;
	import com.distriqt.extension.adverts.builders.AdRequestBuilder;
	import com.distriqt.extension.adverts.events.ConsentEvent;
	import com.distriqt.extension.adverts.events.FullScreenContentEvent;
	import com.distriqt.extension.adverts.events.RewardedVideoAdEvent;
	import com.distriqt.extension.adverts.rewarded.RewardedVideoAd;
	
	import flash.display.Bitmap;
	import flash.filesystem.File;
	import flash.geom.Rectangle;
	import flash.net.URLRequest;
	import flash.net.navigateToURL;
	import flash.utils.setTimeout;
	
	import starling.core.Starling;
	
	import starling.display.Image;
	import starling.display.Sprite;
	
	/**	
	 */
	public class UnityAdsTests extends Sprite
	{
		public static const TAG : String = "";
		
		private var _l : ILogger;
		
		private function log( log:String ):void
		{
			_l.log( TAG, log );
		}
		
		
		////////////////////////////////////////////////////////
		//	FUNCTIONALITY
		//
		
		public function UnityAdsTests( logger:ILogger )
		{
			_l = logger;
		}
		
		
		////////////////////////////////////////////////////////
		//  
		//
		
		
		public function init():void
		{
			try
			{
				try
				{
					log( "Adverts Supported:          " + Adverts.isSupported );
					log( "Adverts Version:            " + Adverts.service.version );
					log( "Adverts Native Version:     " + Adverts.service.nativeVersion );
					log( "UnityAds Version:           " + AdMobUnityAds.service.version );
					log( "UnityAds Native Version:    " + AdMobUnityAds.service.nativeVersion );
					
					log( "ADMOB Supported:            " + Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ) );
					
					if (Adverts.isSupported)
					{
						if (Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ))
						{
							log( "Initialising ADMOB" );
							Adverts.service.setup( AdvertPlatform.PLATFORM_ADMOB );
							Adverts.service.initialise();
						}
						else
						{
							log( "No platform supported" );
						}
						
						Adverts.service.consent.addEventListener( ConsentEvent.STATUS_UPDATED, statusUpdatedHandler );
						Adverts.service.consent.addEventListener( ConsentEvent.STATUS_ERROR, statusErrorHandler );
						
						Adverts.service.consent.getConsentStatus( Config.admob_publisherId );
						
						
						function statusUpdatedHandler( event:ConsentEvent ):void
						{
							log( "statusUpdatedHandler(): " + event.status
										 + " inEea:" + event.inEeaOrUnknown );
						}
						
						function statusErrorHandler( event:ConsentEvent ):void
						{
							log( "statusErrorHandler(): " + event.error );
						}
						
						
						Adverts.service.getAdvertisingId(
								function( info:AdvertisingIdInfo ):void
								{
									log( "Advertising ID: " + info.advertisingId );
									log( "isLimitAdTrackingEnabled : " + info.isLimitAdTrackingEnabled );
								}
						);
						
					}
					else
					{
						log( "Not supported..." );
					}
					
					
					
				}
				catch (e:Error)
				{
					log( "ERROR::"+e.message );
				}
			}
			catch (e:Error)
			{
				trace( e );
			}
		}
		
		
		private var _adView:RewardedVideoAd;
		
		public function load():void
		{
			log( "load" );
			if (Adverts.isSupported && Adverts.service.rewardedVideoAds.isSupported)
			{
				try
				{
					_adView = Adverts.service.rewardedVideoAds.createRewardedVideoAd();
					_adView.addEventListener( RewardedVideoAdEvent.LOADED, loadedHandler );
					_adView.addEventListener( RewardedVideoAdEvent.ERROR, errorHandler );
					_adView.setAdUnitId( Config.admob_rewardedAdUnitID );
					_adView.load( new AdRequestBuilder()
//										  .addTestDevice( Config.test_id )
										  .build()
					);
				}
				catch (e:Error)
				{
				}
			}
		}
		
		public function show():void
		{
			log( "show" );
			if (Adverts.isSupported && Adverts.service.rewardedVideoAds.isSupported)
			{
				try
				{
					if (_adView.isLoaded())
					{
						_adView.addEventListener( FullScreenContentEvent.SHOW, showHandler );
						_adView.addEventListener( FullScreenContentEvent.DISMISSED, dismissedHandler );
						
						_adView.show();
					}
					else
					{
						log( "NOT LOADED" );
					}
				}
				catch (e:Error)
				{
				}
			}
		}
		
		
		public function destroy():void
		{
			log( "destroy" );
			if (_adView != null)
			{
				_adView.removeEventListener( FullScreenContentEvent.SHOW, showHandler );
				_adView.removeEventListener( FullScreenContentEvent.DISMISSED, dismissedHandler );
				_adView.removeEventListener( RewardedVideoAdEvent.LOADED, loadedHandler );
				_adView.removeEventListener( RewardedVideoAdEvent.ERROR, errorHandler );
				_adView.destroy();
				_adView = null;
			}
		}
		
		
		
		
		private function loadedHandler( event:RewardedVideoAdEvent ):void
		{
			log( "loadedHandler" );
		}
		
		private function errorHandler( event:RewardedVideoAdEvent ):void
		{
			log( "errorHandler:: " + event.errorCode );
		}
		
		private function showHandler( event:FullScreenContentEvent ):void
		{
			// The rewarded video ad has been shown and is now visible to the user
			log( "showHandler" );
		}
		
		private function dismissedHandler( event:FullScreenContentEvent ):void
		{
			// Control has returned to your application
			// you should reactivate any paused / stopped parts of your application.
			log( "dismissedHandler" );
		}
		
		
		
		//
		//	OPTIONAL
		//
		
		
		public function setConsent():void
		{
			log( "setConsent" );
			AdMobUnityAds.instance.setConsent(true);
		}
		
		
	}
	
	
}
