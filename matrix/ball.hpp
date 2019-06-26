#ifndef BALL_HPP
#define BALL_HPP
#include "drawable.hpp"
class circle : public drawable {
protected:

   int radius;
 
public:

   circle( max7219 & w, const hwlib::xy & midpoint, int radius ):
      drawable( w, 
         midpoint - hwlib::xy( radius, radius ), 
         hwlib::xy( radius, radius ) * 2 ),
      radius( radius )
   {}
   
   void draw() override {
	   hwlib::circle c( location + hwlib::xy( radius, radius ), radius );
	   c.draw( w );
   }
};

// ===========================================================================

class ball : public circle {
protected:

   hwlib::xy speed;
   bool show_points;	
   
public:

   ball( max7219 & w,  const hwlib::xy & midpoint, 
		int radius, const hwlib::xy & speed, bool show_points=0 
   ):
      circle( w, midpoint, radius ),
      speed( speed ),
	  show_points( show_points )
   {}
   void update( tilt_sensor tilt ) override{
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
   void interact( drawable & other, hwlib::xy place ) override{
   	   	if( this != & other){
			 if( overlaps( other )){
				 location = place;
				 show_points=1;
			 }
		}
   }
   bool pointShow(){
	    bool tmp_show = show_points;
	    show_points=0;
   		return tmp_show;
   }
	
};




#endif // BALL_HPP