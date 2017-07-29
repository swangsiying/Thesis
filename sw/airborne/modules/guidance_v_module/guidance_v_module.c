/*
 * guidance_h_module.c
 *
 *  Created on: Jul 16, 2017
 *      Author: siying
 */


#include "firmwares/rotorcraft/autopilot.h"
#include "modules/guidance_v_module/guidance_v_module.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modules/replay_cmd/replay_cmd.h"
#include "firmwares/rotorcraft/guidance.h"
#include "modules/motion_primitive/motion_primitive.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"

void guidance_v_module_init(void);
void guidance_v_module_enter(void);
void guidance_v_module_run(bool in_flight);



void guidance_v_module_init(void){

}

void guidance_v_module_enter(void){

}

void guidance_v_module_run(bool in_flight){
printf("height = %f\n", height_setpoint);
	//z_0 = stateGetPositionNed_f()->z;
	guidance_v_guided_vel_enabled = false;
	guidance_v_z_sp = POS_BFP_OF_REAL(height_setpoint);
}
