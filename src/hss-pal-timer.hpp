/**
 * @file        hss-pal-timer.hpp
 * @brief       Timer platform abstraction layer class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>
#include "hss-types.hpp"

#ifndef HSS_PAL_TIMER_HPP_
#define HSS_PAL_TIMER_HPP_

namespace hss
{

/**
 * @addtogroup hssPal
 * @{
 */

/**
 * @class TimerPAL
 * @brief Timer abstract API 
 */
class TimerPAL
{
    public:

        /**
         * @brief   Initialize the timer
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t         init    () = 0;

        /**
         * @brief   Deinitialize the timer
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t         deinit   () = 0;

        /**
         * @brief   Starts the timer
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t         start   () = 0;

        /**
         * @brief       Elapsed time since the timer was started
         * @param[out]  elapsed Time in milliseconds
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t         elapsed (uint32_t &elapsed) = 0;

        /**
         * @brief   Stops the timer
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t         stop    () = 0;

        /**
         * @brief       Introduces a delay during the specified time
         * @param[in]   timeout    Delay time in milliseconds
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t        delayMilli (uint32_t timeout) = 0;

        /**
         * @brief       Introduces a delay during the specified time
         * @param[in]   timeout     Delay time in microseconds
         * @return High-side switch error code 
         * @retval      OK          If success
         * @retval      INIT_ERROR  If hardware interface error
         */
        virtual  Error_t        delayMicro  (uint32_t timeout) = 0;

};

/** @} */

}

#endif /** HSS_PAL_TIMER_HPP_ **/
