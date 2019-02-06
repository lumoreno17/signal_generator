/**
 * @file Thresholding.cpp
 * @author Luciana Moreno (lumoreno.borges@gmail.com)
 * @brief Thresholding class
 * @version 0.1
 * @date 2019-01-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <bits/stdc++.h>
#include <chrono>
#include <../src/internal/Thresholding.h>

namespace hyro
{
  /**
   * @brief Construct a new Thresholding:: Thresholding object
   */
Thresholding::Thresholding(float amplitude, float thresholding):
  m_amplitude(amplitude), m_thresholding(thresholding)
{
}

/* Convert the signal value in a digital one */
float Thresholding::getThreshValue(double signal){

  return (signal < m_thresholding) ?  -m_amplitude : m_amplitude;

}
}