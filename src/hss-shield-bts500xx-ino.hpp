/**
 * @file        hss-shield-bts500xx-ino.hpp
 * @brief       Power PROFET +12V Shield with BTS500xx-1LUA class
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTS500XX_INO_HPP
#define HSS_SHIELD_BTS500XX_INO_HPP

#include "hss-arduino.hpp"
#include "hss-shield-bts500xx.hpp"
#include "hss-variants.hpp"
#include "hss-shield-platf.hpp"

namespace hss
{

/**
 * @brief Power PROFET +12V Shield with BTS500xx-1LUA Arduino API
 */
class Bts500xxShieldIno : public Bts500xxShield
{
    public:
        Bts500xxShieldIno();
        Bts500xxShieldIno(Bts500xxHwConfig_t config);
        ~Bts500xxShieldIno();
};

}

#endif /** HSS_SHIELD_BTS500XX_INO_HPP */