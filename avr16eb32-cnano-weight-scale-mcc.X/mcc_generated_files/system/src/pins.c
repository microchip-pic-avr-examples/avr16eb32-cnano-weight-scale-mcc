/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
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

#include "../pins.h"

static void (*IO_PC2_InterruptHandler)(void);
static void (*IO_PC1_InterruptHandler)(void);
static void (*IO_PA5_InterruptHandler)(void);
static void (*IO_PA4_InterruptHandler)(void);
static void (*oledC_SCK_InterruptHandler)(void);
static void (*IO_PD4_InterruptHandler)(void);
static void (*IO_PD5_InterruptHandler)(void);
static void (*BUTTON_InterruptHandler)(void);
static void (*oledC_RST_InterruptHandler)(void);
static void (*oledC_EN_InterruptHandler)(void);
static void (*oledC_DC_InterruptHandler)(void);
static void (*oledC_RW_InterruptHandler)(void);
static void (*oledC_nCS_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{
  /* DIR Registers Initialization */
    PORTA.DIR = 0x50;
    PORTC.DIR = 0xB;
    PORTD.DIR = 0x84;
    PORTF.DIR = 0x8;

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTC.OUT = 0x2;
    PORTD.OUT = 0x0;
    PORTF.OUT = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x0;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0xB;
    PORTF.PIN7CTRL = 0x0;

  /* EVGENCTRL registers Initialization */
    PORTA.EVGENCTRLA = 0x0;
    PORTC.EVGENCTRLA = 0x0;
    PORTD.EVGENCTRLA = 0x0;
    PORTF.EVGENCTRLA = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TCEROUTEA = 0x0;
    PORTMUX.TCFROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x4;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    IO_PC2_SetInterruptHandler(IO_PC2_DefaultInterruptHandler);
    IO_PC1_SetInterruptHandler(IO_PC1_DefaultInterruptHandler);
    IO_PA5_SetInterruptHandler(IO_PA5_DefaultInterruptHandler);
    IO_PA4_SetInterruptHandler(IO_PA4_DefaultInterruptHandler);
    oledC_SCK_SetInterruptHandler(oledC_SCK_DefaultInterruptHandler);
    IO_PD4_SetInterruptHandler(IO_PD4_DefaultInterruptHandler);
    IO_PD5_SetInterruptHandler(IO_PD5_DefaultInterruptHandler);
    BUTTON_SetInterruptHandler(BUTTON_DefaultInterruptHandler);
    oledC_RST_SetInterruptHandler(oledC_RST_DefaultInterruptHandler);
    oledC_EN_SetInterruptHandler(oledC_EN_DefaultInterruptHandler);
    oledC_DC_SetInterruptHandler(oledC_DC_DefaultInterruptHandler);
    oledC_RW_SetInterruptHandler(oledC_RW_DefaultInterruptHandler);
    oledC_nCS_SetInterruptHandler(oledC_nCS_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for IO_PC2 at application runtime
*/
void IO_PC2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC2_InterruptHandler = interruptHandler;
}

void IO_PC2_DefaultInterruptHandler(void)
{
    // add your IO_PC2 interrupt custom code
    // or set custom function using IO_PC2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PC1 at application runtime
*/
void IO_PC1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PC1_InterruptHandler = interruptHandler;
}

void IO_PC1_DefaultInterruptHandler(void)
{
    // add your IO_PC1 interrupt custom code
    // or set custom function using IO_PC1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA5 at application runtime
*/
void IO_PA5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA5_InterruptHandler = interruptHandler;
}

void IO_PA5_DefaultInterruptHandler(void)
{
    // add your IO_PA5 interrupt custom code
    // or set custom function using IO_PA5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PA4 at application runtime
*/
void IO_PA4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PA4_InterruptHandler = interruptHandler;
}

void IO_PA4_DefaultInterruptHandler(void)
{
    // add your IO_PA4 interrupt custom code
    // or set custom function using IO_PA4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for oledC_SCK at application runtime
*/
void oledC_SCK_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    oledC_SCK_InterruptHandler = interruptHandler;
}

void oledC_SCK_DefaultInterruptHandler(void)
{
    // add your oledC_SCK interrupt custom code
    // or set custom function using oledC_SCK_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD4 at application runtime
*/
void IO_PD4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD4_InterruptHandler = interruptHandler;
}

void IO_PD4_DefaultInterruptHandler(void)
{
    // add your IO_PD4 interrupt custom code
    // or set custom function using IO_PD4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD5 at application runtime
*/
void IO_PD5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD5_InterruptHandler = interruptHandler;
}

void IO_PD5_DefaultInterruptHandler(void)
{
    // add your IO_PD5 interrupt custom code
    // or set custom function using IO_PD5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUTTON at application runtime
*/
void BUTTON_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUTTON_InterruptHandler = interruptHandler;
}

void BUTTON_DefaultInterruptHandler(void)
{
    // add your BUTTON interrupt custom code
    // or set custom function using BUTTON_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for oledC_RST at application runtime
*/
void oledC_RST_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    oledC_RST_InterruptHandler = interruptHandler;
}

void oledC_RST_DefaultInterruptHandler(void)
{
    // add your oledC_RST interrupt custom code
    // or set custom function using oledC_RST_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for oledC_EN at application runtime
*/
void oledC_EN_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    oledC_EN_InterruptHandler = interruptHandler;
}

void oledC_EN_DefaultInterruptHandler(void)
{
    // add your oledC_EN interrupt custom code
    // or set custom function using oledC_EN_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for oledC_DC at application runtime
*/
void oledC_DC_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    oledC_DC_InterruptHandler = interruptHandler;
}

void oledC_DC_DefaultInterruptHandler(void)
{
    // add your oledC_DC interrupt custom code
    // or set custom function using oledC_DC_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for oledC_RW at application runtime
*/
void oledC_RW_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    oledC_RW_InterruptHandler = interruptHandler;
}

void oledC_RW_DefaultInterruptHandler(void)
{
    // add your oledC_RW interrupt custom code
    // or set custom function using oledC_RW_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for oledC_nCS at application runtime
*/
void oledC_nCS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    oledC_nCS_InterruptHandler = interruptHandler;
}

void oledC_nCS_DefaultInterruptHandler(void)
{
    // add your oledC_nCS interrupt custom code
    // or set custom function using oledC_nCS_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       IO_PA5_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       IO_PA4_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT6_bm)
    {
       oledC_SCK_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT2_bm)
    {
       IO_PC2_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT1_bm)
    {
       IO_PC1_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT0_bm)
    {
       oledC_RST_InterruptHandler(); 
    }
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       oledC_EN_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       IO_PD4_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       IO_PD5_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       oledC_DC_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       oledC_RW_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       BUTTON_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       oledC_nCS_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/