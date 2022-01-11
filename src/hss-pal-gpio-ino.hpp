/**
 * @file        hss-pal-gpio-ino.hpp
 * @brief       GPIO platform abstraction layer Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_PAL_GPIO_INO_HPP_
#define HSS_PAL_GPIO_INO_HPP_

#include "hss-pal-gpio.hpp"

namespace hss
{

/**
 * @addtogroup arduinoPal
 * @{
 */

/**
 * @class  GPIOIno
 * @brief  GPIO platform abstraction layer Arduino API
 */
class GPIOIno: virtual public GPIOPAL
{
private:

    uint8_t     pin;
    uint8_t     mode;
    VLogic_t    logic;

public:

    static constexpr uint8_t  unusedPin = 0xFFU;    /**< Unused pin */

                GPIOIno();
                GPIOIno(uint8_t pin, uint8_t mode, VLogic_t logic);
                ~GPIOIno();
    Error_t     init();
    Error_t     deinit();
    VLevel_t    read();
    Error_t     write(VLevel_t level);
    Error_t     enable();
    Error_t     disable();
};

/** @} */

}

#endif /** HSS_PAL_GPIO_INO_HPP_ **/
