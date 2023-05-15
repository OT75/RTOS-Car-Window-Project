#include "semph.h"


void Semph_Init(void) {
	vSemaphoreCreateBinary( xManualDownSemaphore );
	vSemaphoreCreateBinary( xAutoDownSemaphore );
	vSemaphoreCreateBinary( xManualUpSemaphore );
	vSemaphoreCreateBinary( xAutoUpSemaphore );
	vSemaphoreCreateBinary( xlockSemaphore );


}