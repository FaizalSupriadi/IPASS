#ifndef BALL_HPP
#define BALL_HPP
#include "drawable.hpp"
class squareBall : public drawable {
protected:
   	
   hwlib::xy speed;
   bool show_points;	
   
public:

   squareBall( max7219 & w, const hwlib::xy & location, const hwlib::xy & speed, bool show_points=0 
   ):
      drawable( w, location, hwlib::xy(0,0) ),
      speed( speed ),
	  show_points( show_points )
   {}
	
   void clearPix(){
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
				 
	    hwlib::cout << "TOUCH\n"<< hwlib::flush;
			 }
		}
   }
	
   void update( tilt_sensor tilt ) override{
    	if( tilt.get() ){
			speed = hwlib::xy( 1, 1 );
		}else if( !tilt.get() ){
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
	
// void draw() override {
//	   clearPix();
//	   if( location.y == end.y ){
//	   		for( int i = location.x; i < end.x; i++ ){		
//				for( int j = 0; j < end.x - location.x; j++ ){
//						w.setPixel( i, location.y+j, 1 );
//					}
//			}
//	   	}else{
//			for( int i = location.y; i < end.y; i++ ){
//				for( int j = location.x; j < end.x; j++ ){
//					w.setPixel( i, j, 1 );	
//				}
//			}   
// 		}
//    w.render();
// }

	
	
   bool pointShow(){
	    bool tmp_show = show_points;
	    show_points=0;
   		return tmp_show;
   }
	
};




#endif // BALL_HPP