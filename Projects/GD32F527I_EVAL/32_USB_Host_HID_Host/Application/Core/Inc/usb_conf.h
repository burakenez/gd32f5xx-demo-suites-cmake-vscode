/*!
    \file    usb_conf.h
    \brief   general low level driver configuration

    \version 2024-12-27, V1.2.0, demo for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef __USB_CONF_H
#define __USB_CONF_H

#include "gd32f5xx.h"
#include "gd32f527i_eval.h" 
#include "gd32f527i_lcd_eval.h"

/* USB Core and PHY interface configuration */

#ifdef USE_USB_FS
    #define USB_FS_CORE
#endif /* USE_USB_FS */

#ifdef USE_USB_HS
    #define USB_HS_CORE
#endif /* USE_USB_HS */

/* USB FIFO size config */
#ifdef USB_FS_CORE
    #define USB_RX_FIFO_FS_SIZE                            128
    #define USB_HTX_NPFIFO_FS_SIZE                         96
    #define USB_HTX_PFIFO_FS_SIZE                          96

    #define USBFS_SOF_OUTPUT                               0
    #define USBFS_LOW_POWER                                0
#endif /* USB_FS_CORE */

#ifdef USB_HS_CORE
    #define USB_RX_FIFO_HS_SIZE                            512
    #define USB_HTX_NPFIFO_HS_SIZE                         256
    #define USB_HTX_PFIFO_HS_SIZE                          256

    #ifdef USE_ULPI_PHY
        #define USB_ULPI_PHY_ENABLED
    #endif

    #ifdef USE_EMBEDDED_PHY
        #define USB_EMBEDDED_PHY_ENABLED
    #endif

//    #define USB_HS_INTERNAL_DMA_ENABLED

    #define USBHS_SOF_OUTPUT                               0
    #define USBHS_LOW_POWER                                0
#endif /* USB_HS_CORE */

#define USE_HOST_MODE
//#define USE_DEVICE_MODE
//#define USE_OTG_MODE

#ifndef USB_FS_CORE
    #ifndef USB_HS_CORE
        #error "USB_HS_CORE or USB_FS_CORE should be defined"
    #endif
#endif

#ifndef USE_DEVICE_MODE
    #ifndef USE_HOST_MODE
        #error "USE_DEVICE_MODE or USE_HOST_MODE should be defined"
    #endif
#endif

#ifndef USE_USB_HS
    #ifndef USE_USB_FS
        #error "USE_USB_HS or USE_USB_FS should be defined"
    #endif
#endif

/* In Cortex-M33 Core, all variables and data structures during the USB transaction 
   process should be 4-bytes aligned */
#if defined (__GNUC__)         /* GNU Compiler */
    #define __ALIGN_END __attribute__ ((aligned (4)))
    #define __ALIGN_BEGIN
#else
    #define __ALIGN_END

    #if defined (__CC_ARM)     /* ARM Compiler */
        #define __ALIGN_BEGIN __align(4)
    #elif defined (__ICCARM__) /* IAR Compiler */
        #define __ALIGN_BEGIN
    #elif defined (__TASKING__)/* TASKING Compiler */
        #define __ALIGN_BEGIN __align(4)
    #endif /* __CC_ARM */
#endif /* __GNUC__ */

/* __packed keyword used to decrease the data type alignment to 1-byte */
#if defined (__GNUC__)       /* GNU Compiler */
    #ifndef __packed
        #define __packed __unaligned
    #endif
#elif defined (__TASKING__)    /* TASKING Compiler */
    #define __packed __unaligned
#endif /* __GNUC__ */

#endif /* __USB_CONF_H */
