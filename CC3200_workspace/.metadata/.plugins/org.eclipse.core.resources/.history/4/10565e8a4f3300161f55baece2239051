/*
 * includes.h
 *
 *  Created on: May 23, 2016
 *      Author: Rafi
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// SimpleLink includes
#include "simplelink.h"
#include "ff.h"

// driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_common_reg.h"
#include "hw_apps_rcm.h"
#include "rom.h"
#include "pin.h"
#include "rom_map.h"
#include "prcm.h"
#include "sdhost.h"

#include "utils.h"
#include "interrupt.h"
#include "gpio.h"
#include "spi.h"


// common interface includes
#include "uart_if.h"
#include "gpio_if.h"
#include "i2c_if.h"
#include "common.h"
#include "pinmux.h"


// HTTP Client lib
#include <http/client/httpcli.h>
#include <http/client/common.h>

// JSON Parser
#include "jsmn.h"

#define READ_SIZE           1450
#define MAX_BUFF_SIZE       1460

extern volatile unsigned long  g_ulStatus;//SimpleLink Status
extern unsigned long  g_ulDestinationIP; // IP address of destination server
extern unsigned long  g_ulGatewayIP; //Network Gateway IP address
extern unsigned char  g_ucConnectionSSID[SSID_LEN_MAX+1]; //Connection SSID
extern unsigned char  g_ucConnectionBSSID[BSSID_LEN_MAX]; //Connection BSSID
extern unsigned char g_buff[MAX_BUFF_SIZE+1];
extern long bytesReceived; // variable to store the file size

// Aplication Specific
#include "parameters.h"
#include "SimpleLinkFunctions.h"


#include "HMC5883.h"
#include "ADXL345.h"
#include "IMU.h"



#endif /* INCLUDES_H_ */
