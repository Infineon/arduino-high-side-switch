/**
 * @file        hss-pal-gpio-ino.cpp
 * @brief       GPIO platform abstraction layer Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */


#include <Arduino.h>
#include "hss-pal-gpio-ino.hpp"

using namespace hss;

/**
 * @brief   Constructor of the GPIO class for arduino
 * @details This function is setting the basics for a GPIO.
 */
GPIOIno::GPIOIno() : pin(0), mode(OUTPUT), logic(POSITIVE)
{

}

/**
 * @brief    Constructor of the  GPIO class for arduino
 * @details  This function is setting the basics for a GPIO. It allows to set the pin number,
 *           mode of the pin and the logic level.
 * @param[in]   pin     Number of the desired pin
 * @param[in]   mode    Defines the mode of the pin (INPUT, OUTPUT, etc.)
 * @param[in]   logic   Defines the logic level of the pin
 */
GPIOIno::GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic)
: pin(pin), mode(mode), logic(logic)
{

}

/**
 * @brief   Initialize the GPIO
 * @details This function is initializing the chosen pin.
 * @return  High-side switch error code
 */
Error_t GPIOIno::init()
{
    pinMode(this->pin, this->mode);
    return OK;
}

/**
 * @brief   Deinitialize the GPIO
 * @details This function is deinitializing the chosen pin.
 * @return  High-side switch error code
 */
Error_t GPIOIno::deinit()
{
    return OK;
}

/**
 * @brief   Read GPIO logic level
 * @details This function reads the logic level of the chosen pin and
 *          returns the logic level value.
 * @return  VLevel_t
 * @retval  0    GPIO_LOW
 * @retval  1    GPIO_HIGH
 */
GPIOIno::VLevel_t GPIOIno::read()
{
    return (VLevel_t) digitalRead(this->pin);
}

/**
 * @brief   Set GPIO logic level
 * @details This functions sets the logic level of the chosen pin.
 * @param[in]   level   Desired logic level of the pin
 * @return High-side switch error code
 */
Error_t GPIOIno::write(VLevel_t level)
{
    digitalWrite(this->pin, level);
    return OK;
}

/**
 * @brief   Enable the GPIO
 * @details This functions enable the chosen pin. Depending on the chosen logic of the pin
 *          it sets the right logic level of the pin.
 * @return  High-side switch error code
 */
Error_t GPIOIno::enable()
{
    if(this->logic == POSITIVE){
        digitalWrite(this->pin, GPIO_HIGH);
    }
    else if(this->logic == NEGATIVE){
        digitalWrite(this->pin, GPIO_LOW);;
    }
    return OK;
}

/**
 * @brief   Disable the GPIO
 * @details This functions disables the chosen pin. Depending on the chosen logic of the pin
 *          it sets the right logic level of the pin.
 * @return  High-side switch error code
 */
Error_t GPIOIno::disable()
{
    if(this->logic == POSITIVE){
        digitalWrite(this->pin, GPIO_LOW);
    }
    else if(this->logic == NEGATIVE){
        digitalWrite(this->pin, GPIO_HIGH);
    }
    return OK;
}





