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
 * This is a test application for the distriqt extension
 * 
 * @author Michael Archbold & Shane Korin
 * 	
 */
package
{
	import com.distriqt.extension.admob.ironsource.AdMobIronSource;
	
	import flash.display.Sprite;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	import flash.text.TextFormat;
	
	
	/**	
	 * Sample application for using the IronSource Native Extension
	 */
	public class TestIronSource extends Sprite
	{
		
		//
		//	VARIABLES
		//
		
		
		private var _text		: TextField;
		
		
		/**
		 * Class constructor
		 */
		public function TestIronSource()
		{
			super();
			create();
			init();
		}
		
		
		
		//
		//	INITIALISATION
		//	
		
		private function create( ):void
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
		
		
		private function init( ):void
		{
			try
			{
				AdMobIronSource.instance.init();
				
				message( "IronSource Supported: " + AdMobIronSource.isSupported );
				if (AdMobIronSource.isSupported)
				{
					message( "IronSource Version:       " + AdMobIronSource.instance.version );
					message( "IronSource nativeVersion: " + AdMobIronSource.instance.nativeVersion );
				}
				
				AdMobIronSource.instance.validateIntegration();
				
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
		
		
		private function mouseClickHandler( event:MouseEvent ):void
		{
			//
			//	Do something when user clicks screen?
			//	
		}
		
		
		private function activateHandler( event:Event ):void
		{
		}
		
		private function deactivateHandler( event:Event ):void
		{
		}

		
		//
		//	EXTENSION HANDLERS
		//
		

		
	}
}

