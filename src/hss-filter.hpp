/**
 * @file        hss-filter.hpp
 * @brief       Exponential filter class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_FILTER_HPP_
#define HSS_FILTER_HPP_

#include <stdint.h>

namespace hss
{

/**
 * @addtogroup hssCorelib
 * @{
 */

/**
 * @brief  Exponential filter API
 */
class ExponentialFilter
{
    public:

        ExponentialFilter();
        ExponentialFilter(float y);
        ExponentialFilter(float y, float a);

        void setFilter(float y, float a);
        void setAlpha(float a);
        void setToNewValue(float y);
        void input(float x);
        float output();

    private:

        float alpha;    /**< Smoothing constant */
        float y;        /**< Output value */
        float y_last;   /**< Last output value */
        float x;        /**< Input value*/
};

/** @} */

}

#endif /** FILTER_HPP_ **/