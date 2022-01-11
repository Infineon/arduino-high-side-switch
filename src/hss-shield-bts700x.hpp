/**
 * @file        hss-shield-bts700x.hpp
 * @brief       Profet +2 (12V) shield with BTS700x-1EPP class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTS700x_HPP_
#define HSS_SHIELD_BTS700x_HPP_

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
 * @brief  Profet +2 (12V) shield with BTS700x-1EPP API
 */

class Bts700xShield : public HssShield
{
    public:

                        Bts700xShield(GPIOPAL *led1, GPIOPAL *led2, GPIOPAL *led3, GPIOPAL *led4, Hss *hsw1, Hss *hsw2, Hss *hsw3, Hss *hsw4, TimerPAL *timer,
                                      GPIOPAL *oloff, GPIOPAL *pushButtonDigital, ADCPAL *pushButtonAnalog, ADCPAL *vBat, BtxVariants_t* btxVariant);
                        ~Bts700xShield();

        Error_t         init();
        Error_t         deinit();
        Error_t         switchHxOn(uint8_t x);
        Error_t         switchHxOff(uint8_t x);
        Error_t         switchesHxOn(bool h1 = false, bool h2 = false, bool h3 = false, bool h4 = false);
        Error_t         switchesHxOff(bool h1 = false, bool h2 = false, bool h3 = false, bool h4 = false);

        DiagStatus_t    readDiagx(uint8_t x);

        float           readIsx(uint8_t x);
        float           readVss();

        bool            digitalReadButton();
        bool            analogReadButton();

        void            setVoltageOffset(float offset);

    protected:

        ExponentialFilter   *filterVbat;    /**< Battery voltage filter */

        GPIOPAL             *led1;  /**< Shield LED 1 */
        GPIOPAL             *led2;  /**< Shield LED 2 */
        GPIOPAL             *led3;  /**< Shield LED 3 */
        GPIOPAL             *led4;  /**< Shield LED 4 */

        Hss                 *hss1;  /**< Shield switch 1 */
        Hss                 *hss2;  /**< Shield switch 2 */
        Hss                 *hss3;  /**< Shield switch 3 */
        Hss                 *hss4;  /**< Shield switch 4 */

        TimerPAL            *timer; /**< Timer instance */

        GPIOPAL             *oloff; /**< Output offset */

        GPIOPAL             *pushButtonDigital; /**< Digital push button */
        ADCPAL              *pushButtonAnalog;  /**< Analog push button */
        ADCPAL              *vBat;              /**< Battery voltage */

        BtxVariants_t       *btxVariant;        /**< BTx switch variant */

    private:

        DiagStatus_t        diagnosisOff(float currentOn, float currentOff);

        float               vBatOffset = 0.0;   /**< Battery voltage offset */
        const uint16_t      rSense = 1000;      /**< Diagnosis current sense resistor */
};

/** @} */

}

#endif /** HSS_SHIELD_BTS700x_HPP_ */