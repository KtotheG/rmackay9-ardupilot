/*
  OreoLED I2C driver
*/
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <AP_HAL.h>

#if CONFIG_HAL_BOARD != HAL_BOARD_PX4

#include "OreoLED_I2C.h"

extern const AP_HAL::HAL& hal;

#define OREOLED_BRIGHT                  0xFF    // full brightness
#define OREOLED_MEDIUM                  0xFF    // medium brightness
#define OREOLED_DIM                     0xFF    // dim
#define OREOLED_OFF                     0x00    // off

#define OREOLED_BASE_I2C_ADDR           0x68    // default I2C bus address for 1st LED

#define OREOLED_PATTERN_OFF             0x00    // led off
#define OREOLED_PATTERN_SINE            0x01    // sine wave pattern
#define OREOLED_PATTERN_SOLID           0x02    // solid pattern
#define OREOLED_PATTERN_SIREN           0x03    // siren pattern
#define OREOLED_PATTERN_STROBE          0x04    // strobe pattern
#define OREOLED_PATTERN_FADEIN          0x05    // fade in pattern
#define OREOLED_PATTERN_FADEOUT         0x06    // fade out pattern
#define OREOLED_PATTERN_PARAMUPDATE     0x07    // parameter update pattern

#define OREOLED_PARAM_BIAS_RED          0x00    // set redness
#define OREOLED_PARAM_BIAS_GREEN        0x01    // set greenness
#define OREOLED_PARAM_BIAS_BLUE         0x02    // set blueness
#define OREOLED_PARAM_AMPLITUDE_RED     0x03    // set max red during sire, strobe or fade-in
#define OREOLED_PARAM_AMPLITUDE_GREEN   0x04    // set max green during sire, strobe or fade-in
#define OREOLED_PARAM_AMPLITUDE_BLUE    0x05    // set max blue during sire, strobe or fade-in
#define OREOLED_PARAM_PERIOD            0x06
#define OREOLED_PARAM_REPEAT            0x07
#define OREOLED_PARAM_PHASEOFFSET       0x08
#define OREOLED_PARAM_MACRO             0x09

#define OREOLED_PARAM_MACRO_RESET       0x00
#define OREOLED_PARAM_MACRO_FWUPDATE    0x01
#define OREOLED_PARAM_MACRO_AUTOPILOT   0x02
#define OREOLED_PARAM_MACRO_CALIBRATE   0x03
#define OREOLED_PARAM_MACRO_POWERON     0x04
#define OREOLED_PARAM_MACRO_POWEROFF    0x05
#define OREOLED_PARAM_MACRO_RED         0x06
#define OREOLED_PARAM_MACRO_GREEN       0x07
#define OREOLED_PARAM_MACRO_BLUE        0x08
#define OREOLED_PARAM_MACRO_AMBER       0x09
#define OREOLED_PARAM_MACRO_WHITE       0x0A

// constructor
OreoLED_I2C::OreoLED_I2C() : NotifyDevice(),
    _overall_health(false)
{
    // default individual led health to false
    memset(_healthy, 0, sizeof(_healthy));
}

// init - initialised the device
bool OreoLED_I2C::init()
{
    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();

    // take i2c bus sempahore
    if (!i2c_sem->take(HAL_SEMAPHORE_BLOCK_FOREVER)) {
        return false;
    }

    // disable recording of i2c lockup errors
    hal.i2c->ignore_errors(true);

    uint8_t cmd[] = {OREOLED_PATTERN_OFF};

    // default overall health to unhealthy
    _overall_health = false;

    // attempt to turn each led off
    for (uint8_t i=0; i<OREOLED_NUM_LEDS; i++) {
        _healthy[i] = (hal.i2c->write(OREOLED_BASE_I2C_ADDR + i, sizeof(cmd), cmd) == 0);

        // set overall health
        if (_healthy[i]) {
            _overall_health = true;
        }
    }

    // re-enable recording of i2c lockup errors
    hal.i2c->ignore_errors(false);

    // give back i2c semaphore
    i2c_sem->give();

    // return success if we managed to talk to at least one LED
    return (_overall_health);
}

// update - updates device according to timed_updated.  Should be
// called at 50Hz
void OreoLED_I2C::update()
{
    static uint8_t counter = 0;

    // return immediately if not healthy
    if (!_overall_health) {
        return;
    }

    // increment counter
    counter++;
    if (counter >= 100) {
        counter = 0;
    }

    // flash LED red
    if (counter == 0) {
        set_rgb(0xFF, 0x0, 0x0);
    }

    // flash LED green
    if (counter == 50) {
        set_rgb(0x0, 0xFF, 0x0);
    }
}

// set_rgb - set color as a combination of red, green and blue values
void OreoLED_I2C::set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    // return immediately if no healty leds
    if (!_overall_health) {
        return;
    }

    // get pointer to i2c bus semaphore
    AP_HAL::Semaphore* i2c_sem = hal.i2c->get_semaphore();

    // exit immediately if we can't take the semaphore
    if (i2c_sem == NULL || !i2c_sem->take(5)) {
        return;
    }

    // create desired pattern command
    uint8_t cmd[] = {OREOLED_PATTERN_SOLID, OREOLED_PARAM_BIAS_RED, red, OREOLED_PARAM_BIAS_GREEN, green, OREOLED_PARAM_BIAS_BLUE, blue};

    // send pattern to healthy LEDs
    for (uint8_t i=0; i<OREOLED_NUM_LEDS; i++) {
        if (_healthy[i]) {
            hal.i2c->write(OREOLED_BASE_I2C_ADDR + i, sizeof(cmd), cmd);
        }
    }

    // give back i2c semaphore
    i2c_sem->give();
}

#endif // CONFIG_HAL_BOARD != HAL_BOARD_PX4
