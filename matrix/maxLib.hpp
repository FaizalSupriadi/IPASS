///@file
#ifndef MAXLIB_HPP
#define MAXLIB_HPP
#include "maxLibCommand.hpp"
#include "maxScreen.hpp"
#include "hwlib.hpp"

screen screenM[ MATRIX_AMOUNT ]; // Outside of the class, because it doesn't work inside private/public. If you do put it in private/public, it will freeze.
class max7219{
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	int width;
	int height;
	
public:
	
	
	max7219( hwlib::spi_bus & bus, hwlib::pin_out & sel, int width, int height ):
		bus( bus ),
		sel( sel ),
		width( width ),
		height( height )
		
	{		
		clear();
		for( int i=0; i< MATRIX_AMOUNT; i++){
			screenM[i] = screen();
		}
	}
	
	void clear(){
		uint8_t tmp[2] = { MAX7219_REG_DECODE, MAX7219_REG_NO_OP };				//0x09, 0x00
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_BRIGHTNESS; 
		tmp[1] = 0x0F;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_SCAN_LIMIT; 
		tmp[1] = 0x07;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_SHUTDOWN; 
		tmp[1] = 0x01;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_DISPLAYTEST; 
		tmp[1] = MAX7219_REG_NO_OP;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		for( unsigned int i=0; i<8; i++ ){
			tmp[0] = ( uint8_t )( i + 1 );
			tmp[1] = 0x00;
			bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		}
	}
	
	
	void render(){
		uint8_t data[ MATRIX_SIZE ];
		for( int i=0; i<8; i++ ){
			for( int j=0; j<(width*height); j++ ){
				data[ 2*(MATRIX_AMOUNT-j-1) ] = ( uint8_t ) ( i+1 );
				data[ 2*(MATRIX_AMOUNT-j-1)+1 ] = screenM[j].getRow(i);
			}
			bus.transaction( sel ).write_and_read( MATRIX_SIZE, data, nullptr );
		}
		
	}
	
	void setPixel( int x, int y, bool state){
		int z = 0;
		if( height >= width ){
			z = width*( x/8 ) + ( y/8 );
		} else{
			z = height*( x/8 ) + ( x/8 );
		}
		screenM[z].setPixel( x%8, y%8, state );
	}
	
	/// Return the height.
	int getHeight(){ return height; }
	
	/// Return the width.
	int getWidth(){ return width; }
	
	
};


#endif // MAXLIB_HPP