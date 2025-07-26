#include "stm32f4xx.h"
#define GPIOAEN (1U<<0)
#define GPIOCEN (1U<<2)
#define PIN5 (1U<<5)
#define LED_PIN PIN5
#define PIN13 (1U<<13)
#define BTN_PIN PIN13

void delay(volatile unsigned int time) {
    while (time--) {
        for (volatile int i = 0; i < 1000; i++) {
            // just waste time
        }
    }
}


int main(void){
RCC->AHB1ENR|=GPIOAEN;
RCC->AHB1ENR|=GPIOCEN;
GPIOC->MODER&=~(1U<<26);
GPIOC->MODER&=~(1U<<27);
GPIOA->MODER|=(1U<<10);
GPIOA->MODER&=~(1U<<11);
while(1){

	if(GPIOC->IDR&BTN_PIN){
	GPIOA->BSRR=PIN5;
	}

	else{
	GPIOA->BSRR=~PIN5;
	}
}
}
