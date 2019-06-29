#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include "drawable.hpp"

class obstacle : public drawable{
private:
	hwlib::xy end;
	hwlib::xy locationM;
	hwlib::xy endM;
public:

   obstacle( max7219 & w, const hwlib::xy & location, const hwlib::xy & end ):
      drawable( w, location, hwlib::xy( 0, 0 ) ),
	  end( end ),
	  locationM( location ),
	  endM( end )
			   
   {}
			   
   void randLine( int obstType ){
	    const int_fast16_t y  = random_in_range( 2, 30 );
	   
	    if( obstType == 1){
	    	location = hwlib::xy( 1, y );
	    	end = hwlib::xy( 2, y );
			
		}else if ( obstType == 2 ){
	    	location = hwlib::xy( 6, y );
	    	end = hwlib::xy( 7, y );
			
		}else if ( obstType == 3){	
	    	location = hwlib::xy( 4, y );
	    	end = hwlib::xy( 5, y );
			
		}
   }
			   
   void draw() override {
	  if( location.x == end.x ){
	  	for( int i = location.y; i < end.y; i++ ){
			w.setPixel( location.x, i, 1 );
		}
	  }else{
		for( int i = location.x; i < end.x; i++ ){
			w.setPixel( i, location.y, 1 );
	 	 }
	  }
      w.render();
   }
	
   void reset(){
   		location = locationM;
		end = endM;
   }	
};
#endif //OBSTACLE_HPP