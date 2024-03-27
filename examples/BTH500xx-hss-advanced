/**
 * @file        BTH500xx-hss-advanced.ino
 * @brief       High-Side-Switch Advanced Example for BTH500xx Arduino form factored shield
 * @details     This example shows the usage of all the offered functionalities of the shield.
 *              It does the following:
 *              - Demonstrates the diagnosis functionality of the channels
 *              - Demonstrates the different voltage measurement functionalities
 *              - Demonstrates the temperature measurement
 *
 *              It can be deployed to the Arduino Uno or the XMC's with corresponding form factor.
 * @copyright   Copyright (c) 2023 Infineon Technologies AG
 */

#include <hss-shield-bth500xx-ino.hpp>

/* Uncomment this define in order to remove the Serial.print which tells you about the missing NTC */
// #define NTC_POPULATED

using namespace hss;

/** Creation of the hss board object */
Bth500xxShieldIno HSS = Bth500xxShieldIno();

Error_t err = OK;
DiagStatus_t diagStatus = NORMAL;

float readCurrent = 0.0;
float batteryVoltage = 0.0;
float outputVoltage = 0.0;
float temperature = 0.0;

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

    /** Make sure both switches are turned off */
    HSS.switchesHxOff(1,1);
    delay(1000);
}

void loop()
{
    Serial.println(F("########### Checking Switch 1 ###########\n\n"));
    /** Diagnosis with switch 1 turned off */
    Serial.println(F("Reading the diagnosis status of switch 1 (switch off):"));
    for(int i=0; i<10; i++){
        diagStatus = HSS.readDiagx(1);
    }
    showDiagStatus(diagStatus);

    /** Turn on switch 1 */
    Serial.println(F("Turn on switch 1\n"));
    err = HSS.switchHxOn(1);
    if(OK != err)
    {
        showErrorStatus(err);
    }
    delay(2000);

    /** Read current through switch 1 */
    Serial.println(F("Measure the current through switch 1:"));
    for(int i=0; i<10; i++)
    {
        readCurrent = HSS.readIsx(1);
    }
    Serial.print(F("Current flowing through switch 1: "));
    Serial.print(readCurrent);
    Serial.println(F(" A\n"));
    delay(2000);

    /** Diagnosis with switch 1 turned on */
    Serial.println(F("Reading the diagnosis status of switch 1 (switch on):"));
    for(int i=0; i<10; i++){
        diagStatus = HSS.readDiagx(1);
    }
    showDiagStatus(diagStatus);
    delay(2000);

    /** Measure the output voltage of switch 1 */
    Serial.println(F("Measuring the output voltage of switch 1:"));
    for(int i=0; i<10; i++){
        outputVoltage = HSS.readVOut();
    }
    Serial.print(F("The output voltage of switch 1 is "));
    Serial.print(outputVoltage);
    Serial.println(F(" V\n"));
    delay(2000);

    /** Turn off switch 1 */
    Serial.println(F("Turn off switch 1\n"));
    err = HSS.switchHxOff(1);
    if(OK != err)
    {
        showErrorStatus(err);
    }
    delay(2000);

    Serial.println(F("########### Checking Switch 2 ###########\n\n"));
    /** Diagnosis with switch 2 turned off */
    Serial.println(F("Reading the diagnosis status of switch 2 (switch off):"));
    for(int i=0; i<10; i++){
        diagStatus = HSS.readDiagx(2);
    }
    showDiagStatus(diagStatus);
    delay(2000);

    /** Turn on switch 2 */
    Serial.println(F("Turn on switch 2\n"));
    err = HSS.switchHxOn(2);
    if(OK != err)
    {
        showErrorStatus(err);
    }
    delay(2000);

    /** Read current through switch 2 */
    Serial.println(F("Measure the current through switch 2:"));
    for(int i=0; i<10; i++)
    {
        readCurrent = HSS.readIsx(2);
    }
    Serial.print(F("Current flowing through switch 2: "));
    Serial.print(readCurrent);
    Serial.println(F(" A\n"));
    delay(2000);

    /** Diagnosis with switch 2 turned on */
    Serial.println(F("Reading the diagnosis status of switch 2 (switch on):"));
    for(int i=0; i<10; i++){
        diagStatus = HSS.readDiagx(2);
    }
    showDiagStatus(diagStatus);
    delay(2000);

    /** Turn off switch 2 */
    Serial.println(F("Turn off switch 2\n\n"));
    err = HSS.switchHxOff(2);
    if(OK != err)
    {
        showErrorStatus(err);
    }

    Serial.println(F("########### Check the board temperature and input voltage ###########\n\n"));
    /** Check the board temperature */
    Serial.println(F("Measuring the board temperature:"));
    for(int i=0; i<10; i++){
        temperature = HSS.readTemperature();
    }
    Serial.print(F("The board temperature is "));
    Serial.print(temperature);
    Serial.println(F(" °C\n"));
    #ifndef NTC_POPULATED
        Serial.println(F("The NTC on the boards is not populated, therefore the return value is always -35.43 °C"));
    #endif
    delay(2000);

    /** Measure the battery voltage */
    Serial.println(F("Measuring the battery voltage:"));
    for(int i=0; i<10; i++){
        batteryVoltage = HSS.readVs();
    }
    Serial.print(F("The battery voltage is "));
    Serial.print(batteryVoltage);
    Serial.println(F(" V\n"));
    delay(2000);

    Serial.println(F("Wait for five seconds and then start again ...\n\n\n"));
    delay(5000);
}

/** Helper function to show the different diagnosis states */
void showDiagStatus(DiagStatus_t diagState)
{
    switch (diagState)
    {
    case SHORT_TO_VSS:
        Serial.println(F("You have a short to the supply voltage at this switch\n"));
        break;

    case OPEN_LOAD:
        Serial.println(F("You have an open load at this switch. You should check your connection\n"));
        break;

    case SHORT_TO_GND_OR_OT:
        Serial.println(F("You have a short to the ground or an over-temperature at this switch\n"));
        break;

    case FAULT:
        Serial.println(F("You have a detected fault condition at this switch. Please check the data sheet for more information [page 19-20]\n"));
        break;

    case DIAG_READ_ERROR:
        Serial.println(F("You have a diagnosis read error, which means you have chosen a channel that is invalid"));
        Serial.println(F("Only channel 1 and 2 are valid channels!\n"));
        break;

    default:
        Serial.println(F("Everything is working correctly\n"));
        break;
    }
}

/** Helper function to show the different error codes */
void showErrorStatus(Error_t error)
{
    switch (error)
    {
    case INTF_ERROR:
        Serial.println("You have encountered an interface error\n");
        break;

    case CONF_ERROR:
        Serial.println("You have encountered a configuration error\n");
        break;

    case READ_ERROR:
        Serial.println("You have encountered a reading error\n");
        break;

    case WRITE_ERROR:
        Serial.println("You have encountered a writing error\n");
        break;

    case NULLPTR_ERROR:
        Serial.println("You have encountered a null pointer error\n");
        break;

    case INVALID_CH_ERROR:
        Serial.println("You have encountered an invalid channel error\n");
        break;

    case UNSUPPORTED_OP_ERROR:
        Serial.println("You have encountered an unsupported operation error\n");
        break;

    case INIT_ERROR:
        Serial.println("You have encountered an initialization error\n");
        break;

    default:
        /** Default state is OK, here we do not print anything */
        break;
    }
}