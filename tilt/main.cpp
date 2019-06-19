#include "tilt.hpp"

int main( void ){	 
	
	auto tilt = hwlib::target::pin_in( hwlib::target::pins::d7 );
	auto led = hwlib::target::pin_out( hwlib::target::pins::d5 );
	
	tilt_sensor sense( tilt );
	for(;;){
		led.write( !sense.tilt_get() );
		
	}
}