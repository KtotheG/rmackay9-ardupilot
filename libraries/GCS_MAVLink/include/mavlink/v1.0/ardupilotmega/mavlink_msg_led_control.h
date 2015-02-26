// MESSAGE LED_CONTROL PACKING

#define MAVLINK_MSG_ID_LED_CONTROL 186

typedef struct __mavlink_led_control_t
{
 uint8_t target_system; ///< System ID
 uint8_t target_component; ///< Component ID
 uint8_t pattern; ///< Pattern (see LED_PATTERN_ENUM)
} mavlink_led_control_t;

#define MAVLINK_MSG_ID_LED_CONTROL_LEN 3
#define MAVLINK_MSG_ID_186_LEN 3

#define MAVLINK_MSG_ID_LED_CONTROL_CRC 93
#define MAVLINK_MSG_ID_186_CRC 93



#define MAVLINK_MESSAGE_INFO_LED_CONTROL { \
	"LED_CONTROL", \
	3, \
	{  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_led_control_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_led_control_t, target_component) }, \
         { "pattern", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_led_control_t, pattern) }, \
         } \
}


/**
 * @brief Pack a led_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param pattern Pattern (see LED_PATTERN_ENUM)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
						       uint8_t target_system, uint8_t target_component, uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, pattern);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#else
	mavlink_led_control_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.pattern = pattern;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LED_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a led_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system System ID
 * @param target_component Component ID
 * @param pattern Pattern (see LED_PATTERN_ENUM)
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_led_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
							   mavlink_message_t* msg,
						           uint8_t target_system,uint8_t target_component,uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, pattern);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#else
	mavlink_led_control_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.pattern = pattern;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif

	msg->msgid = MAVLINK_MSG_ID_LED_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
}

/**
 * @brief Encode a led_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param led_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_led_control_t* led_control)
{
	return mavlink_msg_led_control_pack(system_id, component_id, msg, led_control->target_system, led_control->target_component, led_control->pattern);
}

/**
 * @brief Encode a led_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param led_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_led_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_led_control_t* led_control)
{
	return mavlink_msg_led_control_pack_chan(system_id, component_id, chan, msg, led_control->target_system, led_control->target_component, led_control->pattern);
}

/**
 * @brief Send a led_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system System ID
 * @param target_component Component ID
 * @param pattern Pattern (see LED_PATTERN_ENUM)
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_led_control_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[MAVLINK_MSG_ID_LED_CONTROL_LEN];
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, pattern);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
#else
	mavlink_led_control_t packet;
	packet.target_system = target_system;
	packet.target_component = target_component;
	packet.pattern = pattern;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
#endif
}

#if MAVLINK_MSG_ID_LED_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_led_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t pattern)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char *buf = (char *)msgbuf;
	_mav_put_uint8_t(buf, 0, target_system);
	_mav_put_uint8_t(buf, 1, target_component);
	_mav_put_uint8_t(buf, 2, pattern);

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, buf, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
#else
	mavlink_led_control_t *packet = (mavlink_led_control_t *)msgbuf;
	packet->target_system = target_system;
	packet->target_component = target_component;
	packet->pattern = pattern;

#if MAVLINK_CRC_EXTRA
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)packet, MAVLINK_MSG_ID_LED_CONTROL_LEN, MAVLINK_MSG_ID_LED_CONTROL_CRC);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LED_CONTROL, (const char *)packet, MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
#endif
}
#endif

#endif

// MESSAGE LED_CONTROL UNPACKING


/**
 * @brief Get field target_system from led_control message
 *
 * @return System ID
 */
static inline uint8_t mavlink_msg_led_control_get_target_system(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from led_control message
 *
 * @return Component ID
 */
static inline uint8_t mavlink_msg_led_control_get_target_component(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field pattern from led_control message
 *
 * @return Pattern (see LED_PATTERN_ENUM)
 */
static inline uint8_t mavlink_msg_led_control_get_pattern(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a led_control message into a struct
 *
 * @param msg The message to decode
 * @param led_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_led_control_decode(const mavlink_message_t* msg, mavlink_led_control_t* led_control)
{
#if MAVLINK_NEED_BYTE_SWAP
	led_control->target_system = mavlink_msg_led_control_get_target_system(msg);
	led_control->target_component = mavlink_msg_led_control_get_target_component(msg);
	led_control->pattern = mavlink_msg_led_control_get_pattern(msg);
#else
	memcpy(led_control, _MAV_PAYLOAD(msg), MAVLINK_MSG_ID_LED_CONTROL_LEN);
#endif
}
