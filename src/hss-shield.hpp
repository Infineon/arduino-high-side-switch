/**
 * @file        hss-shield.hpp
 * @brief       High side switch shield abstract class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_HPP_
#define HSS_SHIELD_HPP_

#include "hss-types.hpp"
#include <stdint.h>

namespace hss
{

/**
 * @addtogroup hssCorelib
 * @{
 */

/**
 * @brief High side switch shield abstract API
 */

class HssShield
{
    public:

        /**
         * @brief Default destructor
         */
        virtual             ~HssShield(){};

        /**
         * @brief   Initializes the shield including it hardware instances
         * @return  High-side switch error code
         */
        virtual Error_t      init()   = 0;

        /**
         * @brief   Deinitializes the shield including it hardware instances
         * @return  High-side switch error code
         */
        virtual Error_t      deinit() = 0;

        /**
         * @brief       Turns on the specified shield switch output number
         * @param[in]   x   Switch output number
         * @return      High-side switch error code
         */
        virtual Error_t      switchHxOn (uint8_t x) = 0;

        /**
         * @brief       Turns off the specified shield switch output number
         * @param[in]   x   Switch output number
         * @return      High-side switch error code
         */
        virtual Error_t      switchHxOff(uint8_t x) = 0;

        /**
         * @brief       Reads the diagnose from the specified shield switch output number
         * @param[in]   x   Switch output number
         * @return      High-side switch error code
         */
        virtual DiagStatus_t readDiagx  (uint8_t x) = 0;

        /**
         * @brief       Read the diagnose current from the specified shield switch output number
         * @param[in]   x   Switch output number
         * @return      Current value in mA
         */
        virtual float        readIsx    (uint8_t x) = 0;
};

/** @} */

}

#endif /** HSS_SHIELD_HPP_ **/
