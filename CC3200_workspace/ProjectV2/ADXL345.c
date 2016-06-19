/*
 * ADXL345.c
 *
 *  Created on: Jun 6, 2016
 *      Author: Rafi
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <integer.h>

#include "i2c_if.h"
#include "utils.h"

int init_ADXL345(char addr)
{
	unsigned char data[2];
	data[0] = 0x2d;
	data[1] = 0x08;
	if(I2C_IF_Write(addr, data, 2, true)<0)	return -1;
	return 0;
}



int ADXL345_read_accdata(char addr, float* Xacc, float* Yacc, float* Zacc)
{
	unsigned char data[2];
	unsigned char rdata[10];
	SHORT Xdata, Ydata, Zdata;

	data[0] = 0x32;
	if(I2C_IF_Write(addr, data, 1, false)<0)	return -1;
	if(I2C_IF_Read(addr, rdata, 6)<0)			return -1;

	Xdata = (int)rdata[1];
	Xdata <<=8;
	Xdata += (int)rdata[0];

	Ydata = (int)rdata[3];
	Ydata <<=8;
	Ydata += (int)rdata[2];

	Zdata = (int)rdata[5];
	Zdata <<=8;
	Zdata += (int)rdata[4];

	*Xacc = Xdata;
	*Yacc = Ydata;
	*Zacc = Zdata;


	return 0;
}
