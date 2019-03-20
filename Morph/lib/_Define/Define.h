#ifndef DEFINE_H
#define DEFINE_H

#define A true

#define DEGREES_TO_RADIANS 0.017453292519943295769236907684886
#define RADIANS_TO_DEGREES 57.295779513082320876798154814105
#define MATH_E 2.7182818284590452353602874713527



// LIGHT SENSORS
#define LS_NUM 16
#define LS_CALIBRATE_COUNT 10
#define LS_DEFAULT_THRESHOLD 200
#define LS_BUFFER 200
#define LS_INTERVAL_ANGLE 22.5

#if A
    #define BROKEN_LIGHT_SENSOR 5
#else
    #define BROKEN_LIGHT_SENSOR 4
#endif

// Pins
#define LS_0 A7
#define LS_1 A6
#define LS_2 A10
#define LS_3 A11
#define LS_4 A12
#define LS_5 A13
#define LS_6 A3
#define LS_7 A2
#define LS_8 A1
#define LS_9 A0
#define LS_10 A22
#define LS_11 A21
#define LS_12 A24
#define LS_13 A23
#define LS_14 A9
#define LS_15 A8

// Angles
#define LS_ANGLE_0 0
#define LS_ANGLE_1 22.5
#define LS_ANGLE_2 45
#define LS_ANGLE_3 67.5
#define LS_ANGLE_4 90
#define LS_ANGLE_5 112.5
#define LS_ANGLE_6 135
#define LS_ANGLE_7 157.5
#define LS_ANGLE_8 180
#define LS_ANGLE_9 202.5
#define LS_ANGLE_10 225
#define LS_ANGLE_11 247.5
#define LS_ANGLE_12 270
#define LS_ANGLE_13 292.5
#define LS_ANGLE_14 315
#define LS_ANGLE_15 337.5

// I Values
#define LS_I_0 0
#define LS_I_1 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_1)))
#define LS_I_2 (sqrt(2) / 2)
#define LS_I_3 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_3)))
#define LS_I_4 1
#define LS_I_5 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_5)))
#define LS_I_6 (sqrt(2) / 2)
#define LS_I_7 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_7)))
#define LS_I_8 0
#define LS_I_9 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_9)))
#define LS_I_10 (-sqrt(2) / 2)
#define LS_I_11 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_11)))
#define LS_I_12 -1
#define LS_I_13 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_13)))
#define LS_I_14 (-sqrt(2) / 2)
#define LS_I_15 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_15)))

// J Values
#define LS_J_0 1
#define LS_J_1 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_1)))
#define LS_J_2 (sqrt(2) / 2)
#define LS_J_3 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_3)))
#define LS_J_4 0
#define LS_J_5 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_5)))
#define LS_J_6 (-sqrt(2) / 2)
#define LS_J_7 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_7)))
#define LS_J_8 -1
#define LS_J_9 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_9)))
#define LS_J_10 (-sqrt(2) / 2)
#define LS_J_11 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_11)))
#define LS_J_12 0
#define LS_J_13 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_13)))
#define LS_J_14 (sqrt(2) / 2)
#define LS_J_15 (RADIANS_TO_DEGREES * (cos(DEGREES_TO_RADIANS * LS_ANGLE_15)))

#endif