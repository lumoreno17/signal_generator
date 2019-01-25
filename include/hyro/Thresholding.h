/**
 * @brief Thresholding class definition.
 * A class to convert sinusuidal signals in digital signals
 * 
 */
#pragma once

#ifndef THRESHOLDING_H
#define THRESHOLDING_H

#define THRESHOLDING 0
namespace hyro
{
class Thresholding{
  /**
   * @brief Class variables.
   * data_sample is the sinusoidal signal value and 
   * amplitude is the amplitude of the digital signal.
   * 
   */
  double data_sample, amplitude;
  public:
    /**
     * @brief Construct a new Thresholding object
     * 
     * @param data_sample the input value to be analyzed
     * @param amplitude the amplitude of the digital signal 
     */
    Thresholding(double data_sample, double amplitude);
    /**
     * @brief Comparison between the data_sample value and threshold value
     * 
     * If the data_sample value is greater than the threshold it returns the amplitude value
     * If the data_sample value is less than the threshold value it returns the negative value of amplitude
     * @return float 
     */
    float makeThresholding();
};
}

#endif // THRESHOLDING_H