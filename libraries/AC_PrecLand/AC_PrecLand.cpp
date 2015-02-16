/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#include <AP_HAL.h>
#include <AC_PrecLand.h>
#include <AC_PrecLand_Backend.h>

extern const AP_HAL::HAL& hal;

const AP_Param::GroupInfo AC_PrecLand::var_info[] PROGMEM = {
    // @DisplayName: Precision Land enabled/disabled and behaviour
    // @Description: Precision Land enabled/disabled and behaviour
    // @Values: 0:Disabled, 1:Enabled Always Land, 2:Enabled Strict
    // @User: Advanced
    AP_GROUPINFO("ENABLED", 0, AC_PrecLand, _enabled, 0),

    // @Param: TYPE
    // @DisplayName: Precision Land Type
    // @Description: Precision Land Type
    // @Values: 0:None, 1:CompanionComputer, 2:IRLock
    // @User: Advanced
    AP_GROUPINFO("TYPE",    1, AC_PrecLand, _type, 0),

    // @Param: SPEED
    // @DisplayName: Precision Land horizontal speed maximum in cm/s
    // @Description: Precision Land horizontal speed maximum in cm/s
    // @Range: 0 500
    // @User: Advanced
    AP_GROUPINFO("SPEED",   2, AC_PrecLand, _speed_xy, AC_PRECLAND_SPEED_XY_DEFAULT),

    AP_GROUPEND
};

// Default constructor.
// Note that the Vector/Matrix constructors already implicitly zero
// their values.
//
AC_PrecLand::AC_PrecLand(const AP_AHRS& ahrs, const AP_InertialNav& inav,
                         AC_PID& pid_precland_xy, float dt) :
    _ahrs(ahrs),
    _inav(inav),
    _pid_precland_xy(pid_precland_xy),
    _dt(dt),
    _last_update_ms(0),
    _backend(NULL)
{
    // set parameters to defaults
    AP_Param::setup_object_defaults(this, var_info);

    // other initialisation
    _backend_state.healthy = false;
}


// init - perform any required initialisation of backends
void AC_PrecLand::init()
{
    // exit immediately if init has already been run
    if (_backend != NULL) {
        return;
    }

    // default health to false
    _backend = NULL;
    _backend_state.healthy = false;

    // instantiate backend based on type parameter
    switch ((enum PrecLandType)_type) {
        // no type defined
        case PRECLAND_TYPE_NONE:
        default:
            return;
        // companion computer
        case PRECLAND_TYPE_COMPANION:
            _backend = new AC_PrecLand_Companion(*this, backend_state);
            break;
        // IR Lock
        case PRECLAND_TYPE_IRLOCK:
            _backend = new AC_PrecLand_IRLock(*this, backend_state);
            break;
    }

    // init backend
    if (_backend != NULL) {
        _backend->init();
    }
}

// get_target_shift - returns 3D vector of earth-frame position adjustments to target
const Vector3f &get_target_shift(Vector3f orig_target)
{
    // exit immediately if not enabled

    // get body-frame angles to target from backend

    // convert body-frame angles to earth-frame angles

    // convert earth-frame angles to desired velocity

    // convert desired velocity to position shift using dt

    // return adjusted target
    return _target_shift;
}