#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
//to work with interrupts we will use :
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

uint32_t ui32SysClkFreq;

// initialize our  UART interrupt handler

void UARTIntHandler(void)
{
	uint32_t ui32Status;

	ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

	UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts

	while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
	{
		UARTCharPutNonBlocking(UART0_BASE,UARTCharGetNonBlocking(UART0_BASE)); //echo character
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1, 0xFF); 			// LEDs on
		SysCtlDelay(ui32SysClkFreq / (3 * 10)); 							    // delay .1 sec
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1, 0); 				// LEDs off
	}
}

int main(void)
{
// Configure the system clock to run using a 25MHz crystal on the main oscillator, driving the PLL at 480MHz. the system clock we use will be 120MHz.
	ui32SysClkFreq = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
			SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
			SYSCTL_CFG_VCO_480), 120000000);

// Enable the UART0 and GPIOA peripherals (the UART pins are on GPIO Port A) 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
// Configure the pins for the receiver and transmitter
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
// enable the clock for the GPION peripheral.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
// configure the two GPIO pins connected to the D1 and D2 LEDs as outputs
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1);
// Configure the UART baud rate, data configuration as  115200, 8-1-N-N 
	UARTConfigSetExpClk(UART0_BASE, ui32SysClkFreq, 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	IntMasterEnable();        // to enable interrupts
	IntEnable(INT_UART0);     // to enable UART0 interrupts
	UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);  //  select receiver interrupts (RX) and receiver timeout interrupts (RT).

// send chracters to the terminal program
	UARTCharPut(UART0_BASE, 'E');
	UARTCharPut(UART0_BASE, 'n');
	UARTCharPut(UART0_BASE, 't');
	UARTCharPut(UART0_BASE, 'e');
	UARTCharPut(UART0_BASE, 'r');
	UARTCharPut(UART0_BASE, ' ');
	UARTCharPut(UART0_BASE, 'T');
	UARTCharPut(UART0_BASE, 'e');
	UARTCharPut(UART0_BASE, 'x');
	UARTCharPut(UART0_BASE, 't');
	UARTCharPut(UART0_BASE, ':');
	UARTCharPut(UART0_BASE, ' ');

	while (1)
	{
		 // if no using interrupts we can remove the comment signs in the next line
		//		if (UARTCharsAvail(UART0_BASE)) UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));
	}
}
