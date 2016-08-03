/*
 * NMEA.h
 *
 *  Created on: Jun 16, 2016
 *      Author: Rafi
 */

#ifndef NMEA_H_
#define NMEA_H_

void ParseGPS (char c);

extern volatile unsigned int gpsTime, gpsMsecs, gpsKnots, gpsCourse, gpsDate;
extern volatile long gpsLat, gpsLong;
extern volatile char gpsFix;

extern int parseState;
extern unsigned int parseTemp;
extern long ltmp;

#endif /* NMEA_H_ */
