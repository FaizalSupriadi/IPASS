#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <hwlib.hpp>
#include "tilt.hpp"
#include "rand.hpp"
#include "maxLib.hpp"

class drawable {
protected:

   max7219 & w;
   hwlib::xy location;
   hwlib::xy size;
   
public:
   drawable( max7219 & w, const hwlib::xy & location, const hwlib::xy & size ):
      w( w ),
      location( location ),
      size( size )
   {}
   
   virtual void draw() = 0;
   virtual void update(){}
   virtual void update( tilt_sensor tilt){}
   bool overlaps( const drawable & other ); 
   virtual void interact( drawable & other ){}
   virtual void interact( drawable & other, hwlib::xy place ){}
   
   hwlib::ostream & print( hwlib::ostream & out ) const {
      return out << location << " " << ( location + size );
   }      
};

hwlib::ostream & operator<<( hwlib::ostream & lhs, const drawable & rhs ){
   return rhs.print( lhs );
}

bool within( int x, int a, int b ){
   return ( x >= a ) && ( x <= b );
}

bool drawable::overlaps( const drawable & other ){
   
   bool x_overlap = within(
      location.x, 
      other.location.x, 
      other.location.x + other.size.x
   ) || within( 
      other.location.x, 
      location.x, 
      location.x + size.x
   );
     
   bool y_overlap = within( 
      location.y, 
      other.location.y, 
      other.location.y + other.size.y
   ) || within( 
      other.location.y, 
      location.y, 
      location.y + size.y
   );
   
   return x_overlap && y_overlap;
}

// ===========================================================================

class line : public drawable {
private:

   hwlib::xy end;
   
public:

   line( max7219 & w, const hwlib::xy & location, const hwlib::xy & end):
      drawable( w, location, end - location ),
      end( end )
   {}
   
   void draw() override {
	  if( location.x == end.x ){
	  	for( int i = location.y; i < end.y; i++ ){
			w.setPixel( this->location.x, i, 1 );
		}
	  }else{
		for( int i = location.x; i < end.x; i++ ){
			w.setPixel( i, this->location.y, 1 );
	 	 }
	  }
      w.render();
   }
};

#endif // DRAWABLE_HPP