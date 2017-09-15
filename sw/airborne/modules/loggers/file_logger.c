/*
 * Copyright (C) 2014 Freek van Tienen <freek.v.tienen@gmail.com>
 *
 * This file is part of paparazzi.
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
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/** @file modules/loggers/file_logger.c
 *  @brief File logger for Linux based autopilots
 */

#include "file_logger.h"

#include <stdio.h>
#include "std.h"

#include "subsystems/imu.h"
#include "firmwares/rotorcraft/stabilization.h"
#include "state.h"
#include "modules/count_time/count_time.h"
#include "subsystems/actuators/motor_mixing.h"
#include "firmwares/rotorcraft/guidance/guidance_h.h"
#include "modules/replay_cmd/replay_cmd.h"
//#include "modules/computer_vision/opticflow/opticflow_calculator.h"
//#include "modules/guidance_loop_velocity_autonomous_race/guidance_loop_velocity_autonomous_race.h"
//#include "modules/flight_plan_in_guided_mode/flight_plan_in_guided_mode.h"
#include "firmwares/rotorcraft/stabilization/stabilization_attitude_quat_int.h"
#include "subsystems/electrical.h"
//#include "modules/computer_vision/video_capture.h"
#include "subsystems/ahrs/ahrs_int_cmpl_quat.h"
#include "boards/bebop/actuators.h"

/** Set the default File logger path to the USB drive */
#ifndef FILE_LOGGER_PATH
#define FILE_LOGGER_PATH /data/video/usb
#endif

struct Int32Vect2  guidance_h_cmd_earth;
struct Int32Vect2 guidance_h_speed_err;
struct timeval stop, start;
float time_stamp = 0;
float prev_ss_time = 0;
int take_shot = 0;
int shots = 0;

/** The file pointer */
static FILE *file_logger = NULL;

/** Start the file logger and open a new file */
void file_logger_start(void)
{
  shots = 0;
  uint32_t counter = 0;
  char filename[512];

  // Check for available files
  sprintf(filename, "%s/CL_oppo_%05d.csv", STRINGIFY(FILE_LOGGER_PATH), counter);
  while ((file_logger = fopen(filename, "r"))) {
    fclose(file_logger);

    counter++;
    sprintf(filename, "%s/CL_oppo_%05d.csv", STRINGIFY(FILE_LOGGER_PATH), counter);
  }

  file_logger = fopen(filename, "w");
  
  //start clock
  gettimeofday(&start, 0);

/*  if (file_logger != NULL) {
    fprintf(
      file_logger,
      //"counter,x,y,z,v_x,v_y,v_z,phi,theta,psi,phi_int,theta_int,psi_int\n"
    );
  }*/
}

/** Stop the logger an nicely close the file */
void file_logger_stop(void)
{
  if (file_logger != NULL) {
    fclose(file_logger);
    file_logger = NULL;
  }
}

/** Log the values to a csv file */
void file_logger_periodic(void)
{
  if (file_logger == NULL) {
    return;
  }
  //timing
  gettimeofday(&stop, 0);
  double curr_time = (double)(stop.tv_sec + stop.tv_usec / 1000000.0);
  double time_stamp = curr_time - (double)(start.tv_sec + start.tv_usec / 1000000.0);
  
  
  if((time_stamp - prev_ss_time)>0.2)//for 5hz
  {
    //video_capture_shoot();
    prev_ss_time = time_stamp;
    take_shot = shots;
    shots +=1;
  }
  else
  {
    take_shot = 0;
  }
  
  static uint32_t counter;
  struct Int32Quat *quat = stateGetNedToBodyQuat_i();
//flow_v_x,flow_v_y,body_v_x,body_v_y                                                    //%f,%f,%f,
  fprintf(file_logger, "%d, %f, %f, %f,  %f,%f,%f, %d, %d,%d,%d,   %d,%d,%d,%d,%d,%d,%d,%d,%d,   %f,%f,%f,   %f,%f,%f,%f,%f,%f,     %f,%f,%f,%f ,  %f,%f,%d,%d,   %d,%d,%d,%d,%d,%d,%d, %d, %d,%d,%d,%d, %d,%d,%d , %d,%d\n",
          counter, 
	  
	  time_stamp,
	  time_temp1,
  	  time_temp2,  //4
	  
	  ANGLE_FLOAT_OF_BFP(stab_att_sp_euler.phi),
	  ANGLE_FLOAT_OF_BFP(stab_att_sp_euler.theta),
	  ANGLE_FLOAT_OF_BFP(stab_att_sp_euler.psi), //7

	  stabilization_cmd[COMMAND_THRUST],

	  stab_att_sp_euler.phi,
	  stab_att_sp_euler.theta,
	  stab_att_sp_euler.psi, //11


	  imu.gyro.p,//right hand rule
          imu.gyro.q,
          imu.gyro.r,
          imu.accel.x,//right hand rule (times -1 for gravity vector)
          imu.accel.y,
          imu.accel.z,
          imu.mag.x,//not tested
          imu.mag.y,
          imu.mag.z,  //20
	  
          stateGetNedToBodyEulers_f()->phi,// rad positive roll to the right
          stateGetNedToBodyEulers_f()->theta,//negative pitch forward
          stateGetNedToBodyEulers_f()->psi,//negative counter clockwise
	  
	  stateGetPositionNed_f()->x,//as in debug msg ned?
          stateGetPositionNed_f()->y,
          stateGetPositionNed_f()->z,
          stateGetSpeedNed_f()->x,//as in debug msg?
          stateGetSpeedNed_f()->y,
          stateGetSpeedNed_f()->z,   //29
  
	     //
// 	  stabilization_cmd[COMMAND_ROLL],
// 	  stabilization_cmd[COMMAND_PITCH],
// 	  stabilization_cmd[COMMAND_YAW],
	  

	  ANGLE_FLOAT_OF_BFP(guidance_h_cmd_earth.x),
	  ANGLE_FLOAT_OF_BFP(guidance_h_cmd_earth.y),

	  POS_FLOAT_OF_BFP(guidance_h.sp.pos.x),
	  POS_FLOAT_OF_BFP(guidance_h.sp.pos.y), //33

	  SPEED_FLOAT_OF_BFP(guidance_h_speed_err.x),
	  SPEED_FLOAT_OF_BFP(guidance_h_speed_err.y),
	  
	  guidance_h.gains.p,
	  guidance_h.gains.d,  //37

// 	  stab_att_sp_euler.phi,
// 	  stab_att_sp_euler.theta,
// 	  stab_att_sp_euler.psi,
	  



//	  electrical.vsupply,//voltage in decivolts check
//	  electrical.current,//current in milliamps check? per motor or total?
	  
	  actuators_bebop.rpm_ref[0],//rpm of lf tracking seems to work, verify with matlab
	  actuators_bebop.rpm_ref[1],//rf
	  actuators_bebop.rpm_ref[2],//rb
	  actuators_bebop.rpm_ref[3],//lb
	  actuators_bebop.rpm_obs[0],//lf
	  actuators_bebop.rpm_obs[1],//rf
	  actuators_bebop.rpm_obs[2],//rb
	  actuators_bebop.rpm_obs[3],//lb 45

	  motor_mixing.commands[0],
	  motor_mixing.commands[1],
	  motor_mixing.commands[2],
	  motor_mixing.commands[3], //49

	  rpy_phi,
	  rpy_theta,
	  rpy_psi,


	 electrical.vsupply,//voltage in decivolts check, uint16_t
	 electrical.current//current in milliamps check? per motor or total?,  int32_t 54

	  /*
	  shots,

	  arc_status.x,
	  arc_status.y,
	  arc_status.z,
	  arc_status.v_x_f,
	  arc_status.v_y_f,
	  arc_status.v_z_f,
	  arc_status.phi_cmd,
	  arc_status.theta_cmd,
	  arc_status.psi_cmd,
	  arc_status.flag_in_arc,

	  accel_AHRS.x,
	  accel_AHRS.y,
	  accel_AHRS.z

			*/  
			  
         );
  counter++;
}
