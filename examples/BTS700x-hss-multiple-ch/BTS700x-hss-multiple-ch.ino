/**
 * @file        BTS700x-hss-multiple-ch.ino
 * @brief       High-Side-Switch Multiple Channel Operation Example for the BTS700x Arduino form factored shields
 * @details     This example demonstrates how to switch on/off multiple channels at once.
 *              Below are the valid chip variants for SHIELD_BTS700x-1EPP having 4 channels:
 *                  - BTS7002
 *                  - BTS7004
 *                  - BTS7006
 *                  - BTS7008
 *
 *              It can be deployed to the Arduino Uno or the XMC's with corresponding form factor.
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 */

#include <hss-shield-bts700x-ino.hpp>

using namespace hss;

/** Creation the hss board object */
/** The user needs to specify the BTS700x variant in the constructor argument */
Bts700xShieldIno HSS = Bts700xShieldIno(&BTS7002);

/** Select channels to be used in parallel (index 0 being channel 1) */
bool switch_no[4] = {true,true,true,true};

Error_t err = OK;

void setup()
{
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /** Initialization of the High-Side-Switch-Board */
    err = HSS.init();
    if(OK!=err)
    {
        Serial.println("Initialization failed!");
    }
    else
        Serial.println("Initialization successful!");

    delay(1000);
}

void loop()
{
    /** Turn on the selected channels */
    Serial.println("\nTurning on all switches at once!");
    HSS.switchesHxOn(switch_no[0],switch_no[1],switch_no[2],switch_no[3]);

    /** Keep them ON for a second */
    delay(1000);

    /** Turn off the selected channels */
    Serial.println("Turning off all switches at once!");
    HSS.switchesHxOff(switch_no[0],switch_no[1],switch_no[2],switch_no[3]);

    /** Keep them OFF for 5 second */
    delay(5000);
}