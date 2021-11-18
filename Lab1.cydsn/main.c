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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    uint8 registerValue;
    LED_Write(0);
    
    for(;;)
    {
        registerValue = Input_Buttons_Read();
        if (((registerValue | 1) == 0b00111) || (registerValue == 0b01101) 
            || ((registerValue | 0b01000) == 0b01110) || (registerValue == 0b10101) 
            || ((registerValue | 0b10000) == 0b10110) || (registerValue == 0b11100) || (registerValue == 0b00001)) 
        {
            LED_Write(1);
            CyDelay(100);
            LED_Write(0);
        }
    }
}

/* [] END OF FILE */
