# STM32F4 GPIO LED Control Using Button Input

This project demonstrates how to control an LED connected to an STM32F4 microcontroller using a push button. The LED turns ON when the button is pressed and turns OFF when the button is released. This example uses direct register programming without any HAL libraries.

---

## Description

- Enables the clock for GPIOA (LED port) and GPIOC (Button port) using the RCC AHB1 peripheral clock register.
- Configures PA5 as output (LED pin).
- Configures PC13 as input (User button pin).
- When the button (PC13) is pressed, the LED on PA5 lights up.
- When the button is released, the LED turns off.

---

## Hardware Setup

- **LED** connected to **PA5** (typically onboard LED on Nucleo or Discovery boards).
- **Push Button** connected to **PC13** (User button on many STM32 boards).

Make sure to connect the LED and button according to these pins or modify the pin definitions in the code accordingly.

---

## Code Highlights

- `GPIOAEN` and `GPIOCEN` enable clocks for GPIOA and GPIOC.
- `PIN5` and `PIN13` macros define the LED and Button pins.
- The `delay()` function provides a simple software delay (not used in main loop but can be used if needed).
- Uses GPIO port input data register (IDR) to read button state.
- Uses GPIO port bit set/reset register (BSRR) to set/reset LED output pin.

---

## How to Build and Run

1. Clone this repository to your local machine.
2. Open the project in your preferred IDE that supports STM32 development (e.g., STM32CubeIDE, Keil uVision, or SW4STM32).
3. Compile and flash the firmware to your STM32F4 microcontroller.
4. Press the button connected to PC13 to turn on the LED on PA5.

---

## Source Code

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
RCC->AHB1ENR |= GPIOAEN; // Enable GPIOA clock
RCC->AHB1ENR |= GPIOCEN; // Enable GPIOC clock
// Configure PC13 as input (button)
GPIOC->MODER &= ~(1U << 26);
GPIOC->MODER &= ~(1U << 27);

// Configure PA5 as output (LED)
GPIOA->MODER |= (1U << 10);
GPIOA->MODER &= ~(1U << 11);

while(1) {
    if(GPIOC->IDR & BTN_PIN) {
        GPIOA->BSRR = PIN5;  // Set PA5 (turn ON LED)
    }
    else {
        GPIOA->BSRR = (1U << (5 + 16)); // Reset PA5 (turn OFF LED)
    }
}
## Acknowledgments

- STM32F4 Hardware Manual
- STM32F4 Reference Manual
- ARM Cortex-M4 Programming Resources

---

Feel free to modify and expand this project according to your needs!
