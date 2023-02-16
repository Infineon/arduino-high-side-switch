/**
 * @file        hss-shield-btt60xx.cpp
 * @brief       Profet (24V) shield with BTT6030-2EKA and BTT6020-1EKA class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-btt60xx.hpp"

using namespace hss;

/**
 * @brief       Profet 24V BTT60xx Shield constructor
 * @param[in]   hsw0   High-side switch 0 instance
 * @param[in]   hsw1   High-side switch 1 instance
 * @param[in]   hsw2   High-side switch 2 instance
 */
Btt60xxShield::Btt60xxShield(Hss *hsw0, Hss *hsw1, Hss *hsw2)
{
    switches[0] = hsw0;
    switches[1] = hsw1;
    switches[2] = hsw2;
}

/**
 * @brief   Destructor of the Profet 24V Shield
 *
 */
Btt60xxShield::~Btt60xxShield()
{

}

/**
 * @brief   Initialize all necessary objects of the Profet 24V Shield
 * @details This function initializes all necessary objects of the Profet 24V Shield.
 *          It returns an error code to see if everything was initialized correctly.
 * @return High-side switch error code
 */
Error_t Btt60xxShield::init()
{
    Error_t err = OK;

    for(uint8_t i = 0; i < hssNum; i++)
    {
        HSS_ASSERT_NULLPTR(switches[i]);
        err = switches[i]->init();
        HSS_ASSERT_RET(err);
    }

    return err;
}

/**
 * @brief   Deinitialize all necessary objects of the Profet 24V Shield
 *
 * This function deinitializes all necessary objects of the Profet 24V Shield.
 * It returns an error code to see if everything was deinitialized correctly.
 *
 * @return High-side switch error code
 */
Error_t Btt60xxShield::deinit()
{
    Error_t err = OK;

    for(uint8_t i = 0; i < hssNum; i++)
    {
        HSS_ASSERT_NULLPTR(switches[i]);
        err = switches[i]->deinit();
        HSS_ASSERT_RET(err);
    }

    return err;
}

/**
 * @brief    Switch on the selected High-Side-Switch
 * @details  This function turns on the desired High-Side-Switch.
 * @param[in]   x    Number of the Switch the should be turned on (0-4). Possible values: \n
 *                    Switch 0    -   Profet 0 (BTT6030 - channel 0) \n
 *                    Switch 1    -   Profet 0 (BTT6030 - channel 1) \n
 *                    Switch 2    -   Profet 1 (BTT6030 - channel 0) \n
 *                    Switch 3    -   Profet 1 (BTT6030 - channel 1) \n
 *                    Switch 4    -   Profet 2 (Single channel)
 * @return High-side switch error code
 */
Error_t Btt60xxShield::switchHxOn(uint8_t x)
{
    Error_t err = OK;

    Channel_t ch = (Channel_t)(x % 2);
    uint8_t hss  = x/2;
    HSS_ASSERT_NULLPTR(switches[hss]);
    err = switches[hss]->enable(ch);

    return err;
}

/**
 * @brief   Switch off the selected High-Side-Switch
 * @details This function turns off the desired High-Side-Switch.
 * @param[in]   x    Number of the Switch the should be turned on (0-4). Possible values: \n
 *                    Switch 0    -   Profet 0 (BTT6030 - channel 0) \n
 *                    Switch 1    -   Profet 0 (BTT6030 - channel 1) \n
 *                    Switch 2    -   Profet 1 (BTT6030 - channel 0) \n
 *                    Switch 3    -   Profet 1 (BTT6030 - channel 1) \n
 *                    Switch 4    -   Profet 2 (Single channel)
 * @return High-side switch error code
 */
Error_t Btt60xxShield::switchHxOff(uint8_t x)
{
    Error_t err = OK;

    Channel_t ch = (Channel_t)(x % 2);
    uint8_t hss  = x/2;
    HSS_ASSERT_NULLPTR(switches[x]);
    err = switches[hss]->disable(ch);

    return err;
}

/**
 * @brief     Turn on the selected High-Side-Switches
 * @details   This function is used to enable multiple switches at once.
 * @param[in] h0_0    Enable the Switch 0 - channel 0 if h0_0 = true
 * @param[in] h1_0    Enable the Switch 0 - channel 1 if h1_0 = true
 * @param[in] h0_1    Enable the Switch 1 - channel 0 if h0_1 = true
 * @param[in] h1_1    Enable the Switch 1 - channel 1 if h1_1 = true
 * @param[in] h2      Enable the Switch 2 - channel 0 if h2   = true
 * @return High-side switch error code
 */
Error_t Btt60xxShield::switchesHxOn(bool h0_0, bool h1_0, bool h0_1, bool h1_1, bool h2)
{
    Error_t err = OK;

    if(h0_0 == true){
        HSS_ASSERT_NULLPTR(switches[0]);
        err = switches[0]->enable();
        HSS_ASSERT_RET(err);
    }

    if(h1_0 == true){
        HSS_ASSERT_NULLPTR(switches[0]);
        err = switches[0]->enable(CHANNEL1);
        HSS_ASSERT_RET(err);
    }

    if(h0_1 == true){
        HSS_ASSERT_NULLPTR(switches[1]);
        err = switches[1]->enable();
        HSS_ASSERT_RET(err);
    }

    if(h1_1 == true){
        HSS_ASSERT_NULLPTR(switches[1]);
        err = switches[1]->enable(CHANNEL1);
        HSS_ASSERT_RET(err);
    }

    if(h2 == true){
        HSS_ASSERT_NULLPTR(switches[2]);
        err = switches[2]->enable();
        HSS_ASSERT_RET(err);
    }
    return err;
}

/**
 * @brief     Turn off the selected High-Side-Switches
 * @details   This function is used to disable multiple switches at once.
 * @param[in] h0_0    Disable the Switch 0 - channel 0 if h0_0 = true
 * @param[in] h1_0    Disable the Switch 0 - channel 1 if h1_0 = true
 * @param[in] h0_1    Disable the Switch 1 - channel 0 if h0_1 = true
 * @param[in] h1_1    Disable the Switch 1 - channel 1 if h1_1 = true
 * @param[in] h2      Disable the Switch 2 - channel 0 if h2   = true
 * @return High-side switch error code
 */
Error_t Btt60xxShield::switchesHxOff(bool h0_0, bool h1_0, bool h0_1, bool h1_1, bool h2)
{
    Error_t err = OK;

    if(h0_0 == true){
        HSS_ASSERT_NULLPTR(switches[0]);
        err = switches[0]->disable();
        HSS_ASSERT_RET(err);
    }

    if(h1_0 == true){
        HSS_ASSERT_NULLPTR(switches[0]);
        err = switches[0]->disable(CHANNEL1);
        HSS_ASSERT_RET(err);
    }

    if(h0_1 == true){
        HSS_ASSERT_NULLPTR(switches[1]);
        err = switches[1]->disable();
        HSS_ASSERT_RET(err);
    }

    if(h1_1 == true){
        HSS_ASSERT_NULLPTR(switches[1]);
        err = switches[1]->disable(CHANNEL1);
        HSS_ASSERT_RET(err);
    }

    if(h2 == true){
        HSS_ASSERT_NULLPTR(switches[2]);
        err = switches[2]->disable();
        HSS_ASSERT_RET(err);
    }
    return err;
}

/**
 * @brief   Read the desired current value of the chosen channel
 * @details This function: \n
 *          - Enables diagnosis for the channel \n
 *          - Selects the channel through dsel \n
 *          - Calls function to get the calibrated sensed current value on chosen channel \n
 *          - Disables diagnosis pin post operation completion \n
 * @param[in]   x    Number of the Switch the should be turned on (0-4). Possible values: \n
 *                    Switch 0    -   Profet 0 (BTT6030 - channel 0) \n
 *                    Switch 1    -   Profet 0 (BTT6030 - channel 1) \n
 *                    Switch 2    -   Profet 1 (BTT6030 - channel 0) \n
 *                    Switch 3    -   Profet 1 (BTT6030 - channel 1) \n
 *                    Switch 4    -   Profet 2 (Single channel)
 * @return  The calibrated value of the current in [A]
 */
float Btt60xxShield::readIsx(uint8_t x)
{
    float iisCalib;
    uint8_t hss = x/2;
    Channel_t ch = Channel_t(x % 2);

    HSS_ASSERT_NULLPTR(switches[hss]);
    switches[hss]->enableDiag();
    iisCalib = switches[hss]->readIs(rSense, ch);
    switches[hss]->disableDiag();

    return iisCalib;
}

/**
 * @brief    Read the diagnosis of the chosen channel
 * @details  This function uses the current signal of the channel to diagnose perform diagnosis.
 *           It returns the different states depending on the channels condition.
 * @param[in]   x    Number of the Switch the should be turned on (0-4). Possible values: \n
 *                    Switch 0    -   Profet 0 (BTT6030 - channel 0) \n
 *                    Switch 1    -   Profet 0 (BTT6030 - channel 1) \n
 *                    Switch 2    -   Profet 1 (BTT6030 - channel 0) \n
 *                    Switch 3    -   Profet 1 (BTT6030 - channel 1) \n
 *                    Switch 4    -   Profet 2 (Single channel)
 * @return      DiagStatus_t
 * @retval      0   Everything works correctly
 * @retval      2   Short to ground
 * @retval      4   Short to battery
 * @retval      5   Open load
 */
DiagStatus_t Btt60xxShield::readDiagx(uint8_t x)
{
    DiagStatus_t diagStatus = NORMAL;
    float currentOn = 0.0;

    uint8_t hss  = x/2;

    switches[hss]->enableDiag();
    if(switches[hss]->getSwitchStatus() == POWER_ON){
        currentOn = readIsx(x);
        diagStatus = switches[hss]->diagRead(currentOn);
    }
    switches[hss]->disableDiag();

    return diagStatus;
}