#include "ball.hpp"

void circle::draw(){	
  hwlib::circle c( location + hwlib::xy( radius, radius ), radius );
  c.draw( w );
}
void ball::update( tilt_sensor tilt ){
	if( tilt.get() ){
		speed.y = 2;
	}else if( !tilt.get() ){
		speed.y = -2;
	}
	location = location + speed; 
	if( location.x > 128 ){
		location.x=0;
	}
}
void ball::interact( drawable & other, hwlib::xy place  ){
	if( this != & other){
		 if( overlaps( other )){
			 location = place;
		 }
	}
}

	
