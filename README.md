# Garoan

An Arduino Library for two motor tracked wheel differential drive robot movement by L293D dual H-bridge motor driver IC.

#### Usage
```cpp
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

void setup() {
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

void loop() {
  // ...
}
```

#### API

##### Constructor

```cpp
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
```

##### Methods

Following methods set direction of robot. Direction can be forward, backward, left, right or "none".

```cpp
void directionForward();
void directionBackward();
void directionLeft();
void directionRight();
void directionNone();
void setDirection(DIRECTIONS direction);
```



Following methods sets speed of motor. Speed can be slow, normal, fast or "zero"

```cpp
void setSpeed(SPEEDS speed);
```


Following methods are used to recall last speed, direction or both.

```cpp
void recallLastDirection();
void recallLastSpeed();
void recallLast();
```

Method to clear current direction and speed.

```cpp
void kill();
```

These methods return current status.

```cpp
enum SPEEDS getCurrentSpeed();
enum DIRECTIONS getCurrentDirection();
bool isMoving();
```

**Data types**

```cpp
enum SPEEDS {
  G_SLOW = 0,
  G_NORMAL = 1,
  G_FAST = 2,
  G_ZERO = _G_NONE
};
```
```cpp
enum DIRECTIONS {
  G_FORWARD = 0,
  G_LEFT = 1,
  G_BACKWARD = 2,
  G_RIGHT = 3,
  G_NONE = _G_NONE
};
```