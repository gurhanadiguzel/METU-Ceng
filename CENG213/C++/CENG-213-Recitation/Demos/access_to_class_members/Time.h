#ifndef TIME_H
#define TIME_H

#include <iostream>

using namespace std;

class Time
{
	private:				// no need to specify since they are private by default 
		//int hours;
		int minutes;
		int seconds;
	public:	
		int hours	;			// means the below part can be accessed in public
		void setTime(int h, int m, int s);
		int getHours();
		int getSeconds();
		void increaseTime();
};

#endif
