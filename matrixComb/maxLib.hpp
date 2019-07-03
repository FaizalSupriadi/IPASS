// ==========================================================================
//
// File      : maxLib.hpp
// Part of   : IPASS Max7219 Library
// Copyright : Faizal.faizalrachmansupriadi@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
///@file
#ifndef MAXLIB_HPP
#define MAXLIB_HPP
#include "maxLibCommand.hpp"
#include "maxScreen.hpp"
#include "hwlib.hpp"
// screenM is outside of the class, because it doesn't work inside private/public. 
// If you do put it in private/public and you run it, the Due will freeze.
screen screenM[ MATRIX_AMOUNT ]; 
 

/// Class that creates a display out of 4 max7219 led matrices.
//
/// This class controls 4 Max7219 led matrices to make them function as a single display.
/// An instance of this class creates an array of Screen objects to store data.
/// You can then use the max7219 object as a window to draw on.
//
/// Data is altered wth the clear() function ( set all data to 0 ) or the setPixel() function ( alter single pixel with X and Y values ).
/// After altering, the data is drawn on the displays with render().
//
/// Also has functions to return width & heigth with getHeight() and getWidth().
class max7219{
private:
	hwlib::spi_bus & bus;
	hwlib::pin_out & sel;
	int width;
	int height;

public:
	/// Constructor method
	//
	/// Constructor method for the Max7219 display object, which needs:
	/// - SPI bus with parameters for clockpin and datapin.
	/// - Latch pin.
	/// - Amount of screens in width.
	/// - Amount of screens in height.
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
	/// Function to clear all screen data to bits of 0.
	//
	/// Initial values are set here. Also used to clear the screen data with all 0 bits.
	/// Data is stored in tmp[2] array of 2 uint8_t( Bytes ).
	/// First byte is for address.
	/// Second byte is for data.
	/// In maxLibCommand.hpp you can see what addresses or values are used.
	void clear(){
		uint8_t tmp[2] = { MAX7219_REG_DECODE, MAX7219_REG_NO_OP };				// Decodemode none.
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_BRIGHTNESS; 										// Brightness 3.
		tmp[1] = MAX7219_REG_DISPLAYTEST;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_SCAN_LIMIT; 										// Scan limit -- use rows 0 to 7.
		tmp[1] = MAX7219_SCAN_LIMIT;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_SHUTDOWN; 											// Shutdown mode.
		tmp[1] = MAX7219_NORMAL_OPERATION;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		tmp[0] = MAX7219_REG_DISPLAYTEST; 										// Display test mode, all on for 0x01.
		tmp[1] = MAX7219_REG_NO_OP;
		bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		
		// Alter addresses 0x01 to 0x08, all off.
		for( unsigned int i=0; i<8; i++ ){
			tmp[0] = ( uint8_t )( i + 1 );
			tmp[1] = 0x00;
			bus.transaction( sel ).write_and_read( 2, tmp, nullptr );
		}
	}
	
	/// Transfer data to chip to draw pixels.
	//
	/// Use this function after drawing to render the changes to the display.
	/// Data array of 2 bytes are created, an address and value.
	/// The array is then pushed to the bus and drawn on display.
	void render(){
		uint8_t data[ MATRIX_SIZE ];
		for( int i=0; i<8; i++ ){
			for( int j=0; j<(width*height); j++ ){
				data[ 2*( MATRIX_AMOUNT - j - 1 ) ] = ( uint8_t ) ( i+1 );
				data[ 2*( MATRIX_AMOUNT - j - 1 ) + 1 ] = screenM[j].getRow(i);
			}
			bus.transaction( sel ).write_and_read( MATRIX_SIZE, data, nullptr );
		}
		
	}
	
	/// Function to alter a single pixel on the display.
	//
	/// This function asks X and Y values to change the corrseponding pixel on the display to a 1 or 0 ( true or false ).
	/// The right display to draw on is automatically selected.
	void setPixel( int x, int y, bool state){
		int tmp = 0;
		if( height >= width ){
			tmp = width*( x/8 ) + ( y/8 );
		} else{
			tmp = height*( x/8 ) + ( x/8 );
		}
		screenM[tmp].setPixel( x%8, y%8, state );
	}
	/// Height value of matrices.
	//
	/// Return the height.
	int getHeight(){ return height; }
	
	/// Width of matrices.
	//
	/// Return the width.
	int getWidth(){ return width; }
	
	
};


#endif // MAXLIB_HPP