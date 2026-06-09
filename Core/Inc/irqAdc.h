/**
  * Created on: Jun 8, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : irqAdc.h
  * @brief          : interrupt based adc to just have the most recent adc reading
  *         I'm going off in the weeds again. pollings more than fine for now
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#ifndef CORE_INC_IRQADC_H_
#define CORE_INC_IRQADC_H_

#include <main.h> /* for chip specific hal drivers */
#include <stdbool.h>

typedef struct {
    ADC_HandleTypeDef *hadc; /* pointer to adc handle */
    void  *callbackFunction;
} IrqAdc_t;


#endif /* CORE_INC_IRQADC_H_ */
