/*
 * HMC5883.h
 *
 *  Created on: Jun 6, 2016
 *      Author: Rafi
 */

#ifndef HMC5883_H_
#define HMC5883_H_


int init_HMC5883(char addr, char cal);

int HMC5883_read_magdata(char addr, float* Xmag, float* Ymag, float* Zmag);

#endif /* HMC5883_H_ */
