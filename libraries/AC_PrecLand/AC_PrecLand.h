/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#ifndef __AC_PRECLAND_H__
#define __AC_PRECLAND_H__

#include <AP_Common.h>
#include <AP_Math.h>
#include <AC_PID.h>             // PID library
#include <AP_InertialNav.h>     // Inertial Navigation library

// definitions
#define AC_PRECLAND_SPEED_XY_DEFAULT            100.0f  // maximum horizontal speed
#define PRECLAND_P                              2.0f    // velocity controller P gain default
#define PRECLAND_I                              1.0f    // velocity controller I gain default
#define PRECLAND_D                              0.0f    // velocity controller D gain default
#define PRECLAND_IMAX                         500.0f    // velocity controller IMAX default

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
    Vector3f get_target_shift(const Vector3f& orig_target);

    // parameter var table
    static const struct AP_Param::GroupInfo var_info[];

private:

    // get_behaviour - returns enabled parameter as an behaviour
    enum PrecLandBehaviour get_behaviour() const { return (enum PrecLandBehaviour)(_enabled.get()); }

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
        bool    healthy;
    } _backend_state;
    AC_PrecLand_Backend         *_backend;  // pointers to backend precision landing driver
};
#endif	// __AC_PRECLAND_H__
