/**
  * Created on: Jun 8, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : stateM_wPwm.h
  * @brief          :
  *         3.​ Details of ii. Airgas A/D w PWM.
  *             a.​ Read the ADC value of channel 2, and if the value is more than 2.5V, set the
  *                 PWM to 100 Hz (50 % duty cycle).
  *             b.​ Blink the status LED to 10 Hz, when the B1 user switch is pressed more than 2
  *                 secs.
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#ifndef CORE_INC_STATEM_WPWM_H_
#define CORE_INC_STATEM_WPWM_H_

#include <main.h> /* for chip specific hal drivers */
#include <stdbool.h>
#include <sftw_pwm.h>

/** @brief Services the "with pwm" state machine
 * @param statusLed pointer to the LED to flash when button is debounced
 * @param pwm pointer to the pwm handler
 * @param pwm_ch uint32_t timer channel for the pwm
 * @return void
 */
void ServiceState_wPwm (SftwPwm_t *statusLed, TIM_HandleTypeDef *pwm, uint32_t pwm_ch);


#endif /* CORE_INC_STATEM_WPWM_H_ */
