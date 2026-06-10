/**
  * Created on: Jun 7, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : sftw_pwm.c
  * @brief          : software/ service based pwm Note currently only supporting 50% duty cycle
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#include <sftw_pwm.h>

/** @brief 'initializer' for SftwPwm_t 'object'
 * @param GPIO_TypeDef *gpiox
 * @param uint16_t      gpio_pin
 * @return SftwPwm_t 'object'
 */
SftwPwm_t SftwPwm(GPIO_TypeDef *gpiox, uint16_t gpio_pin, bool activeHigh){
    SftwPwm_t sftwPwm = {
            .gpiox          = gpiox,
            .gpio_pin       = gpio_pin,
            /* set currentState to off based on activeHigh */
            .currentState   = (activeHigh) ? GPIO_PIN_RESET : GPIO_PIN_SET,
            .timer          = DEFAULT_SFTW_TIMER,
            .activeHigh     = activeHigh
    };
    /* ensure non floating/ on gpio */
    HAL_GPIO_WritePin(sftwPwm.gpiox, sftwPwm.gpio_pin, sftwPwm.currentState);
    return sftwPwm;
};

/** @brief starts the SftwTimer to start driving the SftwPwm
 *    gpio starts high
 * @param *sftwPwm pointer to the software pwm
 *
 * @return void
 */
void EnableSftwPwm(SftwPwm_t *sftwPwm){
    /* TODO: not my favorite way to do this */
    /* Set the timers start time to now (also sets mode to single fire if disabled*/
    ResetTimer(&sftwPwm->timer);
    /* update mode from single fire to periodic */
    sftwPwm->timer.currentMode  = st_periodic;
    /* set currentState to on based on activeHigh */
    sftwPwm->currentState   = (sftwPwm->activeHigh) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(sftwPwm->gpiox, sftwPwm->gpio_pin, sftwPwm->currentState);
};

/** @brief stops the SftwTimer and forces the gpio low
 * @param *sftwPwm pointer to the software pwm
 *
 * @return void
 */
void DisableSftwPwm(SftwPwm_t *sftwPwm){
    /* disable timer */
    sftwPwm->timer.currentMode  = st_disabled;
    /* set currentState to off based on activeHigh */
    sftwPwm->currentState   = (sftwPwm->activeHigh) ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(sftwPwm->gpiox, sftwPwm->gpio_pin, sftwPwm->currentState);
};

/** @brief updates the SftwTimers period in ms
 *    resizes current timeout to match
 * @param *sftwPwm pointer to the software pwm
 * @param period in ms to update the current period to
 * @return void
 */
void UpdateSftwPwm(SftwPwm_t *sftwPwm, uint32_t period){
    /* TODO yeeaah most of sftw_timer should probably just be macros */
    UpdateTimer(&sftwPwm->timer, period);
};

/** @brief services the SftwPwm, changing gpio state when the timers up.
 * @param *sftwPwm pointer to the software pwm
 *
 * @return void
 */
void ServiceSftwPwm(SftwPwm_t *sftwPwm){
    if (TimerUp(&sftwPwm->timer)) {
        sftwPwm->currentState = (sftwPwm->currentState == GPIO_PIN_SET) ? GPIO_PIN_RESET : GPIO_PIN_SET;
        HAL_GPIO_WritePin(sftwPwm->gpiox, sftwPwm->gpio_pin, sftwPwm->currentState);
    }
};

