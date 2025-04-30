/**
 * @author 		Michael Archbold (https://github.com/marchbold)
 * @created		08/01/2016
 */
package com.distriqt.test.adcolony
{
	import com.distriqt.extension.admob.adcolony.AdColony;
	import com.distriqt.extension.admob.adcolony.AdColonyAppOptions;
	
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
	public class AdColonyTests extends Sprite
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
		
		public function AdColonyTests( logger:ILogger )
		{
			_l = logger;
			try
			{
				log( "AdColony Supported: " + AdColony.isSupported );
				if (AdColony.isSupported)
				{
					log( "AdColony Version:   " + AdColony.service.version );
					log( "AdColony Native Version:   " + AdColony.service.nativeVersion );
					
					AdColony.instance.getAppOptions()
							.setPrivacyFrameworkRequired( AdColonyAppOptions.GDPR, true )
							.setPrivacyConsentString( AdColonyAppOptions.GDPR, "1" )
					
				}
				
			}
			catch (e:Error)
			{
				trace( e );
			}
		}
		
		
		////////////////////////////////////////////////////////
		//  
		//
		
		public function test():void 
		{
			
		}
		
		
	}
}
