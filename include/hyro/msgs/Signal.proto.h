/**
 * @file Signal.proto.h
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief Make a bridge of the message header file with the message proto file
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#ifndef SIGNAL_GENERATOR_MSG_SIGNAL_PROTO_H
#define SIGNAL_GENERATOR_MSG_SIGNAL_PROTO_H

#include <hyro/msgs/Signal.h> 
#include <hyro/dynamic/ProtobufTraits.h>
#include <hyro/msgs/Signal.pb.h> 
#include <signal_generator_components_export.h>

namespace hyro
{
  template <>
  struct ProtobufTraits<Signal> : public ProtobufTraitsDefault<Signal, msgs::Signal>
  {
    /* Flow to receive a message */
    static void
    FromMessage (const msgs::Signal & msg,
      Signal * value)
    {
      
      value->timestamp = hyro::Time{msg.timestamp()};
      value->frame_id = msg.frame_id();
      value->value = msg.value();
    }
      
    /* Flow to send a message */
    static void
    ToMessage (const Signal & value,
            msgs::Signal * msg)
    {
      msg->set_timestamp(value.timestamp.count());
      msg->set_frame_id(value.frame_id);
      msg->set_value(value.value);
    }
  };
} // namespace hyro

#endif // HYRO_MSGS_SIGNAL_PROTO_H
