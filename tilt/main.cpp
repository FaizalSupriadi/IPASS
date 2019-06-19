#include "tilt.hpp"

int main( void ){	 
	
	auto tilt = hwlib::target::pin_in( hwlib::target::pins::d7 );
	auto led = hwlib::target::pin_out( hwlib::target::pins::d5 );
	auto led1 = hwlib::target::pin_out( hwlib::target::pins::d4 );
	
	tilt_sensor sense( tilt );
	for(;;){
		// Test with leds.
		led.write( sense.tilt_get() );
		led1.write( !sense.tilt_get() );
		
	}
}