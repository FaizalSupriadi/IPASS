#ifndef MAXSCREEN_HPP
#define MAXSCREEN_HPP
///@file
class screen{
private:
	uint8_t row[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

public:
	uint8_t getRow( int n ){
		if( n < 0 || n > 7 ){
			return 0;
		}return row[n];
	}
	
	void setRow( int n, uint8_t data ){
		if( n < 0 || n > 7 ){
			return;
		}
		row[n] = data;
	}
	
	void setPixel( int x, int y, bool data ){
		row[x] ^= (-data ^ row[x] ) & ( 1 << y );  
		
	}
};






#endif // MAXSCREEN_HPP