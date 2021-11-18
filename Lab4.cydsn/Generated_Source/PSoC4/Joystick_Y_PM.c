/*******************************************************************************
* File Name: Joystick_Y.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Joystick_Y.h"

static Joystick_Y_BACKUP_STRUCT  Joystick_Y_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Joystick_Y_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet Joystick_Y_SUT.c usage_Joystick_Y_Sleep_Wakeup
*******************************************************************************/
void Joystick_Y_Sleep(void)
{
    #if defined(Joystick_Y__PC)
        Joystick_Y_backup.pcState = Joystick_Y_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Joystick_Y_backup.usbState = Joystick_Y_CR1_REG;
            Joystick_Y_USB_POWER_REG |= Joystick_Y_USBIO_ENTER_SLEEP;
            Joystick_Y_CR1_REG &= Joystick_Y_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Joystick_Y__SIO)
        Joystick_Y_backup.sioState = Joystick_Y_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Joystick_Y_SIO_REG &= (uint32)(~Joystick_Y_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Joystick_Y_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to Joystick_Y_Sleep() for an example usage.
*******************************************************************************/
void Joystick_Y_Wakeup(void)
{
    #if defined(Joystick_Y__PC)
        Joystick_Y_PC = Joystick_Y_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Joystick_Y_USB_POWER_REG &= Joystick_Y_USBIO_EXIT_SLEEP_PH1;
            Joystick_Y_CR1_REG = Joystick_Y_backup.usbState;
            Joystick_Y_USB_POWER_REG &= Joystick_Y_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Joystick_Y__SIO)
        Joystick_Y_SIO_REG = Joystick_Y_backup.sioState;
    #endif
}


/* [] END OF FILE */
