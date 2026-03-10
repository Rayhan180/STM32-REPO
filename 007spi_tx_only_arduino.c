#include "stm32_f401re.h"
#include "stm32f4_01SPI_driver.h"
#include "stm32f401xx_GPIO_drive.h"
#include <string.h>

//extern void initialise_monitor_handles(void);


#define LOW  0
#define BTN_PRESSED  LOW

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
    SPI_SSOEConfig(SPI2, ENABLE); // Enable NSS output

//    // <--- SOFTWARE NSS FOR DEBUGGING --->
//    SPI2Handle.SPI_Config.SPI_SSM  = SPI_SSM_EN;   // software NSS
//    SPI_Init(&SPI2Handle);                          // initialize SPI
//    SPI_SSIConfig(SPI2, ENABLE);                    // internal NSS high
//    SPI_SSOEConfig(SPI2, DISABLE);                  // disable hardware NSS

}

void GPIO_ButtonInit(void) {
    GPIO_PeripheralClockControl(GPIOC, ENABLE);
    GPIO_Handle_t button;
    button.pGPIOx = GPIOC;
    button.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    button.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    button.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
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

int main(void) {
    char user_data[] = "Hello World";
    uint8_t dataLen = strlen(user_data);

//	initialise_monitor_handles();  // <-- Enable semihosting


    SPI2_GPIOInits();
    SPI2_Inits();
    GPIO_ButtonInit();
    GPIO_LED_Board();

    //printf("Semihosting is working!\n");

    while (1) {
        if (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13) == BTN_PRESSED) {
            delay(); // debounce
            GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);

            SPI_PeripheralControl(SPI2, ENABLE);

            // Send length first
            SPI_SendData(SPI2, &dataLen, 1);

            // Send actual message
            SPI_SendData(SPI2, (uint8_t*)user_data, dataLen);

            uint8_t dummy;
            while (SPI_GetFlagStatus(SPI2, SPI_SR_RXNE)) {
                dummy = SPI2->DR;   // read and discard
                (void)dummy;
            }

            if (SPI2->SR & (1 << 6)) { // OVR = bit 6
                uint8_t temp;
                temp = SPI2->DR;        // read DR first
                temp = SPI2->SR;        // then read SR
                (void)temp;             // prevent compiler warning
            }


            while (SPI_GetFlagStatus(SPI2, SPI_SR_BSY)); // wait until not busy

            SPI_PeripheralControl(SPI2, DISABLE);

            // wait until button released
            while (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_13) == BTN_PRESSED);
        }
    }

    return 0;
}
