#ifndef BALL_HPP
#define BALL_HPP
#include "drawable.hpp"
class ball : public drawable {
protected:
   	
   hwlib::xy speed;
   bool show_points;	
   
public:

   ball( max7219 & w, const hwlib::xy & location, const hwlib::xy & speed, bool show_points=0 
   ):
      drawable( w, location, hwlib::xy(0,0) ),
      speed( speed ),
	  show_points( show_points )
   {}
	
   void clearPix() override{
   		for( int i = 1; i < 7; i++ ){
			for( int j = 0; j < 32; j++ ){
				w.setPixel( i, j, 0 );	
			}   
   		}
   }	
	
   void interact( drawable & other, hwlib::xy placeStart ) override{
   	   	if( this != & other){
			 if( overlaps( other )){
				location = placeStart;
				show_points=1;				 
			 }
		}
   }
	
   void update( tilt_sensor tilt, hwlib::target::pin_in sw ) override{
   		if( !sw.read() ){
			speed = hwlib::xy( 0, 1 );
   		}else if( !tilt.get()  ){
			speed = hwlib::xy( 1, 1 );
		}else if( tilt.get() ){
			speed = hwlib::xy( -1, 1 );
		}
		location = location + speed;
	    if( location.y >= 32 ){
			location.y = 0;
		}
	    
   }
	
   void draw() override {
		clearPix();
		w.setPixel( location.x, location.y, 1 );
   }
	
   bool pointShow(){
	    bool tmp = show_points;
	    show_points=0;
   		return tmp;
   }
	
};




#endif // BALL_HPP