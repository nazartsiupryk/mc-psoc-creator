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
#define GREEN 0b100
#define NO_COLOR 0b000
#define CLEAR_LINE "             "

#define X_AXIS 0
#define Y_AXIS 1

int8_t angleX = 0;
int8_t angleY = 0;
int8_t newAngle = 0;

uint8_t color = NO_COLOR;

void printAngle(const uint8_t row, const uint8_t col, const int angle);

int8_t getJoystickAngle(const uint8_t axis);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    ADC_SAR_Seq_Start();
    ADC_SAR_Seq_StartConvert();
    
    LCD_Char_Start();
    LCD_Char_ClearDisplay();
    
    LCD_Char_Position(0, 0);
    LCD_Char_PrintString("X: ");
    LCD_Char_Position(1, 0);
    LCD_Char_PrintString("Y: ");
    
    for(;;)
    {
        newAngle = getJoystickAngle(X_AXIS);
        if (angleX != newAngle)
        {
            angleX = newAngle;
            color |= RED;
            Control_Reg_Write(color);
            
            printAngle(0, 3, angleX);
        }
        else
        {
            color &= !RED;
        }
        
        newAngle = getJoystickAngle(Y_AXIS);
        if (angleY != newAngle)
        {
            angleY = newAngle;
            color |= GREEN;
            
            printAngle(1, 3, angleY);
        }
        else
        {
            color &= !GREEN;
        }
        
        Control_Reg_Write(color);
        
        ADC_SAR_Seq_Sleep();
        CyDelay(100);
        ADC_SAR_Seq_Wakeup();
    }
}

int8_t getJoystickAngle(const uint8_t axis)
{
    return ((float)(ADC_SAR_Seq_GetResult16(axis) & 0x7FF) / 0x7FF) * 90 - 45;
}

void printAngle(const uint8_t row, const uint8_t col, const int angle)
{
    LCD_Char_Position(row, col);
    LCD_Char_PrintString(CLEAR_LINE);
    LCD_Char_Position(row, col);
    
    if (angle < 0)
    {
        LCD_Char_PutChar('-');
        LCD_Char_Position(row, col + 1);
        LCD_Char_PrintDecUint16(0 - angle);
    }
    else
    {
        LCD_Char_PrintDecUint16(angle);
    }
}
