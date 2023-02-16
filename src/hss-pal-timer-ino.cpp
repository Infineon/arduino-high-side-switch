/**
 * @file        hss-pal-timer-ino.cpp
 * @brief       Timer platform abstraction layer Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include <Arduino.h>
#include "hss-pal-timer-ino.hpp"

using namespace hss;

/**
 * @brief Constructor of the Timer class for arduino
 */
TimerIno::TimerIno()
{

}

/**
 * @brief Destructor of the Timer class for arduino
 *
 */
TimerIno::~TimerIno()
{

}

/**
 * @brief   Initialization of the Timer
 * @details This function is initializing the Timer and sets
 *          the elapsed time to zero.
 * @return High-side switch error code
 */
Error_t TimerIno::init()
{
    startTime = 0;
    return OK;
}

/**
 * @brief   Deinitialize the Timer
 * @details This function deinitialize the Timer and also
 *          resets the elapsed time variable.
 * @return High-side switch error code
 */
Error_t TimerIno::deinit()
{
    startTime = 0;
    return OK;
}

/**
 * @brief   Start the timer
 * @details This function is starting the timer.
 * @return High-side switch error code
 */
Error_t TimerIno::start()
{
    startTime = millis();
    return OK;
}

/**
 * @brief   Calculate the elapsed time
 * @details This function is calculating the elapsed time since the
 *          start of the timer. The value stored in the given variable
 *          is in milliseconds.
 * @param[in]   &elapsed      Address of a value where the elapsed time should be stored
 * @return High-side switch error code
 */
Error_t TimerIno::elapsed(uint32_t &elapsed)
{
    elapsed = millis() - startTime;
    return OK;
}

/**
 * @brief   Stop the timer
 * @details This function stops the timer and resets the
 *          start time variable.
 * @return High-side switch error code
 */
Error_t TimerIno::stop()
{
    startTime = 0;
    return OK;
}

/**
 * @brief   Time delay
 * @details This function is causing a desired delay of the application.
 *          The input value is given in milliseconds.
 * @param[in]   timeout                 Desired timeout in ms
 * @return High-side switch error code
 */
Error_t TimerIno::delayMilli(uint32_t timeout)
{
    delay(timeout);
    return OK;
}

/**
 * @brief   Time delay
 * @details This function is causing a desired delay of the application.
 *          The input value is given in microseconds.
 * @param[in]   timeout                 Desired timeout in us
 * @return High-side switch error code
 */
Error_t TimerIno::delayMicro(uint32_t timeout)
{
    delayMicroseconds(timeout);
    return OK;
}

