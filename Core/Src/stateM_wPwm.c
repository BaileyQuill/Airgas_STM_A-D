/**
  * Created on: Jun 8, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : stateM_wPwm.c
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

#include <stateM_wPwm.h>
#include <config.h> /* for voltage reference */

/* I learned my lesson from the LEDs -_- but also don't love using their button function explicitly because what if you want to switch to an external button.
 * so macros. long rant for "I don't like stms interface, but also I already burnt enough time down that rabbit hole"
 */
#define GRAB_BUTTON_STATE BSP_PB_GetState(BUTTON_USER)

/* thresholds in volts */
#define PWM_STATE_LOW_2_HIGH_THRESH_V 2.5
#define PWM_STATE_HIGH_2_LOW_THRESH_V 2.5
/* thresholds conv to uint32_t range */
#define ADC_UINT32_MAX_VALUE 4294967295
#define PWM_STATE_L2H_THRESH ( ADC_UINT32_MAX_VALUE * (2.5 / ANALOG_VOLTAGE_REFERENCE) )
#define PWM_STATE_H2L_THRESH ( ADC_UINT32_MAX_VALUE * (2.5 / ANALOG_VOLTAGE_REFERENCE) )

/* debounce time in ms */
#define BUTTON_DB_OFF_2_ON_MS 2000
#define BUTTON_DB_ON_2_OFF_MS 1

#define BUTTON_ON_BLINK_HZ        10
#define BUTTON_ON_BLINK_PERIOD_MS (500 / BUTTON_ON_BLINK_HZ)

typedef enum {
    ap_below_threshold,
    ap_above_threshold,
}AdcPwm_State;

typedef enum {
    bd_off,
    bd_off2on,
    bd_on,
    bd_on2off
}ButtonDebounce_State;

/** @brief Services the "with pwm" state machine
 * @param adc_ch pointer to the adc handler
 * @param statusLed pointer to the LED to flash when button is debounced
 * @return void
 */
void ServiceState_wPwm (ADC_HandleTypeDef *adc_ch, SftwPwm_t *statusLed) {
    /* set states to defaults */
    static AdcPwm_State         adcState    = ap_below_threshold;
    static ButtonDebounce_State buttonState = bd_off;
    static SftwTimer_t          sftwTimer   = DEFAULT_SFTW_TIMER;

    /* Start ADC Conversion. currently using polling, which is blocking when you try to grab it so starting the conversion first.
     * the potential hit to main loop time should be fine in this case since we aren't currently running any other services and don't have any harsh time requirements*/
    HAL_ADC_Start(adc_ch);

    /* run button debounce */
    switch (buttonState) {
        default:
            /* shouldn't be here, get to a known safe state */
            break;

        case bd_off:
            if ( GRAB_BUTTON_STATE == GPIO_PIN_SET ) {
                sftwTimer.period = BUTTON_DB_OFF_2_ON_MS;
                ResetTimer(&sftwTimer);
                buttonState = bd_off2on;
            }
            break;

        case bd_off2on:
            if (GRAB_BUTTON_STATE == GPIO_PIN_RESET) {
                buttonState = bd_off;
            } else if ( TimerUp(&sftwTimer) ) {
                buttonState = bd_on;
                /* button state is on, enable LED blink */
                UpdateSftwPwm(statusLed, BUTTON_ON_BLINK_PERIOD_MS);
                EnableSftwPwm(statusLed);
            }
            break;

        case bd_on:
            if ( GRAB_BUTTON_STATE == GPIO_PIN_RESET ) {
                sftwTimer.period = BUTTON_DB_ON_2_OFF_MS;
                ResetTimer(&sftwTimer);
                buttonState = bd_on2off;
            }
            break;

        case bd_on2off:
            if (GRAB_BUTTON_STATE == GPIO_PIN_SET) {
                buttonState = bd_on;
            } else if ( TimerUp(&sftwTimer) ) {
                buttonState = bd_off;
                /* button state is off, disable LED blink */
                DisableSftwPwm(statusLed);
            }
            break;
    }

    /* Now grab the adc value we started earlier and handle the adcState */
    if ( HAL_ADC_PollForConversion(adc_ch, 1) == HAL_OK ) { /* spin up to 1 ms waiting for adc */
        /* adcValue from 0/ground to 4294967295/vref*/
        uint32_t adcValue = HAL_ADC_GetValue(adc_ch);

        switch (adcState) {
        default:
            /* shouldn't be here, get to a known safe state */
            break;

        case ap_below_threshold:
            if (adcValue > PWM_STATE_L2H_THRESH) {
                adcState = ap_above_threshold;
                /* just passed threshold, startup pwm */
            }
            break;

        case ap_above_threshold:
                if (adcValue < PWM_STATE_H2L_THRESH) {
                    adcState = ap_below_threshold;
                    /* just passed threshold, shutdown pwm */
                }
            break;
        }

    } else {
        /* failed to grab adc value
         * TODO: handle edge case
         */
    }
};
