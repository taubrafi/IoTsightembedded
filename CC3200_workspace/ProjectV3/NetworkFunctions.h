/*
 * NetworkFunctions.h
 *
 *  Created on: Jun 16, 2016
 *      Author: Rafi
 */

#ifndef NETWORKFUNCTIONS_H_
#define NETWORKFUNCTIONS_H_

static void InitializeAppVariables();
static long ConfigureSimpleLinkToDefaultState();
static long WlanConnect();
static int FlushHTTPResponse(HTTPCli_Handle httpClient);
int ParseJSONData(char *ptr);
static int readResponse(HTTPCli_Handle httpClient);
static int HTTPGetMethod(HTTPCli_Handle httpClient, char* strbuffer);
static long ConnectToAP();
static int ConnectToHTTPServer(HTTPCli_Handle httpClient);


#endif /* NETWORKFUNCTIONS_H_ */
