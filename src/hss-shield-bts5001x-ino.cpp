/**
 * @file        hss-shield-bts5001x-ino.cpp
 * @brief       Power Profet (12V) shield with BTS500xx Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-bts5001x-ino.hpp"
#include <Arduino.h>

using namespace hss;

/**
 * @brief       High-Side-Switch-Board constructor
 * @details     Initialize all protected class pointers with a null pointer
 * @param[in]   variantSel  Shield variant types 
 */
Bts5001xShieldIno::Bts5001xShieldIno(BtxVariants_t *variantSel):
Bts5001xShield(hss1 = new HssIno(BTS5001X_HWCONFIG.in, BTS5001X_HWCONFIG.is, variantSel),
               led2 = ((BTS5001X_HWCONFIG.led2 == GPIOIno::unusedPin) ? NULL : new GPIOIno(BTS5001X_HWCONFIG.led2, OUTPUT, GPIOIno::POSITIVE)),
               led3 = ((BTS5001X_HWCONFIG.led3 == GPIOIno::unusedPin) ? NULL : new GPIOIno(BTS5001X_HWCONFIG.led3, OUTPUT, GPIOIno::POSITIVE)),
               pushButton = new ADCIno(BTS5001X_HWCONFIG.pushButtonAnalog),
               vBat = new ADCIno(BTS5001X_HWCONFIG.vBat))
{

}

/**
 * @brief       High-Side-Switch-Board constructor
 * @details     Initialize all protected class pointers with a null pointer
 * @param[in]   variantSel  Shield variant types 
 * @param[in]   config  Pinout hardware configuration
 */
Bts5001xShieldIno::Bts5001xShieldIno(BtxVariants_t *variantSel, BTS5001xHwConfig_t config):
Bts5001xShield(hss1 = new HssIno(config.in, config.is, variantSel),
               led2 = ((config.led2 == GPIOIno::unusedPin) ? NULL : new GPIOIno(config.led2, OUTPUT, GPIOIno::POSITIVE)),
               led3 = ((config.led3 == GPIOIno::unusedPin) ? NULL : new GPIOIno(config.led3, OUTPUT, GPIOIno::POSITIVE)),
               pushButton = new ADCIno(config.pushButtonAnalog),
               vBat = new ADCIno(config.vBat))
{

}


/**
 * @brief Destructor of the High-Side-Switch-Board
 *
 */
Bts5001xShieldIno::~Bts5001xShieldIno()
{

}

