/**
 * @file        BTS700x-hss-single-ch.ino
 * @brief       High-Side-Switch Basic Example for the BTS700x Arduino form factored shields
 * @details     This example demonstrates how to switch on/off single channel in the BTT shield. It also
 *              calls API to read the current value.
 *
 *              You can configure following variants for this shield:
 *              - BTS7002
 *              - BTS7004
 *              - BTS7006
 *              - BTS7008
 *              It can be deployed to the Arduino Uno or the XMC's with corresponding form factor.
 *
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 */


#include <hss-shield-bts700x-ino.hpp>

using namespace hss;

/** Creation the hss board object */
/** The user needs to specify the BTS700x variant in the constructor argument */
Bts700xShieldIno HSS = Bts700xShieldIno(&BTS7002);

Error_t err = OK;

/** Set switch to operate */
int switch_no = 1;

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
    for(int i = 0; i<10; i++){
        readAmps = HSS.readIsx(switch_no);                  // Measure more than once to make use of the internal exponential filter
    }
    Serial.print("Current flowing through the switch: ");
    Serial.print(readAmps);
    Serial.println(" A");
    return;
}