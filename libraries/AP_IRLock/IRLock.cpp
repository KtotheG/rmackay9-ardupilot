/*
 * IRLock.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: MLandes
 */

#include "IRLock.h"

// default constructor
IRLock::IRLock() :
		_last_update(0),
		_num_blocks(0)
{
	// clear the frame buffer
    memset(_current_frame, 0, sizeof(_current_frame));

	// will be adjusted when init is called
	_flags.healthy = false;
}

IRLock::~IRLock() {}

void IRLock::get_current_frame(irlock_block data[IRLOCK_MAX_BLOCKS_PER_FRAME]) const
{
    // clear data
    memset(data, 0, sizeof(data));

	for (uint16_t index=0; index < _num_blocks; ++index) {
		data[index].signature = _current_frame[index].signature;
		data[index].center_x = _current_frame[index].center_x;
		data[index].center_y = _current_frame[index].center_y;
		data[index].width = _current_frame[index].width;
		data[index].height = _current_frame[index].height;
	}
}

// get_angle_to_target - retrieve body frame x and y angles (in radians) to target
//  returns true if angles are available, false if not (i.e. no target)
bool IRLock::get_angle_to_target(float &x_angle_rad, float &y_angle_rad) const
{
    // return false if we have no target
    if (_num_blocks == 0) {
        return false;
    }

    // use data from first object
    x_angle_rad = (((float)(_current_frame[0].center_x-IRLOCK_CENTER_X))/IRLOCK_X_PIXEL_PER_DEGREE) * DEG_TO_RAD;
    y_angle_rad = (((float)(_current_frame[0].center_y-IRLOCK_CENTER_X))/IRLOCK_X_PIXEL_PER_DEGREE) * DEG_TO_RAD;
    return true;
}