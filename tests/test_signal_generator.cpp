/**
 * @file test_signal_generator.cpp
 * @author Luciana Moreno (lumoreno.borges@gmail.com)
 * @brief Unit test for the signal generator hyro package
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <hyro/SignalGeneratorComponent.h>
#include <hyro/DigitalConverterComponent.h>
#include <hyro/utils/DynamicPropertyAccess.h>
#include <hyro/test/ComponentTester.h>
#include <gtest/gtest.h>

/* Macro definition to configure the components */
static void
__assert_and_run_state_machine(hyro::StateMachine& sm,
                               const hyro::ComponentConfiguration& conf,
                               const hyro::ConnectionConfiguration& endpoint)
{
  ASSERT_EQ(hyro::Result::RESULT_OK, sm.init(conf));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.start());

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.connect(endpoint));

  ASSERT_EQ(hyro::Result::RESULT_OK, sm.check());
}

#define ASSERT_AND_RUN_STATE_MACHINE(sm, conf, endpoint) \
  __assert_and_run_state_machine(sm, conf, endpoint)

namespace hyro
{
namespace test
{

/**
 * @brief Construct a new TEST object for SignalGeneratorComponent
 * 
 */
TEST (TestSignalGenerator, SignalGeneratorComponentCheck)
{

  auto signal_generator_configuration = 
      "{"
        "outputs: {"
           "signals: { protocol: 'api'},"
           "fix_dynamic: {protocol: 'api'}"
        "}" 
      "}";


  StateMachine signal_generator_sm(std::make_shared<SignalGeneratorComponent>("/signal_generator"_uri));

  auto result = signal_generator_sm.init(ComponentConfiguration(signal_generator_configuration));

  /* Teste state transitions */
  ASSERT_EQ(Result::RESULT_OK, result);
  result = signal_generator_sm.start();
  ASSERT_EQ(Result::RESULT_OK, result);
  result = signal_generator_sm.connect(ConnectionConfiguration());
  ASSERT_EQ(Result::RESULT_OK, result);
  result = signal_generator_sm.check();
  ASSERT_EQ(Result::RESULT_OK, result);

  /* Create a fake input channel and test connection*/
  auto inputPos = std::make_shared<FakeInput<Signal>>("inputPos"_uri, "api", "/signal_generator/signals");
  ASSERT_TRUE(inputPos->connect());

  signal_generator_sm.update();
  auto valuePos = std::shared_ptr<const Signal>();
  
  /* Test if the fake input is receiving data of SignalGeneratorComponent */
  ReceiveStatus ret = inputPos->receive(valuePos, 500ms);
  ASSERT_EQ(ReceiveStatus::RECEIVE_OK, ret);
  EXPECT_EQ(valuePos->value, 5.0);
  
  /*Test the component behavior in face of a dynamic property which doesn't exists */
  DynamicPropertyAccess dynamic_property_access("/signal_generator"_uri);
  float not_exits;
  ASSERT_ANY_THROW(dynamic_property_access.get("not_exists", not_exits));
  
  /* Dynamic properties variables */
  float m_amplitude, m_frequency;
  bool m_cosine;

  /* Test the acess to the dynamic properties */
  ASSERT_TRUE(dynamic_property_access.get("amplitude", m_amplitude));
  ASSERT_TRUE(dynamic_property_access.get("frequency", m_frequency));
  ASSERT_TRUE(dynamic_property_access.get("cosine", m_cosine));
  
  /* Test the default values of the dynamic properties */
  ASSERT_NEAR(m_amplitude, 5.0f, 0.001);
  ASSERT_NEAR(m_frequency, 3.0f, 0.001);
  ASSERT_EQ(m_cosine, true);

  /* Test the modification of dynamic properties */
  ASSERT_TRUE(dynamic_property_access.set("amplitude", 4.0f));
  ASSERT_TRUE(dynamic_property_access.set("frequency", 3.0f));
  //ASSERT_TRUE(dynamic_property_access.set("cosine", 1));
  
}

/**
 * @brief Construct a new TEST object for DigitalConverterComponent
 * 
 */
TEST (DigitalConverterTest, DynamicPropertyCheck)
{
  /* Log configuration */
  LogConfig config;
  config.level = LogLevel::CRITICAL;
  HyroLoggerManager::Configure(config);

  /* Component configuration */
  auto configuration = ComponentConfiguration("{inputs: {signals: { protocol: 'api' } },"

                                                          "outputs: {digital_signals: { protocol: 'api' }}}");

  StateMachine digital_converter_sm(std::make_shared<DigitalConverterComponent>("/digital_converter"_uri));
  
  /* Create a fake output channel and test connection */
  auto fake_output_signals = std::make_shared<FakeOutput<Signal>>("fake_signals"_uri, "api");
  ASSERT_TRUE(fake_output_signals->start());
  auto endpoint = ConnectionConfiguration("{ signals: { endpoint: 'fake_signals' } }");
  ASSERT_AND_RUN_STATE_MACHINE(digital_converter_sm, configuration, endpoint);
  
  /* Create a fake input channel and test connection */
  auto fake_digital_signals = std::make_shared<FakeInput<float>>("digital_signals"_uri, "api", "/digital_converter/digital_signals");
  ASSERT_TRUE(fake_digital_signals->connect());
  auto value = std::shared_ptr<const float>();

}

int main (int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();

} // main



} // namespace test

} // namespace hyro