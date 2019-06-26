#include "goal.hpp"


#include "rand.hpp"

void goal::draw(){
	line dot( w, location, end );
	dot.draw();
}
void goal::interact( drawable & other, hwlib::xy place ){
	 const int_fast16_t y  = random_in_range( 8, 52 );
	 const int_fast16_t x  = random_in_range( 72, 120 );
	 if( this != & other){
		if( overlaps( other )){
			location = hwlib::xy( x, y );
			end = hwlib::xy( x+1, y+1 );
			points++;
	}
  }
}
