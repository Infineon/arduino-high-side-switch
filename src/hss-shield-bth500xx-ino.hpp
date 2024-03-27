/**
 * @file hss-shield-bth500xx-ino.hpp
 * @brief Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield Arduino class
 * @copyright Copyright (c) 2023 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTH500XX_INO_HPP
#define HSS_SHIELD_BTH500XX_INO_HPP

#include "hss-arduino.hpp"
#include "hss-shield-bth500xx.hpp"
#include "hss-variants.hpp"
#include "hss-shield-platf.hpp"

namespace hss
{

class Bth500xxShieldIno : public Bth500xxShield
{
    public:
        Bth500xxShieldIno();
        Bth500xxShieldIno(Bth500xxHwConfig_t config);
        ~Bth500xxShieldIno();
};

}

#endif /** HSS_SHIELD_BTH500XX_INO_HPP */