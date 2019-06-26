#ifndef TILT_HPP
#define TILT_HPP

#include "hwlib.hpp"

class tilt_sensor{
protected:
	hwlib::target::pin_in tilt;
public:
	/// \brief
	/// The tilt_sensor constructor.
	/// \details
	/// Initializes the tilt attribute.
	tilt_sensor( hwlib::target::pin_in tilt ):
		tilt( tilt )
		{}
	
	/// \brief
	/// Bool function.
	/// \details
	/// Return the tilt.read() value as bool.
	bool get(){
		return tilt.read();
	}
};


#endif // TILT_HPP