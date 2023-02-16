/**
 * @file        hss-pal-adc-ino.cpp
 * @brief       ADC platform abstraction layer Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include <Arduino.h>
#include "hss-pal-adc-ino.hpp"

using namespace hss;

/**
 * @brief Default constructor of the ADC class for arduino
 */
ADCIno::ADCIno() : pin(0)
{

}

/**
 * @brief    Constructor of the ADC class for arduino
 * @details  This constructor takes the number of the pin.
 * @param[in]   pin Number of the desired ADC pin
 */
ADCIno::ADCIno(uint8_t pin) : pin(pin)
{

}

/**
 * @brief Default constructor of the Arduino ADC
 *
 */
ADCIno::~ADCIno()
{

}

/**
 * @brief  ADC initialization
 * @return High-side switch error code
 */
Error_t ADCIno::init()
{
    return OK;
}

/**
 * @brief ADC deinitialization
 * @return High-side switch error code
 */
Error_t ADCIno::deinit()
{
    return OK;
}

/**
 * @brief ADC enable
 * @return High-side switch error code
 */
Error_t ADCIno::enable()
{
    return OK;
}


/**
 * @brief ADC disable
 * @return High-side switch error code
 */
Error_t ADCIno::disable()
{
    return OK;
}

/**
 * @brief Read the current ADC-Value
 * @return uint16_t ADC value
 */
uint16_t ADCIno::ADCRead()
{
    uint16_t result = 0;

    result = analogRead(pin);

    return result;
}

/**
 * @brief   Write on an analog pin
 * @details This functions writes the given value to the analog pin
 * @param[in] value Value to write
 * @return  High-side switch error code
 */
Error_t ADCIno::ADCWrite(uint8_t value)
{
    analogWrite(pin, value);

    return OK;
}

