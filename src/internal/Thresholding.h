/**
 * @brief Thresholding class definition.
 * A class to convert sinusuidal signals in digital signals
 * 
 */
#pragma once

#ifndef THRESHOLDING_H
#define THRESHOLDING_H

namespace hyro
{
class Thresholding
{
public:
  /**
   * @brief Construct a new Thresholding object
   * 
   * @param data_sample the input value to be analyzed
   * @param amplitude the amplitude of the digital signal 
   */
  Thresholding(float amplitude, float thresholding);
  /**
   * @brief Comparison between the data_sample value and threshold value
   * 
   * If the data_sample value is greater than the threshold it returns the amplitude value
   * If the data_sample value is less than the threshold value it returns the negative value of amplitude
   * @return float 
   */
  float getThreshValue(double signal);

private:
  /**
   * @brief Class variables.
   * data_sample is the sinusoidal signal value and 
   * amplitude is the amplitude of the digital signal.
   * 
   */
  double m_amplitude, m_thresholding;
};
}

#endif // THRESHOLDING_H