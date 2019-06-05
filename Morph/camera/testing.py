import sensor, image, time, math
from math import atan2, sqrt, pi, degrees, radians, sin, cos



class Scan:
    def __init__(self):
        self.robot_1 = 1:
        self.robot_2 = 0;


    def init(self, robot_):
        self.robot = robot_
        if self.robot == self.robot_1:
            self.thresholds = [
            (0, 0, 0, 0, 0, 0), # Yellow Goal
            (0, 0, 0, 0, 0, 0)] # Blue Goal
            self.window = (0, 0, 0, 0)

        elif self.robot == self.robot_2:
            self.thresholds = [
            (0, 0, 0, 0, 0, 0), # Yellow Goal
            (0, 0, 0, 0, 0, 0)] # Blue Goal
            self.window = (0, 0, 0, 0)


        sensor.reset()
        sensor.set_pixformat(sensor.RGB565)
        sensor.set_framesize(sensor.QVGA)
        sensor.set_windowing(self.window)
        sensor.skip_frames(time=100)

        sensor.set_auto_exposure(False)
        sensor.set_auto_whitebal(False)

        sensor.skip_frames(time = 250)

        # === GAIN ===
        curr_gain = sensor.get_gain_db()
        sensor.set_auto_gain(False, gain_db=curr_gain)

        # === EXPOSURE ===
        curr_exposure = sensor.get_exposure_us()
        sensor.set_auto_exposure(False, exposure_us = int(curr_exposure*0.5))

        # === WHITE BAL ===
        sensor.set_auto_whitebal(False, rgb_gain_db=(-6.02073, -3.762909, 3.33901))

        sensor.set_brightness(2)
        sensor.set_contrast(2)
        sensor.set_saturation(2)

        sensor.skip_frames(time=500)

    def snapshot(self):
        self.img = sensor.snapshot()

    def calcAngleDist(self)





from pyb import UART, LED
