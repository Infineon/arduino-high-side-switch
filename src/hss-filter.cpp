/**
 * @file        hss-filter.cpp
 * @brief       Exponential filter class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#include "hss-filter.hpp"

using namespace hss;

/**
 * @brief Exponential filter default constructor
 */
ExponentialFilter::ExponentialFilter()
{
    this->y = 0.0;
    this->y_last = 0.0;
    this->x = 0.0;
    this->tau = 1;
}

/**
 * @brief       Exponential filter constructor with initial value
 * @param[in]   y  Initial filter value
 */
ExponentialFilter::ExponentialFilter(float y)
{
    this->y = y;
    this->y_last = y;
    this->x = y;
}

/**
 * @brief       Exponential filter constructor with initial value and time
 * @param[in]   y   Initial filter value
 * @param[in]   t   Time value
 */
ExponentialFilter::ExponentialFilter(float y, uint16_t t)
{
    this->y = y;
    this->y_last = y;
    this->x = y;
    this->tau = pow2(t);
}

/**
 * @brief       Sets filter parameters
 * @param[in]   y   Initial filter value
 * @param[in]   t   Time value
 */
void ExponentialFilter::setFilter(float y, uint16_t t)
{
    this->y = y;
    this->y_last = y;
    this->x = y;
    this->tau = pow2(t);
}

/**
 * @brief       Sets time constant
 * @param[in]   t  Time value
 */
void ExponentialFilter::setTau(uint16_t t)
{
    this->tau = pow2(t);
}

/**
 * @brief       Sets all parameters to new value
 * @param[in]   y   New value
 */
void ExponentialFilter::setToNewValue(float y)
{
    this->y = y_last = x = y;
}

/**
 * @brief       Sets new input
 * @param[in]   x   input value
 */
void ExponentialFilter::input(float x)
{
    y_last = y;
    this->x = x;

    y = y_last + ((x - y_last)/(float)tau);
}

/**
 * @brief   Gets output value
 * @return  Filtered output value
 */
float ExponentialFilter::output()
{
    return y;
}


/**
 * @brief       Calculates power two 
 * @param[in]   p  base to apply power 2
 * @return      Power two result
 */
uint16_t ExponentialFilter::pow2(uint16_t p)
{
    return 1<< p;
}

