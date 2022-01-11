/**
 * @file        hss.hpp
 * @brief       High side switch class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_H_
#define HSS_H_

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "hss-types.hpp"
#include "hss-pal-timer.hpp"
#include "hss-pal-gpio.hpp"
#include "hss-pal-adc.hpp"
#include "hss-variants.hpp"
#include "hss-filter.hpp"

namespace hss
{

/**
 * @addtogroup hssCorelib
 * @{
 */

/**
 * @brief  High side switch API
 */
class Hss
{
    public:

                            Hss(GPIOPAL *den, GPIOPAL *in, ADCPAL *is, TimerPAL *timer, BtxVariants_t *btxVariant);
                            Hss(GPIOPAL *den, GPIOPAL *in0, GPIOPAL *in1, GPIOPAL *dsel, ADCPAL *is, TimerPAL *timer, BtxVariants_t *btxVariant);
                            ~Hss();
        Error_t             init();
        Error_t             deinit();
        Error_t             enable(Channel_t ch=CHANNEL0);
        Error_t             disable(Channel_t ch=CHANNEL0);
        Error_t             enableDiag();
        Error_t             disableDiag();

        Status_t            getSwitchStatus();
        DiagStatus_t        diagRead(float senseCurrent, Channel_t ch=CHANNEL0);
        float               readIs(uint16_t rSense, Channel_t ch=CHANNEL0);

        void                setCurrentOffset(float offset);

    protected:

        GPIOPAL             *den;   /**< Diagnosis enable */
        GPIOPAL             *in0;   /**< Switch input 0 */
        GPIOPAL             *in1;   /**< Switch input 1 */
        GPIOPAL             *dsel;  /**< Diagnosis select */
        ADCPAL              *is;    /**< Diagnosis current */

        TimerPAL            *timer; /**< Timer instace */

        ExponentialFilter   *currentFilter; /**< Current filter */

        BtxVariants_t       *btxVariant;    /**< BTx switch variant */
        Status_t            status;         /**< Switch status */
        Status_t            statusCh0;      /**< Channel 0 status */
        Status_t            statusCh1;      /**< Channel 1 status */

        DiagEnable_t        diagEnb;        /**< Diagnosis enabled flag */
        DiagStatus_t        diagStatus;     /**< Diagnosis status */

        Error_t             selDiagCh(Channel_t ch);

    private:

        float               currentOffset = 0.0;    /**< Diagnosis current offset */

};

}

/** @} */

#endif /** HSS_H_ **/
