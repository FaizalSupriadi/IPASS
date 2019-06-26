#ifndef RAND_HPP
#define RAND_HPP

#include "hwlib.hpp"

uint_fast32_t random(){ 
   static uint_fast32_t n = 0;
   n = n * 214013L + 2531011L; 
   return ( n >> 16) & 0x7fff; 
}

uint_fast32_t random_in_range( 
   uint_fast32_t min, 
   uint_fast32_t max 
){
   auto x = random();
   x = x % ( max - min + 1 ); 
   return min + x;
}


#endif // RAND_HPP