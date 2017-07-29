/*
 * test.h
 *
 *  Created on: Jun 11, 2017
 *      Author: siying
 */

#ifndef MOTION_PRIMITIVE_H_
#define MOTION_PRIMITIVE_H_

extern void hover_mode(float time_spent);
extern void go_straight(float time_spent);
extern void fly_circle(float x_c, float y_c, float omega_rot);
extern	void follow_traj(void);
extern float height_setpoint;
extern float theta_traveled;
#endif /* MOTION_PRIMITIVE_H_ */
