/**
 * @file Timer_0A_Interrupt.c
 *
 * @brief Source code for the Timer_0A_Interrupt driver.
 *
 * This file contains the function definitions for the Timer_0A_Interrupt driver.
 * It uses the Timer 0A module to generate periodic interrupts.
 *
 * @author Antonio Anzora Jr
 */
#include "Timer_0A_Interrupt.h"
// Declare a pointer for the user-defined task function
void (*Timer_0A_Task)(void);

void Timer_0A_Interrupt_Init(void(*task)(void))
{
	// Save the user-defined task function for interrupt handling
	Timer_0A_Task = task;
	// Enable the clock for Timer 0A by setting R0 bit in RCGCTIMER register
	SYSCTL->RCGCTIMER |=  0x01;
	// Disable Timer 0A by clearing TAEN bit in GPTMCTL register
	TIMER0->CTL &= ~0x01;
	// Configure Timer 0A for 16-bit mode by setting GPTMCFG register
	TIMER0->CFG |= 0x04;
	// Set Timer 0A to Periodic Mode in GPTMTAMR register
	TIMER0->TAMR |= 0x02;
	// Clear TAPSR bits in GPTMTAPR register to prepare for prescale value
	TIMER0->TAPR &= ~0x000000FF;
	// Set the prescale value to 50 for 1 MHz timer clock frequency
	TIMER0->TAPR = 50;
	// Set the timer interval for 1 ms (1000 cycles)
	TIMER0->TAILR = (1000 - 1);
	// Acknowledge the Timer 0A interrupt by setting TATOCINT bit in GPTMICR
	TIMER0->ICR |= 0x01;
	// Enable Timer 0A interrupt by setting TATOIM bit in GPTMIMR register
	TIMER0->IMR |= 0x01;
	// Set Timer 0A interrupt priority to level 1 in PRI4 register
	NVIC->IPR[4] = (NVIC->IPR[4] & 0x00FFFFFF) | (1 << 29);
	// Enable IRQ 19 for Timer 0A in ISER[0] register
	NVIC->ISER[0] |= (1 << 19);
	// Enable Timer 0A by setting TAEN bit in GPTMCTL register
	TIMER0->CTL |= 0x01;
}
void TIMER0A_Handler(void)
{
	// Check if Timer 0A timeout interrupt occurred
	if (TIMER0->MIS & 0x01)
	{
		// Call the user-defined task function
		(*Timer_0A_Task)();	
		// Clear the Timer 0A interrupt
		TIMER0->ICR |= 0x01;
	}
}