/**
  * Created on: Jun 7, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : sftw_timer.h
  * @brief          : software/ service based timer
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
#include <stdbool.h>

typedef enum {
	st_disabled,   /* timer always returns false */
	st_singleFire, /* can be used for one off timings, or timers that you want to manualy restart (ie timing based off last completed [whatever timers for]) */
	st_periodic    /* happens every x (SftwTimer_t.period) ms from initial start. */
	/* Note in this mode if the service falls behind the timer will trigger every time it's called until the time timeToFire catches up to current system up time */
}SftwTimer_modes;

typedef struct {
	uint32_t        timeToFire; /* uptime in ms when the timer will fire again */
	uint32_t        period;     /* time in ms to increment timeToFire by for repeate timers */
	SftwTimer_modes current_mode;
} SftwTimer_t;

/** @brief Checks weather the supplied timer is firing
 *   timers in st_periodic mode will increment their next time to fire when returning true.
 * @param *timer pointer to the timer to check
 * @return true if the timer fired.
 */
bool TimerUp (SftwTimer_t *timer);

/** @brief re-enables the timer if disabled and sets the timeToFire to current time + period
 * @param *timer pointer to the timer to reset
 * @return void
 */
void ResetTimer (SftwTimer_t *timer);

/** @brief updates the period and shifts the current timeToFire to match.
 * @param *timer pointer to the timer to update
 * @param uint32_t period in ms to update the timer to
 * @return void
 */
void UpdateTimer (SftwTimer_t *timer, uint32_t newPeriod);

#endif /* CORE_INC_SFTW_PWM_H_ */
