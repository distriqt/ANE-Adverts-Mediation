/**
 * This is a test application for the distriqt extension
 *
 * @author Michael Archbold & Shane Korin
 *
 */
package
{
	import com.distriqt.extension.admob.facebookaudience.AdMobFacebookAudience;
	import com.distriqt.extension.admob.facebookaudience.AdMobFacebookAudience;
	import com.distriqt.extension.adverts.AdvertPlatform;
	import com.distriqt.extension.adverts.AdvertisingIdInfo;
	import com.distriqt.extension.adverts.Adverts;
	import com.distriqt.extension.adverts.builders.AdRequestBuilder;
	import com.distriqt.extension.adverts.events.ConsentEvent;
	import com.distriqt.extension.adverts.events.FullScreenContentEvent;
	import com.distriqt.extension.adverts.events.RewardedVideoAdEvent;
	import com.distriqt.extension.adverts.rewarded.RewardedVideoAd;

	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;


	/**
	 * Sample application for using the AdMob FacebookAudience Mediation Native Extension
	 */
	public class TestFacebookAudience extends Sprite
	{

		public static var admob_rewardedAdUnitID:String = "";
		public static var admob_publisherId:String = "";
		public static var test_id:String = "";

		//
		//	VARIABLES
		//

		private var _text:TextField;


		//
		//	INITIALISATION
		//	

		/**
		 * Class constructor
		 */
		public function TestFacebookAudience()
		{
			super();
			create();
			init();
		}


		private function create():void
		{
			stage.align = StageAlign.TOP_LEFT;
			stage.scaleMode = StageScaleMode.NO_SCALE;

			_text = new TextField();
			_text.defaultTextFormat = new TextFormat( "_typewriter", 18 );
			addChild( _text );

			stage.addEventListener( Event.RESIZE, stage_resizeHandler, false, 0, true );
			stage.addEventListener( MouseEvent.CLICK, mouseClickHandler, false, 0, true );

			addEventListener( Event.ACTIVATE, activateHandler, false, 0, true );
			addEventListener( Event.DEACTIVATE, deactivateHandler, false, 0, true );
		}


		private function init():void
		{
			try
			{
				message( "Adverts Supported:          " + Adverts.isSupported );
				message( "Adverts Version:            " + Adverts.service.version );
				message( "Adverts Native Version:     " + Adverts.service.nativeVersion );
				message( "FacebookAudience Version:   " + AdMobFacebookAudience.service.nativeVersion );

				message( "ADMOB Supported:            " + Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ) );

				if (Adverts.isSupported)
				{
					if (Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ))
					{
						message( "Initialising ADMOB" );
						Adverts.service.setup( AdvertPlatform.PLATFORM_ADMOB );
						AdMobFacebookAudience.service.setAdvertiserTrackingEnabled( true );
						AdMobFacebookAudience.service.setDataProcessingOptions( [ "LDU" ] );
						Adverts.service.initialise();
					}
					else
					{
						message( "No platform supported" );
					}

					Adverts.service.consent.addEventListener( ConsentEvent.STATUS_UPDATED, statusUpdatedHandler );
					Adverts.service.consent.addEventListener( ConsentEvent.STATUS_ERROR, statusErrorHandler );

					Adverts.service.consent.getConsentStatus( admob_publisherId );


					function statusUpdatedHandler( event:ConsentEvent ):void
					{
						message( "statusUpdatedHandler(): " + event.status
										 + " inEea:" + event.inEeaOrUnknown );
					}

					function statusErrorHandler( event:ConsentEvent ):void
					{
						message( "statusErrorHandler(): " + event.error );
					}


					Adverts.service.getAdvertisingId(
							function ( info:AdvertisingIdInfo ):void
							{
								message( "Advertising ID: " + info.advertisingId );
								message( "isLimitAdTrackingEnabled : " + info.isLimitAdTrackingEnabled );
							}
					);


				}
				else
				{
					message( "Not supported..." );
				}


			}
			catch (e:Error)
			{
				message( "ERROR::" + e.message );
			}
		}


		//
		//	FUNCTIONALITY
		//

		private function message( str:String ):void
		{
			trace( str );
			_text.appendText( str + "\n" );
		}


		//
		//	EVENT HANDLERS
		//

		private function stage_resizeHandler( event:Event ):void
		{
			_text.y = 100;
			_text.width = stage.stageWidth;
			_text.height = stage.stageHeight - 200;
		}


		private var _stage:int = 0;
		private var _adView:RewardedVideoAd;

		private function mouseClickHandler( event:MouseEvent ):void
		{
			if (Adverts.isSupported && Adverts.service.rewardedVideoAds.isSupported)
			{
				try
				{
					switch (_stage)
					{
						case 0:
						{
							message( "load" );
							_adView = Adverts.service.rewardedVideoAds.createRewardedVideoAd();
							_adView.addEventListener( RewardedVideoAdEvent.LOADED, adverts_receivedAdHandler );
							_adView.addEventListener( RewardedVideoAdEvent.ERROR, adverts_errorHandler );
							_adView.setAdUnitId( admob_rewardedAdUnitID );
							_adView.load( new AdRequestBuilder()
												  //												  .addTestDevice( test_id )
												  .build()
							);
							break;
						}

						case 1:
						{
							message( "show" );
							if (_adView.isLoaded())
							{
								_adView.addEventListener( FullScreenContentEvent.SHOW, showHandler );
								_adView.addEventListener( FullScreenContentEvent.FAILED_TO_SHOW, failedToShowHandler );
								_adView.addEventListener( FullScreenContentEvent.DISMISSED, dismissedHandler );

								_adView.show();
							}
							else
							{
								message( "NOT LOADED" );
							}
							break;
						}

						case 2:
						{
							message( "destroy" );
							_adView.removeEventListener( FullScreenContentEvent.SHOW, showHandler );
							_adView.removeEventListener( FullScreenContentEvent.FAILED_TO_SHOW, failedToShowHandler );
							_adView.removeEventListener( FullScreenContentEvent.DISMISSED, dismissedHandler );

							_adView.removeEventListener( RewardedVideoAdEvent.LOADED, adverts_receivedAdHandler );
							_adView.removeEventListener( RewardedVideoAdEvent.ERROR, adverts_errorHandler );
							_adView.destroy();
							_adView = null;
							break;
						}

						default:
							_stage = 0;
							return;

					}
				}
				catch (e:Error)
				{
					message( "ERROR::" + e.message );
				}
				_stage++;
			}
		}


		private function activateHandler( event:Event ):void
		{
		}


		private function deactivateHandler( event:Event ):void
		{
		}


		//
		//	EXTENSION LISTENERS
		//

		private function adverts_receivedAdHandler( event:RewardedVideoAdEvent ):void
		{
			message( "adverts_receivedAdHandler" );
		}


		private function adverts_errorHandler( event:RewardedVideoAdEvent ):void
		{
			message( "adverts_errorHandler:: " + event.errorCode );
		}


		private function showHandler( event:FullScreenContentEvent ):void
		{
			// The rewarded video ad has been opened and is now visible to the user
			message( "showHandler" );
		}


		private function failedToShowHandler( event:FullScreenContentEvent ):void
		{
			message( "failedToShowHandler" );
		}


		private function dismissedHandler( event:FullScreenContentEvent ):void
		{
			// Control has returned to your application
			// you should reactivate any paused / stopped parts of your application.
			message( "dismissedHandler" );
		}


	}
}

