/**
 * @file hss-shield-bth500xx.cpp
 * @brief Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield class
 * @copyright Copyright (c) 2023 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "hss-shield-bth500xx.hpp"
#include <math.h>

using namespace hss;

/**
 * @brief       Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield constructor
 * @param[in]   sw1: High-Side-Switch instance 1
 * @param[in]   sw2: High-Side-Switch instance 2
 * @param[in]   vs: ADC instance to measure the supply voltage
 * @param[in]   vOut: ADC instance to measure the output voltage of the first switch
 * @param[in]   temp: ADC instance to measure the temperature
 * @param[in]   btxVariant1: Structure with sensor specific parameters of switch 1
 * @param[in]   btxVariant2: Structure with sensor specific parameters of switch 2
 */
Bth500xxShield::Bth500xxShield(Hss* sw1, Hss* sw2, ADCPAL* vs, ADCPAL* vOut, ADCPAL* temp, BtxVariants_t* btxVariant1, BtxVariants_t* btxVariant2) 
:
switches{sw1, sw2},
vs(vs),
vOut(vOut),
temp(temp),
btxVariant1(btxVariant1),
btxVariant2(btxVariant2) {

}

/**
 * @brief Power PROFET™ + 24V /48V BTH50015-1LUA Smart High-Side Power Switch Shield destructor
 */
Bth500xxShield::~Bth500xxShield() {

}

/**
 * @brief   Initialize all necessary objects of the High-Side-Switch-Board
 * @details This function initializes all necessary objects of the High-Side-Switch-Board.
 *          It returns an error code to see if everything was initialized correctly.
 * @return  Error_t 
 */
Error_t Bth500xxShield::init() {
    Error_t err = OK;

    HSS_ASSERT_NULLPTR(btxVariant1);
    HSS_ASSERT_NULLPTR(btxVariant2);

    for (uint8_t i = 0; i < hssNum; i++) {
        HSS_ASSERT_NULLPTR(switches[i]);
        err = switches[i]->init();
        HSS_ASSERT_RET(err);
    }

    if (nullptr != vs) {
        err = vs->init();
        HSS_ASSERT_RET(err);
    }

    if (nullptr != vOut) {
        err = vOut->init();
        HSS_ASSERT_RET(err);
    }

    if (nullptr != temp) {
        err = temp->init();
        HSS_ASSERT_RET(err);
    }

    filterVs = new ExponentialFilter(0.0, 0.4);
    filterVOut = new ExponentialFilter(0.0, 0.4);
    filterTemp = new ExponentialFilter(0.0, 0.4);

    return err;
}

/**
 * @brief   Deinitialize all necessary objects of the High-Side-Switch-Board
 * @details This function de-initializes all necessary objects of the High-Side-Switch-Board.
 *          It returns an error code to see if everything was de-initialized correctly. 
 * @return  Error_t 
 */
Error_t Bth500xxShield::deinit() {
    Error_t err = OK;

    for (uint8_t i = 0; i < hssNum; i++) {
        HSS_ASSERT_NULLPTR(switches[i]);
        err = switches[i]->deinit();
        HSS_ASSERT_RET(err);
    }

    if (nullptr != vs) {
        err = vs->deinit();
        HSS_ASSERT_RET(err);
    }

    if (nullptr != vOut) {
        err = vOut->deinit();
        HSS_ASSERT_RET(err);
    }

    if (nullptr != temp) {
        err = temp->deinit();
        HSS_ASSERT_RET(err);
    }

    return err;
}

/**
 * @brief       Switch on the selected High-Side-Switch
 * @details     This function turns on the desired High-Side-Switch.
 * @param[in]   x: Number of the Switch the should be turned on (1-2).
 *              Can be either SWITCH1 or SWITCH2.
 * @return      Error_t
 */
Error_t Bth500xxShield::switchHxOn(uint8_t x) {
    Error_t err = OK;

    switch (x) {
        case 1:
            err = switches[0]->enable();
            HSS_ASSERT_RET(err);
            break;

        case 2:
            err = switches[1]->enable();
            HSS_ASSERT_RET(err);
            break;

        default:
            err = INVALID_CH_ERROR;
    }

    return err;
}

Error_t Bth500xxShield::switchHxOff(uint8_t x) {
    Error_t err = OK;

    switch (x) {
        case 1:
            err = switches[0]->disable();
            HSS_ASSERT_RET(err);
            break;

        case 2:
            err = switches[1]->disable();
            HSS_ASSERT_RET(err);
            break;

        default:
            err = INVALID_CH_ERROR;
    }

    return err;
}

/**
 * @brief       Read the diagnosis ouput of the chosen switch
 * @details     This function uses the current signal of the chosen switch to diagnose the switch.
 *              It returns the different states depending on the switch's condition.
 * @param[in]   x: Desired Switch for the diagnosis (1-2)
 *              Can be either SWITCH1 or SWITCH2.
 * @return      DiagStatus_t
 *
 * @retval      -1 Diagnosis read error (chosen channel not valid)
 * @retval      0 Switch is working fine
 * @retval      2 Short circuit to ground
 * @retval      4 Short circuit to Vs
 * @retval      5 Open load detected
 */
DiagStatus_t Bth500xxShield::readDiagx(uint8_t x) {
    DiagStatus_t diagStatus = NORMAL;
    float senseCurrent = 0.0;
    float supplyVoltage = 0.0;
    float outputVoltage = 0.0;

    switch (x) {
        case 1:
            switches[0]->enableDiag();
            senseCurrent = switches[0]->readIs(2000) / btxVariant1->kilis;
            supplyVoltage = readVs();
            outputVoltage = readVOut();
            if(POWER_OFF == switches[0]->getSwitchStatus())
            {
                if(senseCurrent >= btxVariant1->iisFault)
                {
                    if(supplyVoltage == outputVoltage)
                    {
                        diagStatus = SHORT_TO_VSS;
                    }
                    else
                    {
                        diagStatus = OPEN_LOAD;
                    }
                }
            }
            else
            {
                if(senseCurrent >= btxVariant1->iisFault)
                {
                        diagStatus = SHORT_TO_GND_OR_OT;
                }
                else if(((senseCurrent <= 0.0000160) && (senseCurrent > 0.000001)) || (senseCurrent <= 0.000001))
                {
                    diagStatus = OPEN_LOAD;
                }
                else if((outputVoltage <= supplyVoltage) && (senseCurrent > 0.0000160))
                {
                    diagStatus = NORMAL;
                }
            }
            break;

        case 2:
            switches[1]->enableDiag();
            senseCurrent = switches[1]->readIs(2000) / btxVariant2->kilis;
            if(POWER_OFF == switches[1]->getSwitchStatus())
            {
                if(senseCurrent >= btxVariant2->iisFault)
                {
                   diagStatus = FAULT;
                }
            }
            else
            {
                if(senseCurrent >= btxVariant2->iisFault)
                {
                        diagStatus = SHORT_TO_GND_OR_OT;
                }
                else if(((senseCurrent <= 0.00000125) && (senseCurrent > 0.000001)) || (senseCurrent <= 0.000001))
                {
                    diagStatus = OPEN_LOAD;
                }
            }
            break;

        default:
            diagStatus = DIAG_READ_ERROR;
    }

    return diagStatus;
}

/**
 * @brief       Read the desired current value of the chosen switch
 * @details     This function reads the IS pin of the chosen High-Side-Switch
 *              and calculates the current which is flowing through the switch
 *              with the acquired ADC value.
 * @param[in]   x: Number of the desired switch (1-2)
 * @return      The value of the current in [A]
 * @retval      -1.2345 Invalid channel was chosen
 */
float Bth500xxShield::readIsx(uint8_t x) {
    float isCurrent = 0.0;

    switch (x) {
        case 1:
            switches[0]->enableDiag();
            isCurrent = switches[0]->readIs(2000);
            switches[0]->disableDiag();
            break;

        case 2:
            switches[1]->enableDiag();
            isCurrent = switches[1]->readIs(2000);
            switches[1]->disableDiag();
            break;

        default:
            isCurrent = -1.2345;    /* Invalid channel indicator */
    }

    return isCurrent;
}

/**
 * @brief       Switches on High-Side-Switches
 * @details     This function can switch on several High-Side-Switches at once.
 *              But is also possible two only switch on the first or second one.
 * @param[in]   h1: Bool value for the first switch.*true* means turn on, *false* means keep it as is.
 * @param[in]   h2: Bool value for the second switch.*true* means turn on, *false* means keep it as is.
 * @return      Error_t
 */
Error_t Bth500xxShield::switchesHxOn(bool h1, bool h2) {
    Error_t err = OK;

    if (true == h1) {
        err = switches[0]->enable();
        HSS_ASSERT_RET(err);
    }

    if (true == h2) {
        err = switches[1]->enable();
        HSS_ASSERT_RET(err);
    }

    return err;
}

/**
 * @brief       Switches off High-Side-Switches
 * @details     This function can switch off several High-Side-Switches at once.
 *              But is also possible two only switch off the first or second one.
 * @param[in]   h1: Bool value for the first switch.*true* means turn off, *false* means keep it as is.
 * @param[in]   h2: Bool value for the second switch.*true* means turn off, *false* means keep it as is.
 * @return      Error_t
 */
Error_t Bth500xxShield::switchesHxOff(bool h1, bool h2) {
    Error_t err = OK;

    if (true == h1) {
        err = switches[0]->disable();
        HSS_ASSERT_RET(err);
    }

    if (true == h2) {
        err = switches[1]->disable();
        HSS_ASSERT_RET(err);
    }

    return err;
}

/**
 * @brief   Read the supply voltage
 * @details This function is reading the supply voltage of the High-Side-Switch-Board.
 * @return  Value of the supply voltage in [V]
 */
float Bth500xxShield::readVs() {
    float supVol = 0.0;

    supVol = vs->ADCRead() * (5.0/1024.0) * ((5620.0 + 100000.0)/5620.0);
    filterVs->input(supVol);

    return filterVs->output(); 
}

/**
 * @brief   Read the output voltage
 * @details This function is reading the output voltage of High-Side-Switch one
 * @return  Value of the output voltage in [V]
 */
float Bth500xxShield::readVOut() {
    float outVol = 0.0;

    outVol = vOut->ADCRead() * (5.0/1024.0) * ((5620.0 + 100000.0) / 5620.0);
    filterVOut->input(outVol);

    return filterVOut->output();
}

/**
 * @brief   Read the PCB temperature
 * @details This function is reading the temperature of the High-Side-Switch-Board PCB.
 *          If the functions is returning -35.43 °C the NTC is not populated on the PCB and
 *          the temp-object was not passed to the constructor.
 * @return  Value of the temperature in [°C]
 */
float Bth500xxShield::readTemperature() {
    float temperature = 0.0;
    float adcMeas = 0.0;
    float resisNTC = 0.0;

    if(nullptr != temp) {
    adcMeas = temp->ADCRead() * (5.0/1024.0);
    resisNTC = (75.0 * (readVs()/adcMeas)) - 75.0;
    temperature = (1.0/298.15) + ((1.0/3380.0) * log(resisNTC/10000.0));
    temperature = (1.0/temperature) - 273.15;

    filterTemp->input(temperature);

    return filterTemp->output();
    }

    else {
        return -35.43;
    }
}