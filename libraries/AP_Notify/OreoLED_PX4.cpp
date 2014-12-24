/*
  OreoLED PX4 driver
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

#if CONFIG_HAL_BOARD == HAL_BOARD_PX4
#include "OreoLED_PX4.h"
#include "AP_Notify.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <drivers/drv_oreoled.h>
#include <stdio.h>
#include <errno.h>

extern const AP_HAL::HAL& hal;

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
OreoLED_PX4::OreoLED_PX4() : NotifyDevice(),
    _overall_health(false),
    _oreoled_fd(-1)
{
}

// init - initialised the device
bool OreoLED_PX4::init()
{
    // open the tone alarm device
    _oreoled_fd = open(OREOLED_DEVICE_PATH, O_WRONLY);
    if (_oreoled_fd == -1) {
        hal.console->printf("Unable to open " OREOLED_DEVICE_PATH);
        _overall_health = false;
    } else {
        // set overall health
        _overall_health = true;
    }

    // return health
    return _overall_health;
}

// update - updates device according to timed_updated.  Should be
// called at 50Hz
void OreoLED_PX4::update()
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
        set_rgb(0xff, 0x0, 0x0);
    }

    // flash LED green
    if (counter == 50) {
        set_rgb(0x0, 0xff, 0x0);
    }
}

// set_rgb - set color as a combination of red, green and blue values
void OreoLED_PX4::set_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    // return immediately if no healty leds
    if (!_overall_health) {
        return;
    }

    // create desired pattern command
    uint8_t cmd[] = {OREOLED_PATTERN_SOLID, OREOLED_PARAM_BIAS_RED, red, OREOLED_PARAM_BIAS_GREEN, green, OREOLED_PARAM_BIAS_BLUE, blue};

    // send pattern to all LEDs
    for (uint8_t i=0; i<OREOLED_NUM_LEDS; i++) {
        oreoled_rgbset_t rgb_set = {OREOLED_ALL_INSTANCES, OREOLED_PATTERN_SOLID, 0xff, 0x0, 0x0};   // red
        ioctl(_oreoled_fd, OREOLED_SET_RGB, (unsigned long)&rgb_set);
    }
}

#endif // CONFIG_HAL_BOARD == HAL_BOARD_PX4
