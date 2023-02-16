/**
 * @file        hss-shield-bts500xx-ino.cpp
 * @brief       Power PROFET +12V Shield with BTS500xx-1LUA class
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-bts500xx-ino.hpp"
#include <Arduino.h>

using namespace hss;

/**
 * @brief       Constructor of the BTS500xx Arduino Shield class with default pin configuration
 */
Bts500xxShieldIno::Bts500xxShieldIno():
Bts500xxShield (
                    switches[0] = new HssIno(BTS500XX_HWCONFIG.den1, BTS500XX_HWCONFIG.in1, BTS500XX_HWCONFIG.is1, &BTS50005_1LUA),
                    switches[1] = new HssIno(BTS500XX_HWCONFIG.den2, BTS500XX_HWCONFIG.in2, BTS500XX_HWCONFIG.is2, &BTS50010_1LUA),
                    vs = new ADCIno(BTS500XX_HWCONFIG.vs),
                    vOut = new ADCIno(BTS500XX_HWCONFIG.vOut),
                    temp = new ADCIno(BTS500XX_HWCONFIG.temp),
                    btxVariant1 = &BTS50005_1LUA,
                    btxVariant2 = &BTS50010_1LUA
)
{

}

/**
 * @brief       Constructor of the BTS500xx Arduino Shield class with custom pin configuration
 * @param[in]   config Configuration for custom pin configuration
 */
Bts500xxShieldIno::Bts500xxShieldIno(Bts500xxHwConfig_t config):
Bts500xxShield (
                    switches[0] = new HssIno(config.den1, config.in1, config.is1, &BTS50005_1LUA),
                    switches[1] = new HssIno(config.den2, config.in2, config.is2, &BTS50010_1LUA),
                    vs = new ADCIno(config.vs),
                    vOut = new ADCIno(config.vOut),
                    temp = new ADCIno(config.temp),
                    btxVariant1 = &BTS50005_1LUA,
                    btxVariant2 = &BTS50010_1LUA
)
{

}

/**
 * @brief Destructor of the BTS500xx Shield class
 */
Bts500xxShieldIno::~Bts500xxShieldIno()
{

}