/**
 * @author 		Michael Archbold (https://github.com/marchbold)
 * @created		08/01/2016
 */
package com.distriqt.test.tapjoy
{
	import com.distriqt.extension.admob.tapjoy.TapJoy;

	import starling.display.Sprite;

	/**
	 */
	public class TapJoyTests extends Sprite
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

		public function TapJoyTests( logger:ILogger )
		{
			_l = logger;
			try
			{
				log( "TapJoy Supported:   " + TapJoy.isSupported );
				if (!TapJoy.isSupported) return;

				log( "TapJoy Version:     " + TapJoy.service.version );
				log( "TapJoy SDK Version: " + TapJoy.service.nativeVersion );

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
			TapJoy.instance.setSubjectToGDPR( true );
			TapJoy.instance.setUserConsent( true );
			TapJoy.instance.setUSPrivacy( "1YYY" );
		}


	}
}
