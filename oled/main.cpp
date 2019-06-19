#include "oled.hpp"

int main(){
	 namespace target = hwlib::target;
	
	auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
	
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
    auto display = oled( i2c_bus, 0x3c );  
	
	hwlib::graphics_random_circles( display, 5 );
	
	
}