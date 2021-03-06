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

void dynamic_loop(){
  
  /* Initialize dynamic properties with a default value */
  float amplitude,frequency;
  bool cosine;

  char ch;

  do{

    DynamicPropertyAccess dynamic_property_access("/signal_generator"_uri);
    std::cout << "Get dynamic properties..." << std::endl;

    /* Read dynamic properties values */
    dynamic_property_access.get<float>("amplitude", amplitude);
    dynamic_property_access.get<float>("frequency", frequency);
    dynamic_property_access.get<bool>("cosine", cosine);
    std::cout << "Current amplitude: " << amplitude << std::endl << "Current frequency: " << frequency << std::endl;

    /* Get user inputs for dynamic properties */
    std::string amp_str, freq_str, cosine_str;
    std::cout << "Please inform the amplitude: ";
    std::cin >> amp_str;
    std::cout << "Please inform the frequency: ";
    std::cin >> freq_str;
    std::cout << "Please inform the cosine (Inform 1 for sine and 0 for cosine): ";
    std::cin >> cosine_str;

    amplitude = std::stof(amp_str);
    frequency = std::stof(freq_str);
    cosine = std::stoi(cosine_str);
      
      /* Set dynamic properties value */
    dynamic_property_access.set<float>("amplitude", amplitude);
    dynamic_property_access.set<float>("frequency", frequency);
    dynamic_property_access.set<bool>("cosine", cosine);

    std::cout << "Current amplitude2: " << amplitude << std::endl << "Current frequency2: " << frequency << std::endl;
    
    std::cout << "Continue ? [y/N] " << std::endl;
    std::cin >> ch;

  }while (ch != 'N');
}




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

  std::thread th(dynamic_loop);
  
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
  th.join();
  signal_generator_sm.reset();
  digital_converter_sm.reset();
  widgets::reset();
  
  return 0;
}
