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
#include <config.h> /* for voltage reference and adc channel/ reading(s) */

/* thresholds in volts */
#define PWM_STATE_LOW_2_HIGH_THRESH_V 2.0
#define PWM_STATE_HIGH_2_LOW_THRESH_V 1.7
/* thresholds conv to adc range */
#define ADC_MAX_VALUE 4095
#define PWM_STATE_L2H_THRESH ( ADC_MAX_VALUE * (2.5 / ANALOG_VOLTAGE_REFERENCE) )
#define PWM_STATE_H2L_THRESH ( ADC_MAX_VALUE * (2.5 / ANALOG_VOLTAGE_REFERENCE) )

#define STATE_HIGH_BLINK_HZ        0.2
#define STATE_HIGH_BLINK_PERIOD_MS (500 / STATE_HIGH_BLINK_HZ)

#define STATE_LOW__BLINK_HZ        0.05
#define STATE_LOW__BLINK_PERIOD_MS (500 / STATE_LOW__BLINK_HZ)

typedef enum {
    ap_below_threshold,
    ap_above_threshold,
}AdcPwm_State;

/** @brief Services the "with led" state machine
 * @param statusLed pointer to the status LED to flash
 * @return void
 */
void ServiceState_wLed (SftwPwm_t *statusLed) {
    /* set states to defaults */
    static AdcPwm_State         adcState    = ap_below_threshold;

    /* adcValue from 0/ground to vref*/
    uint32_t adcValue = ADC_READINGS[ch_ledAdcIn];
    switch (adcState) {
        default:
        /* shouldn't be here, get to a known safe state */
            UpdateSftwPwm(statusLed, STATE_LOW__BLINK_PERIOD_MS);
            adcState = ap_below_threshold;
        break;

        case ap_below_threshold:
            if (adcValue > PWM_STATE_L2H_THRESH) {
                adcState = ap_above_threshold;
                /* just passed threshold, high mode led */
                UpdateSftwPwm(statusLed, STATE_HIGH_BLINK_PERIOD_MS);
            }
            break;

        case ap_above_threshold:
            if (adcValue < PWM_STATE_H2L_THRESH) {
                adcState = ap_below_threshold;
                /* just passed threshold, high mode led */
                UpdateSftwPwm(statusLed, STATE_LOW__BLINK_PERIOD_MS);
            }
            break;
        }


};
