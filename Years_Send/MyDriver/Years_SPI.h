#ifndef __YEARS_SPI_H__
#define __YEARS_SPI_H__

#include "stm32f10x.h"

void Years_SPI_Init(void);
u8   Years_SPI_RW(u8 dat);
void Years_SPI_CE_H(void);
void Years_SPI_CE_L(void);
void Years_SPI_CSN_H(void);
void Years_SPI_CSN_L(void);

#endif
