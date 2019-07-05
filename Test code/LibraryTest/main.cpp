#include "maxLib.hpp"
#include "hwlib.hpp"

int main( void ){	 
	int width=4, height=4;
	namespace target = hwlib::target;
	
	auto ds 	= target::pin_out( target::pins::d46 );
	auto shcp 	= target::pin_out( target::pins::d47 );
	auto stcp 	= target::pin_out( target::pins::d48 );
	auto spi 	= hwlib::spi_bus_bit_banged_sclk_mosi_miso( stcp, ds, hwlib::pin_in_dummy );
	
	max7219 	screens( spi, shcp, width, height );
	screen		screenTest[1];
	screenTest[1] = screen();
	
	// Test clear function.
	screens.clear();
	hwlib::wait_ms(500);
	
	// Test setPixel for one led and render.
	screens.setPixel( 1, 1, 1);	
	screens.render();
	hwlib::wait_ms(500);
	
	// Test setPixel function for whole display, turn every led on and off one by one.
	for( int i=0; i < 8; i++){
		for( int j=0; j < 32; j++){
			screens.setPixel( i, j, 1);
			screens.render();
			hwlib::wait_ms(10);
			screens.setPixel( i, j, 0);
			screens.render();
		}

	}
	hwlib::wait_ms(500);
	
	// Test if the functions return the width and height.
	hwlib::cout << "Width: "<< screens.getWidth() << "\nHeight: " << screens.getHeight() << "\n" << hwlib::flush;
	
	// Test setRow and getRow by reading, before and after altering a row.
	hwlib::cout << "Row: "  << screenTest[1].getRow( 1 ) << "\n"<< hwlib::flush;
	screenTest[1].setRow( 1, 1 );
	hwlib::cout << "Row: "  << screenTest[1].getRow( 1 ) << "\n"<< hwlib::flush;


}