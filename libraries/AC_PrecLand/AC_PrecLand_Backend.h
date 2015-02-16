/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#ifndef AC_PRECLAND_BACKEND_H
#define AC_PRECLAND_BACKEND_H

#include <AP_Common.h>
#include <AP_Math.h>
#include <AC_PID.h>             // PID library
#include <AP_InertialNav.h>     // Inertial Navigation library
#include <AC_PrecLand.h>        // Precision Landing frontend

class AC_PrecLand_Backend
{
public:

    // Constructor
    AC_PrecLand_Backend(const AC_PrecLand& frontend, AC_PrecLand::precland_state& state);

    // init - perform any required initialisation of backend controller
    virtual void init() = 0;

    // get_target_rad - returns 2D body frame angles (in radians) to target
    //  x : body-frame roll direction, positive = target is to right (looking down)
    //  y : body-frame pitch direction, postiive = target is forward (looking down)
    virtual const Vector2f &get_target_rad() = 0;

private:

    const AC_PrecLand&  _frontend;          // reference to precision landing front end
    AC_PrecLand::precland_state &_state;    // reference to this instances state
};
#endif	// AC_PRECLAND_BACKEND_H