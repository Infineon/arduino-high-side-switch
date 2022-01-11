/**
 * @file        hss.cpp
 * @brief       High side switch class
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdint.h>
#include "hss.hpp"

using namespace hss;

/**
 * @brief   High-Side-Switch constructor
 * @param[in]   den         Diagnosis enable GPIO instance
 * @param[in]   in          Switch input GPIO instance
 * @param[in]   is          Diagnose current ADC instance
 * @param[in]   timer       Timer instance
 * @param[in]   btxVariant  BTx variant
 */
Hss::Hss(GPIOPAL *den, GPIOPAL *in, ADCPAL *is, TimerPAL *timer, BtxVariants_t *btxVariant)
{
    this->den = den;
    this->in0 = in;
    this->in1 = nullptr;
    this->is  = is;
    this->dsel = nullptr;

    this->timer = timer;

    this->btxVariant = btxVariant;

    currentFilter = new ExponentialFilter(0.0, 0.3);

    status = UNINITED;
    diagEnb = DIAG_DIS;
    diagStatus = NOT_ENABLED;
}

/**
 * @brief   High-Side-Switch constructor
 * @details This constructor is used to define all necessary pins
 *          of the 24V PROFET.
 * @param[in]   den         Diagnosis enable GPIO instance
 * @param[in]   in0         Switch input 0 GPIO instance
 * @param[in]   in1         Switch input 1 GPIO instance
 * @param[in]   dsel        Diagnosis select GPIO instance
 * @param[in]   is          Diagnose current ADC instance
 * @param[in]   timer       Timer instance
 * @param[in]   btxVariant  BTx variant
 */
Hss::Hss(GPIOPAL *den, GPIOPAL *in0, GPIOPAL *in1,  GPIOPAL *dsel, ADCPAL *is, TimerPAL *timer, BtxVariants_t *btxVariant)
{
    this->den = den;
    this->in0 = in0;
    this->in1 = in1;
    this->is = is;
    this->dsel = dsel;

    this->timer = timer;

    this->btxVariant = btxVariant;

     currentFilter = new ExponentialFilter(0.0, 0.3);

    status = UNINITED;
    diagEnb = DIAG_DIS;
    diagStatus = NOT_ENABLED;
}

/**
 * @brief Destructor of the High-Side-Switch class
 *
 */
Hss::~Hss()
{

}

/**
 * @brief   Initialize the High-Side-Switch
 * @details This function initializes all necessary objects of the High-Side-Switch.
 *          It retruns an error code to see if everything was initialized correctly.
 * @return High-side switch error code 
 */
Error_t Hss::init()
{
    Error_t err = OK;

    if(nullptr != den)
    {
        err = den->init();
        HSS_ASSERT_RET(err);
    }

    HSS_ASSERT_NULLPTR(in0);
    err = in0->init();
    HSS_ASSERT_RET(err);

    if(nullptr != in1)
    {
        err = in1->init();
        HSS_ASSERT_RET(err);
    }

    HSS_ASSERT_NULLPTR(is);
    err = is->init();
    HSS_ASSERT_RET(err);

    if(nullptr != dsel)
    {
        err = dsel->init();
        HSS_ASSERT_RET(err);
    }

    HSS_ASSERT_NULLPTR(timer);
    err = timer->init();
    HSS_ASSERT_RET(err);

    HSS_ASSERT_NULLPTR(btxVariant);

    status = INITED;
    statusCh0 = POWER_OFF;
    statusCh1 = POWER_OFF;

    return err;
}

/**
 * @brief Deinitialize the High-Side-Switch
 * @return High-side switch error code 
 */
Error_t Hss::deinit()
{
    Error_t err = OK;

    if(nullptr != den)
    {
        err = den->deinit();
        HSS_ASSERT_RET(err);
    }

    HSS_ASSERT_NULLPTR(in0);
    err = in0->deinit();
    HSS_ASSERT_RET(err);

    if(nullptr != in1)
    {
        err = in1->deinit();
        HSS_ASSERT_RET(err);
    }

    if(nullptr != dsel)
    {
        err = dsel->deinit();
        HSS_ASSERT_RET(err);
    }

    HSS_ASSERT_NULLPTR(is);
    err = is->deinit();
    HSS_ASSERT_RET(err);

    HSS_ASSERT_NULLPTR(timer);
    err = timer->deinit();
    HSS_ASSERT_RET(err);

    HSS_ASSERT_NULLPTR(btxVariant);

    status = UNINITED;
    statusCh0 = POWER_OFF;
    statusCh1 = POWER_OFF;

    return err;
}

/**
 * @brief    Enable the High-Side-Switch
 * @details  This function is turning on the High-Side-Switch.
 *           It is also setting the status of the switch to ON.
 * @param[in]   ch      Channel number. Default 0.
 * @return High-side switch error code 
 */
Error_t Hss::enable(Channel_t ch)
{
    Error_t err = OK;

    if(UNINITED != status)
    {
        if(CHANNEL0 == ch || ALL_CHANNELS == ch)
        {
            HSS_ASSERT_NULLPTR(in0);
            err = in0->enable();
            HSS_ASSERT_RET(err);
            statusCh0 = POWER_ON;
        }
        if(CHANNEL1 == ch || ALL_CHANNELS == ch)
        {
            HSS_ASSERT_NULLPTR(in1);
            err = in1->enable();
            HSS_ASSERT_RET(err);
            statusCh1 = POWER_ON;
        }

        status = POWER_ON;
    }
    else
    {
        err = INIT_ERROR;
    }

    return err;
}

/**
 * @brief   Disable the High-Side-Switch
 * @details This function turns off the High-Side-Switch.
 *          It is also setting the status of the switch to OFF.
 * @param[in]   ch      Channel number. Default 0.
 * @return High-side switch error code 
 */
Error_t Hss::disable(Channel_t ch)
{
    Error_t err = OK;

    if(UNINITED != status)
    {

        if(CHANNEL0 == ch || ALL_CHANNELS == ch)
        {
            HSS_ASSERT_NULLPTR(in0);
            err = in0->disable();
            HSS_ASSERT_RET(err);
            statusCh0 = POWER_OFF;
        }
        if(CHANNEL1 == ch || ALL_CHANNELS == ch)
        {
            HSS_ASSERT_NULLPTR(in1);
            err = in1->disable();
            HSS_ASSERT_RET(err);
            statusCh1 = POWER_OFF;
        }

        if((POWER_OFF == statusCh0) && (POWER_OFF == statusCh1))
        {
            status = POWER_OFF;
        }
    }
    else
    {
        err = INIT_ERROR;
    }

    return err;
}

/**
 * @brief   Enable diagnosis function
 * @details This function is enabling the diagnosis function of the High-Side-Switch.
 * @return High-side switch error code 
 */
Error_t Hss::enableDiag()
{
    Error_t err = OK;

    if((nullptr != den) && (UNINITED != status))
    {
        err = den->enable();
        HSS_ASSERT_RET(err);

        diagEnb = DIAG_EN;
    }
    else if(nullptr == den)
    {
        diagEnb = DIAG_EN;
    }
    else
    {
        err = INIT_ERROR;
    }

    return err;
}

/**
 * @brief   Disable diagnosis function
 * @details This function is disabling the diagnosis function of the High-Side-Switch
 * @return High-side switch error code 
 */
Error_t Hss::disableDiag()
{
    Error_t err = OK;

    if((nullptr != den) && (UNINITED != status))
    {
        err = den->disable();
        HSS_ASSERT_RET(err);

        diagEnb = DIAG_DIS;
    }
    else if(nullptr == den)
    {
        diagEnb = DIAG_EN;
    }
    else
    {
        err = INIT_ERROR;
    }

    return err;
}

/**
 * @brief   Selects diagnosis channel for diagnosis
 * @details This function is selecting the channel to perform diagnosis
 * @note    This function is accessed only if the shield is Profet24V
 * @param[in] ch    Channel number (in case of Profet 24V shield)
 * @return High-side switch error code 
 */
Error_t Hss::selDiagCh(Channel_t ch)
{
    Error_t err = OK;

    if(nullptr != dsel)
    {
        if(CHANNEL0 == ch)
        {
            err = dsel->disable();
        }
        else if(CHANNEL1 == ch){
            err = dsel->enable();
        }
        else
        {
            return INVALID_CH_ERROR;
        }
    }

    return err;
}

/**
 * @brief   Get the switch status
 * @details This function returns the current status of the switch.
 * @return  Status_t
 * @retval  0   Uninitialized
 * @retval  1   Initialized
 * @retval  2   Power on
 * @retval  3   Power off
 */
Status_t Hss::getSwitchStatus()
{
    return status;
}

/**
 * @brief   Read ADC value for IS
 * @details This functions is reading the IS signal of the switch.
 *          It returns the calculated current, which is depending on the IS signal.
 * @param[in]   rSense  Resistor value of the current sense resistor in [Ohm]
 * @param[in]   ch      Channel number
 * @note    Before calling this function, ensure IS pin is initialized and
 *          you do not have to pass channel in case your shield does not support multiple channel
 *          and this would default to CHANNEL0 applicable.
 * @return  Value of the current flowing through the switch in [A]
 */
float Hss::readIs(uint16_t rSense, Channel_t ch)
{
    uint16_t adcVal = 0;
    float isVoltage = 0.0;
    float isCurrent = 0.0;

    if(UNINITED != status)
    {
        selDiagCh(ch);

        timer->delayMilli(1);
        adcVal = is->ADCRead();
        isVoltage = (adcVal/1024.0)*5.0;
        isCurrent = ((isVoltage*btxVariant->kilis)/rSense) - currentOffset;
        currentFilter->input(isCurrent);
    }

    return currentFilter->output();
}

/**
 * @brief   Diagnosis of the Sensor
 * @details This function is using the IS signal to determine the state of the switch.
 *          It returns an diagnosis state of the switch.
 * @param[in]   senseCurrent    Sensed current value
 * @param[in]   ch              Channel no. Unused.
 * @return  DiagStatus_t
 *
 * @retval   0  Switch is working fine
 * @retval   1  Fault condition detected
 * @retval   2  Open Load in ON or Inverse Current
 * @note    This function should be called only after you get the Is value.
 *          Also note, in case you are using shield with no channel differentiation,
 *          then ignore the 'ch' parameter and this will default to CHANNEL0.
 */
DiagStatus_t Hss::diagRead(float senseCurrent, Channel_t ch)
{
    (void)ch;

    if(senseCurrent >= (btxVariant->iisFault * btxVariant->kilis)){
        diagStatus = FAULT;
    }
    else if((btxVariant->type == BTS700X) && (senseCurrent <= (btxVariant->iisEn * btxVariant->kilis))){
            diagStatus = FAULT_OL_IC;
    }
    else if((btxVariant->type == BTS5001X) && (senseCurrent <= (btxVariant->iisO * btxVariant->kilis))){
            diagStatus = FAULT_OL_IC;
    }
    else if((btxVariant->type == BTT60X0) && (senseCurrent <= (btxVariant->iisOl * btxVariant->kilis))){
            diagStatus = FAULT_OL_IC;
    }
    else{
        diagStatus = NORMAL;
    }

    return diagStatus;
}

/**
 * @brief   Set current offset
 * @details This function can be used to change the value of the internal variable
 *          of the current offset
 * @param[in]   offset  Desired value of the current offset in [A]
 */
void Hss::setCurrentOffset(float offset)
{
    currentOffset = offset;
}