#include "buttons.h"



// Initialize GPIO pins for driver and passenger push buttons
void PushButton_Init(void) {
    // Enable the GPIO port E peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    
    // Wait for the GPIO port E peripheral to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));
    
    // Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Enable the interrupt for pin PE4
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_4);
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
	
	// Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_5);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Enable the interrupt for pin PE4
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_5);
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_FALLING_EDGE);
		
		    // Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Enable the interrupt for pin PE4
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_2);
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);
	
	// Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Enable the interrupt for pin PE4
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_1);
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_FALLING_EDGE);
    
    // Enable the interrupt at the NVIC level
    IntEnable(INT_GPIOE);
		
}

void on_off_init(){
    // Enable the GPIO port D peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    // Wait for the GPIO port D peripheral to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));

    // Configure pin PD0 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Enable the interrupt for pin PD0
    GPIOIntEnable(GPIO_PORTD_BASE, GPIO_INT_PIN_0);
    GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_BOTH_EDGES);


    // Enable the interrupt at the NVIC level
    IntEnable(INT_GPIOD);
}

void lock_init(){
    // Enable the GPIO port D peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    // Wait for the GPIO port D peripheral to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));
    // Enable the GPIO port D peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Wait for the GPIO port D peripheral to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

		
		    // Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    

	// Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	
	
	// Configure pin PE4 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_6);
    GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

/*void on_off_init(){
    // Enable the GPIO port B peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Wait for the GPIO port B peripheral to be ready
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

    // Configure pin PB2 as an input with a pull-up resistor
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Enable the interrupt for pin PB2
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_INT_PIN_2);
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_BOTH_EDGES);

    // Enable the interrupt at the NVIC level
    IntEnable(INT_GPIOB);
}
*/