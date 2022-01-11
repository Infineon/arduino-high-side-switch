/**
 * @file        hss-shield-bts5001x.hpp
 * @brief       Power Profet (12V) shield with BTS500xx class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTS5001X_HPP_
#define HSS_SHIELD_BTS5001X_HPP_

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
 * @brief  Power Profet (12V) shield with BTS500xx API
 */

class Bts5001xShield : public HssShield
{
    public:

                        Bts5001xShield(Hss * hsw1, GPIOPAL * led2, GPIOPAL * led3, ADCPAL * pushButton, ADCPAL * vBat);
                        ~Bts5001xShield();

        Error_t         init();
        Error_t         deinit();
        Error_t         switchHxOn(uint8_t x = 0);
        Error_t         switchHxOff(uint8_t x = 0);
        DiagStatus_t    readDiagx(uint8_t x = 0);

        float           readIsx(uint8_t x=1);
        float           readVss();
        bool            analogReadButton();

        void            setVoltageOffset(float offset);

    protected:

        ExponentialFilter *filterVbat;     /**< Battery voltage filter */

        Hss      * hss1;                   /**< Shield switch */
        GPIOPAL  * led2;                   /**< Shield LED 2 */
        GPIOPAL  * led3;                   /**< Shield LED 3 */
        ADCPAL   * pushButton;             /**< Analog push button */
        ADCPAL   * vBat;                   /**< Battery voltage */

    private:

        const uint16_t  rSense = 1000;       /**< Diagnosis current sense resistor */
        float           vBatOffset = 0.0;    /**< Battery voltage offset */

};

/** @} */

}

#endif /** HSS_SHIELD_BTS5001X_HPP_ */