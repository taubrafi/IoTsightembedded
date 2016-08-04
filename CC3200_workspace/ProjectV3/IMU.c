/*
 * IMU.c
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
#include "IMU.h"



float Vx = 0;
float Vy = 0;
float Vz = 0;


void IMU_calculate(float Gpx, float Gpy, float Gpz, float Bpx, float Bpy, float Bpz, double* roll, double* pitch, double* yaw)
{
	double phi = atan2(Gpy, Gpz);
	double sinphi = sin(phi);
	double cosphi = cos(phi);

	double theta = atan2(-Gpx, Gpy*sinphi + Gpz*cosphi);
	double sintheta = sin(theta);
	double costheta = cos(theta);

	float Bx = Bpx-Vx;
	float By = Bpy-Vy;
	float Bz = Bpz-Vz;

	double psi = atan2(Bz*sinphi - By*cosphi, Bx*costheta + By*sintheta*sinphi + Bz*sintheta*cosphi);

	double deg2rad = 180 / 3.141592653589793;

	*roll 	= deg2rad * phi;
	*pitch 	= deg2rad * theta;
	*yaw 	= deg2rad * psi;
}
