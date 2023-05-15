#include "FreeRTOS.h"
#include "semphr.h"

extern xSemaphoreHandle xManualDownSemaphore;
extern xSemaphoreHandle xAutoDownSemaphore;
extern xSemaphoreHandle xManualUpSemaphore;
extern xSemaphoreHandle xAutoUpSemaphore;
extern xSemaphoreHandle xMutexLock;
extern xSemaphoreHandle xlockSemaphore;
void Semph_Init(void);