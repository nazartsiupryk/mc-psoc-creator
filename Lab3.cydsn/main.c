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

#define INITIAL_DELAY 3000

#define LIGHTS_BAR "RED YELLOW GREEN"
#define SET_RED    "SET RED TIME:   "
#define SET_YELLOW "SET YELLOW TIME:"
#define SET_GREEN  "SET GREEN TIME: "
#define EMPTY_LINE "                "
#define TIME       "TIME=           "

#define POSITION_RED 0
#define POSITION_YELLOW 4
#define POSITION_GREEN 11
#define POSITITON_SET_TIME 5

uint8_t counter = 0;
CYBIT algorithm = 0;

uint8_t redTime;
uint8_t yellowTime;
uint8_t greenTime;

uint8_t displayMode = 0;
CYBIT modeHasChanged = 0;

struct DisplayCounter
{
    uint8_t position, counter;
};
struct DisplayCounter displayCounter = {0, 0};

inline void runAlgorithm1();
inline void runAlgorithm2();
inline void runAlgorithmGreenPart(const uint8_t* pShift);
inline void runAlgorithmRedPart(const uint8_t* pShift);

CY_ISR(timer_isr_interrupt)
{
    if (counter >= (greenTime + redTime + 2 * yellowTime)) 
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
    counter = 0;
    
    Button_ClearInterrupt();
}

CY_ISR(button_encoder_isr_interrupt)
{
    if (displayMode >= 3)
    {
        displayMode = 0;
    }
    else
    {
        displayMode++;
    }
    modeHasChanged = 1;
    
    Button_Encoder_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    redTime = 8;
    yellowTime = 2;
    greenTime = 8;
    
    displayCounter.counter = redTime;
    displayCounter.position = POSITION_RED;
    
    Timer_Counter_Start();
    timer_isr_StartEx(timer_isr_interrupt);
    button_isr_StartEx(button_isr_interrupt);
    button_encoder_isr_StartEx(button_encoder_isr_interrupt);
    
    QuadDec_Start();
    
    LCD_Char_Start();
    LCD_Char_ClearDisplay();
    
    LCD_Char_Position(0, 5);
    LCD_Char_PrintString("Author");
    LCD_Char_Position(1, 2);
    LCD_Char_PrintString("Denys Shutka");
    CyDelay(INITIAL_DELAY);
    LCD_Char_ClearDisplay();
    
    LCD_Char_Position(0, 0);
    LCD_Char_PrintString(LIGHTS_BAR);
    
    uint8_t currentCounter = displayCounter.counter;
    uint8_t currentPosition = displayCounter.position;
    
    for(;;)
    {
        /* LED algorithm is executed in timer_isr_interrupt */
        
        /* DISPLAY MODES:
         * 0 is "INIT": display remaining time of lighting 
         * 1 is "SET RED": set time for red diode
         * 2 is "SET YELLOW": set time for yellow diode
         * 3 is "SET GREEN": set time for green diode
         */
        
        if (QuadDec_GetCounter() > 20)
        {
            QuadDec_SetCounter(20);
        }
        if (QuadDec_GetCounter() < 1)
        {
            QuadDec_SetCounter(1);
        }
        
        if (modeHasChanged)
        {
            LCD_Char_ClearDisplay();
            if (displayMode == 0)
            {
                LCD_Char_Position(0, 0);
                LCD_Char_PrintString(LIGHTS_BAR);
            }
            else if (displayMode == 1)
            {
                LCD_Char_Position(0, 0);
                LCD_Char_PrintString(SET_RED);
                LCD_Char_Position(1, 0);
                LCD_Char_PrintString(TIME);
                QuadDec_SetCounter(redTime);
            }
            else if (displayMode == 2)
            {
                LCD_Char_Position(0, 0);
                LCD_Char_PrintString(SET_YELLOW);
                LCD_Char_Position(1, 0);
                LCD_Char_PrintString(TIME);
                QuadDec_SetCounter(yellowTime);
            }
            else if (displayMode == 3)
            {
                LCD_Char_Position(0, 0);
                LCD_Char_PrintString(SET_GREEN);
                LCD_Char_Position(1, 0);
                LCD_Char_PrintString(TIME);
                QuadDec_SetCounter(greenTime);
            }
            
            modeHasChanged = 0;
        }
        
        if (displayMode == 0)
        {
            if (currentPosition != displayCounter.position)
            {
                LCD_Char_Position(1, 0);
                LCD_Char_PrintString(EMPTY_LINE);
                currentCounter = displayCounter.counter;
                currentPosition = displayCounter.position;
            }
            currentCounter = displayCounter.counter;
            
            LCD_Char_Position(1, currentPosition);
            if (currentCounter < 10)
            {
                LCD_Char_PutChar('0');
                LCD_Char_Position(1, currentPosition + 1);
            }
            LCD_Char_PrintDecUint16(currentCounter);
        }
        else if (displayMode == 1)
        {
            LCD_Char_Position(1, POSITITON_SET_TIME);
            if (QuadDec_GetCounter() < 10)
            {
                LCD_Char_PutChar('0');
                LCD_Char_Position(1, POSITITON_SET_TIME + 1);
            }
            LCD_Char_PrintDecUint16(QuadDec_GetCounter());
            
            redTime = QuadDec_GetCounter();
        }
        else if (displayMode == 2)
        {
            LCD_Char_Position(1, POSITITON_SET_TIME);
            if (QuadDec_GetCounter() < 10)
            {
                LCD_Char_PutChar('0');
                LCD_Char_Position(1, POSITITON_SET_TIME + 1);
            }
            LCD_Char_PrintDecUint16(QuadDec_GetCounter());
            
            yellowTime = QuadDec_GetCounter();
        }
        else if (displayMode == 3)
        {
            LCD_Char_Position(1, POSITITON_SET_TIME);
            if (QuadDec_GetCounter() < 10)
            {
                LCD_Char_PutChar('0');
                LCD_Char_Position(1, POSITITON_SET_TIME + 1);
            }
            LCD_Char_PrintDecUint16(QuadDec_GetCounter());
            
            greenTime = QuadDec_GetCounter();
        }
    }
}

inline void runAlgorithmGreenPart(const uint8_t* pShift)
{
    if (greenTime > 4)
    {
        if (counter < *pShift + (greenTime - 4))
        {
            Control_Reg_Write(GREEN);
            displayCounter.position = POSITION_GREEN;
            displayCounter.counter = greenTime - (counter - *pShift);
        }
        else if (counter < *pShift + (greenTime - 3))
        {
            Control_Reg_Write(NO_COLOR);
            displayCounter.position = POSITION_GREEN;
            displayCounter.counter = greenTime - (counter - *pShift);
        }
        else if (counter < *pShift + (greenTime - 2))
        {
            Control_Reg_Write(GREEN);
            displayCounter.position = POSITION_GREEN;
            displayCounter.counter = greenTime - (counter - *pShift);
        }
        else if (counter < *pShift + (greenTime - 1))
        {
            Control_Reg_Write(NO_COLOR);
            displayCounter.position = POSITION_GREEN;
            displayCounter.counter = greenTime - (counter - *pShift);
        }
        else if (counter < *pShift + greenTime)
        {
            Control_Reg_Write(GREEN);
            displayCounter.position = POSITION_GREEN;
            displayCounter.counter = greenTime - (counter - *pShift);
        }
        else if (counter < *pShift + greenTime + yellowTime)
        {
            Control_Reg_Write(YELLOW);
            displayCounter.position = POSITION_YELLOW;
            displayCounter.counter = yellowTime - (counter - *pShift - greenTime);
        }
    }
    else
    {
        if (counter < *pShift + greenTime)
        {
            Control_Reg_Write(GREEN);
            displayCounter.position = POSITION_GREEN;
            displayCounter.counter = greenTime - (counter - *pShift);
        }
        else if (counter < *pShift + (greenTime + yellowTime))
        {
            Control_Reg_Write(YELLOW);
            displayCounter.position = POSITION_YELLOW;
            displayCounter.counter = yellowTime - (counter - *pShift - greenTime);
        }
    }
    
}

inline void runAlgorithmRedPart(const uint8_t* pShift)
{
    if (counter < *pShift + redTime)
    {
        Control_Reg_Write(RED);
        displayCounter.position = POSITION_RED;
        displayCounter.counter = redTime - (counter - *pShift);
    }
    else if (counter < *pShift + (redTime + yellowTime))
    {
        Control_Reg_Write(YELLOW);
        displayCounter.position = POSITION_YELLOW;
        displayCounter.counter = yellowTime - (counter - *pShift - redTime);
    }
}

inline void runAlgorithm1()
{
    uint8 shift;
    if (counter < redTime + yellowTime)
    {
        shift = 0;
        runAlgorithmRedPart(&shift);
    }
    else 
    {
        shift = redTime + yellowTime;
        runAlgorithmGreenPart(&shift);
    }
}

inline void runAlgorithm2()
{
    uint8 shift;
    if (counter < greenTime + yellowTime)
    {
        shift = 0;
        runAlgorithmGreenPart(&shift);
    }
    else 
    {
        shift = greenTime + yellowTime;
        runAlgorithmRedPart(&shift);
    }
}
