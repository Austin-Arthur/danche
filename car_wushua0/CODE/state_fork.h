/*
 * state_fork.h
 *
 *  Created on: 2022Äê6ÔÂ4ÈÕ
 *      Author: 22878
 */

#ifndef CODE_STATE_FORK_H_
#define CODE_STATE_FORK_H_

#define fork_left 0
#define fork_right 1

#include "headfile.h"
uint8 Is_fork3();
void state_80();
void state_81();
void state_82();
void state_83();
void state_84();
void state_85();
void state_86();
void state_87();
extern uint8 bottom_pointX;
extern uint8 bottom_pointY;
extern uint8 fork_L_x,fork_L_y;
extern uint8 fork_R_x,fork_R_y;
extern float fork_L_k,fork_R_k;
extern uint8 corner_Lx,corner_Rx;
extern  uint8 x_84;
extern uint8 x_82,btn_82;
extern  int8 Diffff ;
extern uint8 Dif_85;
extern uint8 btnF1,btnF2,BTN;
extern uint8 break_p1,break_p2,break_p3;
#endif /* CODE_STATE_FORK_H_ */
