#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_ORBIT 0
#define DEBUG_COMPASS 0
#define DEBUG_TSSP 0
#define DEBUG_BALL_DATA 0
#define DEBUG_LIGHT 0
#define DEBUG_LINE_DATA 0
#define DEBUG_CAMERA 0
#define DEBUG_CAMERA_RAW 0

#define DEBUG_MANUAL 1

#define DEBUG_ANY DEBUG_MANUAL || DEBUG_ORBIT || DEBUG_COMPASS || DEBUG_LIGHT || DEBUG_CAMERA || DEBUG_CAMERA_RAW

#endif
