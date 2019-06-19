#ifndef OLED_HPP
#define OLED_HPP

#include "oled_init.hpp"

class ssd1306_i2c {
protected:

   /// the i2c channel
   hwlib::i2c_bus & bus;
   uint_fast8_t address;
   
   /// current cursor location in the controller
   hwlib::xy cursor;
	   
public:	
    
   /// construct by providing the i2c channel	
   ssd1306_i2c( hwlib::i2c_bus & bus, uint_fast8_t address = 0x3C ):
      bus( bus ),
      address( address ),
	   cursor( 255, 255 )
   {
      // wait for the controller to be ready for the initialization       
      hwlib::wait_ms( 20 );
   }      
   
   /// send a command without data
   void command( ssd1306_commands c ){
	  /// Put the given commands into array uint8_t data, with prefix uint8_t
      uint8_t data[] = { 
         ssd1306_cmd_prefix, (uint8_t) c 
      };
	  /// Write to the ssd1306 the given commands
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );      
   } 
   
   /// send a command with one data byte
   void command( ssd1306_commands c, uint8_t d0 ){
      uint8_t data[] = { 
         ssd1306_cmd_prefix, (uint8_t) c, 
         ssd1306_cmd_prefix, d0 
      };
	  /// Write to the ssd1306 the given commands
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );    
   } 	
   
   /// send a command with two data bytes
   void command( ssd1306_commands c , uint8_t d0, uint8_t d1 ){
      uint8_t data[] = { 
         ssd1306_cmd_prefix, (uint8_t) c, 
         ssd1306_cmd_prefix, d0, 
         ssd1306_cmd_prefix, d1 
      };
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      );     
   } 	
  
   /// write the pixel byte d at column x page y
   void pixels_byte_write( 
      hwlib::xy location,
      uint8_t d 
   ){

      if( location != cursor ){
         command( ssd1306_commands::column_addr,  location.x,  127 );
         command( ssd1306_commands::page_addr,    location.y,    7 );
         cursor = location;
      }   

      uint8_t data[] = { ssd1306_data_prefix, d };
      bus.write( address ).write( 
         data, 
         sizeof( data ) / sizeof( uint8_t ) 
      ); 
      cursor.x++;  
    
   }
      
}; // class ssd1306_i2c

//=============================================================================================

/// buffered oled window
class glcd_oled_i2c_128x64_buffered : public ssd1306_i2c, public hwlib::window {
private:

   static auto constexpr wsize = hwlib::xy( 128, 64 );

   uint8_t buffer[ wsize.x * wsize.y / 8 ];
         
   void write_implementation( 
      hwlib::xy pos, 
      hwlib::color col
   ) override {
      int a = pos.x + ( pos.y / 8 ) * size.x;

      if( col == hwlib::white ){ 
         buffer[ a ] |=  ( 0x01 << (pos.y % 8 ));  
      } else {
         buffer[ a ] &= ~( 0x01 << ( pos.y % 8 )); 
      }   
   }   
     
public:
   
   /// construct by providing the i2c channel
   glcd_oled_i2c_128x64_buffered( hwlib::i2c_bus & bus, int address = 0x3C ):
      ssd1306_i2c( bus, address ),
      window( wsize, hwlib::white, hwlib::black )
   {
      bus.write( address ).write( 
         ssd1306_initialization, 
         sizeof( ssd1306_initialization ) / sizeof( uint8_t ) 
      );     
   }
   
   void flush() override {
      command( ssd1306_commands::column_addr,  0,  127 );
      command( ssd1306_commands::page_addr,    0,    7 );   
      if(0) for( int y = 0; y < 64 / 8; y++ ){
         for( int x = 0; x < 128; x++ ){
            uint8_t d = buffer[ x + 128 * y ];
            uint8_t data[] = { 0x40, d };
            bus.write( address ).write( 
               data, 
               sizeof( data ) / sizeof( uint8_t ) 
            );
         }   
		 
		 // yield the CPU when this is run with an I2C implementation 
		 // that doesn't ever wait, to
		 //    - prevent polling timing from missing an overflow
		 //    - keep other threads in a in a multi-threading context alive
         hwlib::wait_us( 0 );		 
      }  
      //for( int y = 0; y < 64 / 8; y++ ){
         auto t = bus.write( address );
         t.write( ssd1306_data_prefix );
         t.write( buffer, sizeof( buffer ) / sizeof( uint8_t )  );
      //}   
   }     
   
}; // class glcd_oled_i2c_128x64_buffered

using oled = glcd_oled_i2c_128x64_buffered;

#endif //OLED_HPP