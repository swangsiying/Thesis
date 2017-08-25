/*
 * replay_cmd.c
 *
 *  Created on: Jul 16, 2017
 *      Author: siying
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "math/pprz_algebra_int.h"
#include "math/pprz_algebra_int.h"
#include "firmwares/rotorcraft/guidance.h"
#include "firmwares/rotorcraft/autopilot.h"
#include "modules/replay_cmd/replay_cmd.h"
#include "modules/motion_primitive/motion_primitive.h"
#include "modules/higher_level_logic_replay/higher_level_logic_replay.h"



int index_x = 0;
int index_y = 0;
int index_z = 0;
int rpy_counter;
int rpy_phi,rpy_theta,rpy_psi, rpy_thrust;

double rpy_timestamp, rpy_time1, rpy_time2;

struct Int32Eulers cmd_to_replay;
struct Int32Eulers cmd_quat_to_replay;

#ifndef FILE_RPY_PATH
#define FILE_RPY_PATH /data/ftp/internal_000/
#endif

FILE * file;


void replay_cmd_start(void){

	//if (guidance_h.mode == GUIDANCE_H_MODE_MODULE){
				//printf("IN MODULE MODE\n");

	    char filename[512];
	    sprintf(filename, "%s/avg_CL.csv",  STRINGIFY(FILE_RPY_PATH), index_x, index_y, index_z);
	    //sprintf(filename, "%d%d%d_1.csv",  index_x, index_y, index_z);
	    printf("filename = %s\n", filename);
	    errno = 0;
	    file = fopen(filename , "r");
	    if (file == NULL) {
	    	printf("%s\n", strerror(errno));
	    	printf("file open failed!!!!!!!!!!!!!!!!!\n");
	    }
	}


void replay_cmd_periodic(void){
	if (guidance_h.mode == GUIDANCE_H_MODE_MODULE){
		//printf("periodic\n");

    int n = 500;
    char str[500];
    //printf("filename = %s\n", filename);
    int i;

    if( fgets(str, n, file) != NULL ){

          for (i = 0 ; i < strlen(str) ; i++) {
            if (str[i] == ',') {
              str[i] = ' ';
            }
          }


    sscanf(str, "%d %lf %lf %lf  %d %d %d %d", &rpy_counter, &rpy_timestamp, &rpy_time1, &rpy_time2, &rpy_phi,&rpy_theta, &rpy_psi, &rpy_thrust);
    printf("phi = %d, theta = %d, psi = %d\n" , rpy_phi, rpy_theta, psi_setpoint);
    cmd_to_replay.phi = rpy_phi;
    cmd_to_replay.theta = rpy_theta;
    cmd_to_replay.psi = psi_setpoint;

    //int32_quat_of_eulers(&cmd_quat_to_replay, &cmd_to_replay);
    }
    else {
    	replay_cmd_stop();
    	}
	}
}

void replay_cmd_stop(void){
	if (file != NULL){
		printf("fclose\n");
		fclose(file);
		file = NULL;
		STOP_FLAG = 1;
		previous_primitive = REPLAY_TRAJ;
		current_primitive = HOVER_MODE;
		guidance_h_mode_changed(GUIDANCE_H_MODE_GUIDED);
		guidance_v_mode_changed(GUIDANCE_V_MODE_GUIDED);
	}

}
