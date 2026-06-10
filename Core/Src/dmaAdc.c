/**
  * Created on: Jun 8, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : dmaAdc.h
  * @brief          : dma based adc to just have the most recent adc reading
  *             note: currently only setup to handle one adc device (multiple channels, all same adc device ie ADC1)
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#include <dmaAdc.h>
#include <config.h>
#include <main.h>

volatile uint32_t dmaBuffer [ADC_CHANNEL_COUNT] = {0};

void DmaAdcStart (ADC_HandleTypeDef* hadc) {
    /* Calibrate The ADC On Power-Up For Better Accuracy */
    HAL_ADCEx_Calibration_Start(hadc);
    HAL_ADC_Start_DMA(hadc, &dmaBuffer[0], ADC_CHANNEL_COUNT);
};

/* Hal callback function for the adc */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    for (uint16_t ch_id = 0; ch_id < ADC_CHANNEL_COUNT; ch_id++) {
        ADC_READINGS[ch_id] = dmaBuffer[ch_id];
    }
    HAL_ADC_Start_DMA(hadc, &dmaBuffer[0], ADC_CHANNEL_COUNT);
};

