/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    UC_8410A.h

    Headers for UC-8410A.
    
    2014-08-11	Sun Lee.			Create it.
*/

#ifndef _MODEL_H
#define _MODEL_H

#define	Update_BIOS_Ver	                1			
const char __weak BIOS_version_string[] = "2.0.0S06";  

#define CONFIG_SYS_MEMTEST_RESERVED			(8 * 1024 * 1024)
#define RTC_DS1374					1


/*********************************************
 *	GPIO DEFINE
 *********************************************/
#define PIO_LED_PROGRAM1				16	//GPIO1_16
#define PIO_LED_READY					18	//GPIO1_18 
#define PIO_TPM_INT		  			19	//GPIO1_19
#define PIO_BEEPER                   			20	//GPIO1_20
#define PIO_SW_BUTTON                   		21	//GPIO1_21
#define PIO_BOARD_ID0					13	//GPIO2_13
#define PIO_BOARD_ID1					14	//GPIO2_14
#define PIO_BOARD_ID2					15	//GPIO2_15
#define PIO_SD_RESET					24	//GPIO2_24
#define PIO_LED_MP_0					9	//GPIO4_9
#define PIO_LED_MP_1					10	//GPIO4_10
#define PIO_LED_MP_2					11	//GPIO4_11
#define PIO_LED_MP_3					12	//GPIO4_12
#define PIO_LED_MP_4					13	//GPIO4_13
#define PIO_LED_CEL_1					14	//GPIO4_14
#define PIO_LED_CEL_2					15	//GPIO4_15
#define PIO_LED_CEL_3					16	//GPIO4_16
#define PIO_LED_CEL_4					17	//GPIO4_17
#define PIO_LED_CEL_5					18	//GPIO4_18
#define PIO_LED_PROGRAM2				19	//GPIO4_19
#define PIO_LED_DIA_1					20	//GPIO4_20
#define PIO_LED_DIA_2					21	//GPIO4_21
#define PIO_LED_DIA_3					22	//GPIO4_22
#define PIO_MPE_POWER					27	//GPIO4_27
#define PIO_MPE_RST					28	//GPIO4_26

#endif //_MODEL_H

