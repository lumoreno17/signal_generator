/**
 * @file signal_generator.cpp
 * @author Luciana Moreno Borges (youlumoreno.borges@gmail.com)
 * @brief Configure the components, connect them and start the state machine
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <memory>
#include <QApplication>
#include <QTimer>
#include <hyro/core/StateMachine.h>
#include <hyro/utils/DynamicPropertyAccess.h>
#include <hyro/widgets/WidgetCollection.h>
#include <hyro/utils/StateMachineSpinner.h>
#include <hyro/SignalGeneratorComponent.h>
#include <hyro/DigitalConverterComponent.h>

using namespace hyro;
/**
 * @brief Main loop
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv)
{
  hyro::LogConfig config;
  config.level = hyro::LogLevel::CRITICAL;
  
  /*Components configuration */
  hyro::HyroLoggerManager::Configure(config);
  StateMachine signal_generator_sm(std::make_shared<SignalGeneratorComponent>("/signal_generator"_uri));
  StateMachine digital_converter_sm(std::make_shared<DigitalConverterComponent>("/digital_converter"_uri));
  ComponentConfiguration signal_generator_conf = ComponentConfiguration(
    "{"
      "outputs: {"
        "signals: { protocol: 'api'},"
        "fix_dynamic: {protocol: 'api'}"
      "}" 
    "}"
  );

  ComponentConfiguration digital_converter_conf = ComponentConfiguration(
    "{"
      "inputs: {"
        "signals: { protocol: 'api' }"
      "},"
      "outputs: {"
        "digital_signals: { protocol: 'api'}"
      "}"
    "}"
  );

  auto remote_endpoint = ConnectionConfiguration("{ signals: { endpoint: '/signal_generator/signals'} }");
    
  /*State transistions */

  /*Initialize the component with configurations */
  signal_generator_sm.init(signal_generator_conf);
  signal_generator_sm.start();
  signal_generator_sm.connect();
  signal_generator_sm.check();

  /*Initialize the component with configurations */
  digital_converter_sm.init(digital_converter_conf);
  digital_converter_sm.start();
  digital_converter_sm.connect(remote_endpoint);
  digital_converter_sm.check();

  CancellationTokenSource cancellation_token;

  /*Create spinners*/
  StateMachineSpinner signal_generator_spinner(signal_generator_sm, cancellation_token,10ms);
  StateMachineSpinner digital_converter_spinner(digital_converter_sm, cancellation_token,10ms);
    
  /* Initialize dynamic properties with a default value */
  float m_amplitude = 0.0f;
  float m_frequency = 0.0f;
  bool m_cosine = true;
    
  std::this_thread::sleep_for(2s);

  DynamicPropertyAccess dynamic_property_access("/signal_generator"_uri);

  std::cout << "Get dynamic properties..." << std::endl;
  
  /* Read dynamic properties values */
  dynamic_property_access.get<float>("amplitude", m_amplitude);
  dynamic_property_access.get<float>("frequency", m_frequency);
  dynamic_property_access.get<bool>("cosine", m_cosine);
  std::cout << "Current amplitude: " << m_amplitude << std::endl << "Current frequency: " << m_frequency << std::endl;

  /* Get user inputs for dynamic properties */
  std::string amp_str, freq_str, cosine_str;
  std::cout << "Please inform the amplitude: ";
  std::cin >> amp_str;
  std::cout << "Please inform the frequency: ";
  std::cin >> freq_str;
  std::cout << "Please inform the cosine: ";
  std::cin >> cosine_str;

  m_amplitude = std::stof(amp_str);
  m_frequency = std::stof(freq_str);
  m_cosine = std::stof(cosine_str);
    
    /* Set dynamic properties value */
  dynamic_property_access.set<float>("amplitude", m_amplitude);
  dynamic_property_access.set<float>("frequency", m_frequency);
  dynamic_property_access.set<bool>("cosine", m_cosine);

  std::cout << "Current amplitude2: " << m_amplitude << std::endl << "Current frequency2: " << m_frequency << std::endl;
    
  /*Plot digital signal */
  widgets::plot2d<float>("digital_signal", "/digital_converter/digital_signals", widgets::Plot2dSettings::initWithProtocol("api"));
   
  /*Plot sinusoidal signal */
  widgets::registerChannelListener<hyro::Signal>("/signal_generator/signals", "api", [](hyro::Signal signal){
  widgets::plot2d<float>("Analog signal", "/signal_generator/signals/value", signal.value);
  });

  widgets::exec();
    
  std::this_thread::sleep_for(1s);

  cancellation_token.cancel();
  signal_generator_spinner.wait();
  digital_converter_spinner.wait();
  signal_generator_sm.reset();
  digital_converter_sm.reset();
  widgets::reset();
  
  return 0;
}
