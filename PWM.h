#ifndef __PWM_H
#define __PWM_H

extern uint8_t CCR_Value;

void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
uint16_t PWM_GetCapture(void);

#endif
