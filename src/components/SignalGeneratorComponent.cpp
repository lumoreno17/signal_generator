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
#include <hyro/SignalGenerator.h>
#include <hyro/msgs/Signal.h>
#include <hyro/utils/DynamicPropertyAccess.h>

#include <iostream>

namespace hyro
{
  SignalGeneratorComponent::SignalGeneratorComponent(URI uri): hyro::Component(uri){

  }
  /* Create a log variable */
  std::shared_ptr<hyro::HyroLogger> SignalGeneratorComponent::s_logger = hyro::HyroLoggerManager::CreateLogger("SignalGeneratorComponent");
  
  /*Initialize the object output and register the dynamic properties*/
  hyro::Result
  SignalGeneratorComponent::init (const hyro::ComponentConfiguration & config)
  {
    signal = SignalGenerator();
    std::shared_ptr<ChannelOutput<std::vector<int>>>
      m_dummy = this->registerOutput<std::vector<int>>("fix_dynamic"_uri, config);
    s_logger->info("Init:");
  
    m_output = this->registerOutput<Signal>("signals"_uri, config);

    m_amplitude = 5.0f;
    m_frequency = 3.0f;
    m_cosine = true;

    registerDynamicProperty<float>("amplitude", m_amplitude, [this](const float value){return value>=0 && value<=5;});
    registerDynamicProperty<float>("frequency", m_frequency, [this](const float value){return value>=0 && value<=5;});
    registerDynamicProperty<bool>("cosine", m_cosine, [this](const bool value){return value==true || value==false;});
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
    s_logger->info("Estou no update ...");
    hyro::Signal message;
    signal.setAmplitude(m_amplitude);
    signal.setFrequency(m_frequency);
    message.value = signal.getSignalValue(m_cosine);
    //s_logger->info("Cossine value {}:", m_cosine);
    //s_logger->info("Amplitude value {}:", m_amplitude);
    //s_logger->info("Frequency value {}:", m_frequency);
    m_output->sendAsync(message);
    s_logger->info("Sending data {}:", message);
    return hyro::Result::RESULT_OK;
  }

} // namespace hyro

