#ifndef PINS_H
#define PINS_H

#include <Arduino.h>
#include <Define.h>

// --- Camera --- //


// --- Light Sensors --- //

#define MUX_OUT_1 A11
#define MUX_A0 50
#define MUX_A1 51
#define MUX_A2 52
#define MUX_A3 53

#define MUX_OUT_2 A10
#define MUX_A4 54 
#define MUX_A5 55
#define MUX_A6 56
#define MUX_A7 57


#define LS_1 7
#define LS_2 6
#define LS_3 5
#define LS_4 4
#define LS_5 3
#define LS_6 2
#define LS_7 1
#define LS_8 0
#define LS_9 8
#define LS_10 9
#define LS_11 10
#define LS_12 11
#define LS_13 12
#define LS_14 13
#define LS_15 14
#define LS_16 15

#define LS_17 14//7
#define LS_18 6
#define LS_19 10//5
#define LS_20 2//4
#define LS_21 12//3
#define LS_22 4//2
#define LS_23 8//1
#define LS_24 0
#define LS_25 1//8
#define LS_26 9
#define LS_27 5//10
#define LS_28 13//11
#define LS_29 3//12
#define LS_30 11//13
#define LS_31 7//14
#define LS_32 15


// --- IR Sensors --- //
#define TSSP_PIN_1 24
#define TSSP_PIN_2 14
#define TSSP_PIN_3 15
#define TSSP_PIN_4 16
#define TSSP_PIN_5 17
#define TSSP_PIN_6 20
#define TSSP_PIN_7 25
#define TSSP_PIN_8 12
#define TSSP_PIN_9 11
#define TSSP_PIN_10 3
#define TSSP_PIN_11 40
#define TSSP_PIN_12 41
#define TSSP_PIN_13 42
#define TSSP_PIN_14 43
#define TSSP_PIN_15 44
#define TSSP_PIN_16 49
#define TSSP_PIN_17 38
#define TSSP_PIN_18 39

// --- Motors --- //
// M1 Pins
#define MOTOR_FRONT_LEFT_ENA 29
#define MOTOR_FRONT_LEFT_IN1 28
#define MOTOR_FRONT_LEFT_IN2 27
#define MOTOR_FRONT_LEFT_REVERSED true
//M2 Pins
#define MOTOR_BACK_LEFT_ENA 4
#define MOTOR_BACK_LEFT_IN1 6 
#define MOTOR_BACK_LEFT_IN2 5
#define MOTOR_BACK_LEFT_REVERSED true
//M3 Pins
#define MOTOR_BACK_RIGHT_ENA 23
#define MOTOR_BACK_RIGHT_IN1 21
#define MOTOR_BACK_RIGHT_IN2 22
#define MOTOR_BACK_RIGHT_REVERSED false
//M4 Pins
#define MOTOR_FRONT_RIGHT_ENA 37
#define MOTOR_FRONT_RIGHT_IN1 36
#define MOTOR_FRONT_RIGHT_IN2 35
#define MOTOR_FRONT_RIGHT_REVERSED true

#endif
