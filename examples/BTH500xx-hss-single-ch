/**
 * @file        BTH500xx-hss-single-ch.ino
 * @brief       High-Side-Switch Basic Example for the BTH500xx Arduino form factored shield
 * @details     This example demonstrates how to switch on/off the single channels in the BTS shield.
 *
 *              It can be deployed to the Arduino Uno or the XMC's with corresponding form factor.
 * @copyright   Copyright (c) 2023 Infineon Technologies AG
 */

#include <hss-shield-bth500xx-ino.hpp>

using namespace hss;

/** Creation of the hss board object */
Bth500xxShieldIno HSS = Bth500xxShieldIno();

Error_t err = OK;
float readCurrent = 0.0;

void setup()
{
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println(F("Serial initialized"));

    /** Initialization of the High-Side-Switch-Board */
    err = HSS.init();
    if(OK != err)
    {
        Serial.println(F("Initialization failed"));
    }
    else
    {
        Serial.println(F("Initialization successful!"));
    }
    delay(1000);
}

void loop()
{
    /** Turn on switch 1 */
    Serial.println(F("Turn on Switch 1"));
    err = HSS.switchHxOn(1);
    if(OK != err)
    {
        showErrorStatus(err);
    }
    delay(1000);

    /** Turn off switch 1 */
    Serial.println(F("Turning off Switch 1"));
    err = HSS.switchHxOff(1);
    if(OK != err)
    {
        showErrorStatus(err);
    }
    delay(1000);

    /** Turn on switch 2 */
    Serial.println(F("Turn on Switch 2"));
    err = HSS.switchHxOn(2);
    if(OK != err)
    {
        showErrorStatus(err);
    }
    delay(1000);

    /** Turn off switch 2 */
    Serial.println(F("Turning off Switch 2"));
    err = HSS.switchHxOff(2);
    if(OK != err)
    {
        showErrorStatus(err);
    }

    /** Keep all switches off for five more seconds */
    delay(5000);
}

/** Helper function to show the different error codes */
void showErrorStatus(Error_t error)
{
    switch (error)
    {
    case INTF_ERROR:
        Serial.println(F("You have encountered an interface error"));
        break;

    case CONF_ERROR:
        Serial.println(F("You have encountered a configuration error"));
        break;

    case READ_ERROR:
        Serial.println(F("You have encountered a reading error"));
        break;

    case WRITE_ERROR:
        Serial.println(F("You have encountered a writing error"));
        break;

    case NULLPTR_ERROR:
        Serial.println(F("You have encountered a null pointer error"));
        break;

    case INVALID_CH_ERROR:
        Serial.println(F("You have encountered an invalid channel error"));
        break;

    case UNSUPPORTED_OP_ERROR:
        Serial.println(F("You have encountered an unsupported operation error"));
        break;

    case INIT_ERROR:
        Serial.println(F("You have encountered an initialization error"));
        break;

    default:
        /** Default state is OK, here we do not print anything */
        break;
    }
}