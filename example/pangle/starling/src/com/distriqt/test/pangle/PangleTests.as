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
 * @created		14/10/2022
 * @copyright	https://distriqt.com/copyright/license.txt
 */
package com.distriqt.test.pangle
{
	import com.distriqt.extension.admob.pangle.AdMobPangle;
	import com.distriqt.extension.adverts.AdvertPlatform;
	import com.distriqt.extension.adverts.Adverts;
	import com.distriqt.extension.adverts.events.AdvertsEvent;

	import starling.display.Sprite;

	/**
	 */
	public class PangleTests extends Sprite
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

		public function PangleTests( logger:ILogger )
		{
			_l = logger;
			try
			{
				log( "Pangle Supported: " + AdMobPangle.isSupported );
				if (!AdMobPangle.isSupported) return;

				log( "Pangle Version:       " + AdMobPangle.instance.version );
				log( "Pangle nativeVersion: " + AdMobPangle.instance.nativeVersion );

				Adverts.service.setup( AdvertPlatform.PLATFORM_ADMOB );
				Adverts.service.addEventListener(
						AdvertsEvent.INITIALISED,
						function ( event:AdvertsEvent ):void
						{
							log( "Adverts initialised" );
						} );
				Adverts.service.initialise();
			}
			catch (e:Error)
			{
				trace( e );
			}
		}


		////////////////////////////////////////////////////////
		//  
		//


	}
}
