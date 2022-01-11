/**
 * @file        hss-shield-bts700x-ino.hpp
 * @brief       Profet +2 (12V) shield with BTS700x-1EPP Arduino class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HSS_SHIELD_BTS700X_INO_HPP_
#define HSS_SHIELD_BTS700X_INO_HPP_

#include "hss-arduino.hpp"
#include "hss-shield-bts700x.hpp"
#include "hss-variants.hpp"
#include "hss-shield-platf.hpp"

namespace hss
{

/**
 * @brief  Profet +2 (12V) shield with BTS700x-1EPP Arduino API
 */

class Bts700xShieldIno : public Bts700xShield
{
    public:
                        Bts700xShieldIno(BtxVariants_t *variantSel);
                        Bts700xShieldIno(BtxVariants_t *variantSel, Bts700xHwConfig_t config);
                        ~Bts700xShieldIno();
};

}

#endif /** HSS_SHIELD_BTS700X_INO_HPP_ **/