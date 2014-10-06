// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

/*
 * control_guided.pde - GCS controlled mode
 *      has the following sub modes: direct-servo, ROI
 */

/*
 * update_guided - runs the guided controller
 *  called at 50hz while control_mode is 'GUIDED'
 */
static void update_guided(void)
{
    // do nothing
}

/*
 * guided_set_servo - sets the yaw or pitch servo pwm directly
 */
static bool guided_set_servo(uint8_t servo_num, uint16_t pwm)
{
    // exit immediately if servo_num is invalid
    if (servo_num != CH_YAW && servo_num != CH_PITCH) {
        return false;
    }

    // ensure we are in guided mode
    if (control_mode != GUIDED) {
        set_mode(GUIDED);
    }

    // set guided sub mode
    if (guided_mode != GUIDED_SERVO_DIRECT) {
        guided_mode = GUIDED_SERVO_DIRECT;
    }

    // set yaw servo pwm and send output to servo
    if (servo_num == CH_YAW) {
        channel_yaw.radio_out = constrain_int16(pwm, channel_yaw.radio_min, channel_yaw.radio_max);
        channel_yaw.output();
    }

    // set pitch servo pwm and send output to servo
    if (servo_num == CH_PITCH) {
        channel_pitch.radio_out = constrain_int16(pwm, channel_pitch.radio_min, channel_pitch.radio_max);
        channel_pitch.output();
    }
}
