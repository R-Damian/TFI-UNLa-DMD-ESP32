#ifndef LM35_H
#define LM35_H
#include <stdint.h>

typedef struct
{
	void * pAdcTda;
	double (*adcRead)(void *,uint8_t);
	uint8_t adcPin;

}lm35_t;


lm35_t * lm35Init(void * pAdcTda,double (*adcRead)(void *,uint8_t), uint8_t adcPin);
void lm35Destroy(lm35_t * pLm35);
double lm35Read(lm35_t * pLm35);
void lm35GenericRead(void * pLm35, char * buffer, int bufflen);


#endif
