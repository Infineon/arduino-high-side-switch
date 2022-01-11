/**
 * @file        hss-shield-platf.hpp
 * @brief       Hardware platform predefined Arduino configurations
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_PLATF_HPP_
#define HSS_SHIELD_PLATF_HPP_

#include <stdint.h>

namespace hss
{

/**
 * @addtogroup arduinoWrapper
 * @{
 */

/**
 * @brief BTS700x Shield Pin Configuration
 */
struct Bts700xHwConfig_t
{
    uint8_t led1;   /**< Shield LED 1 pin */
    uint8_t led2;   /**< Shield LED 2 pin */
    uint8_t led3;   /**< Shield LED 3 pin */
    uint8_t led4;   /**< Shield LED 4 pin */

    uint8_t in1;    /**< Switch 1 input pin */
    uint8_t in2;    /**< Switch 2 input pin */
    uint8_t in3;    /**< Switch 3 input pin */
    uint8_t in4;    /**< Switch 4 input pin */

    uint8_t oloff;  /**< Output offset pin */

    uint8_t den1_den3;  /**< Shared diagnosis enable switches 1 and 3 pin*/
    uint8_t den2_den4;  /**< Shared diagnosis enable switches 2 and 4 pin */

    uint8_t pushButtonDigital;  /**< Digital push button pin */

    uint8_t pushButtonAnalog;   /**< Analog push button pin */
    uint8_t vBat;               /**< Battery voltage pin */
    uint8_t is1_is2;            /**< Shared diagnosis current pin switches 1 and 3 */
    uint8_t is3_is4;            /**< Shared diagnosis current pin switches 2 and 4 */
};

/**
 * @brief BTS700x Shield Default Pin Configuration 
 */
extern Bts700xHwConfig_t BTS700X_HWCONFIG;

/**
 * @brief BTS5001x Shield Pin Configuration 
 */
struct BTS5001xHwConfig_t
{
    uint8_t led2;   /**< Shield LED 2 pin */
    uint8_t led3;   /**< Shield LED 3 pin */

    uint8_t in;     /**< Switch input pin */

    uint8_t pushButtonAnalog;   /**< Analog push button pin */

    uint8_t vBat;   /**< Analog push button pin */

    uint8_t is;     /**< Diagnosis current pin */
};

/**
 * @brief BTS5001x Shield Default Pin Configuration 
 */
extern BTS5001xHwConfig_t BTS5001X_HWCONFIG;

/**
 * @brief BTT60xx Shield Pin Configuration 
 */
struct Btt60xxHwConfig_t
{
    //Profet0 - BTT6030 (2 channel) pin config
    uint8_t in0_0;      /**< Switch 0 channel 0 input pin */
    uint8_t den_0;      /**< Switch 0 diagnosis enable pin */
    uint8_t dsel_0;     /**< Switch 0 diagnosis select pin */
    uint8_t in1_0;      /**< Switch 0 channel 1 input pin */
    uint8_t is_0;       /**< Switch 0 diagnosis current pin */

    //Profet1 - BTT6030 (2 channel) pin config
    uint8_t in0_1;      /**< Switch 1 channel 0 input pin */
    uint8_t den_1;      /**< Switch 1 diagnosis enable pin */
    uint8_t dsel_1;     /**< Switch 1 diagnosis select pin */
    uint8_t in1_1;      /**< Switch 1 channel 1 input pin */
    uint8_t is_1;       /**< Switch 1 diagnosis current pin */

    //Profet2 - BTT6020 (1 channel) pin config
    uint8_t in0_2;      /**< Switch 2 input pin */
    uint8_t den_2;      /**< Switch 2 diagnosis enable pin */
    uint8_t is_2;       /**< Switch 2 diagnosis current pin */

};

/**
 * @brief BTT60xx Shield Default Pin Configuration 
 */
extern Btt60xxHwConfig_t BTT60XX_HWCONFIG;

/** @} */

}

#endif /** HSS_SHIELD_PLATF_HPP_ **/