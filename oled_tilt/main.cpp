#include "goal.hpp"
#include <array>

int main( void ){	  
   namespace target = hwlib::target;
   auto scl 		= target::pin_oc( target::pins::scl );
   auto sda 		= target::pin_oc( target::pins::sda );
   
   auto i2c_bus 	= hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
   auto display 	= oled( i2c_bus, 0x3c );  
   auto led 		= target::pin_out( hwlib::target::pins::d5 );
   auto led1 		= target::pin_out( hwlib::target::pins::d4 );
   auto font    	= hwlib::font_default_8x8();
   auto termDisplay = hwlib::terminal_from( display, font );
   
   tilt_sensor tilt( hwlib::target::pin_in( hwlib::target::pins::d7 ));
	
   hwlib::xy location_ball( 2,32 );
   hwlib::xy ball_speed( 4, 0 );
	
   line top( display, hwlib::xy( 0, 0 ), hwlib::xy( 128, 0 ) );
   // line right( display, hwlib::xy( 127, 0 ), hwlib::xy( 127, 63 ) );
   line bottom( display, hwlib::xy( 0, 63 ), hwlib::xy( 127, 63 ) );
   // line left( display, hwlib::xy( 0, 0  ), hwlib::xy( 0, 63 ) );  
   line obstacle( display, hwlib::xy( 64, 24  ), hwlib::xy( 64, 40 ) );	
   ball b( display, location_ball, 4, ball_speed );
   goal goal( display, hwlib::xy( 120, 16 ), hwlib::xy( 121, 17 ) );
    
   std::array< drawable *, 5 > objects = { &goal, &b, &top, &bottom, &obstacle };


   for(;;){
      display.clear();
      for( auto & p : objects ){
         p->draw();
      }
      display.flush();
	   
      hwlib::wait_ms( 80 );
	   
      b.update( tilt );
	   
      for( auto & p : objects ){
         for( auto & other : objects ){
            p->interact( *other, location_ball );
         }
	  }
	  if( b.pointShow() ){
	   	 termDisplay 
         << "\f" << "Your points: " << goal.get_points() << hwlib::flush;   
      	 hwlib::wait_ms( 1'000 );
     	 termDisplay 
         << "\f" << hwlib::flush;
		 goal.reset_points(); 
     	 hwlib::wait_ms( 500 );
   	   }         
	   led.write( tilt.get() );
	   led1.write( !tilt.get() );
   }
}