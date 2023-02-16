/**
 * @file hss-shield-bts500xx.hpp
 * @brief Power PROFET +12V Shield with BTS500xx-1LUA class
 * @copyright Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTS500xx_HPP_
#define HSS_SHIELD_BTS500xx_HPP_

#include "hss-shield.hpp"
#include "hss-variants.hpp"
#include "hss.hpp"

namespace hss
{

/**
 * @addtogroup hssCorelib
 * @{
 */

/**
 * @brief Power PROFET +12V Shield with BTS500xx-1LUA API
 *
 */

class Bts500xxShield: public HssShield
{
    public:

                        Bts500xxShield(Hss *sw1, Hss *sw2, ADCPAL *vs, ADCPAL *vOut, ADCPAL *temp, BtxVariants_t *btxVariant1, BtxVariants_t *btxVariant2);
                        ~Bts500xxShield();

        Error_t         init();
        Error_t         deinit();
        Error_t         switchHxOn(uint8_t x);
        Error_t         switchHxOff(uint8_t x);

        DiagStatus_t    readDiagx(uint8_t x);
        float           readIsx(uint8_t x);

        Error_t         switchesHxOn(bool h1 = false, bool h2 = false);
        Error_t         switchesHxOff(bool h1 = false, bool h2 = false);

        float           readVs();
        float           readVOut();
        float           readTemperature();

    protected:

        static constexpr uint8_t hssNum = 2;    /**< Number of High-Side-Switches */
        Hss * switches[hssNum];                 /**< Array of High-Side-Switches */
        ADCPAL * vs;                            /**< Supply Voltage */
        ADCPAL * vOut;                          /**< Output Voltage of High-Side-Switch 1 */
        ADCPAL * temp;                          /**< Temperature */
        BtxVariants_t * btxVariant1;            /**< Variant of the High-Side-Switch 1 */
        BtxVariants_t * btxVariant2;            /**< Variant of the High-Side-Switch 2 */
        ExponentialFilter * filterVs;           /**< Filter for the supply voltage */
        ExponentialFilter * filterVOut;         /**< Filter for the output voltage for switch 1*/
        ExponentialFilter * filterTemp;         /**< Filter for the temperature */

};

/** @} */

}

#endif /** HSS_SHIELD_BTS500xx_HPP_ */