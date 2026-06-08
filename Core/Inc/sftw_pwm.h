/**
  * Created on: Jun 7, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : sftw_pwm.h
  * @brief          : software/ service based pwm Note currently only supporting 50% duty cycle
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#ifndef CORE_INC_SFTW_PWM_H_
#define CORE_INC_SFTW_PWM_H_

#include <main.h> /* for chip specific hal drivers */
#include "sftw_timer.h"

typedef struct {
	/* GPIOx where x to select the GPIO peripheral for device family */
	GPIO_TypeDef *gpiox;
	/* GPIO_Pin port */
	uint16_t      gpio_pin;
	GPIO_PinState currentState;
	SftwTimer_t   timer;
} SftwPwm_t;

/** @brief 'initializer' for SftwPwm_t 'object'
 * @param GPIO_TypeDef *gpiox
 * @param uint16_t      gpio_pin
 * @return SftwPwm_t 'object'
 */
SftwPwm_t SftwPwm(GPIO_TypeDef *gpiox, uint16_t gpio_pin);

/** @brief starts the SftwTimer to start driving the SftwPwm
 *    gpio starts high
 * @param *sftwPwm pointer to the software pwm
 *
 * @return void
 */
void EnableSftwPwm(SftwPwm_t *sftwPwm);

/** @brief stops the SftwTimer and forces the gpio low
 * @param *sftwPwm pointer to the software pwm
 *
 * @return void
 */
void DisableSftwPwm(SftwPwm_t *sftwPwm);

/** @brief updates the SftwTimers period in ms
 *    resizes current timeout to match
 * @param *sftwPwm pointer to the software pwm
 * @param period in ms to update the current period to
 * @return void
 */
void UpdateSftwPwm(SftwPwm_t *sftwPwm, uint32_t period);

/** @brief services the SftwPwm, changing gpio state when the timers up.
 * @param *sftwPwm pointer to the software pwm
 *
 * @return void
 */
void ServiceSftwPwm(SftwPwm_t *sftwPwm);


#endif /* CORE_INC_SFTW_PWM_H_ */
