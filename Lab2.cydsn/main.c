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

#define RED 0b001
#define YELLOW 0b010
#define GREEN 0b100
#define NO_COLOR 0b000

#define INTERVAL 20

uint8 counter = 0;
CYBIT algorithm = 0;

inline void runAlgorithm1();
inline void runAlgorithm2();

CY_ISR(timer_isr_interrupt)
{
    if (counter >= INTERVAL) 
    {
        counter = 0;
    } 
    
    if (algorithm)
    {
        runAlgorithm2();
    }
    else
    {
        runAlgorithm1();
    }
    
    counter++;
    Timer_Counter_ClearInterrupt(Timer_Counter_INTR_MASK_TC);
}

CY_ISR(button_isr_interrupt)
{
    algorithm = algorithm ? 0 : 1;
    
    Button_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Timer_Counter_Start();
    timer_isr_StartEx(timer_isr_interrupt);
    button_isr_StartEx(button_isr_interrupt);

    for(;;)
    {
        /* Main code is in timer_isr_interrupt */
    }
}

inline void runAlgorithm1()
{
    if (counter < 8)
    {
        Control_Reg_Write(RED);
    }
    else if (counter < 10)
    {
        Control_Reg_Write(YELLOW);
    }
    else if (counter < 14)
    {
        Control_Reg_Write(GREEN);
    }
    else if (counter < 15)
    {
        Control_Reg_Write(NO_COLOR);
    }
    else if (counter < 16)
    {
        Control_Reg_Write(GREEN);
    }
    else if (counter < 17)
    {
        Control_Reg_Write(NO_COLOR);
    }
    else if (counter < 18)
    {
        Control_Reg_Write(GREEN);
    }
    else if (counter < 20)
    {
        Control_Reg_Write(YELLOW);
    }
    else
    {
        Control_Reg_Write(NO_COLOR);
    }
}

inline void runAlgorithm2()
{
    if (counter < 4)
    {
        Control_Reg_Write(GREEN);
    }
    else if (counter < 5)
    {
        Control_Reg_Write(NO_COLOR);
    }
    else if (counter < 6)
    {
        Control_Reg_Write(GREEN);
    }
    else if (counter < 7)
    {
        Control_Reg_Write(NO_COLOR);
    }
    else if (counter < 8)
    {
        Control_Reg_Write(GREEN);
    }
    else if (counter < 10)
    {
        Control_Reg_Write(YELLOW);
    }
    else if (counter < 18)
    {
        Control_Reg_Write(RED);
    }
    else if (counter < 20)
    {
        Control_Reg_Write(YELLOW);
    }
    else
    {
        Control_Reg_Write(NO_COLOR);
    }
}
