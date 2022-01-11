/**
 * @file        hss-shield-btt60xx.hpp
 * @brief       Profet (24V) shield with BTT6030-2EKA and BTT6020-1EKA class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTT60XX_HPP_
#define HSS_SHIELD_BTT60XX_HPP_

#include "hss-shield.hpp"
#include "hss.hpp"
#include "hss-variants.hpp"

namespace hss
{

/**
 * @addtogroup hssCorelib
 * @{
 */

/**
 * @brief  Profet (24V) shield with BTT6030-2EKA and BTT6020-1EKA API
 */

class Btt60xxShield : HssShield
{
    public:

                        Btt60xxShield(Hss * hsw0, Hss * hsw1, Hss * hsw2);
                        ~Btt60xxShield();

        Error_t         init();
        Error_t         deinit();
        Error_t         switchHxOn   (uint8_t x);
        Error_t         switchHxOff  (uint8_t x);
        Error_t         switchesHxOn (bool h0_0 = false, bool h1_0 = false, bool h0_1 = false, bool h1_1 = false, bool h2 = false);
        Error_t         switchesHxOff(bool h0_0 = false, bool h1_0 = false, bool h0_1 = false, bool h1_1 = false, bool h2 = false);
        DiagStatus_t    readDiagx    (uint8_t x);
        float           readIsx      (uint8_t x);

    protected:

        static constexpr uint8_t hssNum = 3;    /**< Number of high side switches in the board */
        Hss * switches[hssNum];                 /**< Shield switches */

    private:

        const uint16_t  rSense = 1200;          /**< Diagnosis current sense resistor */

};

/** @} */

}

#endif /** HSS_SHIELD_BTT60XX_HPP_ */