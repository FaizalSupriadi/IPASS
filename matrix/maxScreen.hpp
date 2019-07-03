// ==========================================================================
//
// File      : maxScreen.hpp
// Part of   : IPASS Max7219 Library
// Copyright : Faizal.faizalrachmansupriadi@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
///@file
#ifndef MAXSCREEN_HPP
#define MAXSCREEN_HPP

/// The screen class is used to store data for a single screen.
//
/// This class is used to store data for a single screen.
/// This class consists of an array with 8 rows, each containing a byte.
/// Each bit represents a led, with 1 as on and 0 as off.
//
/// This class does not turn the led on or off, the max7219 class does this instead.
/// The data in this class is sent to the max7219 class.
//
/// This class has 3 functions to alter the stored data:
/// - getRow( int n ): Read the byte in a row ranging from 0 to 7.
/// - setRow( int n ): Write a byte in a row ranging from 0 to 7.
/// - setPixel( int x, int y, bool data): Write a value true or false on led y on row x.
class screen{
private:
	uint8_t row[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

public:
	
	/// Function to allow reading data from a row.
	//
	/// This function returns a single row, ranging from 0 to 7.
	/// This function needs to have input ranging from 0 to 7 to return the row, else it will return 0
	uint8_t getRow( int n ){
		if( n < 0 || n > 7 ){
			return 0;
		}return row[n];
	}
	
	/// Function to allow setting data from a row.
	//
	/// This function sets a row n with data.
	/// This functions needs to have input ranging from 0 to 7 to set data, otherwise it will do nothing.
	void setRow( int n, uint8_t data ){
		if( n < 0 || n > 7 ){
			return;
		}
		row[n] = data;
	}
	
	/// Function to alter one bit.
	//
	/// This function allows a single led to be toggled on or off by sending x and y coordinates and a value.
	/// Only the concerning bit is changed, the rest of the data stays the same.
	void setPixel( int x, int y, bool data ){
		// First the data is inverted, then it is XOR-ed by row[x], afterwards 1 is shifted to the left by int y,
		// after all that the first bit manipulation and the second are AND-ed together, which then gives row[X] an XOR-ed version of it.
		row[x] ^= (-data ^ row[x] ) & ( 1 << y );  
		
	}
};






#endif // MAXSCREEN_HPP