/*
  Garoan.cpp  -   An Arduino Library for two motor tracked wheel differential
                  drive robot movement by L293D dual H-bridge motor driver IC.
  Created by  -   Asif R. Porosh, November 18, 2017.
  Released in public domain.
*/

#include "Arduino.h"
#include "Garoan.h"

Garoan::Garoan (
  int pinLeftMotorPWM, int pinLeftMotorOUT1, int pinLeftMotorOUT2,
  int pinRightMotorPWM, int pinRightMotorOUT1, int pinRightMotorOUT2,
  int speedMinPWM, int speedMaxPWM
)
{
  pinMode(pinLeftMotorPWM, OUTPUT);
  pinMode(pinLeftMotorOUT1, OUTPUT);
  pinMode(pinLeftMotorOUT2, OUTPUT);
  pinMode(pinRightMotorPWM, OUTPUT);
  pinMode(pinRightMotorOUT1, OUTPUT);
  pinMode(pinRightMotorOUT2, OUTPUT);
  _speedMinPWM = speedMinPWM;
  _speedMaxPWM = speedMaxPWM;
  _speedNormalPWM = (_speedMaxPWM + _speedMinPWM) / 2;
  _currentDirection = G_NONE;
  _currentSpeed = G_ZERO;
  _lastDirection = G_NONE;
  _lastSpeed = G_ZERO;
  _pinLeftMotorPWM = pinLeftMotorPWM;
  _pinRightMotorPWM = pinRightMotorPWM;
  _pinLeftMotorOUT1 = pinLeftMotorOUT1;
  _pinLeftMotorOUT2 = pinLeftMotorOUT2;
  _pinRightMotorOUT1 = pinRightMotorOUT1;
  _pinRightMotorOUT2 = pinRightMotorOUT2;
  setSpeed(G_ZERO);
}

void Garoan::directionForward()
{
  if (_currentDirection != G_FORWARD)
  {
    _storeCurrentDirection();
    _currentDirection = G_FORWARD;
    _isMoving = _currentSpeed != G_ZERO ? true : false;
    digitalWrite(_pinLeftMotorOUT1, HIGH);
    digitalWrite(_pinLeftMotorOUT2, LOW);
    digitalWrite(_pinRightMotorOUT1, HIGH);
    digitalWrite(_pinRightMotorOUT2, LOW);
  }
}

void Garoan::directionBackward()
{
  if (_currentDirection != G_BACKWARD)
  {
    _storeCurrentDirection();
    _currentDirection = G_BACKWARD;
    _isMoving = _currentSpeed != G_ZERO ? true : false;
    digitalWrite(_pinLeftMotorOUT1, LOW);
    digitalWrite(_pinLeftMotorOUT2, HIGH);
    digitalWrite(_pinRightMotorOUT1, LOW);
    digitalWrite(_pinRightMotorOUT2, HIGH);
  }
}

void Garoan::directionLeft()
{
  if (_currentDirection != G_LEFT)
  {
    _storeCurrentDirection();
    _currentDirection = G_LEFT;
    _isMoving = _currentSpeed != G_ZERO ? true : false;
    digitalWrite(_pinLeftMotorOUT1, LOW);
    digitalWrite(_pinLeftMotorOUT2, HIGH);
    digitalWrite(_pinRightMotorOUT1, HIGH);
    digitalWrite(_pinRightMotorOUT2, LOW);
  }
}

void Garoan::directionRight()
{
  if (_currentDirection != G_RIGHT)
  {
    _storeCurrentDirection();
    _currentDirection = G_RIGHT;
    _isMoving = _currentSpeed != G_ZERO ? true : false;
    digitalWrite(_pinLeftMotorOUT1, HIGH);
    digitalWrite(_pinLeftMotorOUT2, LOW);
    digitalWrite(_pinRightMotorOUT1, LOW);
    digitalWrite(_pinRightMotorOUT2, HIGH);
  }
}


void Garoan::directionNone()
{
  if (_currentDirection != G_NONE) {
    _storeCurrentDirection();
    _currentDirection = G_NONE;
    _isMoving = false;
    digitalWrite(_pinLeftMotorOUT1, LOW);
    digitalWrite(_pinLeftMotorOUT2, LOW);
    digitalWrite(_pinRightMotorOUT1, LOW);
    digitalWrite(_pinRightMotorOUT2, LOW);
  }
}

void Garoan::kill()
{
  _storeCurrentSpeed();
  _storeCurrentDirection();
  _currentDirection = G_NONE;
  _currentSpeed = G_ZERO;
  _isMoving = false;
  digitalWrite(_pinLeftMotorOUT1, LOW);
  digitalWrite(_pinLeftMotorOUT2, LOW);
  digitalWrite(_pinRightMotorOUT1, LOW);
  digitalWrite(_pinRightMotorOUT2, LOW);
  analogWrite(_pinLeftMotorPWM, 0);
  analogWrite(_pinRightMotorPWM, 0);
}

void Garoan::_storeCurrentSpeed()
{
  _lastSpeed = _currentSpeed;
}

void Garoan::_storeCurrentDirection()
{
  _lastDirection = _currentDirection;
}

SPEEDS Garoan::getCurrentSpeed()
{
  return _currentSpeed;
}

DIRECTIONS Garoan::getCurrentDirection()
{
  return _currentDirection;
}

bool Garoan::isMoving()
{
  return _isMoving;
}

void Garoan::setSpeed(SPEEDS speed)
{
  if (speed != _currentSpeed)
  {
    _storeCurrentSpeed();
    _currentSpeed = speed;
    _isMoving = _currentSpeed != G_ZERO ? true : false;
    int leftSpeedPwm = 0, rightSpeedPwm = 0;
    _translateSpeedToPWM(&leftSpeedPwm, &rightSpeedPwm, speed);
    analogWrite(_pinLeftMotorPWM, leftSpeedPwm);
    analogWrite(_pinRightMotorPWM, rightSpeedPwm);
  }
}

void Garoan::_translateSpeedToPWM (int *leftMotorPwm, int *rightMotorPwm, SPEEDS speed)
{
  switch (speed)
  {
    case G_ZERO:
      *leftMotorPwm = 0;
      *rightMotorPwm = 0;
      break;
    case G_SLOW:
      *leftMotorPwm = _speedMinPWM;
      *rightMotorPwm = _speedMinPWM;
      break;
    case G_NORMAL:
      *leftMotorPwm = _speedNormalPWM;
      *rightMotorPwm = _speedNormalPWM;
      break;
    case G_FAST:
      *leftMotorPwm = _speedMaxPWM;
      *rightMotorPwm = _speedMaxPWM;
      break;
  }
}

void Garoan::setDirection(DIRECTIONS direction)
{
  switch (direction)
  {
    case G_NONE:
      directionNone();
      break;
    case G_FORWARD:
      directionForward();
      break;
    case G_BACKWARD:
      directionBackward();
      break;
    case G_LEFT:
      directionLeft();
      break;
    case G_RIGHT:
      directionRight();
      break;
  }
}


void Garoan::recallLast()
{
  setDirection(_lastDirection);
  setSpeed(_lastSpeed);
}

void Garoan::recallLastDirection()
{
  setDirection(_lastDirection);
}

void Garoan::recallLastSpeed()
{
  setSpeed(_lastSpeed);
}


