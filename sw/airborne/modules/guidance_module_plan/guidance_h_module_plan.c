/*
 * guidance_h_module_plan.c
 *
 *  Created on: Jul 16, 2017
 *      Author: siying
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modules/replay_cmd/replay_cmd.h"
#include "firmwares/rotorcraft/guidance.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"

void guidance_h_module_init(void);
void guidance_h_module_enter(void);
void guidance_h_module_read_rc(void);
void guideance_h_module_run_a(void);

void guidance_h_module_init(void){

}

void guidance_h_module_enter(void){

}

void guidance_h_module_read_rc(void){

}

void guideance_h_module_run_a(void){
	printf("!!!!");
	replay_cmd_periodic();
	stabilization_attitude_set_rpy_setpoint_i(&cmd_to_replay);
}
