/**
 * @file        BTS5001x-button-test.ino
 * @brief       Button Test Example for Profet 12V BTS5001x Arduino form factored Shields
 * @details     SHIELD_BTS5001x-1TAD Shield have optional user button to
 *              perform switching. This example demonstrates the use of optional user button.
 *
 *              You can configure following variants for this shield:
 *              - BTS50010
 *              - BTS50015
 *
 * @copyright   Copyright (c) 2021 Infineon Technologies AG
 */

#include <hss-shield-bts5001x-ino.hpp>

using namespace hss;

/** Creation the hss board object */
/** The user needs to specify the BTS5001x variant in the constructor argument */
Bts5001xShieldIno HSS = Bts5001xShieldIno(&BTS50015);

Error_t err = OK;
unsigned int iteration = 0;

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
    float voltage = 0.0;
    static bool button_pressed = false;                         // The flag is used to avoid printing constantly
    static bool switch_on = false;

    /** Read push button */
    while(HSS.analogReadButton())
    {
        button_pressed = true;
        delay(10);
    } 

    /** Toogles the output when the button is pressed */
    if(button_pressed)
    {
        button_pressed = false;
        switch_on = !switch_on;

        if(switch_on)
        {
            HSS.switchHxOn();
        }
        else
        {
            HSS.switchHxOff();
        }
    }
    
    delay(50);

    /** Read the Vss value when the switch is ON and only in every 10th iteration (500ms interval) */
    if ((switch_on) && !( iteration % 10 ))
    {
        for(int i = 0; i<10; i++){
            voltage = HSS.readVss();                            // Measure more than once to make use of the internal exponential filter
        }

        Serial.print("Supply voltage is: ");
        Serial.println(voltage);
    }

    iteration++;
}