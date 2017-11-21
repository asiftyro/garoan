/*
  Garoan.h    -   An Arduino Library for two motor tracked wheel differential
                  drive robot movement by L293D dual H-bridge motor driver IC.
  Created by  -   Asif R. Porosh, November 18, 2017.
  Released in public domain.
*/

#ifndef Garoan_h
#define Garoan_h

#include "Arduino.h"

#define _G_NONE -1

enum SPEEDS {
  G_SLOW = 0,
  G_NORMAL = 1,
  G_FAST = 2,
  G_ZERO = _G_NONE
};

enum DIRECTIONS {
  G_FORWARD = 0,
  G_LEFT = 1,
  G_BACKWARD = 2,
  G_RIGHT = 3,
  G_NONE = _G_NONE
};

class Garoan
{
  public:
    Garoan(
      int pinLeftMotorPWM,
      int pinLeftMotorOUT1,
      int pinLeftMotorOUT2,
      int pinRightMotorPWM,
      int pinRightMotorOUT1,
      int pinRightMotorOUT2,
      int speedMinPWM,
      int speedMaxPWM
    );
    
    void directionForward();
    void directionBackward();
    void directionLeft();
    void directionRight();
    void directionNone();
    void setDirection(DIRECTIONS direction);
    
    void recallLastDirection();
    void recallLastSpeed();
    void recallLast();

    
    void kill();
    void setSpeed(SPEEDS speed);
    
    enum SPEEDS getCurrentSpeed();
    enum DIRECTIONS getCurrentDirection();
    bool isMoving();


  private:
    int _speedMinPWM;
    int _speedMaxPWM;
    int _speedNormalPWM;
    
    SPEEDS _currentSpeed;
    DIRECTIONS _currentDirection;
    DIRECTIONS _lastDirection;
    SPEEDS _lastSpeed;

    bool _isMoving;
    int _pinLeftMotorPWM;
    int _pinRightMotorPWM;
    int _pinLeftMotorOUT1;
    int _pinLeftMotorOUT2;
    int _pinRightMotorOUT1;
    int _pinRightMotorOUT2;

    void _storeCurrentSpeed();
    void _storeCurrentDirection();
    void _translateSpeedToPWM(int* leftMotorPwm, int* rightMotorPwm, SPEEDS speed);
};
#endif
