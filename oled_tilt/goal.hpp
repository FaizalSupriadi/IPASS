#ifndef GOAL_HPP
#define GOAL_HPP

#include <hwlib.hpp>
#include "ball.hpp"

class goal : public line {
private:
	
	hwlib::xy end;
	int points;
	
public:
	goal(hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end, int points=0): 
		 line( w, location, end - location ), 
		 end( end ),
		 points( points )
		 
	{}
	void draw()override{		
		line dot( w, location, end );
		dot.draw();
	}
	void interact( drawable & other, hwlib::xy place ) override{
		 const int_fast16_t y  = random_in_range( 8, 52 );
		 const int_fast16_t x  = random_in_range( 80, 120 );
		 if( this != & other){
			if( overlaps( other )){
				location = hwlib::xy( x, y );
				end = hwlib::xy( x+1, y+1 );
				points++;
			}
	  	}
	}
	int get_points(){return points;}
	
	void reset_points(){points=0;}
	
	
};
#endif // GOAL_HPP