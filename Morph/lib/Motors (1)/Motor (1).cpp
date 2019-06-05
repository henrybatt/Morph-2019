#include <Motor1.h>

Motor::Motor(int pwm, int inOne, int inTwo, int rev)
{
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(brkPin, OUTPUT);
    reversed = rev;
    m_pwm = pwm;
    m_inOne = inOne;
    m_inTwo = inTwo;
    analogWriteFrequency(pwm, /* Write Speed */ 19000);
}

void Motor::set(int speed)
{
    analogWrite(m_pwm, speed > 0 ? speed : -speed);
    digitalWrite(m_inOne, speed > 0 ? HIGH : LOW);
    digitalWrite(m_inTwo, speed > 0 ? LOW : HIGH);
}

void Motor::brake()
{
    analogWrite(m_pwm, 0);
}
