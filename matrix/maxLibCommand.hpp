#ifndef MAXLIBINIT_HPP
#define MAXLIBINIT_HPP
#include <stdint.h>
///@file

/// NO-OP register addres: If this is send as an address, the matrix this is sent to changes nothing,
/// diregarding the data sent to the same chip.

constexpr uint8_t MAX7219_REG_NO_OP 			= 0x00;

/// The decode register address: Sets the decode mode.
constexpr uint8_t MAX7219_REG_DECODE			= 0x09;
constexpr uint8_t MAX7219_REG_BRIGHTNESS		= 0x0A;
constexpr uint8_t MAX7219_REG_SCAN_LIMIT		= 0x0B;
constexpr uint8_t MAX7219_REG_SHUTDOWN			= 0x0C;
constexpr uint8_t MAX7219_REG_DISPLAYTEST		= 0x0F;

constexpr uint8_t MAX7219_COLUMN1				= 0x01;
constexpr uint8_t MAX7219_COLUMN2				= 0x02;
constexpr uint8_t MAX7219_COLUMN3				= 0x03;
constexpr uint8_t MAX7219_COLUMN4				= 0x04;
constexpr uint8_t MAX7219_COLUMN5				= 0x05;
constexpr uint8_t MAX7219_COLUMN6				= 0x06;
constexpr uint8_t MAX7219_COLUMN7				= 0x07;
constexpr uint8_t MAX7219_COLUMN8				= 0x08;
	
/// Multi-purpose data: Send no data to a column, can be used for a NO-OP on certain.
constexpr uint8_t MAX7219_NO_OP_DATA			= 0x00;
/// The ammount of columns that can be adressed: 1 to 8 (0x00 to 0x007).
constexpr uint8_t MAX7219_SCAN_LIMIT			= 0x07;
/// Enable shutdown mode and display test.
constexpr uint8_t MAX7219_NORMAL_OPERATION		= 0x01;
/// Brightness of LEDs (0x01 to 0x1F).
constexpr uint8_t BRIGHTNESS_LVL				= 0x05;

/// The amount of matrices.
constexpr uint8_t MATRIX_AMOUNT					= 4;
/// The size of the matrices.
constexpr uint8_t MATRIX_SIZE					= ( MATRIX_AMOUNT+MATRIX_AMOUNT );

constexpr uint8_t PIXELBUFFER					= 0x0;

#endif // MAXLIBINIT_HPP