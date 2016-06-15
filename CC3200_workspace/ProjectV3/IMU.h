/*
 * IMU.h
 *
 *  Created on: Jun 6, 2016
 *      Author: Rafi
 */

#ifndef IMU_H_
#define IMU_H_


void IMU_calculate(float Gpx, float Gpy, float Gpz, float Bpx, float Bpy, float Bpz, double* roll, double* pitch, double* yaw);



#endif /* IMU_H_ */
