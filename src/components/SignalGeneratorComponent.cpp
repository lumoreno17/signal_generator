/**
 * @file SignalGeneratorComponent.cpp
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief Signal Generator component
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <hyro/SignalGeneratorComponent.h>
#include <hyro/msgs/common/Basic.h>
#include <../src/internal/SignalGenerator.h>
#include <hyro/msgs/Signal.h>
#include <hyro/utils/DynamicPropertyAccess.h>

#include <iostream>

namespace hyro
{
  /* Create a log variable */
  std::shared_ptr<hyro::HyroLogger> SignalGeneratorComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("SignalGeneratorComponent");
  
  /*Initialize the object output and register the dynamic properties*/
  hyro::Result
  SignalGeneratorComponent::init (const hyro::ComponentConfiguration & config)
  {
    m_signal = SignalGenerator();
    std::shared_ptr<ChannelOutput<std::vector<int>>>
    m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config);
    s_logger->info("Init:");
  
    m_output = this->registerOutput<Signal>("signals"_uri, config);
    
    m_amplitude = config.parameters.getParameter<float>("amplitude", 5.0f);
    m_frequency = config.parameters.getParameter<float>("frequency", 3.0f);
    m_cosine = config.parameters.getParameter<bool>("func", true);

    registerDynamicProperty<float>("amplitude", m_amplitude, [](const float value){return true;});
    registerDynamicProperty<float>("frequency", m_frequency, [](const float value){return true;});
    registerDynamicProperty<bool>("cosine", m_cosine, [](const bool value){return value;});

    DynamicPropertyAccess dynamic_property_access("/signal_generator"_uri);

    std::cout << "Get dynamic properties..." << std::endl;

    return hyro::Result::RESULT_OK;
  }
  
  /* State transitions */
  hyro::Result
  SignalGeneratorComponent::reset ()
  {
    m_output.reset();
    return hyro::Result::RESULT_OK;
  }

  hyro::Result
  SignalGeneratorComponent::check ()
  {
    return hyro::Result::RESULT_OK;
  }

  hyro::Result
  SignalGeneratorComponent::start ()
  {
    return hyro::Result::RESULT_OK;
  }
  
  /* Set the dynamic properties, get sunusoidal signal and make it available on the output*/
  hyro::Result
  SignalGeneratorComponent::update()
  {
    s_logger->info("I'm on update ...");
    hyro::Signal message;
    m_signal.setAmplitude(m_amplitude);
    m_signal.setFrequency(m_frequency);
    
    if(m_cosine){
      message.value = m_signal.getSignalValue(cosine);
    }
    else {
      message.value = m_signal.getSignalValue(sine);
    }
    m_output->sendAsync(message);
    s_logger->info("Sending data {}:", message);
    return hyro::Result::RESULT_OK;
  }

} // namespace hyro

