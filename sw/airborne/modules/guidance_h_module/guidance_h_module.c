/*
 * Copyright (C) siying
 *
 * This file is part of paparazzi
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file "modules/guidance_h_module/guidance_h_module.c"
 * @author siying
 * Logic for MODULE
 */
#include "firmwares/rotorcraft/autopilot.h"
#include "modules/guidance_h_module/guidance_h_module.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "modules/replay_cmd/replay_cmd.h"
#include "firmwares/rotorcraft/guidance.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude.h"
#include "firmwares/rotorcraft/stabilization/stabilization_indi.h"



void guidance_h_module_init(void){

}

void guidance_h_module_enter(void){

}

void guidance_h_module_read_rc(void){

}

void guidance_h_module_run(bool in_flight){
	replay_cmd_periodic();
	quat_from_earth_cmd_i(&stab_att_sp_quat, &cmd_use_quat, rpy_psi);
	//int32_quat_of_eulers(&stab_att_sp_quat, &cmd_to_replay);
	stabilization_attitude_run(in_flight);
}





