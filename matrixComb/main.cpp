#include "maxLib.hpp"
#include "applicationAll.hpp"
#include <array>

int main( void ){	 
	int width=4, height=4;
	
	namespace target = hwlib::target;
	
	auto ds 	= target::pin_out( target::pins::d46 );
	auto shcp 	= target::pin_out( target::pins::d47 );
	auto stcp 	= target::pin_out( target::pins::d48 );
	
	auto sw2	= target::pin_in ( target::pins::d5  );
	auto sw		= target::pin_in ( target::pins::d6  );
	
	auto tilt	= target::pin_in ( target::pins::d7  );
	
	auto spi 	= hwlib::spi_bus_bit_banged_sclk_mosi_miso( stcp, ds, hwlib::pin_in_dummy );
	
	max7219 	screens( spi, shcp, width, height );
	
	//Maximum width
	//int width_pix  = ( 8 * screens.getWidth() - 1 );
	//Maximum height
	int height_pix = ( 8 * screens.getHeight()  );
	
	hwlib::xy ballStart( 3, 3);
	hwlib::xy ballSpeed( 0, 1);
	
	line right( screens, hwlib::xy( 0, 0), hwlib::xy( 0, height_pix ) );
	line left ( screens, hwlib::xy( 7, 0), hwlib::xy( 7,  height_pix ) );
	obstacle obstacleTop( screens, hwlib::xy( 1, 18), hwlib::xy( 2, 18));
	obstacle obstacleMid( screens, hwlib::xy( 4, 24), hwlib::xy( 5, 24));
	obstacle obstacleBot( screens, hwlib::xy( 6, 10), hwlib::xy( 7, 10));
	ball b( screens, ballStart, ballSpeed  ) ;
	goal g{ screens, hwlib::xy( 4, 28), hwlib::xy( 6, 30) };
	
	std::array< drawable *, 7 > objects = { &g, &b, &left, &right, &obstacleTop, &obstacleMid, &obstacleBot };

	for(;;){
		//Button to refresh the screen by hand.
		if( !sw.read() ){
			screens.clear();
		}else{
			//Draw all objects in the array.
			for( auto & p : objects ){
        		 p->draw();
      		}
			//Update the ball with tilt and switch parameters.
			b.update( tilt, sw2 );
	   		
			//If the ball interacts with an object it resets, unless it's the goal.
		  	for( auto & p : objects ){
				 for( auto & other : objects ){
					p->interact( *other, ballStart );
				 }
			}
			
			//If pointShow is true, pointShow is true when the ball interacts with an object other than the goal.
			if( b.pointShow() ){ 
				//Reset screen.
			 	for( int i = 0; i < 8; i++ ){
					for( int j = 0; j < 32; j++ ){
						screens.setPixel( i, j, 0 );	
					}   
				} 
				
				//Show points in rows.
				for( int i = 0; i <= ( ( g.getPoints()-1 ) * 1 )/32; i++){
					int tmp	= 32*i;
					line points( screens, hwlib::xy( i, 0 ), hwlib::xy( i, g.getPoints()-tmp ) );
					points.draw();
				}
				
				//Confirm when you're done watching your score.
				while( sw2.read() ){
				}
				
				//Reset screen.
				for( int i = 0; i < 8; i++ ){
					for( int j = 0; j < 32; j++ ){
						screens.setPixel( i, j, 0 );	
					}   
				}
				//reset score/objects.
				g.resetPoints();
				g.resetObj();
				
				obstacleTop.reset();
				obstacleMid.reset();
				obstacleBot.reset();
				
				//If the ball touches the goal, it randomizes the obstacles.
			}else if( g.getLineRand() ){ 	
				obstacleTop.randLine( 1 );
				obstacleMid.randLine( 2 );
				obstacleBot.randLine( 3 );
			}
			
		}
		hwlib::wait_ms(300);
		
	}
}