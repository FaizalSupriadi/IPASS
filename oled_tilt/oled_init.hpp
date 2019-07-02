// ==========================================================================
//
// File      : oled_init.hpp
// Part of   : IPASS Oled Library
// Copyright : Faizal.faizalrachmansupriadi@student.hu.nl 2019
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// ==========================================================================
///@file
#ifndef OLED_INIT_HPP
#define OLED_INIT_HPP

#include "hwlib.hpp"

/// SSD1306 chip commands
enum class ssd1306_commands : uint8_t {
   set_contrast                          = 0x81,
   display_all_on_resume                 = 0xa4,
   display_all_on                        = 0xa5,
   normal_display                        = 0xa6,
   invert_display                        = 0xa7,
   display_off                           = 0xae,
   display_on                            = 0xaf,
   set_display_offset                    = 0xd3,
   set_compins                           = 0xda,
   set_vcom_detect                       = 0xdb,
   set_display_clock_div                 = 0xd5,
   set_precharge                         = 0xd9,
   set_multiplex                         = 0xa8,
   set_low_column                        = 0x00,
   set_high_column                       = 0x10,
   set_start_line                        = 0x40,
   memory_mode                           = 0x20,
   column_addr                           = 0x21,
   page_addr                             = 0x22,
   com_scan_inc                          = 0xc0,
   com_scan_dec                          = 0xc8,
   seg_remap                             = 0xa0,
   charge_pump                           = 0x8d,
   external_vcc                          = 0x01,
   switch_cap_vcc                        = 0x02,
   activate_scroll                       = 0x2f,
   deactivate_scroll                     = 0x2e,
   set_vertical_scroll_area              = 0xa3,
   right_horizontal_scroll               = 0x26,
   left_horizontal_scroll                = 0x27,
   vertical_and_right_horizontal_scroll  = 0x29,
   vertical_and_left_horizontal_scroll   = 0x2A   
};   

/// value to send over i2c before a command
constexpr uint8_t ssd1306_cmd_prefix  = 0x80; //128

/// value to send over i2c before a command
constexpr uint8_t ssd1306_data_prefix = 0x40; //64

/// SSD1306 chip initialization
constexpr const uint8_t ssd1306_initialization[] = {
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::display_off,                  
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_display_clock_div, 0x80,
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_multiplex,         0x3f,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_display_offset,    0x00,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_start_line       | 0x00,  
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::charge_pump,           0x14,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::memory_mode,           0x00,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::seg_remap            | 0x01,
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::com_scan_dec,
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_compins,           0x12,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_contrast,          0xcf,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_precharge,         0xf1,  
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::set_vcom_detect,       0x40,   
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::display_all_on_resume,          
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::normal_display,                
   ssd1306_cmd_prefix, (uint8_t) ssd1306_commands::display_on                     
};


#endif //OLED_INIT_HPP