
#include "stm32_f401re.h"
#include "stm32f401xx_GPIO_drive.h"
#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	for (uint32_t i= 0; i <500000/2 ; i++);
}

int main(void)
{
	GPIO_Handle_t Gpio_Board_Switch;
	GPIO_Handle_t Gpio_BOARD_LED;


	/* --- Configure PA5 as output (controlled by PA7) --- */
	Gpio_BOARD_LED.pGPIOx = GPIOA;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /* --- Configure PC13 as input (Switch connected to baord) --- */
    Gpio_Board_Switch.pGPIOx = GPIOC;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;



	GPIO_PeripheralClockControl(GPIOA, ENABLE);
	GPIO_PeripheralClockControl(GPIOC, ENABLE);


	GPIO_Init(&Gpio_Board_Switch);
	GPIO_Init(&Gpio_BOARD_LED);



	while(1)
	{

		if (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13) == BTN_PRESSED)
		{
			delay();
			GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);

		}
	}
	return 0;
}
