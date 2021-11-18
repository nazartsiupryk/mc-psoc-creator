/*******************************************************************************
* File Name: Button_Encoder.c  
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
#include "Button_Encoder.h"

static Button_Encoder_BACKUP_STRUCT  Button_Encoder_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: Button_Encoder_Sleep
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
*  \snippet Button_Encoder_SUT.c usage_Button_Encoder_Sleep_Wakeup
*******************************************************************************/
void Button_Encoder_Sleep(void)
{
    #if defined(Button_Encoder__PC)
        Button_Encoder_backup.pcState = Button_Encoder_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            Button_Encoder_backup.usbState = Button_Encoder_CR1_REG;
            Button_Encoder_USB_POWER_REG |= Button_Encoder_USBIO_ENTER_SLEEP;
            Button_Encoder_CR1_REG &= Button_Encoder_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Button_Encoder__SIO)
        Button_Encoder_backup.sioState = Button_Encoder_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        Button_Encoder_SIO_REG &= (uint32)(~Button_Encoder_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: Button_Encoder_Wakeup
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
*  Refer to Button_Encoder_Sleep() for an example usage.
*******************************************************************************/
void Button_Encoder_Wakeup(void)
{
    #if defined(Button_Encoder__PC)
        Button_Encoder_PC = Button_Encoder_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            Button_Encoder_USB_POWER_REG &= Button_Encoder_USBIO_EXIT_SLEEP_PH1;
            Button_Encoder_CR1_REG = Button_Encoder_backup.usbState;
            Button_Encoder_USB_POWER_REG &= Button_Encoder_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(Button_Encoder__SIO)
        Button_Encoder_SIO_REG = Button_Encoder_backup.sioState;
    #endif
}


/* [] END OF FILE */
