 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "OLEDC_Click.h"
#include "OLEDC_colors.h"
#include "OLEDC_shapes.h"
#include <util/delay.h>
#include <stdbool.h>
#include <util/atomic.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define PRINTF_ENABLED                  true
/* if PRINTF_ENABLED is defined as true, the data is displayed in the 
 * serial terminal window, otherwise the data can be plotted on a graph 
 * using the Data Visualizer tool */

#if(PRINTF_ENABLED == true)
#define PRINT(X)                        printf(X)
#else
#define PRINT(X)
#endif

#if(PRINTF_ENABLED == false)
#define DV_SEND(X)                      Send_DV_Data(X)
#else
#define DV_SEND(X)
#endif

#define VOLTAGE_REF                     1024.0      /* mV */
#define MAX_ADC_STEPS_SIGNED            2048.0      /* half of 12-bit range */
#define PGA_GAIN                        16.0        
#define SAMPLE_NUMBER                   1024.0
/* the above defines are based on the ADC settings in MCC UI and
 * should be updated accordingly if the MCC settings are changed */

#define START_TOKEN                     0x03        /* Start Frame Token */
#define END_TOKEN                       0xFC        /* End Frame Token */
/* the above defines are required for Data Visualizer operation */

#define SOFTWARE_ACC_NUMBER             128         /* minimum accepted value is 1 */
#define SCALE_FACTOR                    1726.6      /* scale factor for 3.3V supply determined as the ratio between the known weight divided by the corresponding mV reading */
                                                    /* if 5V supply is used, scale factor is approximately 1142.6 */
#define MILLIVOLTS_TO_GRAMS(voltage)    (int32_t)lroundf(SCALE_FACTOR * (voltage))
#define ADC_STEPS_TO_MILLIVOLTS(adcVal) ((float)adcVal * VOLTAGE_REF) / (PGA_GAIN * MAX_ADC_STEPS_SIGNED * SAMPLE_NUMBER)
#define MAX_OLED_ROW_CHARS              10

/* function used to read the ADC result */
void ADC0_Handler(void);

/* function used to accumulate and average burst conversion results in software
 * receives as parameter the number of burst conversion results to accumulate
 * returns the average of the accumulated burst conversion results */
int32_t Accumulate_and_Average_Burst_Conversions(uint16_t numberOfBurstConversions);

/* function used to measure the tare of the weight scale */
void Scale_Tare(void);

/* function used to measure the weight of the object placed on the scale 
 * returns the measured weight in grams */
int32_t Scale_Measure(void);

/* function used to determine if the button was pressed */
void Button_Handler(void);

/* function used to display the weight measurement on the OLED Click board
 * receives as parameters two strings that will be displayed on the first and
 * second rows of the OLED screen */
void Main_Display(const char *string1, const char *string2);

/* function used to convert an integer to a string 
 * receives as parameters the data to be converted and the pointer to the
 * allocated memory location */
void IntegerToString(int32_t data, char *buffer);

/* function used to send the data to the Data Visualizer 
 * receives as parameter the data to be plotted on the DV graph */
void Send_DV_Data(int32_t data);

volatile bool sampleAvailable = false;
volatile diff_adc_result_t adcResult;
volatile bool buttonPressed = false;
int32_t scaleOffset = 0;

void ADC0_Handler(void)
{
    adcResult = ADC0_GetConversionResult();
    sampleAvailable = true;
}

int32_t Accumulate_and_Average_Burst_Conversions(uint16_t numberOfBurstConversions)
{
    diff_adc_result_t bufferedAdcResult;
    int32_t averagedResult;
    bool busy = true;
    int32_t accumulator = 0;
    uint16_t counter = 0;
    if(numberOfBurstConversions > 0)
    {
        while(busy)
        {  
            if(sampleAvailable)
            {
                sampleAvailable = false;
                ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
                {
                    bufferedAdcResult = adcResult;
                }
                accumulator += bufferedAdcResult;
                counter++;
                if(counter == numberOfBurstConversions)
                {
                    counter = 0;
                    averagedResult = accumulator;
                    accumulator = 0;
                    busy = false;
                }
            }
        }
        averagedResult = averagedResult / numberOfBurstConversions;
    }
    else
    {
        averagedResult = 0;
    }
    return averagedResult;
}

void Scale_Tare(void)
{
    Main_Display("Measuring", "tare...");
    PRINT("Measuring tare... \n\r");
    scaleOffset = Accumulate_and_Average_Burst_Conversions(SOFTWARE_ACC_NUMBER);
    Main_Display("Place the", "object!");
    PRINT("Place the object! \n\r");
    _delay_ms(5000);
    Main_Display("Measuring", "...");
    PRINT("Measuring... \n\r");
}

int32_t Scale_Measure(void)
{  
    int32_t measuredWeight;
    measuredWeight = MILLIVOLTS_TO_GRAMS(ADC_STEPS_TO_MILLIVOLTS((Accumulate_and_Average_Burst_Conversions(SOFTWARE_ACC_NUMBER) - scaleOffset)));
    if(measuredWeight <= 0)
    {
        measuredWeight = 0;
    }
    return measuredWeight;
}

void Button_Handler(void)
{
    buttonPressed = true;
}

void Main_Display(const char *string1, const char *string2)
{
    char temp_string[MAX_OLED_ROW_CHARS];
    oledC_clearScreen();
    strcpy(temp_string, string1);
    oledC_printString(temp_string, OLEDC_COLOR_WHITE, 0);
    strcpy(temp_string, string2);
    oledC_printString(temp_string, OLEDC_COLOR_WHITE, 1);
}

void IntegerToString(int32_t data, char *buffer)
{
    snprintf(buffer, 9, "%.3f kg", (float)data / 1000.0);
}

void Send_DV_Data(int32_t data)
{
    while(!(USART0_IsTxReady()));
    USART0_Write(START_TOKEN);
    for(uint8_t i = 0; i < sizeof(int32_t); i++)
    {
        while(!(USART0_IsTxReady()));
        USART0_Write((uint8_t)(data >> (i * 8) & 0xFF));
    }
    while(!(USART0_IsTxReady()));
    USART0_Write(END_TOKEN);
}

int main(void)
{
    SYSTEM_Initialize();
    ADC0_ResultReadyCallbackRegister(ADC0_Handler);
    BUTTON_SetInterruptHandler(Button_Handler); 
    oledC_setup();
    oledC_clearScreen(); 
    Scale_Tare();
    char buffer[MAX_OLED_ROW_CHARS];
    int32_t measuredWeight;

    while(1)
    {
        measuredWeight = Scale_Measure();
        IntegerToString(measuredWeight, buffer);
        Main_Display("Measured:", buffer);
        PRINT("Measured weight = ");
        PRINT(buffer);
        PRINT("\n\r");
        DV_SEND(measuredWeight);
        if(buttonPressed)
        {
            buttonPressed = false;
            _delay_ms(3000);
            Scale_Tare();
        }
    }    
}