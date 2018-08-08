/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    led.h

    Definitions of Freescale gpio control.
    
    2015-08-21	Sun Lee	
*/

#ifndef _LED_H
#define _LED_H

#define FSL_GPIO1_GPDIR_BASE	0x2300000 //GPIO1 direction register
#define FSL_GPIO1_GPODR_BASE	0x2300004 //GPIO1 open drain register	
#define FSL_GPIO1_GPDAT_BASE	0x2300008 //GPIO1 data register
#define FSL_GPIO1_GPIER_BASE	0x230000c //GPIO1 interrupt event register
#define FSL_GPIO1_GPIMR_BASE	0x2300010 //GPIO1 interrupt mask register
#define FSL_GPIO1_GPICR_BASE	0x2300014 //GPIO1 interrupt control register
#define FSL_GPIO1_GPIBE_BASE	0x2300018 //GPIO1 Input Buffer Enable Register

#define FSL_GPIO2_GPDIR_BASE	0x2310000 //GPIO2 direction register
#define FSL_GPIO2_GPODR_BASE	0x2310004 //GPIO2 open drain register	
#define FSL_GPIO2_GPDAT_BASE	0x2310008 //GPIO2 data register
#define FSL_GPIO2_GPIER_BASE	0x231000c //GPIO2 interrupt event register
#define FSL_GPIO2_GPIMR_BASE	0x2310010 //GPIO2 interrupt mask register
#define FSL_GPIO2_GPICR_BASE	0x2310014 //GPIO2 interrupt control register
#define FSL_GPIO2_GPIBE_BASE	0x2310018 //GPIO2 Input Buffer Enable Register

#define FSL_GPIO3_GPDIR_BASE	0x2320000 //GPIO3 direction register
#define FSL_GPIO3_GPODR_BASE	0x2320004 //GPIO3 open drain register	
#define FSL_GPIO3_GPDAT_BASE	0x2320008 //GPIO3 data register
#define FSL_GPIO3_GPIER_BASE	0x232000c //GPIO3 interrupt event register
#define FSL_GPIO3_GPIMR_BASE	0x2320010 //GPIO3 interrupt mask register
#define FSL_GPIO3_GPICR_BASE	0x2320014 //GPIO3 interrupt control register
#define FSL_GPIO3_GPIBE_BASE	0x2320018 //GPIO3 Input Buffer Enable Register

#define FSL_GPIO4_GPDIR_BASE	0x2330000 //GPIO4 direction register
#define FSL_GPIO4_GPODR_BASE	0x2330004 //GPIO4 open drain register	
#define FSL_GPIO4_GPDAT_BASE	0x2330008 //GPIO4 data register
#define FSL_GPIO4_GPIER_BASE	0x233000c //GPIO4 interrupt event register
#define FSL_GPIO4_GPIMR_BASE	0x2330010 //GPIO4 interrupt mask register
#define FSL_GPIO4_GPICR_BASE	0x2330014 //GPIO4 interrupt control register
#define FSL_GPIO4_GPIBE_BASE	0x2330018 //GPIO4 Input Buffer Enable Register

#define CPLD_DI_BASE		0x78000010 //CPLD DI~3 register
#define CPLD_DO_BASE		0x78000020 //CPLD DO~3 register
#define CPLD_GP0_BASE		0x78000040 //CPLD GPO~3 register


void FSL_gpio_direction_output(UINT8 port,UINT8 gpio, UINT8 value);
UINT8 FSL_gpio_direction_input(UINT8 port,UINT8 gpio);
//#ifdef	LED_MP
//int LED_MPTEST(UINT8 led);
//#endif	// LED_MP
void CPLD_DO(UINT8 gpio, UINT8 value);
void CPLD_DO_FOR_PCI104(UINT8 gpio, UINT8 value);
UINT8 CPLD_DI(UINT8 gpio);

#endif	//_LED_H
