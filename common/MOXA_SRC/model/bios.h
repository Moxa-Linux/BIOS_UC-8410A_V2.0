/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    bios.h

    Headers for BIOS function.
    
    2014-08-11	Sun Lee.			Create it.
*/

#ifndef _BIOS_H
#define _BIOS_H
/*------------------------------------------------------ Macro / Define -----------------------------*/
#define DBG

// DiagTest return value 
#define DIAG_OK		0
#define DIAG_FAIL	1
#define DIAG_ESC	2


#define Freescale_MODEL_MAX_NUM 1


#define UART_BUF_MAX_SIZE						256 
#define GENERAL_UART_BUF_MAX_SIZE						2048
#define UART_MAX_AMOUNT                     	18

#define GENERAL_UART_MAX_AMOUNT                      	2		// MAX PGC UART number



/* Define For Memory Base Address */
#define SDRAM_REMAP_BASE                  		0x80000000
#define SDRAM_UART_TX_BASE(x)               (SDRAM_REMAP_BASE+ (x * UART_BUF_MAX_SIZE))
#define SDRAM_UART_RX_BASE(x)               (SDRAM_UART_TX_BASE(UART_MAX_AMOUNT) + (x * UART_BUF_MAX_SIZE))


#define SDRAM_GENERAL_UART_TX_BASE(x) (SDRAM_UART_RX_BASE(GENERAL_UART_MAX_AMOUNT) + (x * GENERAL_UART_BUF_MAX_SIZE))
#define SDRAM_GENERAL_UART_RX_BASE(x) (SDRAM_GENERAL_UART_TX_BASE(GENERAL_UART_MAX_AMOUNT) + (x * GENERAL_UART_BUF_MAX_SIZE))

/*------------------------------------------------------ Structure ----------------------------------*/
struct _SysModelInfo_{
	unsigned char	hw_id;	/* hw id */
	unsigned long	hw_exid; /* hw external id */
	unsigned short	burn_id;/* burn-in id */
	unsigned char	support_flag;	/* interface */
	unsigned char	port;   /* uart max num */
	unsigned char	lan;    /* lan num */
	unsigned char	wlan;	/* wlan num */
	unsigned int	pci;    /* support pci */
	unsigned int	smcflash0; /* SMC_0 Flash type*/
	unsigned int	smcflash1; /* SMC_2 Flash */
	unsigned long	serial;
	unsigned char	modelName[32];
};
typedef struct _SysModelInfo_ _SysModelInfo;

/*------------------------------------------------------ Extern / Function Declaration -----------------*/

#endif //_BIOS_H

