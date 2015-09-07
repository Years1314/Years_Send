#ifndef _Years_KEY_H_
#define _Years_KEY_H_

#include "board.h"
#include "config.h"

void Years_KEY_Init(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
void Key_Event(void);

#endif
