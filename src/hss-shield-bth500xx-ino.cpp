/**
 * @file hss-shield-bth500xx-ino.cpp
 * @brief Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield Arduino class
 * @copyright Copyright (c) 2023 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-bth500xx-ino.hpp"
#include <Arduino.h>

using namespace hss;

/**
 * @brief Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield Arduino constructor
 * 
 */
Bth500xxShieldIno::Bth500xxShieldIno():
Bth500xxShield (
    switches[0] = new HssIno(BTH500XX_HWCONFIG.den1, BTH500XX_HWCONFIG.in1, BTH500XX_HWCONFIG.is1, &BTH50015_1LUA),
    switches[1] = new HssIno(BTH500XX_HWCONFIG.den2, BTH500XX_HWCONFIG.in2, BTH500XX_HWCONFIG.is2, &BTH50030_1LUA),
    vs = new ADCIno(BTH500XX_HWCONFIG.vs),
    vOut = new ADCIno(BTH500XX_HWCONFIG.vOut),
    temp = nullptr,
    btxVariant1 = &BTH50015_1LUA,
    btxVariant2 = &BTH50030_1LUA
)
{

}

/**
 * @brief       Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield Arduino constructor
 * @details     This constructor has a function parameter in order to pass a custom pin configuration to the shield-object
 * @param[in]   config: Configuration structure for custom pin configuration
 */
Bth500xxShieldIno::Bth500xxShieldIno(Bth500xxHwConfig_t config):
Bth500xxShield (
    switches[0] = new HssIno(config.den1, config.in1, config.is1, &BTH50015_1LUA),
    switches[1] = new HssIno(config.den2, config.in2, config.is2, &BTH50030_1LUA),
    vs = new ADCIno(config.vs),
    vOut = new ADCIno(config.vOut),
    config.temp != NULL ? temp = new ADCIno(config.temp) : temp = nullptr,
    btxVariant1 = &BTH50015_1LUA,
    btxVariant2 = &BTH50030_1LUA
)
{

}

/**
 * @brief Destroy the Bth 5 0 0xx Shield Ino:: Bth 5 0 0xx Shield Ino object
 * 
 */
Bth500xxShieldIno::~Bth500xxShieldIno()
{

}