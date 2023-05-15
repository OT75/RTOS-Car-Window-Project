#ifndef __L298N_H__
#define __L298N_H__

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"

// Define L298N input pins and port
#define IN1_PIN         GPIO_PIN_2
#define IN2_PIN         GPIO_PIN_3
#define IN_PORT         GPIO_PORTA_BASE

// Initialize PWM for driving motor
void Motor_Init(void);

// Initialize GPIO pins for L298N inputs
void L298N_Init(void);

// Move motor forward
void L298N_MoveForward(void);

// Move motor backward
void L298N_MoveBackward(void);

// Stop motor
void L298N_Stop(void);

#endif // __L298N_H__
