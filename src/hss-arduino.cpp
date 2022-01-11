/**
 * @file        hss-arduino.cpp
 * @brief       High side switch Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */
#include "hss-arduino.hpp"
#include <Arduino.h>

using namespace hss;

/**
 * @brief   Constructor of the Arduino High-Side-Switch class
 * @details This functions is the default constructor of the Arduino High-Side-Switch class.
 *          There are different variants of the High-Side-Switch, therefore you have to chose one.
 * @param[in]   in            Pin number of the input pin
 * @param[in]   is            Pin number of the sense current output
 * @param[in]   btxVariant    Shield Variant type
 */
HssIno::HssIno(uint8_t in, uint8_t is, BtxVariants_t * btxVariant)
: Hss(nullptr,
      new GPIOIno(in,  OUTPUT, GPIOIno::POSITIVE),
      nullptr,
      nullptr,
      new ADCIno(is),
      new TimerIno(),
      btxVariant)
{

}

/**
 * @brief   Constructor of the Arduino High-Side-Switch class
 * @details This functions is the default constructor of the Arduino High-Side-Switch class.
 *          There are different variants of the High-Side-Switch, therefore you have to chose one.
 * @param[in]   den           Pin number of the diagnostic enable pin
 * @param[in]   in            Pin number of the input pin
 * @param[in]   is            Pin number of the sense current output
 * @param[in]   btxVariant    Shield Variant type
 */
HssIno::HssIno(uint8_t den, uint8_t in, uint8_t is, BtxVariants_t * btxVariant)
: Hss(new GPIOIno(den, OUTPUT, GPIOIno::POSITIVE),
      new GPIOIno(in,  OUTPUT, GPIOIno::POSITIVE),
      nullptr,
      nullptr,
      new ADCIno(is),
      new TimerIno(),
      btxVariant)
{

}

/**
 * @brief   Constructor of the Arduino High-Side-Switch class
 * @details This functions is the default constructor of the Arduino High-Side-Switch class.
 *          There are different variants of the High-Side-Switch, therefore you have to chose one.
 * @param[in]   den           Pin number of the diagnostic enable pin
 * @param[in]   in0           Pin number of the input pin 0
 * @param[in]   in1           Pin number of the input pin 1
 * @param[in]   dsel          Pin number of diagnosis channel select
 * @param[in]   is            Pin number of the sense current output
 * @param[in]   btxVariant    Shield Variant type
 */
HssIno::HssIno(uint8_t den, uint8_t in0, uint8_t in1, uint8_t dsel, uint8_t is, BtxVariants_t * btxVariant)
: Hss(new GPIOIno(den, OUTPUT, GPIOIno::POSITIVE),
      new GPIOIno(in0,  OUTPUT, GPIOIno::POSITIVE),
      new GPIOIno(in1,  OUTPUT, GPIOIno::POSITIVE),
      new GPIOIno(dsel,  OUTPUT, GPIOIno::POSITIVE),
      new ADCIno(is),
      new TimerIno(),
      btxVariant)
{

}

/**
 * @brief Destructor of the Arduino High-Side-Switch
 *
 */
HssIno::~HssIno()
{
    delete den;
    delete in0;
    delete in1;
    delete dsel;
    delete is;
    delete timer;
}