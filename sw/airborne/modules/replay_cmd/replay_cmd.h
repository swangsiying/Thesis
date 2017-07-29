/*
 * replay_cmd.h
 *
 *  Created on: Jul 16, 2017
 *      Author: siying
 */

#ifndef REPLAY_CMD_H_
#define REPLAY_CMD_H_

extern struct Int32Eulers cmd_to_replay;
extern struct Int32Eulers cmd_quat_to_replay;
extern int rpy_phi, rpy_theta, rpy_psi;

extern void replay_cmd_start(void);
extern void replay_cmd_stop(void);
extern void replay_cmd_periodic(void);

#endif /* REPLAY_CMD_H_ */
