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
package com.distriqt.test.tapjoy
{
	import com.distriqt.extension.admob.tapjoy.TapJoy;
	
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
	public class TapJoyTests extends Sprite
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
		
		public function TapJoyTests( logger:ILogger )
		{
			_l = logger;
			try
			{
				log( "TapJoy Supported: " + TapJoy.isSupported );
				if (TapJoy.isSupported)
				{
					log( "TapJoy Version:   " + TapJoy.service.version );
					log( "TapJoy SDK Version:   " + TapJoy.service.nativeVersion );
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
			TapJoy.instance.setUserConsent( true );
		}
		
		
	}
}
