/**
 * @file        hss-shield-platf.cpp
 * @brief       Hardware platform predefined Arduino configurations
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-platf.hpp"

namespace hss
{

#if (defined(XMC1100_Boot_Kit) || defined(ARDUINO_AVR_UNO))

#include <Arduino.h>

/**
 * @brief BTS700x Shield Arduino Uno Pin Configuration
 */
Bts700xHwConfig_t BTS700X_HWCONFIG = 
{
    .led1 = 4,                      
    .led2 = 5,                      
    .led3 = 12,                     
    .led4 = 13,                     

    .in1 = 9,                       
    .in2 = 10,                      
    .in3 = 11,                      
    .in4 = 3,                       

    .oloff = 7,                     

    .den1_den3 = 6,                 
    .den2_den4 = 8,                 

    .pushButtonDigital = 2,         

    .pushButtonAnalog = A0,         
    .vBat =             A1,         
    .is1_is2 =          A2,         
    .is3_is4 =          A3          
};

/**
 * @brief BTS5001x Shield Arduino Uno Pin Configuration 
 */
BTS5001xHwConfig_t BTS5001X_HWCONFIG = 
{
    .led2 = 9,                      
    .led3 = 5,                      

    .in = 6,                        

    .pushButtonAnalog = A0,         
    .vBat = A5,                     
    .is = A2,                       

};

/**
 * @brief BTT60xx Shield Arduino Uno Pin Configuration 
 */
Btt60xxHwConfig_t BTT60XX_HWCONFIG = 
{
    ///Profet0 - BTT6030 (2 channel) pin config
    .in0_0  = A3,
    .den_0  = A4,
    .dsel_0 = 2,
    .in1_0  = 3,
    .is_0   = A0,

    ///Profet1 - BTT6030 (2 channel) pin config
    .in0_1  = 4,
    .den_1  = 5,
    .dsel_1 = 6,
    .in1_1  = 7,
    .is_1   = A1,

    ///Profet2 - BTT6020 (1 channel) pin config
    .in0_2  = 8,
    .den_2  = 9,
    .is_2   = A2,
};

#else

#error "You did not define a supported platform! \
Please make sure you're defining a custom default platform \
in hss-shield-platf.cpp, or use the non-default shield \
constructor."

#endif

}