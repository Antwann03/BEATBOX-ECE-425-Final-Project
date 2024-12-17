#include "TM4C123GH6PM.h"
#include "LCD_Display.h"
#include "SysTick_Delay.h"
#include "PMOD_ENC.h"
#include "Timer_0A_Interrupt.h"
#include "Buzzer.h"
static uint8_t state = 0;
static uint8_t last_state = 0;
static uint8_t pmod_enc_btn_pressed = 0;
static int prev_main_menu_counter = 0xFF;
static int main_menu_counter = 0;
#define MAX_COUNT 3

void PMOD_ENC_Task(void);

void PMOD_ENC_Task(void)
{
	state = PMOD_ENC_Get_State();
	
	if (PMOD_ENC_Button_Read(state) && !PMOD_ENC_Button_Read(last_state))
	{
		pmod_enc_btn_pressed = 1;
	}
	
	if (main_menu_counter < 0)
	{
		main_menu_counter = 0;
	}
	else if (main_menu_counter > MAX_COUNT)
	{
		main_menu_counter = MAX_COUNT;
	}
	else
	{
		main_menu_counter = main_menu_counter + PMOD_ENC_Get_Rotation(state, last_state);
	}
	last_state = state;
}
int main (void)
{
	//Initialize the LEDs on the EduBase board (Port B)
  //EduBase_LEDs_Init();
	
	//Initialize the buttons (SW2 - SW5) on the EduBase board (Port D)
	//EduBase_Button_Init();
	
//Initialize the DMT - 1206 Magnetic Buzzer (Port C)
Buzzer_Init();
	
// Initializes the SysTick timer to provide a delay function.
SysTick_Delay_Init();

// Initializes the PMOD encoder interface for reading input.
PMOD_ENC_Init();

// Initializes Timer 0A interrupt to handle encoder tasks.
Timer_0A_Interrupt_Init(&PMOD_ENC_Task);

// Retrieves the last state of the PMOD encoder.
last_state = PMOD_ENC_Get_State();

// Initializes the LCD display for use with the system.
EduBase_LCD_Init();

// Creates a custom character on the LCD based on the provided location and pattern.
EduBase_LCD_Create_Custom_Character(RIGHT_ARROW_LOCATION, right_arrow);	
	
//MARIO BODY

// Creates a custom character for Mario's left leg on the LCD at the specified location.
EduBase_LCD_Create_Custom_Character(MARIO_LEFT_LEG_LOCATION, mario_left_leg);

// Creates a custom character for Mario's left hat on the LCD at the specified location.
EduBase_LCD_Create_Custom_Character(MARIO_LEFT_HAT_LOCATION, mario_left_hat);

// Creates a custom character for Mario's torso on the LCD at the specified location.
EduBase_LCD_Create_Custom_Character(MARIO_TORSO_LOCATION, mario_torso);

// Creates a custom character for Mario's middle hat on the LCD at the specified location.
EduBase_LCD_Create_Custom_Character(MARIO_MIDDLE_HAT_LOCATION, mario_middle_hat);

// Creates a custom character for Mario's right hat on the LCD at the specified location.
EduBase_LCD_Create_Custom_Character(MARIO_RIGHT_HAT_LOCATION, mario_right_hat);

// Creates a custom character for Mario's right leg on the LCD at the specified location.
EduBase_LCD_Create_Custom_Character(MARIO_RIGHT_LEG_LOCATION, mario_right_leg);

/*
//MARIO STAR BODY	
	EduBase_LCD_Create_Custom_Character(MARIO_STAR_LEFT_LOCATION, mario_star_left);
	EduBase_LCD_Create_Custom_Character(MARIO_STAR_LEFT__LEG_LOCATION, mario_star_left_leg);
	EduBase_LCD_Create_Custom_Character(MARIO_STAR_MIDDLE_LOCATION, mario_star_middle);
	EduBase_LCD_Create_Custom_Character(MARIO_STAR_BOTTOM_MIDDLE_LOCATION, mario_star_bottom_middle);
	EduBase_LCD_Create_Custom_Character(MARIO_STAR_RIGHT_LOCATION, mario_star_right);
	EduBase_LCD_Create_Custom_Character(MARIO_STAR_RIGHT_LEG_LOCATION, mario_star_right_leg);
*/

	while(1)
{
//	uint8_t edubase_button_status = Get_EduBase_Button_Status();
	
// Checks for main menu counter if it has changed.
if(prev_main_menu_counter != main_menu_counter)
{
    // Clears the LCD display to update the screen.
    EduBase_LCD_Clear_Display();
    
    // Displays the current main menu based on the main menu counter.
    Display_Main_Menu(main_menu_counter);
    
    // Updates the previous main menu counter to the current one for future comparisons.
    prev_main_menu_counter = main_menu_counter;
}
		// Processes the user's main menu selection based on the current menu state.
		Process_Main_Menu_Selection();

		// Delays 100 microseconds
		SysTick_Delay1ms(100);
}
}

// Displays the main menu on the LCD based on the current state.
void Display_Main_Menu(int main_menu_state)
{
    // Switches between different main menu states to update the display accordingly.
    switch(main_menu_state)
    {
			// Case 0x00: Displays "Super Mario Bros" and "Doom Theme" on the LCD.
			case 0x00:
			{
				// Sets the cursor to the top-left corner of the first row.
        EduBase_LCD_Set_Cursor(0,0);   
				// Sends custom character data (if any) to the LCD.
        EduBase_LCD_Send_Data(0x03);   
        // Sets the cursor to the beginning of the second row.
        EduBase_LCD_Set_Cursor(1,0);
				// Displays "Super Mario Bros" on the second row of the LC
				EduBase_LCD_Display_String("Super Mario Bros");
				// Sets the cursor to the second column of the second row.
        EduBase_LCD_Set_Cursor(1,1);
        // Displays "Doom Theme" on the second row of the LCD.
        EduBase_LCD_Display_String("Doom Theme");	
        break;
        }
        // Case 0x01: Similar to case 0x00 but with different row positioning.
        case 0x01:
        {
            // Sets the cursor to the first column of the second row.
            EduBase_LCD_Set_Cursor(0,1);
            // Sends custom character data (if any) to the LCD.
            EduBase_LCD_Send_Data(0x03);
            // Sets the cursor to the beginning of the second row.
            EduBase_LCD_Set_Cursor(1,0);
            // Displays "Super Mario Bros" on the second row.
            EduBase_LCD_Display_String("Super Mario Bros");
            // Sets the cursor to the second column of the second row.
            EduBase_LCD_Set_Cursor(1,1);
            // Displays "Doom Theme" on the second row.
            EduBase_LCD_Display_String("Doom Theme");
            break;
        }
        // Case 0x02: Displays "Like Him" and "MF Doom" on the LCD.
        case 0x02:
        {
            // Sets the cursor to the top-left corner of the first row.
            EduBase_LCD_Set_Cursor(0,0);
            // Sends custom character data (if any) to the LCD.
            EduBase_LCD_Send_Data(0x03);
            // Sets the cursor to the beginning of the second row.
            EduBase_LCD_Set_Cursor(1,0);
            // Displays "Like Him" on the second row of the LCD.
            EduBase_LCD_Display_String("Like Him");
            // Sets the cursor to the second column of the second row.
            EduBase_LCD_Set_Cursor(1,1);
            // Displays "MF Doom" on the second row of the LCD.
            EduBase_LCD_Display_String("MF Doom");
            break;
        }
        // Case 0x03: Similar to case 0x02 but with different row positioning.
        case 0x03:
        {
            // Sets the cursor to the first column of the second row.
            EduBase_LCD_Set_Cursor(0,1);
            // Sends custom character data (if any) to the LCD.
            EduBase_LCD_Send_Data(0x03);
            // Sets the cursor to the beginning of the second row.
            EduBase_LCD_Set_Cursor(1,0);
            // Displays "Like Him" on the second row.
            EduBase_LCD_Display_String("Like Him");
            // Sets the cursor to the second column of the second row.
            EduBase_LCD_Set_Cursor(1,1);
            // Displays "MF Doom" on the second row.
            EduBase_LCD_Display_String("MF Doom");
            break;
        }
    }
}
void Process_Main_Menu_Selection(void) {
    // Check if the button was pressed on the PMOD encoder
    if (pmod_enc_btn_pressed == 1) {
        // Reset the button press flag and previous menu counter
        pmod_enc_btn_pressed = 0;
        prev_main_menu_counter = 0xFF;
        // Switch based on the current main menu state
        switch(main_menu_counter) {
        case 0x00: {
        // Display the full Mario image on the LCD
        EduBase_LCD_Clear_Display();
				EduBase_LCD_Display_Mario_Full_Image();  // Combines all the parts into one full image
        SysTick_Delay1ms(200);
        // Scroll the full image to the right
        for (int i = 0; i < 41; i++) { // Adjust the number of scrolls as needed
        EduBase_LCD_Scroll_Display_Right();
        SysTick_Delay1ms(50);
				}
        // Scroll the full image to the left
        for (int i = 0; i < 41; i++) { // Adjust the number of scrolls as needed
        EduBase_LCD_Scroll_Display_Left();
				EduBase_LCD_Set_Cursor(41, 1);
        EduBase_LCD_Send_Data(0x03);
        EduBase_LCD_Display_String("Song On");
        // Play the Super Mario Bros Theme song
				Play_Super_Mario_Bros_Theme();
        SysTick_Delay1ms(50);
        EduBase_LCD_Display_Mario_Full_Image();
				}
				break;
				}
        case 0x01: {
        // Play the Doom Theme song
				Play_Doom_Theme_Song();	
        SysTick_Delay1ms(3000);
        break;
				}
        case 0x02: {
        // Play "Like Him" by Tyler, The Creator
        Tyler_The_Creator_Like_Him(); // Start-up, needs more flow
        SysTick_Delay1ms(3000);
        break;
				}
        case 0x03: {
        // Placeholder for additional functionality
        SysTick_Delay1ms(3000);
        break;
				}
			}
		}
	}