#include "sensor.h"

/* ================= SENSOR ================= */

uint16_t Water_ReadLevel(void)
{
    HAL_ADC_Start(&hadc);

    if (HAL_ADC_PollForConversion(&hadc, 100) == HAL_OK)
    {
        uint16_t val = (uint16_t)HAL_ADC_GetValue(&hadc);
        HAL_ADC_Stop(&hadc);
        return val;
    }

    HAL_ADC_Stop(&hadc);
    return 0;
}

uint8_t Tilt_IsDetected(void)
{
    return (HAL_GPIO_ReadPin(TILT_SENSOR_PORT, TILT_SENSOR_PIN) == GPIO_PIN_SET) ? 1 : 0;
}

/* ================= ULTRASONIC ================= */

float Ultra_Measure(GPIO_TypeDef* trig_port, uint16_t trig_pin, GPIO_TypeDef* echo_port, uint16_t echo_pin)
{
    uint32_t timeout, echo_start, echo_end;

    /* TRIG */
    HAL_GPIO_WritePin(trig_port, trig_pin, GPIO_PIN_RESET);
    Delay_us(2);
    HAL_GPIO_WritePin(trig_port, trig_pin, GPIO_PIN_SET);
    Delay_us(10);
    HAL_GPIO_WritePin(trig_port, trig_pin, GPIO_PIN_RESET);

    /* ECHO HIGH Wait */
    timeout = HAL_GetTick();
    while (HAL_GPIO_ReadPin(echo_port, echo_pin) == GPIO_PIN_RESET)
    {
        if ((HAL_GetTick() - timeout) > 30)
            return -1.0f;
    }

    echo_start = __HAL_TIM_GET_COUNTER(&htim1);

    /* ECHO LOW Wait */
    timeout = HAL_GetTick();
    while (HAL_GPIO_ReadPin(echo_port, echo_pin) == GPIO_PIN_SET)
    {
        if ((HAL_GetTick() - timeout) > 30)
            return -1.0f;
    }

    echo_end = __HAL_TIM_GET_COUNTER(&htim1);

    uint32_t duration_us = echo_end - echo_start;
    return (float)duration_us / 58.0f;
}

void Delay_us(uint32_t us)
{
    uint32_t start = __HAL_TIM_GET_COUNTER(&htim1);
    while ((__HAL_TIM_GET_COUNTER(&htim1) - start) < us);
}