// MESSAGE PARAM_VALUE PACKING

#define MAVLINK_MSG_ID_PARAM_VALUE 82

typedef struct __param_value_t 
{
	int8_t param_id[15]; ///< Onboard parameter id
	float param_value; ///< Onboard parameter value

} param_value_t;

/**
 * @brief Send a param_value message
 *
 * @param param_id Onboard parameter id
 * @param param_value Onboard parameter value
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t message_param_value_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const int8_t* param_id, float param_value)
{
	msg->msgid = MAVLINK_MSG_ID_PARAM_VALUE;
	uint16_t i = 0;

	i += put_array_by_index(param_id, 15, i, msg->payload); //Onboard parameter id
	i += put_float_by_index(param_value, i, msg->payload); //Onboard parameter value

	return finalize_message(msg, system_id, component_id, i);
}

static inline uint16_t message_param_value_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const param_value_t* param_value)
{
	return message_param_value_pack(system_id, component_id, msg, param_value->param_id, param_value->param_value);
}

#if !defined(_WIN32) && !defined(__linux) && !defined(__APPLE__)

#include "global_data.h"

static inline void message_param_value_send(mavlink_channel_t chan, const int8_t* param_id, float param_value)
{
	mavlink_message_t msg;
	message_param_value_pack(global_data.param[PARAM_SYSTEM_ID], global_data.param[PARAM_COMPONENT_ID], &msg, param_id, param_value);
	mavlink_send_uart(chan, &msg);
}

#endif
// MESSAGE PARAM_VALUE UNPACKING

/**
 * @brief Get field param_id from param_value message
 *
 * @return Onboard parameter id
 */
static inline uint16_t message_param_value_get_param_id(const mavlink_message_t* msg, int8_t* r_data)
{

	memcpy(r_data, msg->payload, 15);
	return 15;
}

/**
 * @brief Get field param_value from param_value message
 *
 * @return Onboard parameter value
 */
static inline float message_param_value_get_param_value(const mavlink_message_t* msg)
{
	generic_32bit r;
	r.b[3] = (msg->payload+15)[0];
	r.b[2] = (msg->payload+15)[1];
	r.b[1] = (msg->payload+15)[2];
	r.b[0] = (msg->payload+15)[3];
	return (float)r.f;
}

static inline void message_param_value_decode(const mavlink_message_t* msg, param_value_t* param_value)
{
	message_param_value_get_param_id(msg, param_value->param_id);
	param_value->param_value = message_param_value_get_param_value(msg);
}
