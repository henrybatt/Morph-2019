#ifndef IMU_H
#define IMU_H

#include <I2C.h>
#include <Define.h>
#include <Common.h>
#include <Debug.h>
#include <Pins.h>



class IMU {
public:
  double heading;

  IMU() {};
  void init();

  Vector3D readAccelerometer();
  Vector3D readGyroscope();
  Vector3D readMagnetometer();

  void read();
  void calibrate();


private:
  long previousTime;
  long previousDrift;
  double calibration;
  double drift = 0;
  double convertRawAcceleration(int raw) {
    double a = (raw * 2.0) / 32768.0;
    return a;
  }

  double convertRawGyro(int raw) {
    double g = (raw * 1000.0) / 32768.0;
    return g;
  }



};


#endif
