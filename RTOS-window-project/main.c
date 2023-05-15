#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "DIO.h"
#include <stdint.h>
#include "FreeRTOSConfig.h"
#include "DataTypes.h"
#include <stdio.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include <stdbool.h>
#include <stdlib.h>
#include "driverlib/pwm.h"
#include "buttons.h"
#include "motor.h"
#include "semph.h"

 
#define mainSW_INTURRUPT_ID ((IRQn_Type)0)
#define mainSW_INTURRUPT_PortF ((IRQn_Type)30)
#define mainSW_INTURRUPT_PortE ((IRQn_Type)4)

#define mainSW_INTURRUPT_PortD ((IRQn_Type)3)
int switchState=0;


xSemaphoreHandle xBinarySemaphore;
QueueHandle_t uCountingQueue;
uint8_t arr[20]={};
int index = 0;
xSemaphoreHandle xMutexLock;
xSemaphoreHandle xManualDownSemaphore;
xSemaphoreHandle xAutoDownSemaphore;
xSemaphoreHandle xManualUpSemaphore;
xSemaphoreHandle xlockSemaphore;
xSemaphoreHandle xAutoUpSemaphore;
unsigned portBASE_TYPE uxPriorityManualUp;
unsigned portBASE_TYPE uxPriorityManualDown;
TaskHandle_t xTaskHandleManualUp;
TaskHandle_t xTaskHandleManualDown;
volatile bool up = false;
volatile bool down = false;
volatile bool locked = false;
volatile bool upBefore = false;
volatile bool downBefore = false;
volatile bool fromDriver = false;
volatile bool end = false;

	
#define GPIO_PD0_MOTOR_LIMIT_SW1     0x00000001
#define GPIO_PD1_MOTOR_LIMIT_SW2     0x00000002

	
void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}



static void vTask1(void *pvParameters){
	while(1){
		for(int i = 0 ; i <10; i++){
			//xQueueSendToBack(uCountingQueue,&i +1, 0);
		}
	}
}

//----------------------------------------------------Manual Up Driver----------------------------------------------------
void vWindowUpDriver(){
  xSemaphoreTake( xManualUpSemaphore, 0 );
	while(1){
  xSemaphoreTake( xManualUpSemaphore, portMAX_DELAY );
	{	

			while(((((GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) == 0x00)&&locked==false)||(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) == 0x00&&fromDriver==true&&locked==true))||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x00) &&(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5)!= 0x00)){
				xSemaphoreTake( xMutexLock, portMAX_DELAY );
				if(down==true) {
					up = false;
					xSemaphoreGive( xMutexLock );
          L298N_Stop(); // Stop motor if down button is pressed
          Delay_ms(500);
          break;
        }
				L298N_MoveForward();
				xSemaphoreGive( xMutexLock );
			}
			  GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2 | GPIO_INT_PIN_3 | GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
				L298N_Stop();
	}
			Delay_ms(1000);
		fromDriver=false;
	GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2 | GPIO_INT_PIN_3 | GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);

	}
}

//----------------------------------------------------Manual Down Driver----------------------------------------------------
void vWindowDownDriver(){
  xSemaphoreTake( xManualDownSemaphore, 0 );
	while(1){
  xSemaphoreTake( xManualDownSemaphore, portMAX_DELAY );
	{	

			while(((((GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) == 0x00)&&locked==false)||(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) == 0x00&&fromDriver==true&&locked==true))||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0x00)/*&&(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4)!= 0x00)*/){
				xSemaphoreTake( xMutexLock, portMAX_DELAY );
				if(up==true) {
					down = false;
					xSemaphoreGive( xMutexLock );
          L298N_Stop(); // Stop motor if down button is pressed
          Delay_ms(500);
          break;
        }
				L298N_MoveBackward();
				xSemaphoreGive( xMutexLock );
			}
				GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2 | GPIO_INT_PIN_3 | GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
				L298N_Stop();
	}
	Delay_ms(1000);
	fromDriver=false;
	GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2 | GPIO_INT_PIN_3 | GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
	}
}

//----------------------------------------------------Auto Up Driver----------------------------------------------------
void vAutoUpDriver(){
  xSemaphoreTake( xAutoUpSemaphore, 0 );
	while(1) {
    xSemaphoreTake( xAutoUpSemaphore, portMAX_DELAY );
    {	 
      while((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) != 0x00) && ((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) != 0x00)&&locked==false)||(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) != 0x00) && ((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) != 0x00)&&fromDriver==true&&locked==true)) {
			xSemaphoreTake( xMutexLock, portMAX_DELAY );
        if(down==true) {
					up = false;
					xSemaphoreGive( xMutexLock );
          L298N_Stop(); // Stop motor if down button is pressed
          Delay_ms(500);
          break;
        }
        L298N_MoveForward();
			xSemaphoreGive( xMutexLock );
				
			      //jamming control
      if(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) == 0x00){
        L298N_Stop();
        Delay_ms(500);
        L298N_MoveBackward();
				if((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) == 0x00)){
				L298N_Stop();
				break;
				}
        Delay_ms(1000);
				L298N_Stop();
				break;
      }
      }
   
      L298N_Stop();
			    Delay_ms(500);
		up = false;
		upBefore=false;
		fromDriver=false;
    }
	}

}



//----------------------------------------------------Auto Down Driver----------------------------------------------------
void vAutoDownDriver(){
  xSemaphoreTake( xAutoDownSemaphore, 0 );
	while(1){
  xSemaphoreTake( xAutoDownSemaphore, portMAX_DELAY );
  {	 
			while(((GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2)!= 0x00)&&locked==false)||(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2)!= 0x00&&fromDriver==true&&locked==true)){
			xSemaphoreTake( xMutexLock, portMAX_DELAY );
          if(up==true) {
					down = false;
					xSemaphoreGive( xMutexLock );
          L298N_Stop(); // Stop motor if down button is pressed
          Delay_ms(500);
          break;
        }
		  L298N_MoveBackward();
			xSemaphoreGive( xMutexLock );
							      //jamming control
      if(GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_6) == 0x00){
        L298N_Stop();
        Delay_ms(500);
        L298N_MoveForward();
				if((GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_5) == 0x00)){
				L298N_Stop();
				break;
				}
        Delay_ms(500);
				break;
      }
			}
      L298N_Stop();
  }
	
		down=false;
		downBefore=false;
		Delay_ms(500);
		fromDriver=false;
//clear

}
}

//----------------------------------------------------locktask----------------------------------------------------
void vlockTask(){
  xSemaphoreTake( xlockSemaphore, 0 );
	while(1){
  xSemaphoreTake( xlockSemaphore, portMAX_DELAY );
  {	
		xSemaphoreTake( xMutexLock,portMAX_DELAY);
      // Clear the interrupt flag
    GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_0);
		
    if(locked==true){
			locked=false;
		}
		else{
			locked=true;
		}
			xSemaphoreGive( xMutexLock );
  }

}
}

//----------------------------------------------------Buttons ISR----------------------------------------------------
void GPIOE_Handler(void)
{   
    GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2 | GPIO_INT_PIN_3 | GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);
		GPIOIntClear(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2 | GPIO_INT_PIN_3 | GPIO_INT_PIN_4 | GPIO_INT_PIN_5 | GPIO_INT_PIN_6 | GPIO_INT_PIN_7);

		portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) == 0x00 ||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0x00) /* check if interrupt causes by PF4/SW1*/
    {   
			if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0x00){
						fromDriver=true;
					}
				Delay_ms(100);
			if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) == 0x00 ||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0x00)
			{Delay_ms(250);
        // Check if switch was pushed or pulled shortly
        if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4) == 0x00||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0x00) {
					if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) == 0x00){\
					}
            // Normal window down command
					xSemaphoreGiveFromISR( xManualDownSemaphore,&xHigherPriorityTaskWoken );
  
        } else {
					down=true;
					// Fully close the window
					if(!downBefore){
					downBefore=true;
          xSemaphoreGiveFromISR( xAutoDownSemaphore,&xHigherPriorityTaskWoken );
					}
        }
				
    } }
    else if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) == 0x00||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x00) /* check if interrupt causes by PF0/SW2 */
     {   Delay_ms(100);
if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) == 0x00||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x00)
				{
					if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x00){
						fromDriver=true;
					}
						Delay_ms(500);
        // Check if switch was pushed or pulled shortly
        if (GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5) == 0x00||GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x00) {
					if(GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) == 0x00){\
				}
            
            // Normal window up command
					xSemaphoreGiveFromISR( xManualUpSemaphore,&xHigherPriorityTaskWoken );

            
        } else {
					up = true;
					//if var =false
            // Fully open the window
					if(!upBefore){
					upBefore=true;
          xSemaphoreGiveFromISR( xAutoUpSemaphore,&xHigherPriorityTaskWoken );
					}
					
        }
				
    }}
 
    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

//----------------------------------------------------Lock ISR----------------------------------------------------
void GPIOD_Handler(void)
{				
	    GPIOIntClear(GPIO_PORTD_BASE, GPIO_INT_PIN_0 );
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR( xlockSemaphore,&xHigherPriorityTaskWoken );
		    portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

//maximum limit
//jamming should not exceed limit
//driver lock

//----------------------------------------------------MAIN----------------------------------------------------
int main( void )
{
	PushButton_Init();
	on_off_init();
	L298N_Init();
	lock_init();
	NVIC_SetPriority(mainSW_INTURRUPT_PortE,6);
	NVIC_SetPriority(mainSW_INTURRUPT_PortD,6);
	uCountingQueue = xQueueCreate(10, sizeof(uint8_t));    
	vSemaphoreCreateBinary( xBinarySemaphore );
	Semph_Init();
	xMutexLock = xSemaphoreCreateMutex();
	locked = false;

	/* Check the semaphore was created successfully. */
	if( xMutexLock != NULL )
	{

				xTaskCreate( vWindowDownDriver, "Task2", 240, NULL, 3, &xTaskHandleManualDown );
		
				xTaskCreate( vAutoDownDriver, "Task3", 240, NULL, 4, NULL );
		
				xTaskCreate( vWindowUpDriver, "Task1", 240, NULL, 3, &xTaskHandleManualUp );
		
				xTaskCreate( vAutoUpDriver, "Task4", 240, NULL, 4, NULL );
		
				xTaskCreate( vlockTask, "Task5", 240, NULL, 3, NULL );

        /* Start the scheduler so the created tasks start executing. */
        vTaskStartScheduler();
	for( ;; );

	}
}
void vApplicationIdleHook( void )
{    
    // Enable GPIO port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Configure PF2 as output
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	while(1) {
        // Toggle the blue LED every 1 second
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        Delay_ms(500);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        Delay_ms(500);
    }
}