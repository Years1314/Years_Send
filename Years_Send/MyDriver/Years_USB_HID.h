#ifndef __Years_USB_HID_H__
#define __Years_USB_HID_H__

#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_config.h"

extern u8 Hid_RxData[63];

void USB_HID_Init(void);
//void Usb_Hid_Adddata(u8 *dataToSend , u8 length);
//void Usb_Hid_Send (void);
void USB_SendString(u8 *str);


#endif
