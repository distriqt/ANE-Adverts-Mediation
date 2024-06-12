/**
 *        __       __               __
 *   ____/ /_ ____/ /______ _ ___  / /_
 *  / __  / / ___/ __/ ___/ / __ `/ __/
 * / /_/ / (__  ) / / /  / / /_/ / /
 * \__,_/_/____/_/ /_/  /_/\__, /_/
 *                           / /
 *                           \/
 * https://distriqt.com
 *
 * @author 		Michael Archbold (https://github.com/marchbold)
 * @created		08/01/2016
 * @copyright	https://distriqt.com/copyright/license.txt
 */
package com.distriqt.test.applovin
{
	import com.distriqt.extension.admob.applovin.AdMobAppLovin;
	import com.distriqt.extension.adverts.AdvertPlatform;
	import com.distriqt.extension.adverts.Adverts;
	import com.distriqt.extension.adverts.RequestConfiguration;
	import com.distriqt.extension.adverts.builders.AdRequestBuilder;
	import com.distriqt.extension.adverts.events.AdInspectorEvent;
	import com.distriqt.extension.adverts.events.ConsentEvent;
	import com.distriqt.extension.adverts.events.FullScreenContentEvent;
	import com.distriqt.extension.adverts.events.RewardedVideoAdEvent;
	import com.distriqt.extension.adverts.rewarded.RewardedVideoAd;
	import com.distriqt.extension.idfa.IDFA;
	import com.distriqt.extension.idfa.TrackingAuthorisationStatus;
	import com.distriqt.extension.idfa.events.IDFAEvent;

	import starling.display.Sprite;

	/**
	 */
	public class AppLovinTests extends Sprite
	{
		public static const TAG:String = "";

		private var _l:ILogger;

		private function log( log:String ):void
		{
			_l.log( TAG, log );
		}


		////////////////////////////////////////////////////////
		//	FUNCTIONALITY
		//

		public function AppLovinTests( logger:ILogger )
		{
			_l = logger;

			IDFA.service.addEventListener( IDFAEvent.COMPLETE, idfaCompleteHandler );

		}

		public function getIDFA():void
		{
			log( "getIDFA" );


			IDFA.service.requestAuthorisation(
					function ( status:String ):void
					{
						log( "status = " + status );
						if (status == TrackingAuthorisationStatus.AUTHORISED)
						{
							IDFA.service.getIDFA();
						}
					}
			);
		}

		private function idfaCompleteHandler( event:IDFAEvent ):void
		{
			Config.test_id = event.identifier;
			log( "identifier: " + event.identifier );
			log( "isLimitAdTrackingEnabled: " + event.isLimitAdTrackingEnabled );
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
					log( "AppLovin Version:           " + AdMobAppLovin.service.version );
					log( "AppLovin Native Version:    " + AdMobAppLovin.service.nativeVersion );

					log( "ADMOB Supported:            " + Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ) );

					if (Adverts.isSupported)
					{
						if (Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ))
						{
							log( "Initialising ADMOB" );
							Adverts.service.setup( AdvertPlatform.PLATFORM_ADMOB );

							if (Config.test_id != "")
							{
								var reqConfig:RequestConfiguration = Adverts.service.getRequestConfiguration();
								reqConfig.setTestDeviceIds([ Config.test_id ]);
								Adverts.service.setRequestConfiguration( reqConfig );
							}

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


					}
					else
					{
						log( "Not supported..." );
					}


				}
				catch (e:Error)
				{
					log( "ERROR::" + e.message );
				}
			}
			catch (e:Error)
			{
				trace( e );
			}
		}


		public function openAdInspector():void
		{
			if (Adverts.isSupported)
			{
				Adverts.service.addEventListener( AdInspectorEvent.CLOSED, adInspector_closedHandler );
				Adverts.service.openAdInspector();
			}
		}


		private function adInspector_closedHandler( event:AdInspectorEvent ):void
		{
			Adverts.service.removeEventListener( AdInspectorEvent.CLOSED, adInspector_closedHandler );
			log( "adInspector_closedHandler( [" + event.errorCode + ", " + event.errorMessage + "]" );
		}


		private var _adView:RewardedVideoAd;

		public function load():void
		{
			log( "load" );
			if (Adverts.isSupported && Adverts.service.rewardedVideoAds.isSupported)
			{
				try
				{
					var builder:AdRequestBuilder = new AdRequestBuilder();
					if (Config.test_id != "") builder.addTestDevice( Config.test_id );

					_adView = Adverts.service.rewardedVideoAds.createRewardedVideoAd();
					_adView.addEventListener( RewardedVideoAdEvent.LOADED, loadedHandler );
					_adView.addEventListener( RewardedVideoAdEvent.ERROR, errorHandler );
					_adView.setAdUnitId( Config.admob_rewardedAdUnitID );
					_adView.load( builder.build() );
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
			log( "errorHandler:: " + event.errorCode + ":" + event.errorMessage );
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


		public function initializeSdk():void
		{
			log( "initializeSdk" );
			AdMobAppLovin.service.initializeSdk( "" );
		}


	}


}
