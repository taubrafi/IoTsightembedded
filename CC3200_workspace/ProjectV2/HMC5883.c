/*
 * HMC5883.c
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

SHORT Xmcal=400, Ymcal=400, Zmcal=400;
SHORT Xmoff=0, Ymoff=0, Zmoff=0;


int init_HMC5883(char addr, char cal)
{
	unsigned char data[5];
	unsigned char rdata[10];

	I2C_IF_Open(I2C_MASTER_MODE_STD);

	if(cal)
	{
		data[0] = 0x00;
		data[1] =  0x71;
		data[2] =  0xA0;
		data[3] =  0x00;
		if(I2C_IF_Write(addr, data, 4, true) < 0) 	return -1;
		UtilsDelay(2000000); //75ms delay

		data[0] = 0x00;
		if(I2C_IF_Write(addr, data, 1, false)<0)	return -1;
		if(I2C_IF_Read(addr, rdata, 9)<0)			return -1;

		Xmcal = (int)rdata[3];
		Xmcal <<=8;
		Xmcal += (int)rdata[4];

		Zmcal = (int)rdata[5];
		Zmcal <<=8;
		Zmcal += (int)rdata[5];

		Ymcal = (int)rdata[7];
		Ymcal <<=8;
		Ymcal += (int)rdata[8];
	}
	else
	{
		Xmcal=400;
		Ymcal=400;
		Zmcal=400;

	}

	data[0] = 0x00;
	data[1] =  0x70;
	data[2] =  0xA0;
	data[3] =  0x00;
	if(I2C_IF_Write(addr, data, 4, true) < 0)	return -1;
	UtilsDelay(2000000); //75ms delay

	return 0;
}



int HMC5883_read_magdata(char addr, float* Xmag, float* Ymag, float* Zmag)
{
	unsigned char data[2];
	unsigned char rdata[10];
	SHORT Xdata, Ydata, Zdata;

	data[0] = 0x00;
	if(I2C_IF_Write(addr, data, 1, false)<0)	return -1;
	if(I2C_IF_Read(addr, rdata, 9)<0)			return -1;

	Xdata = (int)rdata[3];
	Xdata <<=8;
	Xdata += (int)rdata[4];

	Ydata = (int)rdata[7];
	Ydata <<=8;
	Ydata += (int)rdata[8];

	Zdata = (int)rdata[5];
	Zdata <<=8;
	Zdata += (int)rdata[5];

	*Xmag = (float)(Xdata-Xmoff) / Xmcal;
	*Ymag = (float)(Ydata-Ymoff) / Ymcal;
	*Zmag = (float)(Zdata-Zmoff) / Zmcal;

	return 0;
}



