/**
 * @file        hss-shield-bts700x-ino.cpp
 * @brief       Profet +2 (12V) shield with BTS700x-1EPP Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-bts700x-ino.hpp"
#include <Arduino.h>

using namespace hss;

/**
 * @brief       BTS700xShield High-Side-Switch constructor
 * @details     Initializes all class pointers
 * @param[in]   variantSel  Shield variant type
 */
Bts700xShieldIno::Bts700xShieldIno(BtxVariants_t *variantSel):
Bts700xShield   (   led1 = ((BTS700X_HWCONFIG.led1 == GPIOIno::unusedPin) ? NULL : new GPIOIno(BTS700X_HWCONFIG.led1, OUTPUT, GPIOIno::POSITIVE)),
                    led2 = ((BTS700X_HWCONFIG.led2 == GPIOIno::unusedPin) ? NULL : new GPIOIno(BTS700X_HWCONFIG.led2, OUTPUT, GPIOIno::POSITIVE)),
                    led3 = ((BTS700X_HWCONFIG.led3 == GPIOIno::unusedPin) ? NULL : new GPIOIno(BTS700X_HWCONFIG.led3, OUTPUT, GPIOIno::POSITIVE)),
                    led4 = ((BTS700X_HWCONFIG.led4 == GPIOIno::unusedPin) ? NULL : new GPIOIno(BTS700X_HWCONFIG.led4, OUTPUT, GPIOIno::POSITIVE)),
                    hss1 = new HssIno(BTS700X_HWCONFIG.den1_den3, BTS700X_HWCONFIG.in1, BTS700X_HWCONFIG.is1_is2, variantSel),
                    hss2 = new HssIno(BTS700X_HWCONFIG.den2_den4, BTS700X_HWCONFIG.in2, BTS700X_HWCONFIG.is1_is2, variantSel),
                    hss3 = new HssIno(BTS700X_HWCONFIG.den1_den3, BTS700X_HWCONFIG.in3, BTS700X_HWCONFIG.is3_is4, variantSel),
                    hss4 = new HssIno(BTS700X_HWCONFIG.den2_den4, BTS700X_HWCONFIG.in4, BTS700X_HWCONFIG.is3_is4, variantSel),
                    timer = new TimerIno(),
                    oloff = new GPIOIno(BTS700X_HWCONFIG.oloff, OUTPUT, GPIOIno::POSITIVE),
                    pushButtonDigital = new GPIOIno(BTS700X_HWCONFIG.pushButtonDigital, INPUT_PULLUP, GPIOIno::POSITIVE),
                    pushButtonAnalog = new ADCIno(BTS700X_HWCONFIG.pushButtonAnalog),
                    vBat = new ADCIno(BTS700X_HWCONFIG.vBat),
                    btxVariant = variantSel
                )
{

}

/**
 * @brief       BTS700xShield High-Side-Switch constructor for custom configuration
 * @details     Initialize all class pointers. This constructor allows to pass custom shield configuration
 * @param[in]   variantSel  Shield variant types
 * @param[in]   config  Pinout hardware configuration
 */
Bts700xShieldIno::Bts700xShieldIno(BtxVariants_t *variantSel, Bts700xHwConfig_t config):
Bts700xShield   (   led1 = ((config.led1 == GPIOIno::unusedPin) ? NULL : new GPIOIno(config.led1, OUTPUT, GPIOIno::POSITIVE)),
                    led2 = ((config.led2 == GPIOIno::unusedPin) ? NULL : new GPIOIno(config.led2, OUTPUT, GPIOIno::POSITIVE)),
                    led3 = ((config.led3 == GPIOIno::unusedPin) ? NULL : new GPIOIno(config.led3, OUTPUT, GPIOIno::POSITIVE)),
                    led4 = ((config.led4 == GPIOIno::unusedPin) ? NULL : new GPIOIno(config.led4, OUTPUT, GPIOIno::POSITIVE)),
                    hss1 = new HssIno(config.den1_den3, config.in1, config.is1_is2, variantSel),
                    hss2 = new HssIno(config.den2_den4, config.in2, config.is1_is2, variantSel),
                    hss3 = new HssIno(config.den1_den3, config.in3, config.is3_is4, variantSel),
                    hss4 = new HssIno(config.den2_den4, config.in4, config.is3_is4, variantSel),
                    timer = new TimerIno(),
                    oloff = new GPIOIno(config.oloff, OUTPUT, GPIOIno::POSITIVE),
                    pushButtonDigital = new GPIOIno(config.pushButtonDigital, INPUT_PULLUP, GPIOIno::POSITIVE),
                    pushButtonAnalog = new ADCIno(config.pushButtonAnalog),
                    vBat = new ADCIno(config.vBat),
                    btxVariant = variantSel
                )
{

}

/**
 * @brief Destructor of the BTS700x Shield
 *
 */
Bts700xShieldIno::~Bts700xShieldIno()
{

}