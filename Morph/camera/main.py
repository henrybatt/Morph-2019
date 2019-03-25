# 2019 Morph Camera Code

import sensor, image, time, math
from math import atan2, sqrt, pi, degrees, radians, sin, cos
from pyb import UART, LED

# --- Stuff to Change --- #

ROBOT = "A"

DEBUG_WHITEBALANCE = False
DEBUG_BLOBS = True


# -+- Robot A -+- #

BLUE_GOAL_A = [(39, 61, -37, -15, -42, 2)]
YELLOW_GOAL_A = [(68, 91, -5, 37, 21, 127)]

WHITE_BAL_A = (-6.02073, -6.02073, -1.638652)

VWIN_A = (55, 0, 240, 240)
CENTRE_X_A = 120
CENTRE_Y_A = 120
MAX_RADIUS_A = 180

# -+- Robot B -+- #

BLUE_GOAL_B = [(42, 56, -45, -6, -51, -18)]
YELLOW_GOAL_B = [(58, 84, -8, 59, 29, 77)]

WHITE_BAL_B = (-6.02073, -2.868481, 5.986629)

VWIN_B = (58, 0, 174, 164)
CENTRE_X_B = 88
CENTRE_Y_B = 85
MAX_RADIUS_B = 88

# -------------- #

exec("VWIN = VWIN_" + ROBOT)
exec("CENTRE_X = CENTRE_X_" + ROBOT)
exec("CENTRE_Y = CENTRE_Y_" + ROBOT)
exec("MAX_RADIUS = MAX_RADIUS_" + ROBOT)
exec("WHITE_BAL = WHITE_BAL_" + ROBOT)
exec("BLUE_GOAL = BLUE_GOAL_" + ROBOT)
exec("YELLOW_GOAL = YELLOW_GOAL_" + ROBOT)

debugCount = 0
DEBUG_COUNT_MAX = 30

# No blob angle
NO_ANGLE = 0

# - Sensor Setup -#
sensor.reset()

sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_windowing(VWIN)
sensor.skip_frames(time=100)

# - White Balance - #

if DEBUG_WHITEBALANCE:
    sensor.set_auto_whitebal(True)
else:
    sensor.set_auto_whitebal(False, rgb_gain_db=WHITE_BAL)

    sensor.set_brightness(0)
    sensor.set_contrast(3)
    sensor.set_saturation(2)
    sensor.set_auto_exposure(False, exposure_us=10000)
    sensor.set_auto_gain(False, gain_db=15)
    sensor.skip_frames(time=500)


uart = UART(3, 115200, timeout_char=10)

def send(data):
    # Sends data with starting character of 255
    uart.writechar(255)
    if DEBUG_BLOBS:
        print(data)
    for i in data:
        i = round(i)
        uart.writechar(i)


def angleDist(object, img):
    # Calculates angle and distance towards blob
    dx = object.cx() - CENTRE_X
    dy = object.cy() - CENTRE_Y

    angle = (450 - degrees(atan2(dy, dx))) % 360
    distance = (sqrt(dx**2 + dy**2))
    return (angle, distance)

def sortBlobs(blobs, img):
    # Organises blob data and ensures it is within mirror and biggest
    if len(blobs) > 0:
        for blob in sorted(blobs, key=lambda x: x.pixels(), reverse = True):
            angle, distance = angleDist(blob, img)
            if distance < MAX_RADIUS:
                if DEBUG_BLOBS:
                    img.draw_cross(blob.cx(), blob.cy())
                    img.draw_rectangle(blob.rect())
                    img.draw_line((CENTRE_X, CENTRE_Y, blob.cx(), blob.cy()),thickness=2)

                return (angle, distance)
    return (NO_ANGLE, NO_ANGLE)

def findData(blueThreshold,yellowThreshold):
    # Find Blobs and calculate Angles and Distances
    img = sensor.snapshot()

    blueBlob = img.find_blobs(blueThreshold,x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
    yellowBlob = img.find_blobs(yellowThreshold,x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)

    yellowAngle, yellowDist = sortBlobs(yellowBlob, img)
    blueAngle, blueDist = sortBlobs(blueBlob, img)

    return ([yellowAngle, yellowDist, blueAngle, blueDist])



while True:
    if DEBUG_WHITEBALANCE:
        # Print white balance values
        debugCount += 1
        if debugCount >= DEBUG_COUNT_MAX:
            print(sensor.get_rgb_gain_db())
            debugCount = 0

    else:
        # Find Blob data and send
        data = findData(BLUE_GOAL,YELLOW_GOAL)
        send(data)
