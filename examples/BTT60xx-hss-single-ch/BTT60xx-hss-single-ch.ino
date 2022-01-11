/**
 * @file        BTT600x-hss-single-ch.ino
 * @brief       High-Side-Switch Basic Example for the BTT600x Arduino form factored shields
 * @details     This example demonstrates how to switch on/off single channel in the BTT shield. It also
 *              calls API to read the current value.
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

/** Set channel to operate
 * switch_no    Controls
 *     0         OUT0.0
 *     1         OUT0.1
 *     2         OUT1.0
 *     3         OUT1.1
 *     4         OUT 2
 */
int switch_no = 0;

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
        Serial.println("Initialization successful!\n");

    delay(1000);
}

void loop()
{
    /** Turn on the selected channel */
    Serial.println("\nTurning on selected switch...");
    HSS.switchHxOn(switch_no);

   /** Wait for a second before reading diagnose current */
    delay(1000);

    /** Read current value */
    readCurrent();

    /** Keep all switches on for a second */
    delay(1000);

    /** Turn off the selected channel */
    Serial.println("Turning off the selected switch");
    HSS.switchHxOff(switch_no);

    /** Keep all switches off for a second */
    delay(5000);
}

/**
 * @brief       Read current flowing through the switch
 */
void readCurrent()
{
    float readAmps = 0.0;
    for(int i = 0; i<10; i++){                              // Measure more than once to make use of the internal exponential filter
        readAmps = HSS.readIsx(switch_no);
    }
    Serial.print("Current flowing through the switch: ");
    Serial.print(readAmps);
    Serial.println(" A");
    return;
}