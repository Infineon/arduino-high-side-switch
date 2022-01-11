/**
 * @file        BTS5001x-hss-advanced.ino
 * @brief       High-Side-Switch Advanced Example for BTS5001x Arduino form factored shields
 * @details     This example shows the usage of all the offered functionalities of the shield.
 *              It does the following:
 *              - Switches a channel ON
 *              - Reads current through the switch, battery voltage and performs diagnosis in 'ON' state
 *              - Switches the channel OFF
 *
 *              You can configure following variants for this shield:
 *              - BTS50010
 *              - BTS50015
 *
 *              It can be deployed to the Arduino Uno or the XMC's with corresponding form factor.
 *
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 */


#include <hss-shield-bts5001x-ino.hpp>

using namespace hss;

/** Creation the hss board object */
/** The user needs to specify the BTS5001x variant in the constructor argument */
Bts5001xShieldIno HSS = Bts5001xShieldIno(&BTS50015);

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
        /** Turn on the selected channel */
        Serial.println("\n--> Turning the switch ON");
        HSS.switchHxOn();

        /** Wait for a second before reading diagnosis*/
        delay(1000);

        /** Get switch related params like current, diagnosis output while it is in 'ON' state */
        getSwitchParams();

        /** Keep switch on for a second */
        delay(1000);

        /** Turn off the selected channel */
        Serial.print("--> Turning the switch OFF");
        HSS.switchHxOff();

        /** Keep switch off for a second */
        delay(5000);
}

/**
 * @brief       Perform switch related functionalities
 * @details     This function is going to perform the following:
 *              - Read current through the selected switch
 *              - Perform diagnosis
 *              - Read the battery voltage
 */
void getSwitchParams()
{
    Serial.println("Reading the current, battery voltage and diagnosis status of switch ...");
    /** Read current value */
    readCurrent();
    /** Get diagnosis result */
    readDiagnosis();
    /** Read battery voltage */
    readBatteryVoltage();
}


/**
 * @brief       Read current flowing through the switch
 */
void readCurrent()
{
    float readAmps = 0.0;
    for(int i = 0; i<10; i++){                              // Measure more than once to make use of the internal exponential filter
        readAmps = HSS.readIsx();
    }
    Serial.print("Current flowing through the switch: ");
    Serial.print(readAmps);
    Serial.println(" A");
    return;
}

/**
 * @brief       Read diagnosis status of the switch
 */
void readDiagnosis()
{
    DiagStatus_t switchStatus;

    for(int i = 0; i<10; i++){
        switchStatus = HSS.readDiagx();                     // Read the diagnosis function more than once to make sure the IS value is correct (internal exponential filter)
    }

    if(switchStatus == FAULT_OL_IC)
    {
        Serial.println("Open load with enabled switch or inverse current detected!");
    }
    if(switchStatus == FAULT)
    {
        Serial.println("Overtemperature, overload or shot to ground detected!");
    }
    if(switchStatus == NORMAL)
    {
        Serial.println("Normal operation!");
    }
    return;
}

/**
 * @brief       Reads the current battery voltage
 */
void readBatteryVoltage()
{
    float batteryVoltage = 0.0;
    for(int i = 0; i<10; i++){
        batteryVoltage = HSS.readVss();
    }
    Serial.print("Current battery voltage : ");
    Serial.print(batteryVoltage);
    Serial.println(" V");
    return;
}