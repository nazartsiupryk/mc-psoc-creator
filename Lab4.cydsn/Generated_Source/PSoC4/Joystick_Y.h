/*******************************************************************************
* File Name: Joystick_Y.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Joystick_Y_H) /* Pins Joystick_Y_H */
#define CY_PINS_Joystick_Y_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Joystick_Y_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Joystick_Y_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Joystick_Y_Read(void);
void    Joystick_Y_Write(uint8 value);
uint8   Joystick_Y_ReadDataReg(void);
#if defined(Joystick_Y__PC) || (CY_PSOC4_4200L) 
    void    Joystick_Y_SetDriveMode(uint8 mode);
#endif
void    Joystick_Y_SetInterruptMode(uint16 position, uint16 mode);
uint8   Joystick_Y_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Joystick_Y_Sleep(void); 
void Joystick_Y_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Joystick_Y__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Joystick_Y_DRIVE_MODE_BITS        (3)
    #define Joystick_Y_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Joystick_Y_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Joystick_Y_SetDriveMode() function.
         *  @{
         */
        #define Joystick_Y_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Joystick_Y_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Joystick_Y_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Joystick_Y_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Joystick_Y_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Joystick_Y_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Joystick_Y_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Joystick_Y_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Joystick_Y_MASK               Joystick_Y__MASK
#define Joystick_Y_SHIFT              Joystick_Y__SHIFT
#define Joystick_Y_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Joystick_Y_SetInterruptMode() function.
     *  @{
     */
        #define Joystick_Y_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Joystick_Y_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Joystick_Y_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Joystick_Y_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Joystick_Y__SIO)
    #define Joystick_Y_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Joystick_Y__PC) && (CY_PSOC4_4200L)
    #define Joystick_Y_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Joystick_Y_USBIO_DISABLE              ((uint32)(~Joystick_Y_USBIO_ENABLE))
    #define Joystick_Y_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Joystick_Y_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Joystick_Y_USBIO_ENTER_SLEEP          ((uint32)((1u << Joystick_Y_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Joystick_Y_USBIO_SUSPEND_DEL_SHIFT)))
    #define Joystick_Y_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Joystick_Y_USBIO_SUSPEND_SHIFT)))
    #define Joystick_Y_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Joystick_Y_USBIO_SUSPEND_DEL_SHIFT)))
    #define Joystick_Y_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Joystick_Y__PC)
    /* Port Configuration */
    #define Joystick_Y_PC                 (* (reg32 *) Joystick_Y__PC)
#endif
/* Pin State */
#define Joystick_Y_PS                     (* (reg32 *) Joystick_Y__PS)
/* Data Register */
#define Joystick_Y_DR                     (* (reg32 *) Joystick_Y__DR)
/* Input Buffer Disable Override */
#define Joystick_Y_INP_DIS                (* (reg32 *) Joystick_Y__PC2)

/* Interrupt configuration Registers */
#define Joystick_Y_INTCFG                 (* (reg32 *) Joystick_Y__INTCFG)
#define Joystick_Y_INTSTAT                (* (reg32 *) Joystick_Y__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Joystick_Y_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Joystick_Y__SIO)
    #define Joystick_Y_SIO_REG            (* (reg32 *) Joystick_Y__SIO)
#endif /* (Joystick_Y__SIO_CFG) */

/* USBIO registers */
#if !defined(Joystick_Y__PC) && (CY_PSOC4_4200L)
    #define Joystick_Y_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Joystick_Y_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Joystick_Y_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Joystick_Y_DRIVE_MODE_SHIFT       (0x00u)
#define Joystick_Y_DRIVE_MODE_MASK        (0x07u << Joystick_Y_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Joystick_Y_H */


/* [] END OF FILE */
