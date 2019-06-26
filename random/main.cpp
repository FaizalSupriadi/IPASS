
#include "rand.hpp"

int main( void ){
	auto led = hwlib::target::pin_out( hwlib::target::pins::d5 );
	auto led1 = hwlib::target::pin_out( hwlib::target::pins::d4 );
	
	for( unsigned int n = 0; n < 30; n++ ){
		
         const int_fast16_t x  = random_in_range( 1, 3 );
		 if(x==1){
			led.write(0); 
		    led1.write(0); 
		 	led.write(1);
			hwlib::wait_ms(200);
		 }
		 if(x==2){
		 	led.write(0); 
		    led1.write(0); 
			led1.write(1);
			 hwlib::wait_ms(200);
		 }
		 if(x==3){
		 	led.write(0); 
		    led1.write(0); 
		    led.write(1); 
		    led1.write(1); 
			 hwlib::wait_ms(200);
		 }
		
		 
	}

	
}