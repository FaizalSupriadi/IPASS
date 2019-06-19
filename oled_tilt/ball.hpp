#ifndef BALL_HPP
#define BALL_HPP
#include "drawable.hpp"

class circle : public drawable {
protected:

   int radius;
 
public:

   circle( hwlib::window & w, const hwlib::xy & midpoint, int radius ):
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
private:

   hwlib::xy speed;
   
public:

   ball( hwlib::window & w,  const hwlib::xy & midpoint, 
		int radius, const hwlib::xy & speed 
   ):
      circle( w, midpoint, radius ),
      speed( speed )  
   {}

   void update() override {
      location = location + speed; 
   }
   
   void interact( drawable & other, hwlib::xy place ) override{
      if( this != & other){
         if( overlaps( other )){
			 location = place;
		 }
      }
   }   
};




#endif // BALL_HPP