/*
 * higher_level_logic.h
 *
 *  Created on: Jun 12, 2017
 *      Author: siying
 */

#ifndef HIGHER_LEVEL_LOGIC_H_
#define HIGHER_LEVEL_LOGIC_H_

enum primitive_level{STANDBY, HOVER_MODE, GO_STRAIGHT, FLY_CIRCLE, FOLLOW_TRAJ};


extern enum primitive_level current_primitive;
extern enum primitive_level previous_primitive;
extern int RETURN_FLAG;
extern int STOP_FLAG;

#endif /* HIGHER_LEVEL_LOGIC_H_ */

