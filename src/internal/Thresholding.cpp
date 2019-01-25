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
#include <hyro/Thresholding.h>

namespace hyro
{
  /**
   * @brief Construct a new Thresholding:: Thresholding object
   */
Thresholding::Thresholding(double data_sample, float amplitude, float thresholding):
  data_sample(data_sample), amplitude(amplitude), thresholding(thresholding)
{
}

/* Convert the signal value in a digital one */
float Thresholding::makeThresholding(){
  if(data_sample > thresholding){
    data_sample = amplitude;
    return data_sample;
  }
  
  data_sample = -1 * amplitude;
  return data_sample;
  
}
}