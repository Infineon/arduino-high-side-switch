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
    this->alpha = 0.4;
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
    this->alpha = 0.4;
}

/**
 * @brief       Exponential filter constructor with initial value and alpha
 * @param[in]   y   Initial filter value
 * @param[in]   t   Time value
 */
ExponentialFilter::ExponentialFilter(float y, float a)
{
    this->y = y;
    this->y_last = y;
    this->x = y;
    this->alpha = a;
}

/**
 * @brief       Sets filter parameters
 * @param[in]   y   Initial filter value
 * @param[in]   t   Time value
 */
void ExponentialFilter::setFilter(float y, float a)
{
    this->y = y;
    this->y_last = y;
    this->x = y;
    this->alpha = a;
}

/**
 * @brief       Sets alpha
 * @param[in]   t  Time value
 */
void ExponentialFilter::setAlpha(float a)
{
    this->alpha = a;
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
    this->y = (alpha * y_last) + ((1 - alpha) * x);
}

/**
 * @brief   Gets output value
 * @return  Filtered output value
 */
float ExponentialFilter::output()
{
    return y;
}