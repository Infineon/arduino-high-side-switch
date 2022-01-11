/**
 * @file        hss-arduino.hpp
 * @brief       High side switch Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_ARDUINO_HPP_
#define HSS_ARDUINO_HPP_

#include "hss.hpp"
#include "hss-pal-gpio-ino.hpp"
#include "hss-pal-adc-ino.hpp"
#include "hss-pal-timer-ino.hpp"

namespace hss
{

/**
 * @class   HssIno
 * @brief   High side switch Arduino API
 */
class HssIno : public Hss
{
    public:
        HssIno(uint8_t in, uint8_t is, BtxVariants_t * btxVariant);
        HssIno(uint8_t den, uint8_t in, uint8_t is, BtxVariants_t * btxVariant);
        HssIno(uint8_t den, uint8_t in0, uint8_t in1, uint8_t dsel, uint8_t is, BtxVariants_t * btxVariant);
        ~HssIno();
};

}

#endif /** HSS_ARDUINO_HPP_ **/