/**
 * @file        hss-shield-btt60xx-ino.cpp
 * @brief       Profet (24V) shield with BTT6030-2EKA and BTT6020-1EKA Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-btt60xx-ino.hpp"
#include <Arduino.h>

using namespace hss;

/**
 * @brief   Profet (24V) BTT6030 Shield constructor
 * @details Initialize all protected class pointers.
 */
Btt60xxShieldIno::Btt60xxShieldIno():
Btt60xxShield  (
                        switches[0] = new HssIno(BTT60XX_HWCONFIG.den_0, BTT60XX_HWCONFIG.in0_0, BTT60XX_HWCONFIG.in1_0, BTT60XX_HWCONFIG.dsel_0, BTT60XX_HWCONFIG.is_0, &BTT6030),
                        switches[1] = new HssIno(BTT60XX_HWCONFIG.den_1, BTT60XX_HWCONFIG.in0_1, BTT60XX_HWCONFIG.in1_1, BTT60XX_HWCONFIG.dsel_1, BTT60XX_HWCONFIG.is_1, &BTT6030),
                        switches[2] = new HssIno(BTT60XX_HWCONFIG.den_2, BTT60XX_HWCONFIG.in0_2, BTT60XX_HWCONFIG.is_2, &BTT6020)
                    )
{

}

/**
 * @brief       Profet (24V) BTT6030 Shield constructor for custom configuration
 * @details     Initialize all class pointers. This constructor allows to pass custom shield configuration.
 * @param[in]   config  Pinout hardware configuration
 */
Btt60xxShieldIno::Btt60xxShieldIno(Btt60xxHwConfig_t config):
Btt60xxShield  (
                        switches[0] = new HssIno(config.den_0, config.in0_0, config.in1_0, config.dsel_0, config.is_0, &BTT6030),
                        switches[1] = new HssIno(config.den_1, config.in0_1, config.in1_1, config.dsel_1, config.is_1, &BTT6030),
                        switches[2] = new HssIno(config.den_2, config.in0_2, config.is_2, &BTT6020)
                    )
{

}

/**
 * @brief Destructor of the Profet (24V) BTT6030 Shield
 *
 */
Btt60xxShieldIno::~Btt60xxShieldIno()
{

}