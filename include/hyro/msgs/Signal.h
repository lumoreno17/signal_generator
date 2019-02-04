/**
 * @file Signal.h
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief Declare a Signal message 
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#ifndef HYRO_MSGS_SIGNAL_H
#define HYRO_MSGS_SIGNAL_H

#include <string>
#include <signal_generator_components_export.h>
#include <hyro/common/Time.h>
namespace hyro
{ 
  /**
   * @brief Message components: timestamp, frame_id and value
   * 
   */
  struct SIGNAL_GENERATOR_COMPONENTS_EXPORT Signal
  {
    Time timestamp;
    std::string frame_id;
    float value;
  };

  inline std::ostream &
  operator << (std::ostream & os, const Signal & signal)
  {
    return os << "{timestamp: " << signal.timestamp.count() << "ns, frame_id: " << signal.frame_id << "value: " << signal.value << "}";
  }

} // namespace hyro

#include <hyro/msgs/Signal.proto.h>
#endif // HYRO_MSGS_SIGNAL_H

