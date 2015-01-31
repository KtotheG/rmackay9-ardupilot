// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
//
#ifndef __ARDUCOPTER_CONFIG_H__
#define __ARDUCOPTER_CONFIG_H__
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
//
//  DO NOT EDIT this file to adjust your configuration.  Create your own
//  APM_Config.h and use APM_Config.h.example as a reference.
//
// WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
///
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// Default and automatic configuration details.
//
// Notes for maintainers:
//
// - Try to keep this file organised in the same order as APM_Config.h.example
//
#include "defines.h"

///
/// DO NOT EDIT THIS INCLUDE - if you want to make a local change, make that
/// change in your local copy of APM_Config.h.
///
#ifdef USE_CMAKE_APM_CONFIG
 #include "APM_Config_cmake.h"  // <== Prefer cmake config if it exists
#else
 #include "APM_Config.h" // <== THIS INCLUDE, DO NOT EDIT IT. EVER.
#endif


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// HARDWARE CONFIGURATION AND CONNECTIONS
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

#ifdef CONFIG_APM_HARDWARE
#error CONFIG_APM_HARDWARE option is deprecated! use CONFIG_HAL_BOARD instead
#endif

#ifndef CONFIG_HAL_BOARD
#error CONFIG_HAL_BOARD must be defined to build ArduCopter
#endif

#ifdef __AVR_ATmega1280__
#error ATmega1280 is not supported
#endif

//////////////////////////////////////////////////////////////////////////////
// sensor types

#define CONFIG_BARO     HAL_BARO_DEFAULT
#define CONFIG_COMPASS  HAL_COMPASS_DEFAULT

#ifdef HAL_SERIAL0_BAUD_DEFAULT
# define SERIAL0_BAUD HAL_SERIAL0_BAUD_DEFAULT
#endif

//////////////////////////////////////////////////////////////////////////////
// HIL_MODE                                 OPTIONAL

#ifndef HIL_MODE
 #define HIL_MODE        HIL_MODE_DISABLED
#endif

#if HIL_MODE != HIL_MODE_DISABLED       // we are in HIL mode
 #undef CONFIG_BARO
 #define CONFIG_BARO HAL_BARO_HIL
 #undef  CONFIG_COMPASS
 #define CONFIG_COMPASS HAL_COMPASS_HIL
#endif

#define MAGNETOMETER ENABLED

// disable some features for APM1/APM2
#if HAL_CPU_CLASS < HAL_CPU_CLASS_75
 # define PARACHUTE DISABLED
 # define AC_RALLY DISABLED
 # define EPM_ENABLED DISABLED
 # define CLI_ENABLED           DISABLED
 # define FRSKY_TELEM_ENABLED   DISABLED
 # define NAV_GUIDED            DISABLED
#endif


#if HAL_CPU_CLASS < HAL_CPU_CLASS_75 || CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL || CONFIG_HAL_BOARD == HAL_BOARD_LINUX
 // low power CPUs (APM1, APM2 and SITL)
 # define MAIN_LOOP_RATE    100
 # define MAIN_LOOP_SECONDS 0.01
 # define MAIN_LOOP_MICROS  10000
#else
 // high power CPUs (Flymaple, PX4, Pixhawk, VRBrain)
 # define MAIN_LOOP_RATE    400
 # define MAIN_LOOP_SECONDS 0.0025
 # define MAIN_LOOP_MICROS  2500
#endif

//////////////////////////////////////////////////////////////////////////////
// FRAME_CONFIG
//
#ifndef FRAME_CONFIG
 # define FRAME_CONFIG   QUAD_FRAME
#endif

#if FRAME_CONFIG == QUAD_FRAME
 # define FRAME_CONFIG_STRING "QUAD"
#elif FRAME_CONFIG == TRI_FRAME
 # define FRAME_CONFIG_STRING "TRI"
#elif FRAME_CONFIG == HEXA_FRAME
 # define FRAME_CONFIG_STRING "HEXA"
#elif FRAME_CONFIG == Y6_FRAME
 # define FRAME_CONFIG_STRING "Y6"
#elif FRAME_CONFIG == OCTA_FRAME
 # define FRAME_CONFIG_STRING "OCTA"
#elif FRAME_CONFIG == OCTA_QUAD_FRAME
 # define FRAME_CONFIG_STRING "OCTA_QUAD"
#elif FRAME_CONFIG == HELI_FRAME
 # define FRAME_CONFIG_STRING "HELI"
#elif FRAME_CONFIG == SINGLE_FRAME
 # define FRAME_CONFIG_STRING "SINGLE"
#elif FRAME_CONFIG == COAX_FRAME
 # define FRAME_CONFIG_STRING "COAX"
#else
 # define FRAME_CONFIG_STRING "UNKNOWN"
#endif

/////////////////////////////////////////////////////////////////////////////////
// TradHeli defaults
#if FRAME_CONFIG == HELI_FRAME
  # define RC_FAST_SPEED                        125
  # define WP_YAW_BEHAVIOR_DEFAULT              WP_YAW_BEHAVIOR_LOOK_AHEAD
  # define RATE_ROLL_D                          0
  # define RATE_PITCH_D                         0
  # define MPU6K_FILTER                         10
  # define HELI_STAB_COLLECTIVE_MIN_DEFAULT     0
  # define HELI_STAB_COLLECTIVE_MAX_DEFAULT     1000
  # define THR_MIN_DEFAULT                      0
  # define AUTOTUNE_ENABLED                     DISABLED
#endif

/////////////////////////////////////////////////////////////////////////////////
// Y6 defaults
#if FRAME_CONFIG == Y6_FRAME
  # define RATE_ROLL_P                  0.1f
  # define RATE_ROLL_D                  0.006f
  # define RATE_PITCH_P                 0.1f
  # define RATE_PITCH_D                 0.006f
  # define RATE_YAW_P                   0.150f
  # define RATE_YAW_I                   0.015f
#endif

//////////////////////////////////////////////////////////////////////////////
// ADC Enable - used to eliminate for systems which don't have ADC.
//
#ifndef CONFIG_ADC
 # if CONFIG_HAL_BOARD == HAL_BOARD_APM1
  #   define CONFIG_ADC ENABLED
 # else
  #   define CONFIG_ADC DISABLED
 # endif
#endif

//////////////////////////////////////////////////////////////////////////////
// PWM control
// default RC speed in Hz
#ifndef RC_FAST_SPEED
   #   define RC_FAST_SPEED 490
#endif

////////////////////////////////////////////////////////
// LED and IO Pins
//
#if CONFIG_HAL_BOARD == HAL_BOARD_APM1
#elif CONFIG_HAL_BOARD == HAL_BOARD_APM2
#elif CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL
#elif CONFIG_HAL_BOARD == HAL_BOARD_PX4
#elif CONFIG_HAL_BOARD == HAL_BOARD_FLYMAPLE
#elif CONFIG_HAL_BOARD == HAL_BOARD_LINUX
 # define LED_ON           LOW
 # define LED_OFF          HIGH
#elif CONFIG_HAL_BOARD == HAL_BOARD_VRBRAIN
#endif

//////////////////////////////////////////////////////////////////////////////
// Barometer
//

#ifndef CONFIG_BARO
 # define CONFIG_BARO AP_BARO_BMP085
#endif

//////////////////////////////////////////////////////////////////////////////
// Sonar
//

#ifndef CONFIG_SONAR
 # define CONFIG_SONAR ENABLED
#endif

#ifndef SONAR_ALT_HEALTH_MAX
 # define SONAR_ALT_HEALTH_MAX 3            // number of good reads that indicates a healthy sonar
#endif

#ifndef SONAR_RELIABLE_DISTANCE_PCT
 # define SONAR_RELIABLE_DISTANCE_PCT 0.60f // we trust the sonar out to 60% of it's maximum range
#endif

#ifndef SONAR_GAIN_DEFAULT
 # define SONAR_GAIN_DEFAULT 0.8            // gain for controlling how quickly sonar range adjusts target altitude (lower means slower reaction)
#endif

#ifndef THR_SURFACE_TRACKING_VELZ_MAX
 # define THR_SURFACE_TRACKING_VELZ_MAX 150 // max vertical speed change while surface tracking with sonar
#endif

#ifndef SONAR_TIMEOUT_MS
 # define SONAR_TIMEOUT_MS  1000            // desired sonar alt will reset to current sonar alt after this many milliseconds without a good sonar alt
#endif

#ifndef SONAR_TILT_CORRECTION               // by disable tilt correction for use of range finder data by EKF
 # define SONAR_TILT_CORRECTION DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// Channel 7 and 8 default options
//

#ifndef CH7_OPTION
 # define CH7_OPTION            AUX_SWITCH_DO_NOTHING
#endif

#ifndef CH8_OPTION
 # define CH8_OPTION            AUX_SWITCH_DO_NOTHING
#endif

//////////////////////////////////////////////////////////////////////////////
// HIL_MODE                                 OPTIONAL

#ifndef HIL_MODE
 #define HIL_MODE        HIL_MODE_DISABLED
#endif

#if HIL_MODE != HIL_MODE_DISABLED       // we are in HIL mode

 #undef CONFIG_SONAR
 #define CONFIG_SONAR DISABLED

#endif


#ifndef MAV_SYSTEM_ID
 # define MAV_SYSTEM_ID          1
#endif


//////////////////////////////////////////////////////////////////////////////
// Serial port speeds.
//
#ifndef SERIAL0_BAUD
 # define SERIAL0_BAUD                   115200
#endif
#ifndef SERIAL1_BAUD
 # define SERIAL1_BAUD                    57600
#endif
#ifndef SERIAL2_BAUD
 # define SERIAL2_BAUD                    57600
#endif


//////////////////////////////////////////////////////////////////////////////
// Battery monitoring
//
#ifndef FS_BATT_VOLTAGE_DEFAULT
 # define FS_BATT_VOLTAGE_DEFAULT       10.5f       // default battery voltage below which failsafe will be triggered
#endif

#ifndef FS_BATT_MAH_DEFAULT
 # define FS_BATT_MAH_DEFAULT             0         // default battery capacity (in mah) below which failsafe will be triggered
#endif

#ifndef BOARD_VOLTAGE_MIN
 # define BOARD_VOLTAGE_MIN             4.3f        // min board voltage in volts for pre-arm checks
#endif

#ifndef BOARD_VOLTAGE_MAX
 # define BOARD_VOLTAGE_MAX             5.8f        // max board voltage in volts for pre-arm checks
#endif

// GPS failsafe
#ifndef FAILSAFE_GPS_TIMEOUT_MS
 # define FAILSAFE_GPS_TIMEOUT_MS       5000    // gps failsafe triggers after 5 seconds with no GPS
#endif
#ifndef GPS_HDOP_GOOD_DEFAULT
 # define GPS_HDOP_GOOD_DEFAULT         230     // minimum hdop that represents a good position.  used during pre-arm checks if fence is enabled
#endif

// GCS failsafe
#ifndef FS_GCS
 # define FS_GCS                        DISABLED
#endif
#ifndef FS_GCS_TIMEOUT_MS
 # define FS_GCS_TIMEOUT_MS             5000    // gcs failsafe triggers after 5 seconds with no GCS heartbeat
#endif

// Radio failsafe while using RC_override
#ifndef FS_RADIO_RC_OVERRIDE_TIMEOUT_MS
 # define FS_RADIO_RC_OVERRIDE_TIMEOUT_MS  2000    // RC Radio failsafe triggers after 2 seconds while using RC_override from ground station
#endif

// Radio failsafe
#ifndef FS_RADIO_TIMEOUT_MS
 #define FS_RADIO_TIMEOUT_MS            500     // RC Radio Failsafe triggers after 500 miliseconds with No RC Input
#endif

// possible values for FS_GCS parameter
#define FS_GCS_DISABLED                     0
#define FS_GCS_ENABLED_ALWAYS_RTL           1
#define FS_GCS_ENABLED_CONTINUE_MISSION     2

// pre-arm baro vs inertial nav max alt disparity
#ifndef PREARM_MAX_ALT_DISPARITY_CM
 # define PREARM_MAX_ALT_DISPARITY_CM       100     // barometer and inertial nav altitude must be within this many centimeters
#endif

// pre-arm check max velocity
#ifndef PREARM_MAX_VELOCITY_CMS
 # define PREARM_MAX_VELOCITY_CMS           50.0f   // vehicle must be travelling under 50cm/s before arming
#endif

// arming check's maximum acceptable accelerometer vector difference (in m/s/s) between primary and backup accelerometers
#ifndef PREARM_MAX_ACCEL_VECTOR_DIFF
  #define PREARM_MAX_ACCEL_VECTOR_DIFF      0.70f    // pre arm accel check will fail if primary and backup accelerometer vectors differ by 0.7m/s/s
#endif

// arming check's maximum acceptable rotation rate difference (in rad/sec) between primary and backup gyros
#ifndef PREARM_MAX_GYRO_VECTOR_DIFF
  #define PREARM_MAX_GYRO_VECTOR_DIFF       0.0873f  // pre arm gyro check will fail if primary and backup gyro vectors differ by 0.0873 rad/sec (=5deg/sec)
#endif

//////////////////////////////////////////////////////////////////////////////
//  EKF & DCM Checker
#ifndef EKFCHECK_THRESHOLD_DEFAULT
 # define EKFCHECK_THRESHOLD_DEFAULT    0.8f    // EKF checker's default compass and velocity variance above which the EKF's horizontal position will be considered bad
#endif
#ifndef DCMCHECK_THRESHOLD_DEFAULT
 # define DCMCHECK_THRESHOLD_DEFAULT    0.8f    // DCM checker's default yaw error threshold above which we will abandon horizontal position hold.  The units are sin(angle) so 0.8 = about 60degrees of error
#endif

//////////////////////////////////////////////////////////////////////////////
//  MAGNETOMETER
#ifndef MAGNETOMETER
 # define MAGNETOMETER                   ENABLED
#endif

// expected magnetic field strength.  pre-arm checks will fail if 50% higher or lower than this value
#if CONFIG_HAL_BOARD == HAL_BOARD_APM1 || CONFIG_HAL_BOARD == HAL_BOARD_APM2
 #ifndef COMPASS_MAGFIELD_EXPECTED
  # define COMPASS_MAGFIELD_EXPECTED     330        // pre arm will fail if mag field > 544 or < 115
 #endif
#else // PX4, SITL
 #ifndef COMPASS_MAGFIELD_EXPECTED
  #define COMPASS_MAGFIELD_EXPECTED      530        // pre arm will fail if mag field > 874 or < 185
 #endif
#endif

// max compass offset length (i.e. sqrt(offs_x^2+offs_y^2+offs_Z^2))
#ifndef CONFIG_ARCH_BOARD_PX4FMU_V1
 #ifndef COMPASS_OFFSETS_MAX
  # define COMPASS_OFFSETS_MAX          600         // PX4 onboard compass has high offsets
 #endif
#else   // APM1, APM2, SITL, FLYMAPLE, etc
 #ifndef COMPASS_OFFSETS_MAX
  # define COMPASS_OFFSETS_MAX          500
 #endif
#endif

// arming check's maximum acceptable vector difference between internal and external compass after vectors are normalized to field length of 1.0
#ifndef COMPASS_ACCEPTABLE_VECTOR_DIFF
  #define COMPASS_ACCEPTABLE_VECTOR_DIFF    0.75    // pre arm compass check will fail if internal vs external compass direction differ by more than 45 degrees
 #endif

//////////////////////////////////////////////////////////////////////////////
//  OPTICAL_FLOW
#ifndef OPTFLOW
 #if AP_AHRS_NAVEKF_AVAILABLE
  # define OPTFLOW       ENABLED
 #else
  # define OPTFLOW       DISABLED
 #endif
#endif

//////////////////////////////////////////////////////////////////////////////
//  Auto Tuning
#ifndef AUTOTUNE_ENABLED
 # define AUTOTUNE_ENABLED  ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
//  Crop Sprayer
#ifndef SPRAYER
 # define SPRAYER  DISABLED
#endif

//////////////////////////////////////////////////////////////////////////////
//	EPM cargo gripper
#ifndef EPM_ENABLED
 # define EPM_ENABLED ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// Parachute release
#ifndef PARACHUTE
 # define PARACHUTE ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// Nav-Guided - allows external nav computer to control vehicle
#ifndef NAV_GUIDED
 # define NAV_GUIDED    ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// RADIO CONFIGURATION
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// FLIGHT_MODE
//

#ifndef FLIGHT_MODE_1
 # define FLIGHT_MODE_1                  STABILIZE
#endif
#ifndef FLIGHT_MODE_2
 # define FLIGHT_MODE_2                  STABILIZE
#endif
#ifndef FLIGHT_MODE_3
 # define FLIGHT_MODE_3                  STABILIZE
#endif
#ifndef FLIGHT_MODE_4
 # define FLIGHT_MODE_4                  STABILIZE
#endif
#ifndef FLIGHT_MODE_5
 # define FLIGHT_MODE_5                  STABILIZE
#endif
#ifndef FLIGHT_MODE_6
 # define FLIGHT_MODE_6                  STABILIZE
#endif


//////////////////////////////////////////////////////////////////////////////
// Throttle Failsafe
//
#ifndef FS_THR_VALUE_DEFAULT
 # define FS_THR_VALUE_DEFAULT             975
#endif

#ifndef LAND_SPEED
 # define LAND_SPEED    50          // the descent speed for the final stage of landing in cm/s
#endif
#ifndef LAND_START_ALT
 # define LAND_START_ALT 1000         // altitude in cm where land controller switches to slow rate of descent
#endif
#ifndef LAND_DETECTOR_TRIGGER
 # define LAND_DETECTOR_TRIGGER 50    // number of 50hz iterations with near zero climb rate and low throttle that triggers landing complete.
#endif
#ifndef LAND_DETECTOR_MAYBE_TRIGGER
 # define LAND_DETECTOR_MAYBE_TRIGGER   10  // number of 50hz iterations with near zero climb rate and low throttle that means we might be landed (used to reset horizontal position targets to prevent tipping over)
#endif
#ifndef LAND_DETECTOR_CLIMBRATE_MAX
# define LAND_DETECTOR_CLIMBRATE_MAX    30  // vehicle climb rate must be between -30 and +30 cm/s
#endif
#ifndef LAND_DETECTOR_BARO_CLIMBRATE_MAX
# define LAND_DETECTOR_BARO_CLIMBRATE_MAX   150  // barometer climb rate must be between -150cm/s ~ +150cm/s
#endif
#ifndef LAND_DETECTOR_ROTATION_MAX
 # define LAND_DETECTOR_ROTATION_MAX    0.50f   // vehicle rotation must be below 0.5 rad/sec (=30deg/sec for) vehicle to consider itself landed
#endif
#ifndef LAND_REQUIRE_MIN_THROTTLE_TO_DISARM
 # define LAND_REQUIRE_MIN_THROTTLE_TO_DISARM DISABLED  // we do not require pilot to reduce throttle to minimum before vehicle will disarm in AUTO, LAND or RTL
#endif
#ifndef LAND_REPOSITION_DEFAULT
 # define LAND_REPOSITION_DEFAULT   1   // by default the pilot can override roll/pitch during landing
#endif
#ifndef LAND_WITH_DELAY_MS
 # define LAND_WITH_DELAY_MS        4000    // default delay (in milliseconds) when a land-with-delay is triggered during a failsafe event
#endif

//////////////////////////////////////////////////////////////////////////////
// CAMERA TRIGGER AND CONTROL
//
#ifndef CAMERA
 # define CAMERA        ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// MOUNT (ANTENNA OR CAMERA)
//
#ifndef MOUNT
 # define MOUNT         ENABLED
#endif


//////////////////////////////////////////////////////////////////////////////
// Flight mode definitions
//

// Acro Mode
#ifndef ACRO_RP_P
 # define ACRO_RP_P                 4.5f
#endif

#ifndef ACRO_YAW_P
 # define ACRO_YAW_P                4.5f
#endif

#ifndef ACRO_LEVEL_MAX_ANGLE
 # define ACRO_LEVEL_MAX_ANGLE      3000
#endif

#ifndef ACRO_BALANCE_ROLL
 #define ACRO_BALANCE_ROLL          1.0f
#endif

#ifndef ACRO_BALANCE_PITCH
 #define ACRO_BALANCE_PITCH         1.0f
#endif

#ifndef ACRO_EXPO_DEFAULT
 #define ACRO_EXPO_DEFAULT          0.3f
#endif

// Stabilize (angle controller) gains
#ifndef STABILIZE_ROLL_P
 # define STABILIZE_ROLL_P          4.5f
#endif

#ifndef STABILIZE_PITCH_P
 # define STABILIZE_PITCH_P         4.5f
#endif

#ifndef  STABILIZE_YAW_P
 # define STABILIZE_YAW_P           4.5f
#endif

// RTL Mode
#ifndef RTL_ALT_FINAL
 # define RTL_ALT_FINAL             0       // the altitude the vehicle will move to as the final stage of Returning to Launch.  Set to zero to land.
#endif

#ifndef RTL_ALT
 # define RTL_ALT 				    1500    // default alt to return to home in cm, 0 = Maintain current altitude
#endif

#ifndef RTL_LOITER_TIME
 # define RTL_LOITER_TIME           5000    // Time (in milliseconds) to loiter above home before begining final descent
#endif

// AUTO Mode
#ifndef WP_YAW_BEHAVIOR_DEFAULT
 # define WP_YAW_BEHAVIOR_DEFAULT   WP_YAW_BEHAVIOR_LOOK_AT_NEXT_WP_EXCEPT_RTL
#endif

#ifndef AUTO_YAW_SLEW_RATE
 # define AUTO_YAW_SLEW_RATE    60              // degrees/sec
#endif

#ifndef YAW_LOOK_AHEAD_MIN_SPEED
 # define YAW_LOOK_AHEAD_MIN_SPEED  100             // minimum ground speed in cm/s required before copter is aimed at ground course
#endif

// Super Simple mode
#ifndef SUPER_SIMPLE_RADIUS
 # define SUPER_SIMPLE_RADIUS       1000
#endif

//////////////////////////////////////////////////////////////////////////////
// Stabilize Rate Control
//
#ifndef ROLL_PITCH_INPUT_MAX
 # define ROLL_PITCH_INPUT_MAX      4500            // roll, pitch input range
#endif
#ifndef DEFAULT_ANGLE_MAX
 # define DEFAULT_ANGLE_MAX         4500            // ANGLE_MAX parameters default value
#endif
#ifndef ANGLE_RATE_MAX
 # define ANGLE_RATE_MAX            18000           // default maximum rotation rate in roll/pitch axis requested by angle controller used in stabilize, loiter, rtl, auto flight modes
#endif

//////////////////////////////////////////////////////////////////////////////
// Rate controller gains
//

#ifndef RATE_ROLL_P
 # define RATE_ROLL_P        		0.150f
#endif
#ifndef RATE_ROLL_I
 # define RATE_ROLL_I        		0.100f
#endif
#ifndef RATE_ROLL_D
 # define RATE_ROLL_D        		0.004f
#endif
#ifndef RATE_ROLL_IMAX
 # define RATE_ROLL_IMAX         	1000
#endif
#ifndef RATE_ROLL_FILT_HZ
 # define RATE_ROLL_FILT_HZ         20.0f
#endif

#ifndef RATE_PITCH_P
 # define RATE_PITCH_P       		0.150f
#endif
#ifndef RATE_PITCH_I
 # define RATE_PITCH_I       		0.100f
#endif
#ifndef RATE_PITCH_D
 # define RATE_PITCH_D       		0.004f
#endif
#ifndef RATE_PITCH_IMAX
 # define RATE_PITCH_IMAX        	1000
#endif
#ifndef RATE_PITCH_FILT_HZ
 # define RATE_PITCH_FILT_HZ        20.0f
#endif


#ifndef RATE_YAW_P
 # define RATE_YAW_P              	0.200f
#endif
#ifndef RATE_YAW_I
 # define RATE_YAW_I              	0.020f
#endif
#ifndef RATE_YAW_D
 # define RATE_YAW_D              	0.000f
#endif
#ifndef RATE_YAW_IMAX
 # define RATE_YAW_IMAX            	1000
#endif
#ifndef RATE_YAW_FILT_HZ
 # define RATE_YAW_FILT_HZ          AC_PID_FILT_HZ_DEFAULT
#endif

//////////////////////////////////////////////////////////////////////////////
// Loiter position control gains
//
#ifndef POS_XY_P
 # define POS_XY_P             	1.0f
#endif

//////////////////////////////////////////////////////////////////////////////
// Velocity (horizontal) gains
//
#ifndef VEL_XY_P
 # define VEL_XY_P              1.0f
#endif
#ifndef VEL_XY_I
 # define VEL_XY_I              0.5f
#endif
#ifndef VEL_XY_IMAX
 # define VEL_XY_IMAX           1000
#endif
#ifndef VEL_XY_FILT_HZ
 # define VEL_XY_FILT_HZ        5.0f
#endif

//////////////////////////////////////////////////////////////////////////////
// PosHold parameter defaults
//
#ifndef POSHOLD_ENABLED
 # define POSHOLD_ENABLED               ENABLED // PosHold flight mode enabled by default
#endif
#ifndef POSHOLD_BRAKE_RATE_DEFAULT
 # define POSHOLD_BRAKE_RATE_DEFAULT    8       // default POSHOLD_BRAKE_RATE param value.  Rotation rate during braking in deg/sec
#endif
#ifndef POSHOLD_BRAKE_ANGLE_DEFAULT
 # define POSHOLD_BRAKE_ANGLE_DEFAULT   3000    // default POSHOLD_BRAKE_ANGLE param value.  Max lean angle during braking in centi-degrees
#endif

//////////////////////////////////////////////////////////////////////////////
// Throttle control gains
//
#ifndef THR_MID_DEFAULT
 # define THR_MID_DEFAULT       500             // Throttle output (0 ~ 1000) when throttle stick is in mid position
#endif

#ifndef THR_MIN_DEFAULT
 # define THR_MIN_DEFAULT       130             // minimum throttle sent to the motors when armed and pilot throttle above zero
#endif
#ifndef THR_MAX_DEFAULT
 # define THR_MAX_DEFAULT       1000            // maximum throttle sent to the motors
#endif

#ifndef THR_DZ_DEFAULT
# define THR_DZ_DEFAULT         100             // the deadzone above and below mid throttle while in althold or loiter
#endif

#ifndef ALT_HOLD_P
 # define ALT_HOLD_P            1.0f
#endif

// Velocity (vertical) control gains
#ifndef VEL_Z_P
 # define VEL_Z_P       5.0f
#endif

// Accel (vertical) control gains
#ifndef ACCEL_Z_P
 # define ACCEL_Z_P     0.50f
#endif
#ifndef ACCEL_Z_I
 # define ACCEL_Z_I     1.00f
#endif
#ifndef ACCEL_Z_D
 # define ACCEL_Z_D     0.0f
#endif
#ifndef ACCEL_Z_IMAX
 # define ACCEL_Z_IMAX  800
#endif
#ifndef ACCEL_Z_FILT_HZ
 # define ACCEL_Z_FILT_HZ   20.0f
#endif

// default maximum vertical velocity and acceleration the pilot may request
#ifndef PILOT_VELZ_MAX
 # define PILOT_VELZ_MAX    250     // maximum vertical velocity in cm/s
#endif
#ifndef PILOT_ACCEL_Z_DEFAULT
 # define PILOT_ACCEL_Z_DEFAULT 250 // vertical acceleration in cm/s/s while altitude is under pilot control
#endif

// max distance in cm above or below current location that will be used for the alt target when transitioning to alt-hold mode
#ifndef ALT_HOLD_INIT_MAX_OVERSHOOT
 # define ALT_HOLD_INIT_MAX_OVERSHOOT 200
#endif
// the acceleration used to define the distance-velocity curve
#ifndef ALT_HOLD_ACCEL_MAX
 # define ALT_HOLD_ACCEL_MAX 250    // if you change this you must also update the duplicate declaration in AC_WPNav.h
#endif

//////////////////////////////////////////////////////////////////////////////
// Dataflash logging control
//
#ifndef LOGGING_ENABLED
 # define LOGGING_ENABLED                ENABLED
#endif

#if CONFIG_HAL_BOARD == HAL_BOARD_APM1 || CONFIG_HAL_BOARD == HAL_BOARD_APM2 || CONFIG_HAL_BOARD == HAL_BOARD_AVR_SITL
 // APM1 & APM2 default logging
 # define DEFAULT_LOG_BITMASK \
    MASK_LOG_ATTITUDE_MED | \
    MASK_LOG_GPS | \
    MASK_LOG_PM | \
    MASK_LOG_CTUN | \
    MASK_LOG_NTUN | \
    MASK_LOG_RCIN | \
    MASK_LOG_CMD | \
    MASK_LOG_CURRENT
#else
 // PX4, Pixhawk, FlyMaple default logging
 # define DEFAULT_LOG_BITMASK \
    MASK_LOG_ATTITUDE_MED | \
    MASK_LOG_GPS | \
    MASK_LOG_PM | \
    MASK_LOG_CTUN | \
    MASK_LOG_NTUN | \
    MASK_LOG_RCIN | \
    MASK_LOG_IMU | \
    MASK_LOG_CMD | \
    MASK_LOG_CURRENT | \
    MASK_LOG_RCOUT | \
    MASK_LOG_OPTFLOW | \
    MASK_LOG_COMPASS | \
    MASK_LOG_CAMERA
#endif

//////////////////////////////////////////////////////////////////////////////
// AP_Limits Defaults
//

// Enable/disable AP_Limits
#ifndef AC_FENCE
 #define AC_FENCE ENABLED
#endif

#ifndef AC_RALLY
 #define AC_RALLY   ENABLED
#endif

//////////////////////////////////////////////////////////////////////////////
// Developer Items
//

// use this to completely disable the CLI
#ifndef CLI_ENABLED
  #  define CLI_ENABLED           ENABLED
#endif

//use this to completely disable FRSKY TELEM
#ifndef FRSKY_TELEM_ENABLED
  #  define FRSKY_TELEM_ENABLED          ENABLED
#endif

/*
  build a firmware version string.
  GIT_VERSION comes from Makefile builds
*/
#ifndef GIT_VERSION
#define FIRMWARE_STRING THISFIRMWARE
#else
#define FIRMWARE_STRING THISFIRMWARE " (" GIT_VERSION ")"
#endif

#endif // __ARDUCOPTER_CONFIG_H__
