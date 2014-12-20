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
#ifndef __OREOLED_I2C_H__
#define __OREOLED_I2C_H__

class OreoLED_I2C : public RGBLed
{
public:
    // constuctor
    OreoLED_I2C();

    bool hw_init(void);
    bool hw_set_rgb(uint8_t r, uint8_t g, uint8_t b);

private:
    // health flags for each LED
    uint8_t _healthy1 : 1;
    uint8_t _healthy2 : 1;
    uint8_t _healthy3 : 1;
    uint8_t _healthy4 : 1;
};

#endif // __OREOLED_I2C_H__
