/*
   OreoLED I2C driver

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
#ifndef __OREOLED_PX4_H__
#define __OREOLED_PX4_H__

#include <AP_HAL.h>
#include "NotifyDevice.h"

#define OREOLED_NUM_LEDS    4   // maximum number of individual LEDs connected to the oreo led cpu

class OreoLED_PX4 : public NotifyDevice
{
public:
    // constuctor
    OreoLED_PX4();

    // init - initialised the device
    bool init(void);

    // update - updates device according to timed_updated.  Should be
    // called at 50Hz
    void update();

    // healthy - return true if at least one LED is responding
    bool healthy() const { return _overall_health; }

    // set_rgb - set color as a combination of red, green and blue values for all LEDs
    void set_rgb(uint8_t red, uint8_t green, uint8_t blue);

private:
    // overall health
    uint8_t _overall_health : 1;

    // file descriptor
    int     _oreoled_fd;
};

#endif // __OREOLED_PX4_H__
