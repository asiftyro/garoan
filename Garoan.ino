#include "Garoan.h"

// left wheel motor pins
#define PIN_LEFT_MOTOR_EN   44
#define PIN_LEFT_MOTOR_OUT1 42
#define PIN_LEFT_MOTOR_OUT2 43

// right wheel motor pins
#define PIN_RIGHT_MOTOR_EN    45
#define PIN_RIGHT_MOTOR_OUT1  41
#define PIN_RIGHT_MOTOR_OUT2  40

#define MOTOR_PWM_MIN 110
#define MOTOR_PWM_MAX 255

//init
Garoan garoan(
  PIN_LEFT_MOTOR_EN,
  PIN_LEFT_MOTOR_OUT1,
  PIN_LEFT_MOTOR_OUT2,
  PIN_RIGHT_MOTOR_EN,
  PIN_RIGHT_MOTOR_OUT1,
  PIN_RIGHT_MOTOR_OUT2,
  MOTOR_PWM_MIN,
  MOTOR_PWM_MAX
);

void setup()
{
  garoan.setDirection(G_LEFT);
  garoan.setSpeed(G_SLOW);
  delay(1500);
  
  garoan.setSpeed(G_FAST);
  delay(1500);
  
  garoan.recallLastSpeed();
  delay(1500);
  
  garoan.setDirection(G_RIGHT);
  delay(1500);
  
  garoan.recallLastDirection();
  delay(1500);
  
  garoan.kill();
  delay(3000);
  
  garoan.recallLast();
  delay(3000);
  garoan.kill();
}

void loop()
{
  // ...
}
