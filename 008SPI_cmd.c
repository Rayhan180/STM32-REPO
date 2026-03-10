/*
 * 008SPI_cmd.c
 *
 *  Created on: Nov 2, 2025
 *      Author: MZH9PH
 */


#include "stm32_f401re.h"
#include "stm32f4_01SPI_driver.h"
#include "stm32f401xx_GPIO_drive.h"
#include <string.h>


#define COMMAND_LED_CTRL       0x50
#define COMMAND_SENSOR_READ    0x51
#define COMMAND_LED_READ       0x52
#define COMMAND_PRINT          0x53
#define COMMAND_ID_READ        0x54

#define LED_ON			1
#define LED_OFF			0

#define ANALOG_PIN0   0
#define ANALOG_PIN1   1
#define ANALOG_PIN2   2
#define ANALOG_PIN3   3
#define ANALOG_PIN4   4

#define LED_PIN			9  // ARDUINO LED

#define LOW  0
#define BTN_PRESSED  LOW

uint8_t ackbyte;

void SPI2_GPIOInits(void);
void SPI2_Inits(void);
void GPIO_ButtonInit(void);
void GPIO_LED_Board(void);
void delay(void);

void SPI2_GPIOInits(void) {
    GPIO_Handle_t SPIPins;

    GPIO_PeripheralClockControl(GPIOB, ENABLE);  // <-- Missing line

    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    // SCK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GPIO_Init(&SPIPins);

    // MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_14;
    GPIO_Init(&SPIPins);

    // MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_15;
    GPIO_Init(&SPIPins);

    // NSS
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
    GPIO_Init(&SPIPins);
}

void SPI2_Inits(void) {
    SPI_Handle_t SPI2Handle;
    SPI2Handle.pSPIx = SPI2;
    SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI2Handle.SPI_Config.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI2Handle.SPI_Config.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8; // 1 MHz
    SPI2Handle.SPI_Config.SPI_DFF = SPI_DFF_8BITS;
    SPI2Handle.SPI_Config.SPI_CPOL = SPI_CPOL_LOW;
    SPI2Handle.SPI_Config.SPI_CPHA = SPI_CPHA_LOW;
    SPI2Handle.SPI_Config.SPI_SSM  = SPI_SSM_DI; // Hardware NSS
    SPI_Init(&SPI2Handle);
}

void GPIO_ButtonInit(void) {
    GPIO_PeripheralClockControl(GPIOC, ENABLE);
    GPIO_Handle_t button;
    button.pGPIOx = GPIOC;
    button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_Init(&button);
}

void GPIO_LED_Board(void) {
    GPIO_PeripheralClockControl(GPIOA, ENABLE);
    GPIO_Handle_t led;
    led.pGPIOx = GPIOA;
    led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIO_Init(&led);
}

void delay(void) {
    for (uint32_t i = 0; i < 500000; i++);
}

uint8_t SPY_Verify_Response (){
	if (ackbyte == 0xF5)
	{
		return 1;
	}
	return 0;


}

int main(void) {

	uint8_t dumm_write = 0xff;
	uint8_t args[2];
	uint8_t dummy_read;

    SPI2_GPIOInits();
    SPI2_Inits();
    GPIO_ButtonInit();
    GPIO_LED_Board();

    SPI_SSOEConfig(SPI2, ENABLE); // Enable NSS output

    while (1) {
        if (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13) == BTN_PRESSED) {  // button pressed will make the reg 0
            delay(); // debounce
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5); // toggle stm32 board pin

            //printf("Button pressed! Starting SPI communication...\n");

            SPI_PeripheralControl(SPI2, ENABLE);  // enable spi peripheral

            //printf("SPI2 Peripheral Enabled.\n");

            uint8_t commandcode_led = COMMAND_LED_CTRL; // 0X50 IS assigning to unsigned 8-bit integer (a byte).

            SPI_SendData(SPI2, &commandcode_led, 1);

            //printf("Command 0x%x sent to slave.\n", commandcode_led);

            delay(); // debounce

            // Check NSS after send
            //uint8_t nss_state_during = GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_12);
           // printf("During send - NSS state: %d\n", nss_state_during);

            SPI_ReceiveData(SPI2, &dummy_read, 1); // by reading clear off the rxne

            SPI_SendData(SPI2, &dumm_write, 1); // send some dummy bits (1 byte) to fetch the response from the slave

            SPI_ReceiveData(SPI2, &ackbyte, 1);

            //printf("ACK byte received: 0x%x\n", ackbyte);

            if (SPY_Verify_Response (ackbyte)){
            	// send arguments
            	args [0] = LED_PIN;  // arduino 9 pin
            	args [1] = LED_ON;

            	SPI_SendData(SPI2, args, 2);

            	//printf("Arguments sent: LED_PIN=%d, LED_ON=%d\n", args[0], args[1]);
            }

            else {
                      // printf("Invalid ACK response: 0x%x\n", ackbyte);
                   }


            while (SPI_GetFlagStatus(SPI2, SPI_SR_BSY)); // wait until not busy

            SPI_PeripheralControl(SPI2, DISABLE);

            // wait until button released
            while (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13) == BTN_PRESSED);
        }
    }

    return 0;
}
