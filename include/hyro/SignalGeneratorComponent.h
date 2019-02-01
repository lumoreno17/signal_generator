/**
 * @file SignalGeneratorComponent.h
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief A Signal Generator component class
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#ifndef HYRO_SIGNALGENERATORCOMPONENT_H
#define HYRO_SIGNALGENERATORCOMPONENT_H

#include <signal_generator_components_export.h>

#include <hyro/core/Component.h>
#include <hyro/msgs/Signal.h>
#include <../src/internal/SignalGenerator.h>
#include <hyro/msgs/common/Basic.h>

namespace hyro
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT SignalGeneratorComponent : public Component
{
public:
 
  using Component::Component;

  /**
  * @brief Destroy the Signal Generator Component object
  * 
  */
  inline virtual 
  ~SignalGeneratorComponent () override = default;

  /*State transistions*/

  virtual Result
  init (const hyro::ComponentConfiguration & config) override;

  virtual Result
  reset () override;

  virtual Result
  check () override;

  virtual Result
  start () override;

  virtual Result
  update () override;

private:

  static std::shared_ptr<hyro::HyroLogger> s_logger;
  std::shared_ptr<hyro::ChannelOutput<Signal>> m_output; 
  float m_amplitude, m_frequency;
  bool m_cosine;
  SignalGenerator m_signal;
};

} // namespace hyro
#endif // HYRO_SIGNALGENERATORCOMPONENT_H
