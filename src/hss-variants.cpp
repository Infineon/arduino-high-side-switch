/**
 * @file        hss-variants.cpp
 * @brief       High side switch hardware variants
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-variants.hpp"

namespace hss
{

/**
 * @brief   BTS7002.
 * @details Is rated for nominal 21 A and is the Profet with the highest useable power
 */
BtxVariants_t BTS7002 = {
    .type = BTS700X,
    .kilis = 22700,
    .iisFault = 0.0044,
    .iisOl = 0.0018,
    .iisEn = 0.000002
};

/**
 * @brief   BTS7002.
 * @details Is rated for nominal 15 A
 */
BtxVariants_t BTS7004 = {
    .type = BTS700X,
    .kilis = 20000,
    .iisFault = 0.0044,
    .iisOl = 0.0018,
    .iisEn = 0.000002
};

/**
 * @brief   BTS7006.
 * @details Is rated for nominal 12.5 A
 */
BtxVariants_t BTS7006 = {
    .type = BTS700X,
    .kilis = 17700,
    .iisFault = 0.0044,
    .iisOl = 0.0018,
    .iisEn = 0.000002
};

/**
 * @brief   BTS7008.
 * @details Is rated for nominal 11 A
 */
BtxVariants_t BTS7008 = {
    .type = BTS700X,
    .kilis = 14500,
    .iisFault = 0.0044,
    .iisOl = 0.0018,
    .iisEn = 0.000002
};

/**
 * @brief   BTS50010-1TAD.
 * @details Is rated for nominal 40 A
 */
BtxVariants_t BTS50010 = {
    .type = BTS5001X,
    .kilis = 52100,
    .iisFault = 0.0035,
    .iisOl = 0.0,
    .iisEn = 0.0,
    .iisO = 0.000008
};

/**
 * @brief   BTS50015-1TAD.
 * @details Is rated for nominal 33 A
 */
BtxVariants_t BTS50015 = {
    .type = BTS5001X,
    .kilis = 51500,
    .iisFault = 0.0035,
    .iisOl = 0.0,
    .iisEn = 0.0,
    .iisO = 0.000005
};

/**
 * @brief   BTT6020.
 * @details Is rated for nominal 7 A
 */
BtxVariants_t BTT6020 = {
    .type = BTT60X0,
    .kilis = 2950,
    .iisFault = 0.006,
    .iisOl = 0.000004
};

/**
 * @brief   BTT6030.
 * @details Is rated for nominal 5 A per channel
 */
BtxVariants_t BTT6030 = {
    .type = BTT60X0,
    .kilis = 2240,
    .iisFault = 0.006,
    .iisOl = 0.000005
};

}