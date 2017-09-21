/*
 * Copyright (C) siying


 * @file "modules/higher_level_logic/higher_level_logic.c"
 * @author siying
 * Defines higher level logic
 */

#include "firmwares/rotorcraft/autopilot.h"
#include "firmwares/rotorcraft/guidance.h"
#include "modules/count_time/count_time.h"
#include "modules/motion_primitive/motion_primitive.h"
#include "modules/higher_level_logic/higher_level_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef PI
#define PI 3.1415926
#endif


enum primitive_level previous_primitive = STANDBY;
enum primitive_level current_primitive = STANDBY;

int RETURN_FLAG = 0;
int STOP_FLAG = 0;


void higher_level_run(){
	if (guidance_h.mode != GUIDANCE_H_MODE_GUIDED){
		printf("NOT IN GUIDED MODE\n");
		//current_primitive = STANDBY;
		//previous_primitive = STANDBY;
		return;
	}
	else
	{

		switch(current_primitive)
		{
		case STANDBY:
			current_primitive = HOVER_MODE;
			break;


		case HOVER_MODE:
			hover_mode(5.0);
			if (time_temp1 > 10.0){
				current_primitive = FOLLOW_TRAJ;
				printf("Switch to go straight\n");
			}
			break;


		case GO_STRAIGHT:
			go_straight(4.0);
			if (time_temp2 > 4.0){
				current_primitive = HOVER_MODE;
				printf("Switch to hover\n");
				RETURN_FLAG = !(RETURN_FLAG);
			}
			break;

		case FLY_CIRCLE:
			fly_circle(0.5,0.5,30);
			if (theta_traveled > 2*PI){
				current_primitive = HOVER_MODE;
				printf("Switch to hover\n");
			}
			break;

		case FOLLOW_TRAJ:
			follow_traj();
			if (time_temp2 > 2.45){
				current_primitive = HOVER_MODE;
				printf("Switch to hover\n");
				STOP_FLAG = 1;
			}
			break;
		}
	}
}




/*
 RETURN_FLAG = 0;

switch  (current_primitive)
case HOVER: hover_mode(xxx seconds)
if time> xxx  then switch mode
current_primitive = GO_STRAIGHT;


case GO_STRAIGHT: go_straight(xxx seconds)
if time> xxx  then switch mode
current_primitive = HOVER_MODE;
RETURN_FLAG = !(RETURN_FLAG);
*/
