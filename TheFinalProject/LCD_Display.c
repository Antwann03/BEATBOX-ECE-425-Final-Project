/**
 * @file LCD_Display.c
 *
 * @brief Source code for the LCD_Display driver.
 *
 * This file contains the function definitions for the EduBase_LCD driver.
 * It interfaces with the EduBase Board 16x2 Liquid Crystal Display (LCD). 
 * The following pins are used:
 *  - Data Pin 4      [D4]  (PA2)
 *  - Data Pin 5      [D5]  (PA3)
 *  - Data Pin 6      [D6]  (PA4)
 *  - Data Pin 7      [D7]  (PA5)
 *	- LCD Enable      [E]   (PC6)
 *  - Register Select [RS]  (PE0)
 *
 * @author Antonio Anzora Jr
 */
 
#include "LCD_Display.h"

static uint8_t display_control = 0x00;
static uint8_t display_mode = 0x00;
void EduBase_LCD_Ports_Init(void)
{
	// Enable clock to Port A (R0 bit in RCGCGPIO)
	SYSCTL -> RCGCGPIO |= 0x01;
	// Set PA5, PA4, PA3, PA2 pins as output
	GPIOA -> DIR |= 0x3C;
	// Set PA5, PA4, PA3, PA2 pins to GPIO
	GPIOA -> AFSEL &= ~(0x3C);
	// Enable digital functionality for PA5, PA4, PA3, PA2 pins
	GPIOA -> DEN |= 0x3C;
	// Initialize PA5, PA4, PA3, PA2 pins to zero
	GPIOA -> DATA &= ~(0x3C);
	// Enable clock to Port C (R2 bit in RCGCGPIO)
	SYSCTL -> RCGCGPIO |= 0x04;
	// Set PC6 pin as output
	GPIOC -> DIR |= 0x40;
	// Set PC6 to GPIO
	GPIOC -> AFSEL &= ~(0x40);
	// Enable digital functionality for PC6
	GPIOC -> DEN |= 0x40;
	// Initialize PC6 to zero
	GPIOC -> DATA &= ~(0x40);
	// Enable clock to Port E (R4 bit in RCGCGPIO)
	SYSCTL -> RCGCGPIO |= 0x10;
	// Set PE0 pin as output
	GPIOE -> DIR |= 0x01;
	// Set PE0 to GPIO
	GPIOE -> AFSEL &= ~(0x01);
	// Enable digital functionality for PE0
	GPIOE -> DEN |= 0x01;	
	// Initialize PE0 to zero
	GPIOE -> DATA &= ~(0x01);
}
void EduBase_LCD_Pulse_Enable(void)
{
	GPIOC -> DATA &= ~(0x40);
	SysTick_Delay1us(1);
	GPIOC -> DATA |= 0x40;
	SysTick_Delay1us(1);
	GPIOC -> DATA &= ~(0x40);
}
void EduBase_LCD_Write_4_Bits(uint8_t data, uint8_t control_flag)
{
	//Set the upper nibble for (PA2 - PA5)
	GPIOA -> DATA |= (data & 0xF0) >> 0x2;
	
	//Set or clear the register select (RS) pin based on the control flag 
	//0 for command and 1 for data
	if (control_flag & 0x01)
	{
		GPIOE ->DATA |= 0x01;
	}
	
	else
	{
		GPIOE -> DATA &= ~(0x01);
	}
	
	//Output a short pulse on the PC6 pin to enable the LCD
	EduBase_LCD_Pulse_Enable();

	//Clear the LCD data lines (PA2 - PA5) and provide a 1 ms delay
	GPIOA -> DATA &= ~(0x3C);
	SysTick_Delay1us(1000);
}

void EduBase_LCD_Send_Command(uint8_t command)
{
	//Transmit the upper nibble of the command byte
	EduBase_LCD_Write_4_Bits(command & 0xF0, SEND_COMMAND_FLAG);
	
	//Transmit the lower nibble of the command byte
	EduBase_LCD_Write_4_Bits(command << 0x4, SEND_COMMAND_FLAG);
	if (command < 3)
	{
		SysTick_Delay1us(1520);
	}
	else
	{
		SysTick_Delay1us(37);
	}
}

void EduBase_LCD_Send_Data(uint8_t data)
{
	//Transmit the upper nibble of the data byte
	EduBase_LCD_Write_4_Bits(data & 0xF0, SEND_DATA_FLAG);
	
	//Transmit the lower nibble of the data byte
	EduBase_LCD_Write_4_Bits(data << 0x4, SEND_DATA_FLAG);
}

void EduBase_LCD_Init(void)
{
	//Initialize the GPIO pins used by the LCD
	EduBase_LCD_Ports_Init();
	//Provide a delay of 50 ms after the LCD is powered on
	SysTick_Delay1us(50000);
	//Transmit function set intialization commans as part of the LCD initialization sequence
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(4500);
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(4500);
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(150);
	//Transmit function set intialization commans as part of the LCD initialization sequence
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_FOUR_BIT_MODE, SEND_COMMAND_FLAG);
	//Configure the LCD to use 5x8 dots and two rows
	EduBase_LCD_Send_Command(FUNCTION_SET | CONFIG_5x8_DOTS | CONFIG_TWO_LINES);
	//Transmit a Display Control command to enable the display of the LCD
	EduBase_LCD_Enable_Display();
	//Transmit a Return Home command to set the DDRAM address to 0 and to return 
	//the display from being shifted to the original position
	EduBase_LCD_Return_Home();
	
	//Transmit a Clear Display command to clear the display and set the DDRAM addres to 0
	EduBase_LCD_Clear_Display();
	
	//Turn off the cursor and the blinking of cursor position character
	EduBase_LCD_Disable_Cursor_Blink();
	EduBase_LCD_Disable_Cursor();
}

void EduBase_LCD_Clear_Display(void)
{
	EduBase_LCD_Send_Command(CLEAR_DISPLAY);
}

void EduBase_LCD_Return_Home(void)
{
	EduBase_LCD_Send_Command(RETURN_HOME);
}

void EduBase_LCD_Set_Cursor(uint8_t col, uint8_t row)
{
	if(col < 16)
	{
		if (row == 0)
		{
			EduBase_LCD_Send_Command(SET_DDRAM_ADDR | col);
		}
		
		else if (row == 1)
		{
			EduBase_LCD_Send_Command(SET_DDRAM_ADDR | (col + 0x40));
		}
	}
}

void EduBase_LCD_Disable_Display(void)
{
	display_control = display_control & ~(DISPLAY_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Enable_Display(void)
{
	display_control = display_control | (DISPLAY_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Disable_Cursor(void)
{
	display_control = display_control & ~(CURSOR_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Enable_Cursor(void)
{
	display_control = display_control | CURSOR_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Disable_Cursor_Blink(void)
{
	display_control = display_control & ~(CURSOR_BLINK_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Enable_Cursor_Blink(void)
{
	display_control = display_control | CURSOR_BLINK_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Scroll_Display_Left(void)
{
	EduBase_LCD_Send_Command(CURSOR_OR_DISPLAY_SHIFT | DISPLAY_MOVE | MOVE_LEFT);
}

void EduBase_LCD_Scroll_Display_Right(void)
{
		EduBase_LCD_Send_Command(CURSOR_OR_DISPLAY_SHIFT | DISPLAY_MOVE | MOVE_RIGHT);
}

void EduBase_LCD_Left_to_Right(void)
{
	display_mode = display_mode | ENTRY_SHIFT_INCREMENT;
	EduBase_LCD_Send_Command(ENTRY_MODE_SET | display_mode);
}

void EduBase_LCD_Right_to_Left(void)
{
	display_mode = display_mode & ~ENTRY_SHIFT_INCREMENT;
	EduBase_LCD_Send_Command(ENTRY_MODE_SET | display_mode);
}

void EduBase_LCD_Create_Custom_Character(uint8_t location, uint8_t character_buffer[])
{
	location = location & 0x7;
	EduBase_LCD_Send_Command(SET_CGRAM_ADDR | (location << 3));
	for (int i = 0; i < 8; i++)
	{
		EduBase_LCD_Send_Data(character_buffer[i]);
	}
}

void EduBase_LCD_Display_String(char* string)
{
	for(unsigned int i = 0; i < strlen(string); i++)
	{
		EduBase_LCD_Send_Data(string[i]);
	}
}

void EduBase_LCD_Display_Integer(int value)
{
	char integer_buffer[32];
	sprintf(integer_buffer, "%d", value);
	EduBase_LCD_Display_String(integer_buffer);
}

void EduBase_LCD_Display_Double(double value)
{
	char double_buffer[32];
	sprintf(double_buffer, "%.6f", value);
	EduBase_LCD_Display_String(double_buffer);
}
void EduBase_LCD_Display_Mario_Left_Hat(void)
{
		EduBase_LCD_Enable_Display();
		EduBase_LCD_Set_Cursor(0, 0);
		EduBase_LCD_Send_Data(MARIO_LEFT_HAT_LOCATION);
}
void EduBase_LCD_Display_Mario_Left_Leg(void)
{
		EduBase_LCD_Enable_Display();
		EduBase_LCD_Set_Cursor(0, 1);
		EduBase_LCD_Send_Data(MARIO_LEFT_LEG_LOCATION);
}
void EduBase_LCD_Display_Mario_Middle_Hat(void)
{
		EduBase_LCD_Enable_Display();
		EduBase_LCD_Set_Cursor(1, 0);
		EduBase_LCD_Send_Data(MARIO_MIDDLE_HAT_LOCATION);
}
void EduBase_LCD_Display_Mario_Torso(void)
{
		EduBase_LCD_Enable_Display();
		EduBase_LCD_Set_Cursor(1, 1);
		EduBase_LCD_Send_Data(MARIO_TORSO_LOCATION);
}
void EduBase_LCD_Display_Mario_Right_Hat(void)
{
		EduBase_LCD_Enable_Display();
		EduBase_LCD_Set_Cursor(2, 0);
		EduBase_LCD_Send_Data(MARIO_RIGHT_HAT_LOCATION);
}
void EduBase_LCD_Display_Mario_Right_Leg(void)
{
		EduBase_LCD_Enable_Display();	
		EduBase_LCD_Set_Cursor(2, 1);
		EduBase_LCD_Send_Data(MARIO_RIGHT_LEG_LOCATION);
}

void EduBase_LCD_Display_Mario_Full_Image(void)
{
    EduBase_LCD_Display_Mario_Left_Hat();
    EduBase_LCD_Display_Mario_Left_Leg();
    EduBase_LCD_Display_Mario_Middle_Hat();
    EduBase_LCD_Display_Mario_Torso();
    EduBase_LCD_Display_Mario_Right_Hat();
    EduBase_LCD_Display_Mario_Right_Leg();
}
/*
//MARIO STAR Full Image
	void EduBase_LCD_Display_Mario_Star_Left(void)
	{
		EduBase_LCD_Enable_Display();
	
		EduBase_LCD_Set_Cursor(5, 0);
		EduBase_LCD_Send_Data(MARIO_STAR_LEFT_LOCATION);
}
	void EduBase_LCD_Display_Mario_Star_Left_Leg(void)
	{
		EduBase_LCD_Enable_Display();
	
		EduBase_LCD_Set_Cursor(5, 1);
		EduBase_LCD_Send_Data(MARIO_STAR_LEFT__LEG_LOCATION);
}
void EduBase_LCD_Display_Mario_Star_Middle(void)
	{
		EduBase_LCD_Enable_Display();
	
		EduBase_LCD_Set_Cursor(6, 0);
		EduBase_LCD_Send_Data(MARIO_STAR_MIDDLE_LOCATION);
}
	void EduBase_LCD_Display_Mario_Star_Bottom_Middle(void)
	{
		EduBase_LCD_Enable_Display();
	
		EduBase_LCD_Set_Cursor(6, 1);
		EduBase_LCD_Send_Data(MARIO_STAR_BOTTOM_MIDDLE_LOCATION);
}
	void EduBase_LCD_Display_Mario_Star_Right(void)
	{
		EduBase_LCD_Enable_Display();
	
		EduBase_LCD_Set_Cursor(7,0);
		EduBase_LCD_Send_Data(MARIO_STAR_RIGHT_LOCATION);
}
	void EduBase_LCD_Display_Mario_Star_Right_Leg(void)
	{
		EduBase_LCD_Enable_Display();
	
		EduBase_LCD_Set_Cursor(7, 1);
		EduBase_LCD_Send_Data(MARIO_STAR_RIGHT_LEG_LOCATION);
}
	void EduBase_LCD_Display_Mario_Star_Full_Image(void)
{
    EduBase_LCD_Display_Mario_Star_Left();
    EduBase_LCD_Display_Mario_Star_Left_Leg();
    EduBase_LCD_Display_Mario_Star_Middle();
    EduBase_LCD_Display_Mario_Star_Bottom_Middle();
    EduBase_LCD_Display_Mario_Star_Right();
    EduBase_LCD_Display_Mario_Star_Right_Leg();
}
*/