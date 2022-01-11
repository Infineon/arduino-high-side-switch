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
        ExponentialFilter(float y, uint16_t t);

        void setFilter(float y, uint16_t t);
        void setTau(uint16_t t);
        void setToNewValue(float y);
        void input(float x);
        float output();
        uint16_t pow2(uint16_t p);

    private:

        uint16_t tau;   /**< Time constant */

        float y;        /**< Output value */
        float y_last;   /**< Last output value */
        float x;        /**< Input value*/
};

/** @} */

}

#endif /** FILTER_HPP_ **/