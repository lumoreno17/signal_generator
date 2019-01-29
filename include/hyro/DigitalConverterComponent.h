/**
 * @file DigitalConverterComponent.h
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief Digital Converter component 
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#ifndef HYRO_DIGITALCONVERTERCOMPONENT_H
#define HYRO_DIGITALCONVERTERCOMPONENT_H

#include <signal_generator_components_export.h>

#include <hyro/core/Component.h>
#include <hyro/utils/ISpinner.h>

#include <hyro/commands/CommandHandler.h>

#include <hyro/msgs/Signal.h>
#include <hyro/Thresholding.h>

namespace hyro
{

class SIGNAL_GENERATOR_COMPONENTS_EXPORT DigitalConverterComponent : public Component
{
public:
  /**
  * @brief Construct a new Digital Converter Component object
  * 
  * @param uri 
  */
  DigitalConverterComponent(URI uri);
  /**
  * @brief Destroy the Digital Converter Component object
  */
  inline virtual 
  ~DigitalConverterComponent () override = default;

  /**
  * @brief State transitions
  * 
  * @param config configuration parameters
  * @return Result 
  */

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
            
  /**
  * @brief Receive a sinusoidal signal and convert it on a digital one.
  * 
  * @param value the sinusoidal signal value
  */
  void
  callback (std::shared_ptr<const Signal> && value);

private:
  /**
  * @brief Create the input and output channels of the component, a spinner and logger object.
  */
  static std::shared_ptr<hyro::HyroLogger> s_logger;
  std::shared_ptr<hyro::ChannelInput<Signal>> m_input; 
  std::shared_ptr<hyro::ChannelOutput<float>> m_output; 
            
  std::unique_ptr<ISpinner> m_spinner;
  float m_amplitude, m_thresholding;

};

} // namespace hyro
#endif // HYRO_DIGITALCONVERTERCOMPONENT_H
