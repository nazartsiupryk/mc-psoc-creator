/*******************************************************************************
* File Name: Joystick_X.h  
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

#if !defined(CY_PINS_Joystick_X_ALIASES_H) /* Pins Joystick_X_ALIASES_H */
#define CY_PINS_Joystick_X_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Joystick_X_0			(Joystick_X__0__PC)
#define Joystick_X_0_PS		(Joystick_X__0__PS)
#define Joystick_X_0_PC		(Joystick_X__0__PC)
#define Joystick_X_0_DR		(Joystick_X__0__DR)
#define Joystick_X_0_SHIFT	(Joystick_X__0__SHIFT)
#define Joystick_X_0_INTR	((uint16)((uint16)0x0003u << (Joystick_X__0__SHIFT*2u)))

#define Joystick_X_INTR_ALL	 ((uint16)(Joystick_X_0_INTR))


#endif /* End Pins Joystick_X_ALIASES_H */


/* [] END OF FILE */
