#ifndef GOAL_HPP
#define GOAL_HPP

#include <hwlib.hpp>
#include "ball.hpp"

class goal : public drawable {
private:
	
	hwlib::xy end;
	hwlib::xy locationM;
	hwlib::xy endM;
	int points;
	bool lineRand=0;
	
public:
	goal( max7219 & w, const hwlib::xy & location, const hwlib::xy & end, int points=0): 
		 drawable( w, location, end - location - hwlib::xy(1,1) ), 
		 end( end ),
		 locationM( location ),
	 	 endM( end ),
		 points( points )
		 
	{}
   void clearPix() override{
   		for( int i = 1; i < 7; i++ ){
			for( int j = 0; j < 32; j++ ){
				w.setPixel( i, j, 0 );	
			}   
   		}
   }	
	
	void draw() override{	
	   
	   if( location.y == end.y ){
	   		for( int i = location.x; i < end.x; i++ ){		
				for( int j = 0; j < end.x - location.x; j++ ){
						w.setPixel( i, location.y+j, 1 );
					}
			}
	   	}else{
			for( int i = location.y; i < end.y; i++ ){
				for( int j = location.x; j < end.x; j++ ){
					w.setPixel( j, i, 1 );	
				}
			}   
 		}
    	w.render();
 	}

	void interact( drawable & other, hwlib::xy place ) override{
		 const int_fast16_t y  = random_in_range( 4, 28 );
		 const int_fast16_t x  = random_in_range( 1, 5 );
		 if( this != & other){
			if( overlaps( other )){
				location = hwlib::xy( x, y );
				end = hwlib::xy( x+2, y+2 );
				points++;
				lineRand = 1;
			}
	  	}
	}
	
	int getPoints(){ return points; }
	
	bool getLineRand(){ 
		bool tmp = lineRand;
	    lineRand = 0;
		return tmp; }
	
	void resetObj(){ 
		location = locationM;
		end = endM;
	}
	
	void resetPoints(){points=0;}
};

#endif // GOAL_HPP