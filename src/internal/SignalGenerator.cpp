/**
 * @file SignalGenerator.cpp
 * @author Luciana Moreno Borges (lumoreno.borges@gmail.com)
 * @brief Signal Generator class
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <bits/stdc++.h>
#include <chrono>
#include <hyro/SignalGenerator.h>

namespace hyro
{
  /**
   * @brief Construct a new Signal Generator:: Signal Generator object
   * 
   */
SignalGenerator::SignalGenerator():
  m_deg(0)
{
}

 
 /* Get the sine or cos for the desired angle */
float SignalGenerator::getSignalValue(bool cosine)
{
  float rad = m_deg / 180.0 * M_PI;
  m_deg += m_step;

  return (cosine) ? m_amp*cos(rad) : m_amp*sin(rad);
}

/* Set the signal frequency */
void SignalGenerator::setFrequency(float step)
{
  m_step = step;
}

/* Set the amplitude of the sinusoidal signal*/
void SignalGenerator::setAmplitude(float amplitude)
{
  m_amp = amplitude;
}
}
