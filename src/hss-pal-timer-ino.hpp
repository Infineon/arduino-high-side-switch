/**
 * @file        hss-pal-timer-ino.hpp
 * @brief       Timer platform abstraction layer Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_PAL_TIMER_INO_HPP_
#define HSS_PAL_TIMER_INO_HPP_

#include "hss-pal-timer.hpp"

namespace hss
{

/**
 * @addtogroup arduinoPal
 * @{
 */

/**
 * @class TimerIno
 * @brief Timer platform abstraction layer Arduino API
 */
class TimerIno: virtual public TimerPAL
{
    public:

        TimerIno();
        ~TimerIno();
        Error_t init();
        Error_t deinit();
        Error_t start();
        Error_t elapsed(uint32_t &elapsed);
        Error_t stop();
        Error_t delayMilli(uint32_t timeout);
        Error_t delayMicro(uint32_t timeout);

    private:

        uint32_t startTime;
};

/** @} */

}

#endif /** HSS_PAL_TIMER_INO_HPP_ **/