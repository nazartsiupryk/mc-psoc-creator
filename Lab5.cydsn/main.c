/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

#define PHASE_NUMBER 4
#define PHASE_DELAY 10
#define PHASE_1 0b1000
#define PHASE_2 0b0100
#define PHASE_3 0b0010
#define PHASE_4 0b0001
#define STOP 0b0000

#define DIR_STOP 0
#define DIR_FORWARD 1
#define DIR_BACKWARD 2

#define NAME_STOP     "STOP    "
#define NAME_FORWARD  "FORWARD "
#define NAME_BACKWARD "BACK    "
#define NAME_PWM "PWM="
#define NAME_SPEED "SPEED="
#define NUMBER_CLEAR "    "

#define DISPLAY_IDX_DIRECTION 0
#define DISPLAY_IDX_PWM 8
#define DISPLAY_IDX_PWM_VALUE 12
#define DISPLAY_IDX_SPEED 0
#define DISPLAY_IDX_SPEED_VALUE 6

uint8_t motorPhases[PHASE_NUMBER] = {PHASE_1, PHASE_2, PHASE_3, PHASE_4};

uint16_t counter = 0;
uint8_t direction = 0;
uint8_t phaseIdx = 0;

uint8_t pwm = 100;
uint16_t speed = 100;

inline void setupDisplay();

inline void displayDirection();

inline void displayPWM();

inline void displaySpeed();

CY_ISR(timer_isr_interrupt)
{
    if (speed > 0)
    {
        if (counter >= (1000 / (speed * 5)))
        {
            counter = 0;
        }
        
        if (counter == 0)
        {
            if (direction == DIR_FORWARD)
            {
                if (phaseIdx < 0 || phaseIdx >= PHASE_NUMBER)
                {
                    phaseIdx = 0;
                }
                Control_Reg_Write(motorPhases[phaseIdx]);
                phaseIdx++;
            }
            else if (direction == DIR_BACKWARD)
            {
                if (phaseIdx < 0 || phaseIdx >= PHASE_NUMBER)
                {
                    phaseIdx = PHASE_NUMBER - 1;
                }
                Control_Reg_Write(motorPhases[phaseIdx]);
                phaseIdx--;
            }
            else if (direction == DIR_STOP)
            {
                Control_Reg_Write(STOP);
            }
        }
        
        counter++;
    }
    else
    {
        Control_Reg_Write(STOP);
    }
    
    Timer_Counter_ClearInterrupt(Timer_Counter_INTR_MASK_TC);
}

CY_ISR(button_inc_isr_interrupt)
{
    speed += 10;
    if (speed < 0 || speed > 100)
    {
        speed = 100;
    }
    displaySpeed();
    
    Button_inc_ClearInterrupt();
}

CY_ISR(button_dec_isr_interrupt)
{
    speed -= 10;
    if (speed < 0 || speed > 100)
    {
        speed = 0;
    }
    displaySpeed();
    
    Button_dec_ClearInterrupt();
}

CY_ISR(button_direction_isr_interrupt)
{
    direction++;
    if (direction > 2)
    {
        direction = 0;
    }
    displayDirection();
    
    Button_direction_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Timer_Counter_Start();
    PWM_Start();
    timer_isr_StartEx(timer_isr_interrupt);
    button_inc_isr_StartEx(button_inc_isr_interrupt);
    button_dec_isr_StartEx(button_dec_isr_interrupt);
    button_direction_isr_StartEx(button_direction_isr_interrupt);
    
    QuadDec_Start();
    QuadDec_SetCounter(pwm);
    
    setupDisplay();
    
    for(;;)
    {
        /* Step motor rotation is executed in timer_isr_interrupt */
        
        if (QuadDec_GetCounter() > 10)
        {
            QuadDec_SetCounter(10);
        }
        if (QuadDec_GetCounter() < 2)
        {
            QuadDec_SetCounter(2);
        }
        pwm = QuadDec_GetCounter() * 10;
        PWM_WriteCompare(pwm * PWM_PERIOD_REG / 100);
        displayPWM();
        
        CyDelay(50);
    }
}

inline void setupDisplay()
{
    LCD_Char_Start();
    LCD_Char_ClearDisplay();
    
    LCD_Char_Position(0, DISPLAY_IDX_PWM);
    LCD_Char_PrintString(NAME_PWM);
    LCD_Char_Position(1, DISPLAY_IDX_SPEED);
    LCD_Char_PrintString(NAME_SPEED);
    
    displayDirection();
    displayPWM();
    displaySpeed();
}

inline void displayDirection()
{
    LCD_Char_Position(0, DISPLAY_IDX_DIRECTION);
    if (direction == DIR_FORWARD)
    {
        LCD_Char_PrintString(NAME_FORWARD);
    }
    else if (direction == DIR_BACKWARD)
    {
        LCD_Char_PrintString(NAME_BACKWARD);
    }
    else if (direction == DIR_STOP)
    {
        LCD_Char_PrintString(NAME_STOP);
    }
}

inline void displayPWM()
{
    LCD_Char_Position(0, DISPLAY_IDX_PWM_VALUE);
    LCD_Char_PrintString(NUMBER_CLEAR);
    LCD_Char_Position(0, DISPLAY_IDX_PWM_VALUE);
    LCD_Char_PrintDecUint16(pwm);
    LCD_Char_PutChar('%');
}

inline void displaySpeed()
{
    LCD_Char_Position(1, DISPLAY_IDX_SPEED_VALUE);
    LCD_Char_PrintString(NUMBER_CLEAR);
    LCD_Char_Position(1, DISPLAY_IDX_SPEED_VALUE);
    LCD_Char_PrintDecUint16(speed);
}
