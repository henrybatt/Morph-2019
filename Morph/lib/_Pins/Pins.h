#ifndef PINS_H
#define PINS_H

#include <Arduino.h>
#include <Define.h>

// --- Camera --- //


// --- Light Sensors --- //
// #define LS_0 A7
// #define LS_1 A6
// #define LS_2 A10
// #define LS_3 A11
// #define LS_4 A12
// #define LS_5 A13
// #define LS_6 A3
// #define LS_7 A2
// #define LS_8 A1
// #define LS_9 A0
// #define LS_10 A22
// #define LS_11 A21
// #define LS_12 A24
// #define LS_13 A23
// #define LS_14 A9
// #define LS_15 A8
// #define LS_16 A7
// #define LS_17 A6
// #define LS_18 A10
// #define LS_19 A11
// #define LS_20 A12
// #define LS_21 A13
// #define LS_22 A3
// #define LS_23 A2
// #define LS_24 A1
// #define LS_25 A0
// #define LS_26 A22
// #define LS_27 A21
// #define LS_28 A24
// #define LS_29 A23
// #define LS_30 A9
// #define LS_31 A8


// #define LS_0 A7
// #define LS_1 A6
// #define LS_2 A5
// #define LS_3 A4
// #define LS_4 A3
// #define LS_5 A2
// #define LS_6 A1
// #define LS_7 A0
// #define LS_8 A8
// #define LS_9 A9
// #define LS_10 A10
// #define LS_11 A11
// #define LS_12 A12
// #define LS_13 A13
// #define LS_14 A14
// #define LS_15 A15
// #define LS_16 A7
// #define LS_17 A6
// #define LS_18 A5
// #define LS_19 A4
// #define LS_20 A3
// #define LS_21 A2
// #define LS_22 A1
// #define LS_23 A0
// #define LS_24 A8
// #define LS_25 A9
// #define LS_26 A10
// #define LS_27 A11
// #define LS_28 A12
// #define LS_29 A13
// #define LS_30 A14
// #define LS_31 A15

// #define LS_1 A2
// #define LS_2 A3
// #define LS_3 A4
// #define LS_4 A5
// #define LS_5 A6
// #define LS_6 A7
// #define LS_7 A8
// #define LS_8 A9
// #define LS_9 A23
// #define LS_10 A22
// #define LS_11 A21
// #define LS_12 A20
// #define LS_13 A19
// #define LS_14 A18
// #define LS_15 A17
// #define LS_16 A16
// #define LS_17 A2
// #define LS_18 A3
// #define LS_19 A4
// #define LS_20 A5
// #define LS_21 A6
// #define LS_22 A7
// #define LS_23 A8
// #define LS_24 A9
// #define LS_25 A23
// #define LS_26 A22
// #define LS_27 A21
// #define LS_28 A20
// #define LS_29 A19
// #define LS_30 A18
// #define LS_31 A17
// #define LS_32 A16

#define LS_1 A10
#define LS_2 A11
#define LS_3 A13
#define LS_4 A14
#define LS_5 A1
#define LS_6 A1
#define LS_7 A10
#define LS_8 A1
#define LS_9 A1
#define LS_10 A1
#define LS_11 A1
#define LS_12 A1
#define LS_13 A1
#define LS_14 A1
#define LS_15 A1
#define LS_16 A1
#define LS_17 A1
#define LS_18 A1
#define LS_19 A1
#define LS_20 A1
#define LS_21 A1
#define LS_22 A1
#define LS_23 A1
#define LS_24 A1
#define LS_25 A1
#define LS_26 A1
#define LS_27 A1
#define LS_28 A1
#define LS_29 A1
#define LS_30 A1
#define LS_31 A1
#define LS_32 A1

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
