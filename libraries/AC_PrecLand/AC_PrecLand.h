/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#ifndef AC_PRECLAND_H
#define AC_PRECLAND_H

#include <AP_Common.h>
#include <AP_Math.h>
#include <AC_PID.h>             // PID library
#include <AP_InertialNav.h>     // Inertial Navigation library

// definitions
#define AC_PRECLAND_SPEED_XY_DEFAULT            100.0f  // maximum horizontal speed

// declare backend classes
class AC_PrecLand_Backend;
class AC_PrecLand_Companion;
class AC_PrecLand_IRLock;

class AC_PrecLand
{
    // declare backends as friends
    friend class AC_PrecLand_Backend;
    friend class AC_PrecLand_Companion;
    friend class AC_PrecLand_IRLock;

public:

    // precision landing behaviours (held in PRECLAND_ENABLED parameter)
    enum PrecLandBehaviour {
        PRECLAND_BEHAVIOUR_DISABLED,
        PRECLAND_BEHAVIOR_ALWAYSLAND,
        PRECLAND_BEHAVIOR_CAUTIOUS
    };

    // types of precision landing (used for PRECLAND_TYPE parameter)
    enum PrecLandType {
        PRECLAND_TYPE_NONE,
        PRECLAND_TYPE_COMPANION,
        PRECLAND_TYPE_IRLOCK
    };

    // Constructor
    AC_PrecLand(const AP_AHRS& ahrs, const AP_InertialNav& inav, AC_PID& pid_precland_xy, float dt);

    // init - perform any required initialisation of landing controllers
    void init();

    // healthy - returns true if precision landing is healthy
    bool healthy() { return _backend_state.healthy; }

    // get_target_shift - returns 3D vector of earth-frame position adjustments to target
    const Vector3f &get_target_shift(Vector3f orig_target);

    // parameter var table
    static const struct AP_Param::GroupInfo var_info[];

private:

    // get_behaviour - returns enabled parameter as an behaviour
    enum PrecLandBehaviour get_behaviour() const { return (enum PrecLandBehaviour)_enabled; }

    // references to inertial nav and ahrs libraries
    const AP_AHRS&              _ahrs;
    const AP_InertialNav&       _inav;
    AC_PID&                     _pid_precland_xy;   // horizontal PID controller

    // parameters
    AP_Int8                     _enabled;           // enabled/disabled and behaviour
    AP_Int8                     _type;              // precision landing controller type
    AP_Float                    _speed_xy;          // maximum horizontal speed in cm/s

    // internal variables
    float                       _dt;                // time difference (in seconds) between calls from the main program
    uint32_t                    _last_update_ms;    // system time of last get_target_vector call

    // output from controller
    Vector3f                    _target_shift;      // last position shift applied to target

    // backend state
    struct precland_state {
        bool    heathy;
    } _backend_state;
    AC_PrecLand_Backend         *_backend;  // pointers to backend precision landing driver
};
#endif	// AC_PRECLAND_H