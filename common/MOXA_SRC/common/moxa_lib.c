/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    moxa_lib.c

	Functions of common used library.
    
*/


#include <common.h>
#include <command.h>
//#include <asm/gpio.h>
#include <bios.h>
#include <model.h>
#include "../cmd_bios.h"
#include "types.h"
#include "moxa_lib.h"     
#include "led.h"  

unsigned long inet_addr (char *ptr)
{
	int				len,i;
	unsigned short	ch;
	unsigned long	val;
	char			buffer[10];

	for (i = 0, len = 0, val = 0, ch = 0; i < 4; i++) {
		len = get_digit (ptr, &len);
		if ((ptr[len] != '.') && (i < 3)) {
			//printf("inet_addr() return none\r\n");
			return 0;
		}

		memcpy (buffer, ptr, len+1);
		buffer[len] = 0;

		if ((ch = (unsigned short) Atos (buffer)) >= 0xff) {
			//printf("inet_addr() return none\r\n");
			return 0;
		}
		val |= (unsigned char)ch << (i*8);
		ptr += (len+1);
	}
	return val;
}

int get_digit (char *buf, int *len)
{
	int i = 0;
	char ch;

	*len = 0;
	while (1) {
	    ch = *buf++;
	    if ((ch < '0') || (ch >'9')) {
			break;
		}
	    *len = (*len) * 10 + ch - '0';
	    i++;
	}
	return (i);
}

int skip_atoi (const char **s)
{
	int i = 0;

	while (is_digit (**s)) {
		i = i*10 + *((*s)++) - '0';
	}
	return i;
}

int	StrLength (const char *ptr)
{
	int	i = 0;

	while (*ptr++ != 0) {
	    i++;
	}
	return(i);
}

unsigned long bios_lib_simple_strtoul (const char *cp, char **endp, unsigned int base)
{
	unsigned long result = 0,value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit (cp[1])) {
			base = 16;
			cp++;
		}
		if (!base) {
			base = 8;
		}
	}
	if (!base) {
		base = 10;
	}
	while (isxdigit (*cp) &&
		(value = isdigit (*cp) ? *cp-'0' : (islower (*cp) ? toupper(*cp) : *cp)-'A'+10) < base) {
		result = result*base + value;
		cp++;
	}
	if (endp) {
		*endp = (char *)cp;
	}
	return result;
}

long bios_lib_simple_strtol (const char *cp, char **endp, unsigned int base)
{
	if (*cp=='-') {
		return -(bios_lib_simple_strtoul (cp+1,endp,base));
	}
	return bios_lib_simple_strtoul (cp,endp,base);
}

int atoi_simple (char *string)
{
	int res = 0;
	while (*string>='0' && *string <='9') {
		res *= 10;
		res += *string-'0';
		string++;
	}

	return res;
}

int atoi (const char *str) 
{
	return ((int) (bios_lib_simple_strtoul (str, (char **) NULL, 10)));
}

/*
 *	ASCII string to byte binary value  (unsigned char)
 */
unsigned char Atob (char *buf)
{
	unsigned char value = 0;
	char ch;
	int	i = 0;

	for (;;) {
	    ch = *buf++;
	    if ((ch >= '0') && (ch <= '9')) {
			value = (value << 4) | (ch - '0');
		} else if ((ch >= 'a') && (ch <= 'f')) {
			value = (value << 4) | (ch - 'a' + 10);
		} else if ((ch >= 'A') && (ch <= 'F')) {
			value = (value << 4) | (ch - 'A' + 10);
		} else {
			break;
		}
	    i++;
	    if (i >= 2) {
			break;
		}
	}
	return (value);
}
/*
 *	ASCII string to word binary value  (unsigned short)
 */
unsigned short Atow (char *buf)
{
	unsigned short value = 0;
	char ch;
	int	i = 0;

	for (;;) {
	    ch = *buf++;
	    if ((ch >= '0') && (ch <= '9')){
			value = (value << 4) | (ch - '0');
		} else if ((ch >= 'a') && (ch <= 'f')) {
			value = (value << 4) | (ch - 'a' + 10);
		} else if ((ch >= 'A') && (ch <= 'F')) {
			value = (value << 4) | (ch - 'A' + 10);
		} else {
			break;
		}
	    i++;
	    if (i >= 4) {
			break;
		}
	}
	return (value);
}

unsigned long Atoh(char *buf)
{
	unsigned long value = 0;
	char ch;
	int	i=0;

	for (;;) {
	    ch = *buf++;
	    if ((ch >= '0') && (ch <= '9')) {
			value = (value << 4) | (ch - '0');
		} else if ((ch >= 'a') && (ch <= 'f')) {
			value = (value << 4) | (ch - 'a' + 10);
		} else if ((ch >= 'A') && (ch <= 'F')) {
			value = (value << 4) | (ch - 'A' + 10);
		} else {
			break;
		}
	    i++;
	    if (i >= 8) {
			break;
		}
	}
	return (value);
}

/*
 *	ASCII string to unsigned short	(unsigned short)
 */
unsigned short Atos (char *buf)
{
	unsigned short value = 0;
	char ch;

	for (;;) {
	    ch = *buf++;
	    if ((ch >= '0') && (ch <= '9')) {
			value = value * 10 + ch - '0';
		} else {
			break;
		}
	}
	return(value);
}

/*
 *	ASCII string to unsigned short	(unsigned short)
 */
unsigned long Atol (char *buf)
{
	unsigned long value = 0;
	char ch;

	for (;;) {
	    ch = *buf++;
	    if ((ch >= '0') && (ch <= '9')) {
			value = value * 10 + ch - '0';
		} else {
			break;
		}
	}
	return (value);
}

int _is_hex (char c)
{
	return (((c >= '0') && (c <= '9')) ||
            ((c >= 'A') && (c <= 'F')) ||            
            ((c >= 'a') && (c <= 'f')));
}

int _from_hex (char c) 
{
	int ret = 0;

	if ((c >= '0') && (c <= '9')) {
		ret = (c - '0');
	} else if ((c >= 'a') && (c <= 'f')) {
		ret = (c - 'a' + 0x0a);
	} else if ((c >= 'A') && (c <= 'F')) {
		ret = (c - 'A' + 0x0A);
	}
	return ret;
}

char _tolower (char c)
{
	if ((c >= 'A') && (c <= 'Z')) {
		c = (c - 'A') + 'a';
	}
	return c;
}

int	IsDigit (char *buf)
{
	char ch;

	for (;;) {
		ch = *buf++;
		if (ch == 0) {
			break;
		}
		if ((ch >= '0') && (ch <= '9')) {
			continue;
		}
		return (0);
	}
	return (1);
}

int	IsHex (char *buf)
{
	char ch;

	for (;;) {
		ch = *buf++;
		if (ch == 0) {
			break;
		}
		if(_is_hex (ch) == 0) {
			return (0);
		}
	}
	return (1);
}
void Strcpy(unsigned char *dbuf, unsigned char *sbuf)
{
	int	i = 0;

	while (sbuf[i] != 0) {
	    dbuf[i] = sbuf[i];
	    i++;
	}
	dbuf[i] = 0;
	return;
}

unsigned long Inw(unsigned long addr)
{
    return *(volatile unsigned long *)(addr);
}

void Outw(unsigned long addr,unsigned long data)
{
    *(volatile unsigned long *)(addr)=data;
}

unsigned short Inhw(unsigned long addr)
{
    return *(volatile unsigned short *)(addr);
}

void Outhw(unsigned long addr,unsigned short data)
{
    *(volatile unsigned short *)(addr)=data;
}

unsigned char Inb(unsigned long addr)
{
    return *(volatile unsigned char *)(addr);
}

void Outb(unsigned long addr,unsigned char data)
{
    *(volatile unsigned char *)(addr) = data;
}

void * mem_cpy(void * dest, const void *src, long count)
{
	char *tmp = (char *) dest, *s = (char *) src;

	while (count--){
		*tmp++ = *s++;
	}
	return dest;
}

void * mem_set(void * s, char c, long count)
{
	char *xs = (char *) s;

	while (count--){
		*xs++ = c;
	}
	return s;
}

void ShowLED(unsigned char led)
{
	led &= 0x1f;	
	
	if((led & BIT0) > 0){
		FSL_gpio_direction_output(4,PIO_LED_MP_0, 0);
	}else{
		FSL_gpio_direction_output(4,PIO_LED_MP_0, 1);	
	}	
	if((led & BIT1) > 0){
		FSL_gpio_direction_output(4,PIO_LED_MP_1, 0);
	}else{
		FSL_gpio_direction_output(4,PIO_LED_MP_1, 1);
	}
	if((led & BIT2) > 0){
		FSL_gpio_direction_output(4,PIO_LED_MP_2, 0);
	}else{
		FSL_gpio_direction_output(4,PIO_LED_MP_2, 1);
	}
	if((led & BIT3) > 0){
		FSL_gpio_direction_output(4,PIO_LED_MP_3, 0);
	}else{
		FSL_gpio_direction_output(4,PIO_LED_MP_3, 1);
	}
	if((led & BIT4) > 0){
		FSL_gpio_direction_output(4,PIO_LED_MP_4, 0);
	}else{
		FSL_gpio_direction_output(4,PIO_LED_MP_4, 1);
	}
}

void ReadyLed(unsigned char Gpio_pin,unsigned char status)
{
	FSL_gpio_direction_output(1,Gpio_pin, status);
}

/*
 *	subroutine Halt()
 *	function : Halt System and Show Debug LEN for Error Number
 *	input  : Show value on Debug LED
 *	return : None
 */
void Halt(unsigned char value)
{
	for (;;) {
		ShowLED(0);
		udelay(1000*1000);
		ShowLED(value);
		udelay(1000*1000);
	}
}

/*
 * Return:
 *  1: Button Press
 *  0: Button Release
 */
int sw_button_status (void)
{
    if(GetJpStatus(PIO_SW_BUTTON)==0){
        return 1;
    }
	return 0;
}

void Wait_SW_Button(void)
{
	unsigned long count=0;

	while(1) {
		if (GetJpStatus(PIO_SW_BUTTON) == 0) {
			while(1){
				if (GetJpStatus(PIO_SW_BUTTON) == 1) {
					udelay(1000);
					break;
				}
			}
			udelay(1000);
			break;
		}
        	if(count < 500){
			SetBeeperStatus(1);
			ReadyLed (PIO_LED_READY, 1);
			udelay(1000);
			count++;
        	} else if ((count >= 500) && (count < 1000)) {
			SetBeeperStatus(0);
			ReadyLed (PIO_LED_READY, 0);
			udelay(1000);
			count++;
        	} else {
			count = 0;
        	}
	}
	SetBeeperStatus(0);
	ReadyLed (PIO_LED_READY, 0);
	udelay (1000000);
}

void SetBeeperStatus(unsigned char val)
{
	FSL_gpio_direction_output(1,PIO_BEEPER,val);
	return;
}


int GetJpStatus(unsigned char Gpio_pin)
{
	return FSL_gpio_direction_input(1,PIO_SW_BUTTON);	//
}

