#include "lm35.h"
#include "freertos/FreeRTOS.h"
#include <stdio.h>

lm35_t * lm35Init(void * pAdcTda,double (*adcRead)(void *,uint8_t), uint8_t adcPin)
{
	lm35_t * pLm35 = malloc(sizeof(lm35_t));
	pLm35->pAdcTda= pAdcTda;
	pLm35->adcRead= adcRead;
	pLm35->adcPin= adcPin;
	return pLm35;
}


void lm35Destroy(lm35_t * pLm35)
{
	free(pLm35);
}

double lm35Read(lm35_t * pLm35)
{
	return pLm35->adcRead(pLm35->pAdcTda,pLm35->adcPin)*100;

}


void lm35GenericRead(void * pLm35, char * buffer, int bufflen)
{
	double value =  lm35Read(pLm35);
	snprintf(buffer,bufflen,"%f",value);

}
