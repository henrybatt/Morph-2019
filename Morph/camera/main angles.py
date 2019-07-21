# 2019 Morph Camera Code

## ======================= BLOB SCANNER =======================
import image, sensor, time
from math import atan2, sqrt, pi, degrees, radians, sin, cos

class Scan():

    def __init__(self):
        self.ROBOT_1 = 1
        self.ROBOT_2 = 0
        self.NO_ANGLE = 400
        self.debugCount = 0
        self.DEBUG_COUNT_MAX = 30


    def init(self, robot_):
        self.robot = robot_
        if self.robot == self.ROBOT_1:
            self.thresholds = [
            [(1, 37, -31, 56, 9, 37)],  # Yellow Goal
            [(39, 61, -37, -15, -42, 2)]] # Blue Goal
            self.whitebal = (-6.02073, -3.15645, 1.43468)
            self.window = (55, 0, 240, 240)
            self.max_rad = 120

        elif self.robot == self.robot_2:
            self.thresholds = [
            (0, 0, 0, 0, 0, 0), # Yellow Goal
            (0, 0, 0, 0, 0, 0)] # Blue Goal
            self.whitebal = (0, 0, 0)
            self.window = (0, 0, 0, 0)
            self.max_rad = 120


        # - Sensor Setup - #
        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA)
        #sensor.set_windowing(self.window)
        sensor.skip_frames(time=1000)

        # - Balance - #
        sensor.set_auto_whitebal(False, rgb_gain_db=self.whitebal)
        sensor.set_brightness(0)
        sensor.set_contrast(3)
        sensor.set_saturation(2)
        curr_exposure = sensor.get_exposure_us()
        sensor.set_auto_exposure(False, exposure_us=int(curr_exposure*0.5))
        curr_gain = sensor.get_gain_db()
        sensor.set_auto_gain(False, gain_db=curr_gain)
        sensor.set_auto_gain(False, gain_db=15)
        sensor.skip_frames(time=500)


    def whiteBal(self):
        sensor.set_auto_whitebal(True)
        self.debugCount += 1
        if self.debugCount >= self.DEBUG_COUNT_MAX:
            print(sensor.get_rgb_gain_db())
            self.debugCount = 0


    def screenShot(self, debug=False):
        self.img = sensor.snapshot()
        if(debug):
            self.img.draw_cross(int(self.img.width() / 2), int(self.img.height() / 2))
            self.img.draw_circle((int(self.img.width() / 2), int(self.img.height() / 2), self.max_rad))


    def angleDist(self, object):
        # Calculates angle and distance towards blob
        dx = object.cx() - (self.img.width() / 2)
        dy = object.cy() - (self.img.height() / 2)
        angle = (450 - degrees(atan2(dy, dx))) % 360
        distance = (sqrt(dx**2 + dy**2))
        return (angle, distance)


    def sortBlobs(self,blobs, debug=False):
        # Organises blob data and ensures it is within mirror and biggest
        if len(blobs) > 0:
            for blob in sorted(blobs, key=lambda x: x.pixels(), reverse = True):
                angle, distance = scanner.angleDist(blob)
                if distance < self.max_rad:
                    if debug:
                        self.img.draw_cross(blob.cx(), blob.cy())
                        self.img.draw_rectangle(blob.rect())
                        self.img.draw_line(((int(self.img.width() / 2)), int(self.img.height() / 2), blob.cx(), blob.cy()),thickness=2)
                        print(clock.fps())

                    return (angle, distance)
        return (self.NO_ANGLE, self.NO_ANGLE)


    def findData(self, debug=False):
        # Find Blobs and calculate Angles and Distances
        yellowBlob = self.img.find_blobs(self.thresholds[0],x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        blueBlob = self.img.find_blobs(self.thresholds[1],x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        yellowAngle, yellowDist = scanner.sortBlobs(yellowBlob, debug)
        blueAngle, blueDist = scanner.sortBlobs(blueBlob, debug)

        return ([yellowAngle, yellowDist, blueAngle, blueDist])




## ======================= SEND DATA =======================
from pyb import UART, LED

class Sender():

    def __init__(self, bus=3, baud=9600, tout_c=10):
        self.uart = UART(bus, baud, timeout_char=tout_c)

    def sendData(self, data, debug=False):

        sendData = [0x80]

        for i in data:
            i = round(i)
            sendData.append((i >> 7) & 0x7F)
            sendData.append(i & 0x7F)

        if debug:
            print(sendData)
        for i in sendData:
            self.uart.writechar(i)




## ======================= MAIN =======================
clock = time.clock()

scanner = Scan()
sender = Sender()

from pyb import LED
#LED(3).on()

scanner.init(scanner.ROBOT_1)


while True:
    #clock.tick()
    #scanner.whiteBal()
    scanner.screenShot(True) #Display Radius & Cross
    data = scanner.findData(True) #Draw lines and boxs around blobs
    sender.sendData(data, True) #Print angle and distance
    LED(3).toggle()
