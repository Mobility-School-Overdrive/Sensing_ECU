#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "main.h"
#include "stdint.h"

#define WATER_SENSOR_PIN        GPIO_PIN_0
#define WATER_SENSOR_PORT       GPIOA

#define TILT_SENSOR_PIN         GPIO_PIN_9
#define TILT_SENSOR_PORT        GPIOA

#define ULTRA_TRIG_PIN          GPIO_PIN_4 // Back Ultrasonic Sensor
#define ULTRA_TRIG_PORT         GPIOB

#define ULTRA_ECHO_PIN          GPIO_PIN_5
#define ULTRA_ECHO_PORT         GPIOB

#define ULTRA2_TRIG_PIN         GPIO_PIN_10 // Side Ultrasonic Sensor
#define ULTRA2_TRIG_PORT        GPIOA

#define ULTRA2_ECHO_PIN         GPIO_PIN_3
#define ULTRA2_ECHO_PORT        GPIOB

/* Water Level Definition */
#define WATER_LEVEL_LOW         500
#define WATER_LEVEL_MID         2000
#define WATER_LEVEL_HIGH        3500

/* Ultrasonic Sensor Timeout */
#define ULTRA_TIMEOUT_US        30000



uint16_t Water_ReadLevel(void);
uint8_t  Fire_IsDetected(void);
uint8_t  Tilt_IsDetected(void);
float Ultra_Measure(GPIO_TypeDef* trig_port, uint16_t trig_pin, GPIO_TypeDef* echo_port, uint16_t echo_pin);
void Delay_us(uint32_t us);

extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim1;

#endif