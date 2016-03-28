#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_i2c.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

#define     N   100

char Buff[N];
char Data[6][N];

int flgNewGPSstring = 0;
int flgSendAcc = 0;

void newchar(char x);
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count);
void writedata(int n);
int search(char arr[], int size, char x, int end);


void newchar(char x)
{
	static int wrtptr=0;
	wrtptr = wrtptr%N;
	if(x=='$')	wrtptr=0;
	Buff[wrtptr] = x;
	if (x=='\r')    writedata(wrtptr);
	wrtptr++;
}

void writedata(int n)
{
	int c=0;
	int i=0;
	int ind = 0;
	if(Buff[0]!='$') return;

	if(strstr(Buff,"$GPRMC")!=NULL)			ind=0;
	else if(strstr(Buff,"$GPVTG")!=NULL)	ind=1;
	else if(strstr(Buff,"$GPGGA")!=NULL)	ind=2;
	else if(strstr(Buff,"$GPGSA")!=NULL)	ind=3;
	else if(strstr(Buff,"$GPGSV")!=NULL)	ind=4;
	else if(strstr(Buff,"$GPGLL")!=NULL)	ind=5;
	else return;

	while(Buff[i%N]!='\r')
	{
		Data[ind][c++] = Buff[(i++)%N];
		Data[ind][c] = 0;
		if(i==n) break;
	}
	flgNewGPSstring = 1;
}



void UART1IntHandler(void)
{
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART1_BASE, true);
	UARTIntClear(UART1_BASE, ui32Status);

	while(UARTCharsAvail(UART1_BASE))
	{
		int d=UARTCharGetNonBlocking(UART1_BASE);
		if(d=='\r') UARTCharPutNonBlocking(UART1_BASE, '\n');
		UARTCharPutNonBlocking(UART1_BASE, d);

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
		SysCtlDelay(SysCtlClockGet() / (1000 * 3));
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
	}
}


void UART5IntHandler(void)
{
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART5_BASE, true);
	UARTIntClear(UART5_BASE, ui32Status);


	while(UARTCharsAvail(UART5_BASE))
	{
		int d=UARTCharGet(UART5_BASE);
		//UARTCharPut(UART1_BASE, d);
		newchar(d);

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
		SysCtlDelay(SysCtlClockGet() / (1000 * 3));
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);

	}
}



//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
	//
	// Loop while there are more characters to send.
	//
	while(ui32Count--)
	{
		while(UARTSpaceAvail(UART1_BASE)==false)
		{

		}
		//
		// Write the next character to the UART.
		//
		UARTCharPut(UART1_BASE, *pui8Buffer++);
	}
}

//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************
int main(void)
{
	FPUEnable();
	FPULazyStackingEnable();


	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
			SYSCTL_XTAL_16MHZ);


	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);


	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);


	IntMasterEnable();


	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PB1_U1TX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	GPIOPinConfigure(GPIO_PE4_U5RX);
	GPIOPinConfigure(GPIO_PE5_U5TX);
	GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);


	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
					UART_CONFIG_PAR_NONE));

	UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), 9600,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
					UART_CONFIG_PAR_NONE));


	IntEnable(INT_UART1);
	UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

	IntEnable(INT_UART5);
	UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);
	//UARTSend((uint8_t *)"\033[2JEnter text: ", 16);


	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);


	GPIOPinConfigure(GPIO_PA6_I2C1SCL);
	GPIOPinConfigure(GPIO_PA7_I2C1SDA);
	GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
	GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);

	I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), false);



	int i;
	int16_t Xacc, Yacc, Zacc;
	char string[50];

	I2CMasterSlaveAddrSet(I2C1_BASE, 0x53, false);
	I2CMasterDataPut(I2C1_BASE, 0x2D);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C1_BASE))
	{
	}
	I2CMasterDataPut(I2C1_BASE, 0x08);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C1_BASE))
	{
	}

	I2CMasterSlaveAddrSet(I2C1_BASE, 0x53, false);
	I2CMasterDataPut(I2C1_BASE, 0x31);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C1_BASE))
	{
	}
	I2CMasterDataPut(I2C1_BASE, 0x03);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C1_BASE))
	{
	}

	I2CMasterSlaveAddrSet(I2C1_BASE, 0x53, false);
	I2CMasterDataPut(I2C1_BASE, 0x38);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	while(I2CMasterBusy(I2C1_BASE))
	{
	}
	I2CMasterDataPut(I2C1_BASE, 0x00);
	I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
	while(I2CMasterBusy(I2C1_BASE))
	{
	}
	//SysCtlDelay(SysCtlClockGet()/30);



	while(1)
	{
		flgSendAcc=flgSendAcc+1;//flgNewGPSstring;
		if(flgNewGPSstring!=0)
		{
			for(i=0; i<6;i++)
			{
				UARTSend((uint8_t *)Data[i], strlen(Data[i]));
				UARTCharPut(UART1_BASE, '\n');
			}
			flgNewGPSstring=0;
		}


		if(flgSendAcc%5==0)
		{
			I2CMasterSlaveAddrSet(I2C1_BASE, 0x53, false);
			I2CMasterDataPut(I2C1_BASE, 0x32);
			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			I2CMasterSlaveAddrSet(I2C1_BASE, 0x53, true);
			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			Xacc=I2CMasterDataGet(I2C1_BASE);

			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			Xacc+=I2CMasterDataGet(I2C1_BASE)<<8;

			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			Yacc=I2CMasterDataGet(I2C1_BASE);

			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			Yacc+=I2CMasterDataGet(I2C1_BASE)<<8;

			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			Zacc=I2CMasterDataGet(I2C1_BASE);

			I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
			while(I2CMasterBusy(I2C1_BASE))
			{
			}
			Zacc+=I2CMasterDataGet(I2C1_BASE)<<8;

			sprintf(string, "\nAx=%d, Ay=%d, Az=%d\n", Xacc+48, Yacc+20, Zacc-114);
			UARTSend((uint8_t *)string, strlen(string));

			//flgSendAcc = 0;
			SysCtlDelay(SysCtlClockGet()/30);
		}
	}
}
