/**
 *        __       __               __ 
 *   ____/ /_ ____/ /______ _ ___  / /_
 *  / __  / / ___/ __/ ___/ / __ `/ __/
 * / /_/ / (__  ) / / /  / / /_/ / / 
 * \__,_/_/____/_/ /_/  /_/\__, /_/ 
 *                           / / 
 *                           \/ 
 * http://distriqt.com
 */
package
{
	import com.distriqt.extension.admob.applovin.AdMobAppLovin;
	import com.distriqt.extension.adverts.AdSize;
	import com.distriqt.extension.adverts.AdView;
	import com.distriqt.extension.adverts.AdViewParams;
	import com.distriqt.extension.adverts.AdvertPlatform;
	import com.distriqt.extension.adverts.Adverts;
	import com.distriqt.extension.adverts.builders.AdRequestBuilder;
	import com.distriqt.extension.adverts.builders.AdViewParamsBuilder;
	import com.distriqt.extension.adverts.events.AdViewEvent;
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
	 * Sample application for using the AdMob AppLovin Mediation Native Extension
	 */
	public class TestAppLovin extends Sprite
	{
		public static var admob_rewardedAdUnitID:String = "";
		public static var admob_accountId:String = "";
		
		//
		//	VARIABLES
		//
		
		private var _adUnitId	: String;
		private var _text		: TextField;
		
		
		//
		//	INITIALISATION
		//
		
		
		/**
		 * Class constructor
		 */
		public function TestAppLovin()
		{
			super();
			create();
			init();
		}
		
		
		private function create( ):void
		{
			stage.align = StageAlign.TOP_LEFT;
			stage.scaleMode = StageScaleMode.NO_SCALE;
			
			_text = new TextField();
			_text.defaultTextFormat = new TextFormat( "_typewriter", 18, 0x000000 );
			addChild( _text );

			stage.addEventListener( Event.RESIZE, stage_resizeHandler, false, 0, true );
			stage.addEventListener( MouseEvent.CLICK, stage_clickHandler, false, 0, true );
		}
		
		
		private function init( ):void
		{
			try
			{
				message( "Adverts Supported:       " + Adverts.isSupported );
				message( "Adverts Version:         " + Adverts.service.version );
				
				message( "AppLovin Supported:      " + AdMobAppLovin.isSupported );
				message( "AppLovin Version:        " + AdMobAppLovin.service.version );
				message( "AppLovin SDK Version:    " + AdMobAppLovin.service.nativeVersion );
				
				message( "ADMOB Supported:         " + Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ) );
				
				if (Adverts.isSupported)
				{
					if (Adverts.service.isPlatformSupported( AdvertPlatform.PLATFORM_ADMOB ))
					{
						message( "Initialising ADMOB" );
						Adverts.service.initialisePlatform( AdvertPlatform.PLATFORM_ADMOB, admob_accountId );
					}
					else
					{
						message( "No platform supported" );
					}
				}
				else
				{
					message( "Not supported..." );
				}
				
				
				// This is to show your app in the AppLovin dashboard
				// You don't need this once the app is shown in the dashboard
				AdMobAppLovin.service.initializeSdk();
				
				AdMobAppLovin.service.setHasUserConsent( true );
				AdMobAppLovin.service.setIsAgeRestrictedUser( false );
				
			}
			catch (e:Error)
			{
				message( "ERROR::"+e.message );
			}
		}
		
		
		//
		//	FUNCTIONALITY
		//
		
		private function message( str:String ):void
		{
			trace( str );
			_text.appendText(str+"\n");
		}
		
		
		//
		//	EVENT HANDLERS
		//
		
		private function stage_resizeHandler( event:Event ):void
		{
			_text.width  = stage.stageWidth;
			_text.height = stage.stageHeight - 100;
		}
		
		
		private var _stage:int = 0;
		private var _adView:RewardedVideoAd;
		private function stage_clickHandler( event:MouseEvent ):void
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
							
							_adView.load( admob_rewardedAdUnitID,
									new AdRequestBuilder()
//											.addTestDevice( "F1C0AFEFF151A60B62C089B377FFC555" )
											.build()
							);
							break;
						}
						
						case 1:
						{
							message( "show" );
							if (_adView.isLoaded())
							{
								_adView.addEventListener( RewardedVideoAdEvent.OPENED, openedHandler );
								_adView.addEventListener( RewardedVideoAdEvent.VIDEO_STARTED, videoStartedHandler );
								_adView.addEventListener( RewardedVideoAdEvent.LEFT_APPLICATION, leftApplicationHandler );
								_adView.addEventListener( RewardedVideoAdEvent.CLOSED, closedHandler );
								
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
							_adView.removeEventListener( RewardedVideoAdEvent.OPENED, openedHandler );
							_adView.removeEventListener( RewardedVideoAdEvent.VIDEO_STARTED, videoStartedHandler );
							_adView.removeEventListener( RewardedVideoAdEvent.LEFT_APPLICATION, leftApplicationHandler );
							_adView.removeEventListener( RewardedVideoAdEvent.CLOSED, closedHandler );
							
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
		
		
		
		private function openedHandler( event:RewardedVideoAdEvent ):void
		{
			// The rewarded video ad has been opened and is now visible to the user
			message( "openedHandler" );
		}
		
		private function videoStartedHandler( event:RewardedVideoAdEvent ):void
		{
			// Video playback has started
			message( "videoStartedHandler" );
		}
		
		private function leftApplicationHandler( event:RewardedVideoAdEvent ):void
		{
			// Control has left your application,
			// you can deactivate any none important parts of your application
			message( "leftApplicationHandler" );
		}
		
		private function closedHandler( event:RewardedVideoAdEvent ):void
		{
			// Control has returned to your application
			// you should reactivate any paused / stopped parts of your application.
			message( "closedHandler" );
		}
		
		
	}
}

