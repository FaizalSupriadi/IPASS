#ifndef TILT_HPP
#define TILT_HPP

#include "hwlib.hpp"

class tilt_sensor{
protected:
	hwlib::target::pin_in tilt;
public:
	tilt_sensor( hwlib::target::pin_in tilt ):
		tilt( tilt )
		{}
	bool tilt_get(){
		
		/// The tilt sensor has to be 1 to return 1, if it's a float higher than 0 it won't give 1 back.
		if( tilt.read==1 ){
			return 1;
		} 
		return 0;
	}
	
	
};


#endif // TILT_HPP