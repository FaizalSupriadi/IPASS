#include "oled.hpp"
#include "ball.hpp"
#include <array>

int main( void ){	  
   namespace target = hwlib::target;
   auto scl = target::pin_oc( target::pins::scl );
   auto sda = target::pin_oc( target::pins::sda );
   
   auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
   auto display = oled( i2c_bus, 0x3c );  
	
   hwlib::xy location_ball( 0,32 );
   hwlib::xy ball_speed( 5, 0 );
	
   line top( display, hwlib::xy(   0,  0 ), hwlib::xy( 128,  0 ) );
   line right( display, hwlib::xy( 127,  0 ), hwlib::xy( 127, 63 ) );
   line bottom( display, hwlib::xy(   0, 63 ), hwlib::xy( 127, 63 ) );
   line left( display, hwlib::xy(   0, 0  ), hwlib::xy( 0, 63 ) );
   ball b( display, location_ball, 4, ball_speed );
    
   std::array< drawable *, 5 > objects = { &b, &top,&right,&bottom,&left};
	
	
   for(;;){
      display.clear();
      for( auto & p : objects ){
         p->draw();
      }
      display.flush();
	   
      hwlib::wait_ms( 100 );
	   
      for( auto & p : objects ){
          p->update();
      }
	
      for( auto & p : objects ){
         for( auto & other : objects ){
            p->interact( *other, location_ball );
         }
	  }
   }
}