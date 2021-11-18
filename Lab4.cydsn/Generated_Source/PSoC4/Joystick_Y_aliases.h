/*******************************************************************************
* File Name: Joystick_Y.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Joystick_Y_ALIASES_H) /* Pins Joystick_Y_ALIASES_H */
#define CY_PINS_Joystick_Y_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Joystick_Y_0			(Joystick_Y__0__PC)
#define Joystick_Y_0_PS		(Joystick_Y__0__PS)
#define Joystick_Y_0_PC		(Joystick_Y__0__PC)
#define Joystick_Y_0_DR		(Joystick_Y__0__DR)
#define Joystick_Y_0_SHIFT	(Joystick_Y__0__SHIFT)
#define Joystick_Y_0_INTR	((uint16)((uint16)0x0003u << (Joystick_Y__0__SHIFT*2u)))

#define Joystick_Y_INTR_ALL	 ((uint16)(Joystick_Y_0_INTR))


#endif /* End Pins Joystick_Y_ALIASES_H */


/* [] END OF FILE */
