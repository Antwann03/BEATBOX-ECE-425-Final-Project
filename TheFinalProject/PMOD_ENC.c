/**
 * @file PMOD_ENC.c
 * @brief PMOD_ENC driver source code.
 *
 * This file defines functions for interfacing with the PMOD ENC (Rotary Encoder) using GPIO.
 *
 * Pinout for PMOD ENC module:
 *  - Pin 1 (A)  <--> Tiva LaunchPad Pin PD0
 *  - Pin 2 (B)  <--> Tiva LaunchPad Pin PD1
 *  - Pin 3 (BTN) <--> Tiva LaunchPad Pin PD2
 *  - Pin 4 (SWT) <--> Tiva LaunchPad Pin PD3
 *  - Pin 5 (GND) <--> Tiva LaunchPad GND
 *  - Pin 6 (VCC) <--> Tiva LaunchPad 3.3V
 *
 * @author Antonio Anzora Jr
 */

#include "PMOD_ENC.h"
void PMOD_ENC_Init(void)
{
	// Enable clock for Port D by setting R3 bit in the RCGCGPIO register
	SYSCTL ->RCGCGPIO |= 0x08;
	// Configure PD3, PD2, PD1, and PD0 pins as input by clearing Bits 3 to 0 in the DIR register
	GPIOD -> DIR &= ~PMOD_ENC_ALL_PINS_MASK;
	// Configure PD3, PD2, PD1, and PD0 pins to regular GPIO by clearing Bits 3 to 0 in the AFSEL register
	GPIOD -> AFSEL &= ~PMOD_ENC_ALL_PINS_MASK;
	// Enable digital functionality for PD3, PD2, PD1, and PD0 pins by setting Bits 3 to 0 in the DEN register
	GPIOD -> DEN |= PMOD_ENC_ALL_PINS_MASK;
}

uint8_t PMOD_ENC_Get_State(void)
{
	// Return the current state of the PMOD ENC pins (PD0 to PD3)
	uint8_t state =  GPIOD -> DATA & PMOD_ENC_ALL_PINS_MASK;
  return state;
}

int PMOD_ENC_Get_Rotation(uint8_t state, uint8_t last_state)
{
	// Check for changes in Pin A (PD0) state to determine rotation direction
	// Return 1 for clockwise, -1 for counter-clockwise, or 0 if no change
	if ((state & PMOD_ENC_PIN_A_MASK) != 0 && (last_state & PMOD_ENC_PIN_A_MASK) == 0)
	{
		if ((state & PMOD_ENC_PIN_B_MASK) != 0)
		{
			return 1;  // CW rotation
		}
		else
		{
			return -1; // CC rotation
		}
	}
	else
	{
		return 0; // No change in rotation
	}
}
uint8_t PMOD_ENC_Button_Read(uint8_t state)
{
	// Return the state of the button (pressed or not)
  return state & PMOD_ENC_BUTTON_MASK;
}
uint8_t PMOD_ENC_Switch_Read(uint8_t state)
{
	// Return the state of the switch (on or off)
  return state & PMOD_ENC_SWITCH_MASK;
}