/**
 * @file Timer_0A_Interrupt.h
 *
 * @brief Header file for the Timer_0A_Interrupt driver.
 *
 * This file contains the function definitions for the Timer_0A_Interrupt driver.
 * It uses the Timer 0A module to generate periodic interrupts.
 *
 * @author Antonio Anzora Jr
 */
#include "TM4C123GH6PM.h"
// Declare pointer to the user-defined task
extern void (*Timer_0A_Task)(void);
/**
 * @brief Initializes Timer 0A to generate periodic interrupts.
 *
 * Configures Timer 0A to trigger interrupts every 1 ms using the 50MHz system clock.
 * A user-defined task is executed on each interrupt, with priority set to 1.
 *
 * @param task Function to be executed on Timer 0A interrupt.
 * @return None
 */
void Timer_0A_Interrupt_Init(void(*task)(void));

/**
 * @brief ISR for Timer 0A.
 *
 * Handles Timer 0A interrupts, executes the user-defined task, and clears the interrupt flag.
 *
 * @return None
 */
void TIMER0A_Handler(void);
