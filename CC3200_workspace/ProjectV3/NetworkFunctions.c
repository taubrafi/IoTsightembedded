/*
 * NetworkFunctions.c
 *
 *  Created on: Jun 16, 2016
 *      Author: Rafi
 */
#include "includes.h"
#include "NetworkFunctions.h"

volatile unsigned long  g_ulStatus = 0;//SimpleLink Status
unsigned long  g_ulDestinationIP; // IP address of destination server
unsigned long  g_ulGatewayIP = 0; //Network Gateway IP address
unsigned char  g_ucConnectionSSID[SSID_LEN_MAX+1]; //Connection SSID
unsigned char  g_ucConnectionBSSID[BSSID_LEN_MAX]; //Connection BSSID
unsigned char g_buff[MAX_BUFF_SIZE+1];
long bytesReceived = 0; // variable to store the file size

//*****************************************************************************
//
//! \brief This function initializes the application variables
//!
//! \param    None
//!
//! \return None
//!
//*****************************************************************************
static void InitializeAppVariables()
{
	g_ulStatus = 0;
	g_ulGatewayIP = 0;
	memset(g_ucConnectionSSID,0,sizeof(g_ucConnectionSSID));
	memset(g_ucConnectionBSSID,0,sizeof(g_ucConnectionBSSID));
}


//*****************************************************************************
//! \brief This function puts the device in its default state. It:
//!           - Set the mode to STATION
//!           - Configures connection policy to Auto and AutoSmartConfig
//!           - Deletes all the stored profiles
//!           - Enables DHCP
//!           - Disables Scan policy
//!           - Sets Tx power to maximum
//!           - Sets power policy to normal
//!           - Unregister mDNS services
//!           - Remove all filters
//!
//! \param   none
//! \return  On success, zero is returned. On error, negative is returned
//*****************************************************************************
static long ConfigureSimpleLinkToDefaultState()
{
	SlVersionFull   ver = {0};
	_WlanRxFilterOperationCommandBuff_t  RxFilterIdMask = {0};

	unsigned char ucVal = 1;
	unsigned char ucConfigOpt = 0;
	unsigned char ucConfigLen = 0;
	unsigned char ucPower = 0;

	long lRetVal = -1;
	long lMode = -1;

	lMode = sl_Start(0, 0, 0);
	ASSERT_ON_ERROR(lMode);

	// If the device is not in station-mode, try configuring it in station-mode
	if (ROLE_STA != lMode)
	{
		if (ROLE_AP == lMode)
		{
			// If the device is in AP mode, we need to wait for this event
			// before doing anything
			while(!IS_IP_ACQUIRED(g_ulStatus))
			{
#ifndef SL_PLATFORM_MULTI_THREADED
				_SlNonOsMainLoopTask();
#endif
			}
		}

		// Switch to STA role and restart
		lRetVal = sl_WlanSetMode(ROLE_STA);
		ASSERT_ON_ERROR(lRetVal);

		lRetVal = sl_Stop(0xFF);
		ASSERT_ON_ERROR(lRetVal);

		lRetVal = sl_Start(0, 0, 0);
		ASSERT_ON_ERROR(lRetVal);

		// Check if the device is in station again
		if (ROLE_STA != lRetVal)
		{
			// We don't want to proceed if the device is not coming up in STA-mode
			return DEVICE_NOT_IN_STATION_MODE;
		}
	}

	// Get the device's version-information
	ucConfigOpt = SL_DEVICE_GENERAL_VERSION;
	ucConfigLen = sizeof(ver);
	lRetVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &ucConfigOpt,
			&ucConfigLen, (unsigned char *)(&ver));
	ASSERT_ON_ERROR(lRetVal);

	UART_PRINT("Host Driver Version: %s\n\r",SL_DRIVER_VERSION);
	UART_PRINT("Build Version %d.%d.%d.%d.31.%d.%d.%d.%d.%d.%d.%d.%d\n\r",
			ver.NwpVersion[0],ver.NwpVersion[1],ver.NwpVersion[2],ver.NwpVersion[3],
			ver.ChipFwAndPhyVersion.FwVersion[0],ver.ChipFwAndPhyVersion.FwVersion[1],
			ver.ChipFwAndPhyVersion.FwVersion[2],ver.ChipFwAndPhyVersion.FwVersion[3],
			ver.ChipFwAndPhyVersion.PhyVersion[0],ver.ChipFwAndPhyVersion.PhyVersion[1],
			ver.ChipFwAndPhyVersion.PhyVersion[2],ver.ChipFwAndPhyVersion.PhyVersion[3]);

	// Set connection policy to Auto + SmartConfig
	//      (Device's default connection policy)
	lRetVal = sl_WlanPolicySet(SL_POLICY_CONNECTION,
			SL_CONNECTION_POLICY(1, 0, 0, 0, 1), NULL, 0);
	ASSERT_ON_ERROR(lRetVal);

	// Remove all profiles
	lRetVal = sl_WlanProfileDel(0xFF);
	ASSERT_ON_ERROR(lRetVal);

	//
	// Device in station-mode. Disconnect previous connection if any
	// The function returns 0 if 'Disconnected done', negative number if already
	// disconnected Wait for 'disconnection' event if 0 is returned, Ignore
	// other return-codes
	//
	lRetVal = sl_WlanDisconnect();
	if(0 == lRetVal)
	{
		// Wait
		while(IS_CONNECTED(g_ulStatus))
		{
#ifndef SL_PLATFORM_MULTI_THREADED
			_SlNonOsMainLoopTask();
#endif
		}
	}

	// Enable DHCP client
	lRetVal = sl_NetCfgSet(SL_IPV4_STA_P2P_CL_DHCP_ENABLE,1,1,&ucVal);
	ASSERT_ON_ERROR(lRetVal);

	// Disable scan
	ucConfigOpt = SL_SCAN_POLICY(0);
	lRetVal = sl_WlanPolicySet(SL_POLICY_SCAN , ucConfigOpt, NULL, 0);
	ASSERT_ON_ERROR(lRetVal);

	// Set Tx power level for station mode
	// Number between 0-15, as dB offset from max power - 0 will set max power
	ucPower = 0;
	lRetVal = sl_WlanSet(SL_WLAN_CFG_GENERAL_PARAM_ID,
			WLAN_GENERAL_PARAM_OPT_STA_TX_POWER, 1, (unsigned char *)&ucPower);
	ASSERT_ON_ERROR(lRetVal);

	// Set PM policy to normal
	lRetVal = sl_WlanPolicySet(SL_POLICY_PM , SL_NORMAL_POLICY, NULL, 0);
	ASSERT_ON_ERROR(lRetVal);

	// Unregister mDNS services
	lRetVal = sl_NetAppMDNSUnRegisterService(0, 0);
	ASSERT_ON_ERROR(lRetVal);

	// Remove  all 64 filters (8*8)
	memset(RxFilterIdMask.FilterIdMask, 0xFF, 8);
	lRetVal = sl_WlanRxFilterSet(SL_REMOVE_RX_FILTER, (_u8 *)&RxFilterIdMask,
			sizeof(_WlanRxFilterOperationCommandBuff_t));
	ASSERT_ON_ERROR(lRetVal);


	lRetVal = sl_Stop(SL_STOP_TIMEOUT);
	ASSERT_ON_ERROR(lRetVal);

	InitializeAppVariables();

	return SUCCESS;
}



//****************************************************************************
//
//! \brief Connecting to a WLAN Accesspoint
//!
//!  This function connects to the required AP (SSID_NAME) with Security
//!  parameters specified in te form of macros at the top of this file
//!
//! \param  Status value
//!
//! \return  None
//!
//! \warning    If the WLAN connection fails or we don't aquire an IP
//!            address, It will be stuck in this function forever.
//
//****************************************************************************
static long WlanConnect()
{
	SlSecParams_t secParams = {0};
	long lRetVal = 0;

	secParams.Key = (signed char *)SECURITY_KEY;
	secParams.KeyLen = strlen(SECURITY_KEY);
	secParams.Type = SECURITY_TYPE;

	lRetVal = sl_WlanConnect((signed char *)SSID_NAME,
			strlen((const char *)SSID_NAME), 0, &secParams, 0);
	ASSERT_ON_ERROR(lRetVal);

	// Wait for WLAN Event
	while((!IS_CONNECTED(g_ulStatus)) || (!IS_IP_ACQUIRED(g_ulStatus)))
	{
		// wait till connects to an AP
		_SlNonOsMainLoopTask();
	}

	return SUCCESS;

}


//*****************************************************************************
//
//! \brief Flush response body.
//!
//! \param[in]  httpClient - Pointer to HTTP Client instance
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int FlushHTTPResponse(HTTPCli_Handle httpClient)
{
	const char *ids[2] = {
			HTTPCli_FIELD_NAME_CONNECTION, /* App will get connection header value. all others will skip by lib */
			NULL
	};
	char buf[128];
	int id;
	int len = 1;
	bool moreFlag = 0;
	char ** prevRespFilelds = NULL;


	/* Store previosly store array if any */
	prevRespFilelds = HTTPCli_setResponseFields(httpClient, ids);

	/* Read response headers */
	while ((id = HTTPCli_getResponseField(httpClient, buf, sizeof(buf), &moreFlag))
			!= HTTPCli_FIELD_ID_END)
	{

		if(id == 0)
		{
			if(!strncmp(buf, "close", sizeof("close")))
			{
				UART_PRINT("Connection terminated by server\n\r");
			}
		}

	}

	/* Restore previosuly store array if any */
	HTTPCli_setResponseFields(httpClient, (const char **)prevRespFilelds);

	while(1)
	{
		/* Read response data/body */
		/* Note:
                moreFlag will be set to 1 by HTTPCli_readResponseBody() call, if more
                data is available Or in other words content length > length of buffer.
                The remaining data will be read in subsequent call to HTTPCli_readResponseBody().
                Please refer HTTP Client Libary API documenation @ref HTTPCli_readResponseBody
                for more information.
		 */
		HTTPCli_readResponseBody(httpClient, buf, sizeof(buf) - 1, &moreFlag);
		ASSERT_ON_ERROR(len);

		if ((len - 2) >= 0 && buf[len - 2] == '\r' && buf [len - 1] == '\n'){
			break;
		}

		if(!moreFlag)
		{
			/* There no more data. break the loop. */
			break;
		}
	}
	return 0;
}


//*****************************************************************************
//
//! \brief Handler for parsing JSON data
//!
//! \param[in]  ptr - Pointer to http response body data
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
int ParseJSONData(char *ptr)
{
	long lRetVal = 0;
	int noOfToken;
	jsmn_parser parser;
	jsmntok_t   *tokenList;


	/* Initialize JSON PArser */
	jsmn_init(&parser);

	/* Get number of JSON token in stream as we we dont know how many tokens need to pass */
	noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), NULL, 10);
	if(noOfToken <= 0)
	{
		UART_PRINT("Failed to initialize JSON parser\n\r");
		return -1;

	}

	/* Allocate memory to store token */
	tokenList = (jsmntok_t *) malloc(noOfToken*sizeof(jsmntok_t));
	if(tokenList == NULL)
	{
		UART_PRINT("Failed to allocate memory\n\r");
		return -1;
	}

	/* Initialize JSON Parser again */
	jsmn_init(&parser);
	noOfToken = jsmn_parse(&parser, (const char *)ptr, strlen((const char *)ptr), tokenList, noOfToken);
	if(noOfToken < 0)
	{
		UART_PRINT("Failed to parse JSON tokens\n\r");
		lRetVal = noOfToken;
	}
	else
	{
		UART_PRINT("Successfully parsed %ld JSON tokens\n\r", noOfToken);
	}

	free(tokenList);

	return lRetVal;
}

/*!
    \brief This function read respose from server and dump on console

    \param[in]      httpClient - HTTP Client object

    \return         0 on success else -ve

    \note

    \warning
 */
static int readResponse(HTTPCli_Handle httpClient)
{
	long lRetVal = 0;
	int bytesRead = 0;
	int id = 0;
	unsigned long len = 0;
	int json = 0;
	char *dataBuffer=NULL;
	bool moreFlags = 1;
	const char *ids[4] = {
			HTTPCli_FIELD_NAME_CONTENT_LENGTH,
			HTTPCli_FIELD_NAME_CONNECTION,
			HTTPCli_FIELD_NAME_CONTENT_TYPE,
			NULL
	};

	/* Read HTTP POST request status code */
	lRetVal = HTTPCli_getResponseStatus(httpClient);
	if(lRetVal > 0)
	{
		switch(lRetVal)
		{
		case 200:
		{
			UART_PRINT("HTTP Status 200\n\r");
			/*
                 Set response header fields to filter response headers. All
                  other than set by this call we be skipped by library.
			 */
			HTTPCli_setResponseFields(httpClient, (const char **)ids);

			/* Read filter response header and take appropriate action. */
			/* Note:
                    1. id will be same as index of fileds in filter array setted
                    in previous HTTPCli_setResponseFields() call.

                    2. moreFlags will be set to 1 by HTTPCli_getResponseField(), if  field
                    value could not be completely read. A subsequent call to
                    HTTPCli_getResponseField() will read remaining field value and will
                    return HTTPCli_FIELD_ID_DUMMY. Please refer HTTP Client Libary API
                    documenation @ref HTTPCli_getResponseField for more information.
			 */
			while((id = HTTPCli_getResponseField(httpClient, (char *)g_buff, sizeof(g_buff), &moreFlags))
					!= HTTPCli_FIELD_ID_END)
			{

				switch(id)
				{
				case 0: /* HTTPCli_FIELD_NAME_CONTENT_LENGTH */
				{
					len = strtoul((char *)g_buff, NULL, 0);
				}
				break;
				case 1: /* HTTPCli_FIELD_NAME_CONNECTION */
				{
				}
				break;
				case 2: /* HTTPCli_FIELD_NAME_CONTENT_TYPE */
				{
					if(!strncmp((const char *)g_buff, "application/json",
							sizeof("application/json")))
					{
						json = 1;
					}
					else
					{
						/* Note:
                                Developers are advised to use appropriate
                                content handler. In this example all content
                                type other than json are treated as plain text.
						 */
						json = 0;
					}
					UART_PRINT(HTTPCli_FIELD_NAME_CONTENT_TYPE);
					UART_PRINT(" : ");
					UART_PRINT("application/json\n\r");
				}
				break;
				default:
				{
					UART_PRINT("Wrong filter id\n\r");
					lRetVal = -1;
					goto end;
				}
				}
			}
			bytesRead = 0;
			if(len > sizeof(g_buff))
			{
				dataBuffer = (char *) malloc(len);
				if(dataBuffer)
				{
					UART_PRINT("Failed to allocate memory\n\r");
					lRetVal = -1;
					goto end;
				}
			}
			else
			{
				dataBuffer = (char *)g_buff;
			}

			/* Read response data/body */
			/* Note:
                    moreFlag will be set to 1 by HTTPCli_readResponseBody() call, if more
		            data is available Or in other words content length > length of buffer.
		            The remaining data will be read in subsequent call to HTTPCli_readResponseBody().
		            Please refer HTTP Client Libary API documenation @ref HTTPCli_readResponseBody
		            for more information

			 */
			bytesRead = HTTPCli_readResponseBody(httpClient, (char *)dataBuffer, len, &moreFlags);
			if(bytesRead < 0)
			{
				UART_PRINT("Failed to received response body\n\r");
				lRetVal = bytesRead;
				goto end;
			}
			else if( bytesRead < len || moreFlags)
			{
				UART_PRINT("Mismatch in content length and received data length\n\r");
				goto end;
			}
			dataBuffer[bytesRead] = '\0';

			if(json)
			{
				/* Parse JSON data */
				lRetVal = ParseJSONData(dataBuffer);
				if(lRetVal < 0)
				{
					goto end;
				}
			}
			else
			{
				/* treating data as a plain text */
			}

		}
		break;

		case 404:
			UART_PRINT("File not found. \r\n");
			/* Handle response body as per requirement.
                  Note:
                    Developers are advised to take appopriate action for HTTP
                    return status code else flush the response body.
                    In this example we are flushing response body in default
                    case for all other than 200 HTTP Status code.
			 */
		default:
			/* Note:
              Need to flush received buffer explicitly as library will not do
              for next request.Apllication is responsible for reading all the
              data.
			 */
			FlushHTTPResponse(httpClient);
			break;
		}
	}
	else
	{
		UART_PRINT("Failed to receive data from server.\r\n");
		goto end;
	}

	lRetVal = 0;

	end:
	if(len > sizeof(g_buff) && (dataBuffer != NULL))
	{
		free(dataBuffer);
	}
	return lRetVal;
}


//*****************************************************************************
//
//! \brief HTTP GET Demonstration
//!
//! \param[in]  httpClient - Pointer to http client
//!
//! \return 0 on success else error code on failure
//!
//*****************************************************************************
static int HTTPGetMethod(HTTPCli_Handle httpClient, char* strbuffer)
{

	long lRetVal = 0;
	HTTPCli_Field fields[4] = {
			{HTTPCli_FIELD_NAME_HOST, HOST_NAME},
			{HTTPCli_FIELD_NAME_ACCEPT, "*/*"},
			{HTTPCli_FIELD_NAME_CONTENT_LENGTH, "0"},
			{NULL, NULL}
	};
	bool        moreFlags;


	/* Set request header fields to be send for HTTP request. */
	HTTPCli_setRequestFields(httpClient, fields);

	/* Send GET method request. */
	/* Here we are setting moreFlags = 0 as there are no more header fields need to send
       at later stage. Please refer HTTP Library API documentaion @ HTTPCli_sendRequest
       for more information.
	 */
	moreFlags = 0;
	lRetVal = HTTPCli_sendRequest(httpClient, HTTPCli_METHOD_GET, strbuffer, moreFlags);
	if(lRetVal < 0)
	{
		UART_PRINT("Failed to send HTTP GET request.\n\r");
		return lRetVal;
	}


	lRetVal = readResponse(httpClient);

	return lRetVal;
}


//*****************************************************************************
//
//! Function to connect to AP
//!
//! \param  none
//!
//! \return Error-code or SUCCESS
//!
//*****************************************************************************
static long ConnectToAP()
{
	long lRetVal = -1;

	//
	// Following function configure the device to default state by cleaning
	// the persistent settings stored in NVMEM (viz. connection profiles &
	// policies, power policy etc)
	//
	// Applications may choose to skip this step if the developer is sure
	// that the device is in its desired state at start of applicaton
	//
	// Note that all profiles and persistent settings that were done on the
	// device will be lost
	//
	lRetVal = ConfigureSimpleLinkToDefaultState();
	if(lRetVal < 0)
	{
		if (DEVICE_NOT_IN_STATION_MODE == lRetVal)
		{
			UART_PRINT("Failed to configure the device in its default state, "
					"Error-code: %d\n\r", DEVICE_NOT_IN_STATION_MODE);
		}

		return -1;
	}

	UART_PRINT("Device is configured in default state \n\r");

	//
	// Assumption is that the device is configured in station mode already
	// and it is in its default state
	//
	lRetVal = sl_Start(0, 0, 0);
	if (lRetVal < 0 || ROLE_STA != lRetVal)
	{
		ASSERT_ON_ERROR(DEVICE_START_FAILED);
	}

	UART_PRINT("Device started as STATION \n\r");

	// Connecting to WLAN AP - Set with static parameters defined at the top
	// After this call we will be connected and have IP address
	lRetVal = WlanConnect();

	UART_PRINT("Connected to the AP: %s\r\n", SSID_NAME);
	return 0;
}

//*****************************************************************************
//
//! Function to connect to HTTP server
//!
//! \param  httpClient - Pointer to HTTP Client instance
//!
//! \return Error-code or SUCCESS
//!
//*****************************************************************************
static int ConnectToHTTPServer(HTTPCli_Handle httpClient)
{
	long lRetVal = -1;
	struct sockaddr_in addr;


#ifdef USE_PROXY
	struct sockaddr_in paddr;
	paddr.sin_family = AF_INET;
	paddr.sin_port = htons(PROXY_PORT);
	paddr.sin_addr.s_addr = sl_Htonl(PROXY_IP);
	HTTPCli_setProxy((struct sockaddr *)&paddr);
#endif

	/* Resolve HOST NAME/IP */
	lRetVal = sl_NetAppDnsGetHostByName((signed char *)HOST_NAME,
			strlen((const char *)HOST_NAME),
			&g_ulDestinationIP,SL_AF_INET);
	if(lRetVal < 0)
	{
		ASSERT_ON_ERROR(GET_HOST_IP_FAILED);
	}

	/* Set up the input parameters for HTTP Connection */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(HOST_PORT);
	addr.sin_addr.s_addr = sl_Htonl(g_ulDestinationIP);

	/* Testing HTTPCli open call: handle, address params only */
	HTTPCli_construct(httpClient);
	lRetVal = HTTPCli_connect(httpClient, (struct sockaddr *)&addr, 0, NULL);
	if (lRetVal < 0)
	{
		UART_PRINT("Connection to server failed. error(%d)\n\r", lRetVal);
		ASSERT_ON_ERROR(SERVER_CONNECTION_FAILED);
	}
	else
	{
		UART_PRINT("Connection to server created successfully\r\n");
	}

	return 0;
}



