/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#include <AP_HAL.h>
#include <AC_PrecLand_Backend.h>

extern const AP_HAL::HAL& hal;

// Constructor
AC_PrecLand_Companion::AC_PrecLand_Companion(const AC_PrecLand& frontend, AC_PrecLand::precland_state& state)
: AC_PrecLand_Backend(frontend, state)
{
}

// healthy - returns true if precision landing is healthy
void AC_PrecLand_Companion::init()
{
}

// get_target_vector - returns 3D vector to target
const Vector3f& AC_PrecLand_Companion::get_target_vector()
{
    return Vector2f(0,0);
}
