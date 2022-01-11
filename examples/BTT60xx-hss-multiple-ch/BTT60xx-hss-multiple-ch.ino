/**
 * @file        BTT600x-hss-multiple-ch.ino
 * @brief       High-Side-Switch Multiple Channel Operation Example for the BTT600x Arduino form factored shields
 * @details     This example demonstrates how to switch on/off multiple channels at once.
 *
 *              Find below the Profet 24V shield part details and its offered channels:
 *              _________________________________________________________________________________
 *                  Shield Name            Included parts          Supported number of channels
 *              _________________________________________________________________________________
 *               24V_SHIELD_BTT6030    Profet 0 (BTT6030-2ERA)                2
 *                                     Profet 1 (BTT6030-2ERA)                2
 *                                     Profet 2 (BTT6020-1ERA)                1
 *              _________________________________________________________________________________
 *
 *              It can be deployed to the Arduino Uno or the XMC's with corresponding form factor.
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 */

#include <hss-shield-btt60xx-ino.hpp>

using namespace hss;

Btt60xxShieldIno HSS = Btt60xxShieldIno();

Error_t err = OK;

/** Select channels to be used parallelly (index 0 being channel 1)
 *   switch_no              Controls
 *  switch_no[0] = true      OUT0.0
 *  switch_no[1] = true      OUT0.1
 *  switch_no[2] = true      OUT1.0
 *  switch_no[3] = true      OUT1.1
 *  switch_no[4] = true      OUT2
*/
bool switch_no[5] = {true,true,true,true,true};

void setup()
{
    /** Serial initialization */
    Serial.begin(115200);
    Serial.println("Serial initialized");

    /** Initialization of the High-Side-Switch-Board */
    err = HSS.init();
    if(OK!=err)
    {
        Serial.println("Initialization failed!");
    }
    else
        Serial.println("Initialization successful!\n");

    delay(1000);
}

void loop()
{
    /** Turn on the selected channels */
    Serial.println("\nTurning on all switches at once!");
    HSS.switchesHxOn(switch_no[0], switch_no[1], switch_no[2], switch_no[3], switch_no[4]);

    /** Keep all switches on for a second */
    delay(1000);

    /** Turn on the selected channels */
    Serial.println("\nTurning off all switches at once!");
    HSS.switchesHxOff(switch_no[0],switch_no[1],switch_no[2],switch_no[3], switch_no[4]);

    /** Keep all switches off for a second */
    delay(5000);
}