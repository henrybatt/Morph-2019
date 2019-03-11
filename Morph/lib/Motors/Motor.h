#ifndef Motor_h
#define Motor_h

#include <Common.h>

class Motor 
{
	public:
    	Motor(int pwmPin, int dirPin, int brkPin, int rev);
   		void set(int speed);
    	void brake();
	private:
    	int m_brk;
    	int m_pwm;
    	int m_dir;
    	int reversed;

};

#endif