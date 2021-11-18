/*******************************************************************************
* File Name: Input_Buttons.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "Input_Buttons.h"

#if !defined(Input_Buttons_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: Input_Buttons_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 Input_Buttons_Read(void) 
{ 
    return Input_Buttons_Status;
}


/*******************************************************************************
* Function Name: Input_Buttons_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Input_Buttons_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Input_Buttons_Status_Aux_Ctrl |= Input_Buttons_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Input_Buttons_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void Input_Buttons_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    Input_Buttons_Status_Aux_Ctrl &= (uint8)(~Input_Buttons_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Input_Buttons_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void Input_Buttons_WriteMask(uint8 mask) 
{
    #if(Input_Buttons_INPUTS < 8u)
    	mask &= ((uint8)(1u << Input_Buttons_INPUTS) - 1u);
	#endif /* End Input_Buttons_INPUTS < 8u */
    Input_Buttons_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: Input_Buttons_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 Input_Buttons_ReadMask(void) 
{
    return Input_Buttons_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
