#ifndef _Years_Remote_H_
#define _Years_Remote_H_

#include "stm32f10x.h"

void RemotePutRxBuf(unsigned char *RxBuf,u8 data_num);
void Remote_Send(void);

#endif

