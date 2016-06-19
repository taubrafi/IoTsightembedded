/*
 * SimpleLinkFunctions.h
 *
 *  Created on: May 23, 2016
 *      Author: Rafi
 */

#ifndef SIMPLELINKFUNCTIONS_H_
#define SIMPLELINKFUNCTIONS_H_


void SimpleLinkWlanEventHandler(SlWlanEvent_t *pWlanEvent);

void SimpleLinkNetAppEventHandler(SlNetAppEvent_t *pNetAppEvent);

void SimpleLinkHttpServerCallback(SlHttpServerEvent_t *pHttpEvent,
                                  SlHttpServerResponse_t *pHttpResponse);

void SimpleLinkGeneralEventHandler(SlDeviceEvent_t *pDevEvent);

void SimpleLinkSockEventHandler(SlSockEvent_t *pSock);


#endif /* SIMPLELINKFUNCTIONS_H_ */
