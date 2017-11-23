/*
 * Copyright (C) siying


 * @file "modules/higher_level_logic_replay/higher_level_logic_replay.c"
 * @author siying
 * Defines higher level logic
 */

#include "firmwares/rotorcraft/autopilot.h"
#include "firmwares/rotorcraft/guidance.h"
#include "modules/count_time/count_time.h"
#include "modules/motion_primitive/motion_primitive.h"
#include "modules/higher_level_logic_replay/higher_level_logic_replay.h"
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

void higher_level_logic_replay_run(void);

void higher_level_logic_replay_run(void){
	printf("CURRENT MODE = %d\n", guidance_h.mode);
	 if (guidance_h.mode != GUIDANCE_H_MODE_GUIDED){
		current_primitive = STANDBY;
		previous_primitive = STANDBY;
		STOP_FLAG = 0;
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
				current_primitive = REPLAY_TRAJ;
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

		case REPLAY_TRAJ:
			if (previous_primitive != REPLAY_TRAJ){
				replay_cmd_start();
			}
			guidance_h_mode_changed(GUIDANCE_H_MODE_MODULE);
			guidance_v_mode_changed(GUIDANCE_V_MODE_MODULE);
			previous_primitive = REPLAY_TRAJ;
			break;
		}
	}
}


