#ifndef __CAN_H__
#define __CAN_H__

#include "main.h"

#define CAN_ID_FLOOD_DETECTION 0x101
#define CAN_ID_ROLLOVER_DETECTION 0x102

void CAN_Transmit(uint32_t id, uint8_t *data, uint8_t len);
void CAN_SendDistanceSensors(void);

extern CAN_HandleTypeDef hcan;
extern volatile uint16_t water_adc;
extern volatile uint8_t  fire_detect;
extern volatile uint8_t  tilt_detect;
extern volatile int32_t  distance_back;
extern volatile int32_t  distance_side;

#endif