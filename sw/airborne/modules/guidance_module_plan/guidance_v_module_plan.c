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
#include "modules/motion_primitive/motion_primitive.h"
//#include "modules/guidance_module_plan/guidance_v_module_plan.h"
#include "firmwares/rotorcraft/autopilot.h"
#include "firmwares/rotorcraft/guidance.h" //guidance_h.h + guidance_v.h
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"


void guidance_v_module_enter(void);
void guideance_v_module_run(bool in_flight);


void guidance_v_module_enter(void){

}

void guideance_v_module_run(bool in_flight){
	//z_0 = stateGetPositionNed_f()->z;
	guidance_v_guided_vel_enabled = false;
	guidance_v_z_sp = POS_BFP_OF_REAL(height_setpoint);
}
