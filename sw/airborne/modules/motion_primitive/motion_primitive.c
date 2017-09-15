/*
 * test.c
 *
 *  Created on: Jun 9, 2017
 *      Author: siying
 */


#include "firmwares/rotorcraft/autopilot.h"
#include "firmwares/rotorcraft/guidance.h"
#include "modules/count_time/count_time.h"
#include "modules/higher_level_logic/higher_level_logic.h"
//#include "modules/higher_level_logic_replay/higher_level_logic_replay.h"
#include <stdio.h>
#include <stdlib.h>
#ifndef PI
#define PI 3.1415926
#endif

#ifndef POLY_ORDER
#define POLY_ORDER 7
#endif

float x_0, y_0, x_ac, y_ac, z_ac, psi_0,z_0;
float height_setpoint;
int psi_setpoint;
float ref_x, ref_y, ref_z;
float T, circ_radius;
float theta_traveled;
//int count =0;
void hover_mode(float time_spent);
void go_straight(float time_spent);
void fly_circle(float x_c, float y_c, float omega_rot);
void follow_traj(void);
float arctan2(float y, float x);


void hover_mode(float time_spent){
	//printf("Now in hover_mode\n");
	if (previous_primitive != HOVER_MODE){
		printf("Enters hover mode\n\n");
		reset_time(1);
		if (STOP_FLAG == 0){
		x_0 = stateGetPositionNed_f()->x;
		y_0 = stateGetPositionNed_f()->y;
		z_0 = stateGetPositionNed_f()->z;
		psi_0 = stateGetNedToBodyEulers_f()->psi;
		height_setpoint = z_0;
		psi_setpoint = stateGetNedToBodyEulers_i()->psi;
		}
		//printf("Time1 = %f\n", time_temp1);
	}
	if (STOP_FLAG == 1){
			x_0 = stateGetPositionNed_f()->x;
			y_0 = stateGetPositionNed_f()->y;
			z_0 = stateGetPositionNed_f()->z;
			psi_0 = stateGetNedToBodyEulers_f()->psi;
	}
	guidance_h_set_guided_pos(x_0, y_0);
	guidance_h_set_guided_heading(psi_0);
	guidance_v_set_guided_z(z_0);
	previous_primitive = HOVER_MODE;
	printf("Time1 = %f\n", time_temp1);
	printf("pos_x = %f,    pos_y = %f\n, pos_z = %f\n", POS_FLOAT_OF_BFP(guidance_h.sp.pos.x),POS_FLOAT_OF_BFP(guidance_h.sp.pos.y), z_0 );
	//printf("x_0 = %f, y_0 = %f\n", x_0, y_0);
}



void go_straight(float time_spent)
{
	return;
	/*//printf("Now in go_straight\n\n");
	if (previous_primitive != GO_STRAIGHT){
		printf("Enters go_straight mode\n\n");
		reset_time(2);
		x_0 = stateGetPositionNed_f()->x;
		y_0 = stateGetPositionNed_f()->y;
		z_0 = stateGetPositionNed_f()->z;
		psi_0 = stateGetNedToBodyEulers_f()->psi;
		//printf("Time2 = %f\n", time_temp2);
	}
	float accel = 0.5;
	float ref_x, ref_y;


	    if (RETURN_FLAG == 0){

	    ref_x = x_0 + 0.5*accel*time_temp2*time_temp2;
	    ref_y = y_0 + 0.5*accel*time_temp2*time_temp2;
	    }
	    else if (RETURN_FLAG == 1){
	    ref_x = x_0 - 0.5*accel*time_temp2*time_temp2;
	    ref_y = y_0 - 0.5*accel*time_temp2*time_temp2;
	    }
	    guidance_h_set_guided_pos(ref_x, ref_y);
	    guidance_v_set_guided_z(z_0);
	    guidance_h_set_guided_heading(psi_0);
	    previous_primitive = GO_STRAIGHT;
	    printf("Time2 = %f\n", time_temp2);
	    printf("ref_x = %f,     pos_x = %f\n", ref_x,  POS_FLOAT_OF_BFP(guidance_h.sp.pos.x));*/
	    //printf("x_0 = %f, y_0 = %f\n", x_0, y_0);
}


void fly_circle(float x_c, float y_c, float omega_rot){
		if (previous_primitive != FLY_CIRCLE){
			printf("Enters fly circle mode\n\n");
			reset_time(2);
			//printf("Time2 = %f\n", time_temp2);
			x_ac = stateGetPositionNed_f()->x;
		    y_ac = stateGetPositionNed_f()->y;
		    z_ac = stateGetPositionNed_f()->z;

			psi_0 = stateGetNedToBodyEulers_f()->psi;
			circ_radius = sqrtf((x_ac - x_c)*(x_ac - x_c) + (y_ac - y_c)*(y_ac - y_c));
		}
		float x_ref =  x_c + circ_radius;
		float y_ref = y_c;
		float angle_diff = arctan2(y_ac - y_ref, x_ac);
		theta_traveled = RadOfDeg(omega_rot) * time_temp2;   // change to time_temp3!!!!!

		float x_cmd_inref = circ_radius * cos(theta_traveled);
		float y_cmd_inref = circ_radius * sin(theta_traveled);
		float x_cmd_rotated = x_cmd_inref * cos(angle_diff) - y_cmd_inref *sin(angle_diff);
		float y_cmd_rotated = x_cmd_inref * sin(angle_diff) +  y_cmd_inref *cos(angle_diff);

		float x_cmd = x_c + x_cmd_rotated;
		float y_cmd = y_c + y_cmd_rotated;

		guidance_h_set_guided_pos(x_cmd, y_cmd);
		guidance_v_set_guided_z(z_ac);
		guidance_h_set_guided_heading(psi_0);
		previous_primitive = FLY_CIRCLE;
		printf("Time2 = %f\n", time_temp2);
		printf("theta = %f,  pos_x = %f,     pos_y = %f\n", DegOfRad(theta_traveled), POS_FLOAT_OF_BFP(guidance_h.sp.pos.x), POS_FLOAT_OF_BFP(guidance_h.sp.pos.y));
}


void follow_traj(void){
	if (previous_primitive != FOLLOW_TRAJ){
				printf("Enters follow_traj mode\n\n");
				reset_time(2);
				//printf("Time2 = %f\n", time_temp2);
				x_0 = stateGetPositionNed_f()->x;
			    y_0 = stateGetPositionNed_f()->y;
			    z_0 = stateGetPositionNed_f()->z;
				psi_0 = stateGetNedToBodyEulers_f()->psi;
	}


	float px[POLY_ORDER + 1] = {0.0, 0.0, -0.0613, 0.0, 0.1389, -0.0370, 0.0032, 0.0};
	float py[POLY_ORDER + 1] = {0.0, 0.0, -0.8533, 0.0,0.1792, -0.0478, 0.0041, 0.0};
	float pz[POLY_ORDER + 1] = {-2, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

	int i;
	float sum_x = 0, sum_y = 0, sum_z = 0;
	for (i = 0; i < 8; i++){
		sum_x += px[i] * powf(time_temp2, i);
		sum_y += py[i] * powf(time_temp2, i);
		sum_z += pz[i] * powf(time_temp2, i);
		//printf("i = %d, t = %f,  sum_x = %f\n", i, time_temp2, sum_x);
	}

	ref_x = x_0 + sum_x;
	ref_y = y_0 + sum_y;
	ref_z = z_0 + sum_z;
	//printf("i = %d, t = %f\n  ref_x = %f, ref_y = %f\n, ", i, time_temp2, ref_x, ref_y);


	guidance_h_set_guided_pos(ref_x, ref_y);
	guidance_v_set_guided_z(z_0);
	guidance_h_set_guided_heading(psi_0);
	previous_primitive = FOLLOW_TRAJ;
	printf("i = %d, t = %f\n  pos_x = %f, pos_y = %f\n", i, time_temp2, POS_FLOAT_OF_BFP(guidance_h.sp.pos. x), POS_FLOAT_OF_BFP(guidance_h.sp.pos.y));

}




float arctan2(float y, float x)
{
   float coeff_1 = PI/4;
   float coeff_2 = 3*coeff_1;
   float abs_y = fabs(y)+1e-10;      // kludge to prevent 0/0 condition
   float r, angle;

   if (x>=0)
   {
      r = (x - abs_y) / (x + abs_y);
      angle = coeff_1 - coeff_1 * r;
   }
   else
   {
      r = (x + abs_y) / (abs_y - x);
      angle = coeff_2 - coeff_1 * r;
   }
   if (y < 0)
   return(-angle);     // negate if in quad III or IV
   else
   return(angle);
}

