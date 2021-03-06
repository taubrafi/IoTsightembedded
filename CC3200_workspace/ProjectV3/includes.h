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
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

// SimpleLink includes
#include "simplelink.h"
#include "ff.h"

// driverlib includes
#include "hw_ints.h"
#include "hw_types.h"
#include "hw_gpio.h"
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
#include "i2c.h"
#include "uart.h"


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

extern float Xmax, Ymax, Zmax;
extern float Xmin, Ymin, Zmin;




#define APPLICATION_VERSION "1.1.1"
#define APP_NAME            __TIME__

// Application specific status/error codes
typedef enum{
	/* Choosing this number to avoid overlap with host-driver's error codes */
	DEVICE_NOT_IN_STATION_MODE = -0x7D0,
	DEVICE_START_FAILED = DEVICE_NOT_IN_STATION_MODE - 1,
	INVALID_HEX_STRING = DEVICE_START_FAILED - 1,
	TCP_RECV_ERROR = INVALID_HEX_STRING - 1,
	TCP_SEND_ERROR = TCP_RECV_ERROR - 1,
	FILE_NOT_FOUND_ERROR = TCP_SEND_ERROR - 1,
	INVALID_SERVER_RESPONSE = FILE_NOT_FOUND_ERROR - 1,
	FORMAT_NOT_SUPPORTED = INVALID_SERVER_RESPONSE - 1,
	FILE_OPEN_FAILED = FORMAT_NOT_SUPPORTED - 1,
	FILE_WRITE_ERROR = FILE_OPEN_FAILED - 1,
	INVALID_FILE = FILE_WRITE_ERROR - 1,
	SERVER_CONNECTION_FAILED = INVALID_FILE - 1,
	GET_HOST_IP_FAILED = SERVER_CONNECTION_FAILED  - 1,

	STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;



// Aplication Specific
#include "parameters.h"
#include "SimpleLinkFunctions.h"
#include "NetworkFunctions.h"

#include "HMC5883.h"
#include "ADXL345.h"
#include "IMU.h"
#include "NMEA.h"
#include "DS2401.h"



extern void UART1_Handler(void);

#endif /* INCLUDES_H_ */
