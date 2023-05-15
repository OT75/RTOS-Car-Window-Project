#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "DataTypes.h"


#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5

#define IN  0
#define OUT 1

void DIO_Init(int port, int pin, int dir);
void DIO_WritePin( int port, int pin, int value);
void DIO_WritePort(int port, int32 value);

int32 DIO_ReadPin(int port, int pin);
int32 DIO_ReadPort(int port);