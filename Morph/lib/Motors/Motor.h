#ifndef Motor_h
#define Motor_h

#include <Common.h>

class Motor 
{
	public:
    	Motor(int pwm, int inOne, int inTwo, int rev);
   		void set(int speed);
    	void brake();
	private:
    	int m_pwm;
		int m_inOne;
    	int m_inTwo;
    	int reversed;

};

#endif