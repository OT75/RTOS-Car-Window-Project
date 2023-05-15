#ifndef __buttons_H__
#define __buttons_H__

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"


// Initialize GPIO pins for driver and passenger push buttons
void PushButton_Init(void);

// Initialize GPIO pin for on/off switch
void on_off_init(void);

void lock_init(void);

#endif // __MY_GPIO_H__
