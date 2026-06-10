/**
  * Created on: Jun 9, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : stateM_wLed.h
  * @brief          :
  *         2.​ Details of i. Airgas A/D w led status
  *             a.​ Read the ADC value of the channel 1, and if the value is more than 2V, set the
  *                 status LED to blink at 0.2 Hz continuously.
  *             b.​ With the hysteresis of 0.3 Volts from the threshold of 2V , if the voltage is below
  *                 1.7V blink the status LED 0.05 Hz.
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#ifndef CORE_INC_STATEM_WLED_H_
#define CORE_INC_STATEM_WLED_H_

#include <main.h> /* for chip specific hal drivers */
#include <stdbool.h>
#include <sftw_pwm.h>

/** @brief Services the "with led" state machine
 * @param statusLed pointer to the status LED to flash
 * @return void
 */
void ServiceState_wLed (SftwPwm_t *statusLed);


#endif /* CORE_INC_STATEM_WLED_H_ */
