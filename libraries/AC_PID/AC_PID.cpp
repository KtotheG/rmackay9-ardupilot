// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

/// @file	AC_PID.cpp
/// @brief	Generic PID algorithm

#include <AP_Math.h>
#include "AC_PID.h"

const AP_Param::GroupInfo AC_PID::var_info[] PROGMEM = {
    // @Param: P
    // @DisplayName: PID Proportional Gain
    // @Description: P Gain which produces an output value that is proportional to the current error value
    AP_GROUPINFO("P",    0, AC_PID, _kp, 0),

    // @Param: I
    // @DisplayName: PID Integral Gain
    // @Description: I Gain which produces an output that is proportional to both the magnitude and the duration of the error
    AP_GROUPINFO("I",    1, AC_PID, _ki, 0),

    // @Param: D
    // @DisplayName: PID Derivative Gain
    // @Description: D Gain which produces an output that is proportional to the rate of change of the error
    AP_GROUPINFO("D",    2, AC_PID, _kd, 0),

    // 3 was for uint16 IMAX
    // 4 is used by TradHeli for FF

    // @Param: IMAX
    // @DisplayName: PID Integral Maximum
    // @Description: The maximum/minimum value that the I term can output
    AP_GROUPINFO("IMAX", 5, AC_PID, _imax, 0),

    // @Param: FILT_HZ
    // @DisplayName: PID Input filter frequency in Hz
    // @Description: Input filter frequency in Hz
    // @Unit: Hz
    AP_GROUPINFO("FILT", 6, AC_PID, _filt_hz, AC_PID_FILT_HZ_DEFAULT),

    AP_GROUPEND
};

// Constructor
AC_PID::AC_PID(float initial_p, float initial_i, float initial_d, float initial_imax, float initial_filt_hz, float dt) :
    _dt(dt),
    _integrator(0.0f),
    _input_filt(0.0f),
    _last_derivative(0.0f)
{
    // load parameter values from eeprom
    AP_Param::setup_object_defaults(this, var_info);

    _kp = initial_p;
    _ki = initial_i;
    _kd = initial_d;
    _imax = abs(initial_imax);
    _filt_hz = initial_filt_hz;

    // reset input filter to first value received
    _flags._reset_input_filter = true;

    // calculate the input filter alpha
    calc_filt_alpha();
}

// set_dt - set time step in seconds
void AC_PID::set_dt(float dt)
{
    // set dt and calculate the input filter alpha
    _dt = dt;
    calc_filt_alpha();
}

// set_filt_hz - set input filter hz
void AC_PID::set_filt_hz(float hz)
{
    _filt_hz.set(hz);
    // calculate the input filter alpha
    calc_filt_alpha();
}

// set_input - set input to PID controller
//  this should be called before any other calls to get_p, get_i or get_d
void AC_PID::set_input(float input)
{
    // reset input filter to value received
    if (_flags._reset_input_filter) {
        _flags._reset_input_filter = false;
        _input_filt = input;
        _last_derivative = 0.0f;
    }

    // update filter and calculate derivative
    float input_filt_change = _input_filt_alpha * (input - _input_filt);
    _input_filt = _input_filt + input_filt_change;
    if (_dt > 0.0f) {
        _last_derivative = input_filt_change / _dt;
    }
}

float AC_PID::get_p() const
{
    return (_input_filt * _kp);
}

float AC_PID::get_i()
{
    if((_ki != 0) && (_dt != 0)) {
        _integrator += ((float)_input_filt * _ki) * _dt;
        if (_integrator < -_imax) {
            _integrator = -_imax;
        } else if (_integrator > _imax) {
            _integrator = _imax;
        }
        return _integrator;
    }
    return 0;
}

float AC_PID::get_d() const
{
    // add in derivative component
    return (_kd * _last_derivative);
}

float AC_PID::get_pi()
{
    return get_p() + get_i();
}


float AC_PID::get_pid()
{
    return get_p() + get_i() + get_d();
}


void AC_PID::reset_I()
{
    _integrator = 0;
}

void AC_PID::load_gains()
{
    _kp.load();
    _ki.load();
    _kd.load();
    _imax.load();
    _imax = abs(_imax);
    _filt_hz.load();

    // calculate the input filter alpha
    calc_filt_alpha();
}

// save_gains - save gains to eeprom
void AC_PID::save_gains()
{
    _kp.save();
    _ki.save();
    _kd.save();
    _imax.save();
    _filt_hz.save();
}

/// Overload the function call operator to permit easy initialisation
void AC_PID::operator() (float p, float i, float d, float imaxval, float input_filt_hz, float dt)
{
    _kp = p;
    _ki = i;
    _kd = d;
    _imax = abs(imaxval);
    _filt_hz = input_filt_hz;
    _dt = dt;
    // calculate the input filter alpha
    calc_filt_alpha();
}

// calc_filt_alpha - recalculate the input filter alpha
void AC_PID::calc_filt_alpha()
{    
    // calculate alpha
    float rc = 1/(2*PI*_filt_hz);
    _input_filt_alpha = _dt / (_dt + rc);
}
