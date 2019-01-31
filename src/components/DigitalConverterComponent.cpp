/**
 * @file DigitalConverterComponent.cpp
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief Digital converter component: receives a sinusoidal value and converts on a digital one
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <hyro/DigitalConverterComponent.h>

#include <hyro/utils/SpinnerDefault.h>
#include <hyro/utils/SpinnerRated.h>
#include <hyro/factory/CommandFactory.h>

#include <hyro/msgs/common/Basic.h>
#include <hyro/Thresholding.h>
#include <hyro/msgs/Signal.h>

#include <iostream>

namespace hyro
{
  DigitalConverterComponent::DigitalConverterComponent(URI uri): hyro::Component(uri){
    //m_amplitude = 3.0;
    //m_thresholding = 0.0;
  }

  std::shared_ptr<hyro::HyroLogger> DigitalConverterComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("DigitalConverterComponent");
  
  /*Initialize the input and outputs of the object*/
  hyro::Result
  DigitalConverterComponent::init (const hyro::ComponentConfiguration & config)
  {
    m_amplitude = config.parameters.getParameter<float>("amplitude", 3.0);
    m_thresholding = config.parameters.getParameter<float>("thresholding", 0.0);
    m_input = this->registerInput<Signal>("signals"_uri, config);
    m_output = this->registerOutput<float>("digital_signals"_uri, config);
    s_logger->info("Init:");
    return hyro::Result::RESULT_OK;
  }

  /*State transisitions*/
  hyro::Result
  DigitalConverterComponent::reset ()
  {
    m_input.reset();
    m_output.reset();
    return hyro::Result::RESULT_OK;
  }

  hyro::Result
  DigitalConverterComponent::check ()
  {
    if (m_input->connectionStatus() != ConnectionStatus::CONNECTION_UP)
      return Result::RESULT_ERROR;
    return hyro::Result::RESULT_OK;
  }

  /*Define a callback method to receive the sinusoidal signal value*/
  hyro::Result
  DigitalConverterComponent::start ()
  {
    m_spinner = SpinnerDefault::Create(m_input, &DigitalConverterComponent::callback, this, this->suspensionToken());
    return hyro::Result::RESULT_OK;
  }

  hyro::Result
  DigitalConverterComponent::update()
  {
    s_logger->info("Converting signal ...");
    return hyro::Result::RESULT_OK;
  }

  /*Callback function to receive the sinusoidal signal value , configure its parameters 
  and send to another component */
  void
  DigitalConverterComponent::callback (std::shared_ptr<const Signal> && value){
    s_logger->info("I am in callback");
    hyro::Signal analog_signal;
    analog_signal = *value;
    Thresholding digital_converter(m_amplitude,m_thresholding);
    float digital_signal = digital_converter.getThreshValue(analog_signal.value); 
    m_output->sendAsync(digital_signal);
    s_logger->info("Data received {}:", digital_signal);
  } 

} // namespace hyro
