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
 * @created		14/10/2022
 * @copyright	http://distriqt.com/copyright/license.txt
 */
package com.distriqt.test.pangle
{
	import com.distriqt.extension.admob.pangle.AdMobPangle;

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
				if (AdMobPangle.isSupported)
				{
					log( "Pangle Version:       " + AdMobPangle.instance.version );
					log( "Pangle nativeVersion: " + AdMobPangle.instance.nativeVersion );
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


	}
}
