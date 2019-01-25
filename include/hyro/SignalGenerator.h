#pragma once

#ifndef SIGNAL_GENERATOR_H
#define SIGNAL_GENERATOR_H

namespace hyro
{
  class SignalGenerator
  {
    /**
     * @brief Private class variables: m_deg = angle in degrees,
     * m_step the step of the angle, m_amp the signal amplitude 
     * and rad the angle conversion to radians
     * 
     */
    float m_deg, m_step, m_amp, rad;
    public:
      /**
       * @brief Construct a new Signal Generator object
       * 
       */
      SignalGenerator();
      /**
       * @brief Return the sinusoidal signal value
       * 
       * @param cosine Choose the signal type (cossine or sine)
       * @return float the signal value
       */
      float getSignalValue(bool cosine);
      /**
       * @brief Set the Frequency of the signal
       * 
       * @param step the step of the signal angle in radians
       */
      void setFrequency(float step);
      /**
       * @brief Set the signal Amplitude
       * 
       * @param amplitude Desired amplitude
       */
      void setAmplitude(float amplitude);
  };
}

#endif // SIGNAL_GENERATOR_H
