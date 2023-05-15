#include "motor.h"

void Motor_Init(void) {

SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);

// Wait until PWM1 peripheral is enabled
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1));

// Set PWM frequency to 1 kHz
PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, SysCtlClockGet() / 1000);

// Initialize PWM duty cycle to 0%
PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 0);
PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
PWMGenEnable(PWM1_BASE,PWM_GEN_3);

}

void L298N_Init(void) {
    // Enable the GPIO port that is used for L298N inputs
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the GPIO pins for L298N inputs as outputs
    GPIOPinTypeGPIOOutput(IN_PORT, IN1_PIN | IN2_PIN);

    // Set the initial state of the L298N inputs to stop the motor
    GPIOPinWrite(IN_PORT, IN1_PIN | IN2_PIN, 0);
}

void L298N_MoveForward(void) {
    // Set IN1 to high and IN2 to low to move the motor forward
    GPIOPinWrite(IN_PORT, IN1_PIN, IN1_PIN);
    GPIOPinWrite(IN_PORT, IN2_PIN, 0);
}

void L298N_MoveBackward(void) {
    // Set IN1 to low and IN2 to high to move the motor backward
    GPIOPinWrite(IN_PORT, IN1_PIN, 0);
    GPIOPinWrite(IN_PORT, IN2_PIN, IN2_PIN);
}

void L298N_Stop(void) {
    // Set IN1 and IN2 to low to stop the motor
    GPIOPinWrite(IN_PORT, IN1_PIN | IN2_PIN, 0);
}
