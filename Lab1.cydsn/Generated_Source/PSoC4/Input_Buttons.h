/*******************************************************************************
* File Name: Input_Buttons.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_Input_Buttons_H) /* CY_STATUS_REG_Input_Buttons_H */
#define CY_STATUS_REG_Input_Buttons_H

#include "cyfitter.h"

#if ((CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC4) || \
     (CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5))
    #include "cytypes.h"
    #include "CyLib.h"
#else
    #include "syslib/cy_syslib.h"
#endif

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} Input_Buttons_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 Input_Buttons_Read(void) ;
void Input_Buttons_InterruptEnable(void) ;
void Input_Buttons_InterruptDisable(void) ;
void Input_Buttons_WriteMask(uint8 mask) ;
uint8 Input_Buttons_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define Input_Buttons_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define Input_Buttons_INPUTS              5


/***************************************
*             Registers
***************************************/

/* Status Register */
#define Input_Buttons_Status             (* (reg8 *) Input_Buttons_sts_sts_reg__STATUS_REG )
#define Input_Buttons_Status_PTR         (  (reg8 *) Input_Buttons_sts_sts_reg__STATUS_REG )
#define Input_Buttons_Status_Mask        (* (reg8 *) Input_Buttons_sts_sts_reg__MASK_REG )
#define Input_Buttons_Status_Aux_Ctrl    (* (reg8 *) Input_Buttons_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_Input_Buttons_H */


/* [] END OF FILE */
