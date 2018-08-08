/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    led.c

    This file includes functions of Freescale LED controller.
    The LED functions are also included in it.
    
    2015-08-25	Sun Lee
*/

#include <common.h>
#include <command.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <bios.h>
#include <model.h>
#include "../cmd_bios.h"
#include "moxa_console.h"
#include "moxa_lib.h"
#include "types.h"
#include "led.h"


void FSL_gpio_direction_output(UINT8 port,UINT8 gpio, UINT8 value)
{
	UINT32 reg_data0=0;
	
	switch(port){
		case 1:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 |= (BIT0 << (7-gpio));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (7-gpio));
				}else{
					reg_data0 &= ~(BIT0 << (7-gpio));
				}
				VPlong(FSL_GPIO1_GPDAT_BASE) = reg_data0;
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 |= (BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (15-gpio+8));
				}else{
					reg_data0 &= ~(BIT0 << (15-gpio+8));
				}				
				VPlong(FSL_GPIO1_GPDAT_BASE) = reg_data0;
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 |= (BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (23-gpio+16));
				}else{
					reg_data0 &= ~(BIT0 << (23-gpio+16));
				}
				VPlong(FSL_GPIO1_GPDAT_BASE) = reg_data0;				
			}else{			
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 |= (BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (31-gpio+24));
				}else{
					reg_data0 &= ~(BIT0 << (31-gpio+24));
				}
				VPlong(FSL_GPIO1_GPDAT_BASE) = reg_data0;
			}				
			
			break;
		
		case 2:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 |= (BIT0 << (7-gpio));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (7-gpio));
				}else{
					reg_data0 &= ~(BIT0 << (7-gpio));
				}
				VPlong(FSL_GPIO2_GPDAT_BASE) = reg_data0;
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 |= (BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (15-gpio+8));
				}else{
					reg_data0 &= ~(BIT0 << (15-gpio+8));
				}				
				VPlong(FSL_GPIO2_GPDAT_BASE) = reg_data0;
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 |= (BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (23-gpio+16));
				}else{
					reg_data0 &= ~(BIT0 << (23-gpio+16));
				}
				VPlong(FSL_GPIO2_GPDAT_BASE) = reg_data0;				
			}else{			
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 |= (BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (31-gpio+24));
				}else{
					reg_data0 &= ~(BIT0 << (31-gpio+24));
				}
				VPlong(FSL_GPIO2_GPDAT_BASE) = reg_data0;
			}				
			
			break;
		
		case 3:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 |= (BIT0 << (7-gpio));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (7-gpio));
				}else{
					reg_data0 &= ~(BIT0 << (7-gpio));
				}
				VPlong(FSL_GPIO3_GPDAT_BASE) = reg_data0;
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 |= (BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (15-gpio+8));
				}else{
					reg_data0 &= ~(BIT0 << (15-gpio+8));
				}				
				VPlong(FSL_GPIO3_GPDAT_BASE) = reg_data0;
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 |= (BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (23-gpio+16));
				}else{
					reg_data0 &= ~(BIT0 << (23-gpio+16));
				}
				VPlong(FSL_GPIO3_GPDAT_BASE) = reg_data0;				
			}else{			
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 |= (BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (31-gpio+24));
				}else{
					reg_data0 &= ~(BIT0 << (31-gpio+24));
				}
				VPlong(FSL_GPIO3_GPDAT_BASE) = reg_data0;
			}				
			break;
		
		case 4:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 |= (BIT0 << (7-gpio));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (7-gpio));
				}else{
					reg_data0 &= ~(BIT0 << (7-gpio));
				}
				VPlong(FSL_GPIO4_GPDAT_BASE) = reg_data0;
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 |= (BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (15-gpio+8));
				}else{
					reg_data0 &= ~(BIT0 << (15-gpio+8));
				}				
				VPlong(FSL_GPIO4_GPDAT_BASE) = reg_data0;
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 |= (BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (23-gpio+16));
				}else{
					reg_data0 &= ~(BIT0 << (23-gpio+16));
				}
				VPlong(FSL_GPIO4_GPDAT_BASE) = reg_data0;				
			}else{			
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 |= (BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				if(value){
					reg_data0 |= (BIT0 << (31-gpio+24));
				}else{
					reg_data0 &= ~(BIT0 << (31-gpio+24));
				}
				VPlong(FSL_GPIO4_GPDAT_BASE) = reg_data0;
			}				
			break;
		
		default:
			break;
		
	}
	
}


UINT8 FSL_gpio_direction_input(UINT8 port,UINT8 gpio)
{
	UINT32 reg_data0;
	
	switch(port){
		case 1:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (7-gpio));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				reg_data0 &= (BIT0 << (7-gpio));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				reg_data0 &= (BIT0 << (15-gpio+8));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				reg_data0 &= (BIT0 << (23-gpio+16));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else{			
				reg_data0 = VPlong(FSL_GPIO1_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO1_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO1_GPDAT_BASE);
				reg_data0 &= (BIT0 << (31-gpio+24));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}				
			
			break;
		
		case 2:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (7-gpio));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				reg_data0 &= (BIT0 << (7-gpio));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				reg_data0 &= (BIT0 << (15-gpio+8));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				reg_data0 &= (BIT0 << (23-gpio+16));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else{			
				reg_data0 = VPlong(FSL_GPIO2_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO2_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO2_GPDAT_BASE);
				reg_data0 &= (BIT0 << (31-gpio+24));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}				
			
			break;
		
		case 3:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (7-gpio));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				reg_data0 &= (BIT0 << (7-gpio));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				reg_data0 &= (BIT0 << (15-gpio+8));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				reg_data0 &= (BIT0 << (23-gpio+16));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else{			
				reg_data0 = VPlong(FSL_GPIO3_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO3_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO3_GPDAT_BASE);
				reg_data0 &= (BIT0 << (31-gpio+24));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}				
			break;
		
		case 4:
			if(gpio < 8){
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (7-gpio));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				reg_data0 &= (BIT0 << (7-gpio));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 16){
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (15-gpio+8));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				reg_data0 &= (BIT0 << (15-gpio+8));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else if(gpio < 24){
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (23-gpio+16));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				reg_data0 &= (BIT0 << (23-gpio+16));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}else{			
				reg_data0 = VPlong(FSL_GPIO4_GPDIR_BASE);
				reg_data0 &= ~(BIT0 << (31-gpio+24));				
				VPlong(FSL_GPIO4_GPDIR_BASE) = reg_data0;
				
				reg_data0 = VPlong(FSL_GPIO4_GPDAT_BASE);
				reg_data0 &= (BIT0 << (31-gpio+24));
				if(reg_data0 > 0){
					return 1;
				}else{
					return 0;
				}
			}				
			break;
		
		default:
	        return 0xff;
			break;
		
	}
	return 0xff;
}

void CPLD_DO(UINT8 gpio, UINT8 value)
{
	UINT32 reg_data0=0;
	
	reg_data0 = VPlong(CPLD_DO_BASE);
	if(value){
		reg_data0 |= (BIT0 << (7-gpio));
	}else{
		reg_data0 &= ~(BIT0 << (7-gpio));
	}
	VPlong(CPLD_DO_BASE) = reg_data0;
	udelay (100);
	
}

void CPLD_DO_FOR_PCI104(UINT8 gpio, UINT8 value)
{
	UINT32 reg_data0=0;
	
	reg_data0 = VPlong(CPLD_GP0_BASE);
	if(value){
		reg_data0 |= (BIT0 << (7-gpio));
	}else{
		reg_data0 &= ~(BIT0 << (7-gpio));
	}
	VPlong(CPLD_GP0_BASE) = reg_data0;
	udelay (100);
}


UINT8 CPLD_DI(UINT8 gpio)
{
	UINT32 reg_data0;
	
	reg_data0 = VPlong(CPLD_DI_BASE);
	reg_data0 &= (BIT0 << (7-gpio));
	if(reg_data0 > 0){
		return 1;
	}else{
		return 0;
	}
}



