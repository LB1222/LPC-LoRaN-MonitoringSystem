#ifndef _REMOTE_H
#define _REMOTE_H
#include "stm32f10x.h"

extern uint8_t ON_flag;
extern u16 test_flag,set_flag;
extern void RC_Analy(void); 
extern void Rc_Connect(void);


extern void F_M_Controler(u16 speed,u16 time) ;
extern void L_R_Controler(u16 speed,u16 time) ;

#endif

