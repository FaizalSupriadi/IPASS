#include "maxLib.hpp"
#include "drawable.hpp"
#include "hwlib.hpp"
#include <array>
int main( void ){	 
	int width=4, height=4;
	//bool green=1;
	//bool red=0;
	
	namespace target = hwlib::target;
	
	auto ds 	= target::pin_out( target::pins::d46 );
	auto shcp 	= target::pin_out( target::pins::d47 );
	auto stcp 	= target::pin_out( target::pins::d48 );
	auto sw		= target::pin_in( target::pins::d2 );


	
	auto spi 	= hwlib::spi_bus_bit_banged_sclk_mosi_miso( stcp, ds, hwlib::pin_in_dummy );
	
	max7219 	screens( spi, shcp, width, height );
	
	//int width_pix = ( 8 * screens.getWidth() - 1 );
	int height_pix = ( 8 * screens.getHeight()  );
	
	line right( screens, hwlib::xy( 0, 0), hwlib::xy( 0, height_pix ) );
	line left ( screens, hwlib::xy( 7, 0), hwlib::xy( 7,  height_pix ) );
	
	std::array< drawable *, 2 > objects = { &left, &right };

	
	
	
	for(;;){
		
		if( !sw.read() ){
			screens.clear();
		}else{
			for( auto & p : objects ){
        		 p->draw();
      		}
		}
		//screens.clear();
		//screens.setPixel( 0, 0, 1);
		//screens.setPixel( 1, 0, 1);
		//screens.render();
		//hwlib::wait_ms(200);
		
	}
}