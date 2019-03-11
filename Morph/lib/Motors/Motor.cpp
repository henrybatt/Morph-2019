#include <Motor.h>

Motor::Motor(int pwmPin, int dirPin, int brkPin, int rev)
{
    pinMode(pwmPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(brkPin, OUTPUT);
    reversed = rev;
    m_pwm = pwmPin;
    m_dir = dirPin;
    m_brk = brkPin;
    analogWriteFrequency(pwm, /* Write Speed */ 19000);
}

void Motor::set(int speed)
{
    digitalWrite(m_dir, speed > 0 ? !reversed : reversed);
    analogWrite(m_pwm, speed > 0 ? speed : -speed);
    digitalWrite(m_brk, LOW);
}

void Motor::brake()
{
    digitalWrite(m_dir, LOW);
    analogWrite(m_pwm, 0);
    digitalWrite(m_brk, HIGH);
}
