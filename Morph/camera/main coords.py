# 2019 Morph Camera Code

## ======================= BLOB SCANNER =======================
import image, sensor, time
from math import atan2, sqrt, pi, degrees, radians, sin, cos

class Scan():

    def __init__(self):
        self.ROBOT_1 = 1
        self.ROBOT_2 = 0
        self.NO_DATA = 250
        self.debugCount = 0
        self.DEBUG_COUNT_MAX = 30


    def init(self, robot_):
        self.robot = robot_
        if self.robot == self.ROBOT_1:
            self.thresholds = [
            [(56, 72, -15, 6, 22, 64)],  # Yellow Goal
            [(39, 51, -23, 7, -42, -17)]] # Blue Goal
            self.whitebal = (-6.02073, -5.623446, 0.9007286)
            self.window = (55, 0, 240, 240)
            self.max_rad = 140
            self.CENTREX = 160 #120
            self.CENTREY = 120

        elif self.robot == self.robot_2:
            self.thresholds = [
            (0, 0, 0, 0, 0, 0), # Yellow Goal
            (0, 0, 0, 0, 0, 0)] # Blue Goal
            self.whitebal = (0, 0, 0)
            self.window = (0, 0, 0, 0)
            self.max_rad = 120
            self.CENTREX = 120
            self.CENTREY = 120

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
        sensor.set_saturation(3)
        curr_exposure = sensor.get_exposure_us()
        sensor.set_auto_exposure(False, exposure_us=int(curr_exposure*1))
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
            self.img.draw_cross(self.CENTREX, self.CENTREY)
            self.img.draw_circle(self.CENTREX, self.CENTREY, self.max_rad)



    def dist(self, object):
        # Calculates distance towards blob
        dx = object.cx() - (self.img.width() / 2)
        dy = object.cy() - (self.img.height() / 2)
        distance = (sqrt(dx**2 + dy**2))
        return (distance)


    def sortBlobs(self,blobs, debug=False):
        # Organises blob data and ensures it is within mirror and biggest
        if len(blobs) > 0:
            for blob in sorted(blobs, key=lambda x: x.pixels(), reverse = True):
                if scanner.dist(blob) < self.max_rad:
                    if debug:
                        self.img.draw_cross(blob.cx(), blob.cy())
                        self.img.draw_rectangle(blob.rect())
                        self.img.draw_line((self.CENTREX, self.CENTREY, blob.cx(), blob.cy()),thickness=2)

                    return (True, blob.cx(), blob.cy())
        return (False, self.NO_DATA, self.NO_DATA)


    def findData(self, debug=False):
        # Find Blobs and calculate Angles and Distances
        yellowBlob = self.img.find_blobs(self.thresholds[0],x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)
        blueBlob = self.img.find_blobs(self.thresholds[1],x_stride=5, y_stride=5, area_threshold=200, pixel_threshold=200, merge=True, margin=23)

        yellowE, yellowX, yellowY = scanner.sortBlobs(yellowBlob, debug)
        blueE, blueY, blueX = scanner.sortBlobs(blueBlob, debug)

        return ([yellowX, yellowY, blueX, blueY, yellowE, blueE])




## ======================= SEND DATA =======================
from pyb import UART, LED

class Sender():

    def __init__(self, bus=3, baud=9600, tout_c=10):
        self.uart = UART(bus, baud, timeout_char=tout_c)


    def sendData(self, data, debug=False):
        sendData = [255]

        for i in data:
            sendData.append(i)

        for i in sendData:
            self.uart.writechar(i)

        if debug:
            print(sendData)




## ======================= MAIN =======================
clock = time.clock()

LED(1).on()

scanner = Scan()
sender = Sender()

scanner.init(scanner.ROBOT_1)

LED(1).off()



while True:
    #clock.tick()


    #scanner.whiteBal() #Print white balance value
    scanner.screenShot(False) #Display radius & cross
    data = scanner.findData(False) #Draw lines and boxs around blobs
    sender.sendData(data, False) #Print angle and distance


    #LED(2).toggle() #Flashes Green LED
    #print(clock.fps())



