#include "can.h"
#include "string.h"

void CAN_Transmit(uint32_t id, uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

    txHeader.StdId = id;
    txHeader.ExtId = 0;
    txHeader.IDE = CAN_ID_STD;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.DLC = len;
    txHeader.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_AddTxMessage(&hcan, &txHeader, data, &txMailbox) != HAL_OK)
    {
        Error_Handler();
    }
}

void CAN_SendDistanceSensors(void)
{
    uint8_t data[2];

		data[0] = (distance_back < 0) ? 0 : (distance_back > 255 ? 255 : distance_back);
		data[1] = (distance_side < 0) ? 0 : (distance_side > 255 ? 255 : distance_side);

    CAN_Transmit(0x120, data, 2);
}