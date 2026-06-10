/**
  * Created on: Jun 8, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : dmaAdc.h
  * @brief          : dma based adc to just have the most recent adc reading
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#ifndef CORE_INC_DMAADC_H_
#define CORE_INC_DMAADC_H_

#include <main.h> /* for chip specific hal drivers */
#include <stdbool.h>

/** @brief calibrates and starts the dma adc device
 * @param hadc pointer to adc handler
 * @return void
 */
void DmaAdcStart (ADC_HandleTypeDef* hadc);

/* Hal callback function for the adc */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

#endif /* CORE_INC_DMAADC_H_ */
