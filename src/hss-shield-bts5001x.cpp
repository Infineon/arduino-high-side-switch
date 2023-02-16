/**
 * @file        hss-shield-bts5001x.cpp
 * @brief       Power Profet (12V) shield with BTS500xx class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-bts5001x.hpp"

using namespace hss;

/**
 * @brief       High-Side-Switch-Board constructor
 * @details     Initialize all protected class pointers with a null pointer.
 * @param[in]   hsw1   High-side switch 1 instance
 * @param[in]   led2   LED 2 instance
 * @param[in]   led3   LED 3 instance
 * @param[in]   pushButton Push button ADC instance
 * @param[in]   vBat    Battery voltage ADC instance
 */
Bts5001xShield::Bts5001xShield(Hss * hsw1, GPIOPAL * led2, GPIOPAL * led3, ADCPAL * pushButton, ADCPAL * vBat)
:
hss1(hsw1),
led2(led2),
led3(led3),
pushButton(pushButton),
vBat(vBat)
{

}

/**
 * @brief Destructor of the High-Side-Switch-Board
 *
 */
Bts5001xShield::~Bts5001xShield()
{

}

/**
 * @brief Initialize all necessary objects of the High-Side-Switch-Board
 *
 * This function initializes all necessary objects of the High-Side-Switch-Board.
 * It returns an error code to see if everything was initialized correctly.
 *
 * @return hss::Error_t
 */
Error_t Bts5001xShield::init()
{
    Error_t err = OK;

    HSS_ASSERT_NULLPTR(hss1);
    err = hss1->init();
    HSS_ASSERT_RET(err);

    if(nullptr != led2)
    {
        err = led2->init();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != led3)
    {
        err = led3->init();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != pushButton)
    {
        err = pushButton->init();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != vBat)
    {
        err = vBat->init();
        HSS_ASSERT_RET(err);
    }

    filterVbat = new ExponentialFilter(0.0, 0.4);

    return OK;
}

/**
 * @brief Deinitialize all necessary objects of the High-Side-Switch-Board
 *
 * This function deinitializes all necessary objects of the High-Side-Switch-Board.
 * It returns an error code to see if everything was deinitialized correctly.
 *
 * @return High-side switch error code
 */
Error_t Bts5001xShield::deinit()
{
    Error_t err= OK;

    HSS_ASSERT_NULLPTR(hss1);
    err = hss1->deinit();
    HSS_ASSERT_RET(err);

    if(nullptr != led2)
    {
        err = led2->deinit();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != led3)
    {
        err = led3->deinit();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != pushButton)
    {
        err = pushButton->deinit();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != vBat)
    {
        err = vBat->deinit();
        HSS_ASSERT_RET(err);
    }

    return OK;
}

/**
 * @brief       Switch on the selected High-Side-Switch
 * @details     This function turns on the desired High-Side-Switch.
 *              It also turns on the corresponding LED of the switch.
 * @param[in]   x   Number of the Switch the should be turned on (1-4)
 * @return      High-side switch error code
 */
Error_t Bts5001xShield::switchHxOn(uint8_t x)
{
    (void)x;  /** Unused argument */

    Error_t err= OK;

    err = hss1->enable();
    HSS_ASSERT_RET(err);

    if (nullptr != led2)
    {
        err = led2->enable();
        HSS_ASSERT_RET(err);
    }

    return err;
}

/**
 * @brief       Switch off the selected High-Side-Switch
 * @details     This function turns off the desired High-Side-Switch.
 *              It also turns off the corresponding LED of the switch.
 * @param[in]   x   Number of the Switch the should be turned off (1-4)
 * @return      High-side switch error code
 */
Error_t Bts5001xShield::switchHxOff(uint8_t x)
{
    (void)x;  /** Unused argument */

    Error_t err= OK;

    err = hss1->disable();
    HSS_ASSERT_RET(err);

    if (nullptr != led2)
    {
        err = led2->disable();
        HSS_ASSERT_RET(err);
    }

    return err;
}


/**
 * @brief       Read the desired current value of the chosen channel
 * @details     This function reads the IS pin of the chosen High-Side-Switch
 *              and calculates the current which is flowing through the switch
 *              with the acquired ADC value.
 * @param[in]   x   Number of the desired channel (1)
 * @return      The value of the current in [A]
 */
float Bts5001xShield::readIsx(uint8_t x)
{
    (void)x;  /** Unused argument */

    float isVal;

    isVal = hss1->readIs(rSense);

    return isVal;
}

/**
 * @brief       Read the diagnosis of the chosen channel
 * @details     This function uses the current signal of the channel to diagnose the channel.
 *              It returns the different states depending on the channels condition.
 * @param[in]   x   Desired channel for the diagnosis (1)
 * @return      DiagStatus_t
 *
 * @retval  -2  Not enabled
 * @retval  0   Switch is working fine
 * @retval  2   Short circuit to ground
 * @retval  4   Short circuit to Vs
 * @retval  5   Open load detected
 */
DiagStatus_t Bts5001xShield::readDiagx(uint8_t x)
{
    (void)x;  /** Unused argument */

    DiagStatus_t diagStatus = NORMAL;
    float currentOn = 0.0;

    if(hss1->getSwitchStatus() == POWER_ON)
    {
        currentOn = hss1->readIs(rSense);
        diagStatus = hss1->diagRead(currentOn);
    }

    return diagStatus;
}


/**
 * @brief    Reads the batter voltage
 * @details  This functions is reading the attached voltage at the Profet-Board.
 * @return   Value of the battery voltage in [V]
 */
float Bts5001xShield::readVss()
{
    uint16_t adcResult = 0;
    float voltage = 0.0;

    adcResult = vBat->ADCRead();
    voltage = adcResult * ((float)5/(float)1024);   // Vmax/1024 LSB = Resolution of the ADC,
    voltage = (voltage - vBatOffset);
    voltage = voltage * ((float)57/(float)10);      // 57/10 = Reverse Voltage divider to get the supply voltage

    filterVbat->input(voltage);

    return filterVbat->output();
}

/**
 * @brief  Read the button state (analog)
 * @return bool
 * @retval true  If button is pressed
 * @retval false If button is not pressed
 */
bool Bts5001xShield::analogReadButton()
{
    uint16_t result = 0;

    result = pushButton->ADCRead();
    if(result < 20){
        return true;
    }
    else{
        return false;
    }
}

/**
 * @brief       Set battery voltage offset
 * @details     This function can be used to change the value of the internal variable
 *              of the battery voltage offset
 * @param[in]   offset  Desired value of the offset in [V]
 */
void Bts5001xShield::setVoltageOffset(float offset)
{
    vBatOffset = offset;
}
