/**
 * @file        hss-variants.hpp
 * @brief       High side switch hardware variants
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_VARIANTS_HPP_
#define HSS_VARIANTS_HPP_

#include <stdint.h>

namespace hss
{

/**
 * @addtogroup hssCorelib
 * @{
 */

/**
 * @brief   High side switch variant type
 */
enum HssType_t
{   
    BTH500XX,       /**< Power PROFET™ + 24V / 48V family */
    BTS500XX,       /**< PROFET™ + 12V family */
    BTS5001X,       /**< Power PROFET™ family */
    BTS700X,        /**< PROFET™ +2 12V family */
    BTT60X0         /**< PROFET™ + 24V family */
};

/**
 * @brief   High side switch hardware variant struct
 * @details It contains all important parameters for the correct usage of
 *          of the diagnosis functions of the Switch
 */
struct BtxVariants_t
{
    HssType_t       type;           /**< Type of the chosen High side switch */
    const uint16_t  kilis;          /**< Current sense ratio */
    float           iisFault;       /**< Current in case of fault event */
    float           iisOl;          /**< Current in case of an open load */
    float           iisEn;          /**< Leakage current when channel is enabled */
    float           iisO;           /**< Sense offset */
};

extern BtxVariants_t BTH50015_1LUA;
extern BtxVariants_t BTH50030_1LUA;

extern BtxVariants_t BTS50005_1LUA;
extern BtxVariants_t BTS50010_1LUA;

extern BtxVariants_t BTS50015;
extern BtxVariants_t BTS50010;

extern BtxVariants_t BTS7002;
extern BtxVariants_t BTS7004;
extern BtxVariants_t BTS7006;
extern BtxVariants_t BTS7008;

extern BtxVariants_t BTT6030;
extern BtxVariants_t BTT6020;

/** @} */

}

#endif /** HSS_VARIANTS_HPP_ **/