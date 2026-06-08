/**
  * Created on: Jun 7, 2026
  * Author: Bailey Quill
  ******************************************************************************
  * @file           : sftw_timer.c
  * @brief          : software/ service based timer
  ******************************************************************************
  * @attention
  *
  * TODO: license/ copyright
  *
  ******************************************************************************
  */

#include <sftw_timer.h>

/** @brief Checks weather the supplied timer is firing
 *   timers in st_periodic mode will increment their next time to fire when returning true.
 * @param *timer pointer to the timer to check
 * @return true if the timer fired.
 */
bool TimerUp (SftwTimer_t *timer) {
    bool timeElapsed = false;
    switch (timer->currentMode) {
      case st_singleFire:
      case st_periodic:
         if (HAL_GetTick() >= timer->timeToFire) {
             timeElapsed = true;
             if (timer->currentMode == st_periodic) {
                 timer->timeToFire += timer->period;
             } else {
                 timer->currentMode = st_disabled;
             }
         }
         break;

      default:
          break;
    }
    return timeElapsed;
};

/** @brief re-enables the timer if disabled and sets the timeToFire to current time + period
 * @param *timer pointer to the timer to reset
 * @return void
 */
void ResetTimer (SftwTimer_t *timer){
    timer->timeToFire = HAL_GetTick() + timer->period;
    if (timer->currentMode == st_disabled) {
        timer->currentMode = st_singleFire;
    }
};

/** @brief updates the period and shifts the current timeToFire to match.
 * @param *timer pointer to the timer to update
 * @param uint32_t period in ms to update the timer to
 * @return void
 */
void UpdateTimer (SftwTimer_t *timer, uint32_t newPeriod){
    timer->timeToFire += (newPeriod - timer->period);
    timer->period = newPeriod;
};
