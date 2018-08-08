/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    cmd_bios.c

    MM Menu

    2014-08-11	Sun Lee			Created it.
*/
#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <net.h>
#include <usb.h>
#include <fs.h>
#include <i2c.h>
#include <tpm.h>	 	
#include <environment.h> 	
#include <mmc.h>   
#include <bios.h>                        
#include <model.h>
#include <cli.h> 
#include <malloc.h>
#include "cmd_bios.h"
#include "predefine_table.h"	
#include "MOXA_BIOS/types.h"
#include "MOXA_BIOS/moxa_console.h"
#include "MOXA_BIOS/moxa_lib.h"
#include "MOXA_BIOS/test.h"		
#include "MOXA_BIOS/led.h"  

DECLARE_GLOBAL_DATA_PTR;


static char ReturnUboot=0;

#define TOLOWER(c)	if((c) >= 'A' && (c) <= 'Z'){(c)+=('a' - 'A');}
#define TOUPPER(c)	if((c) >= 'a' && (c) <= 'z') (c) -= ('a' - 'A');
char CharBuf[256];
char ShortBuf[64];
char CmdMsg[64];
const char RUNBAR[4][8] = {"\\\r","| \r","/ \r","- \r"};
const char AbortString[20] = {"Abort this test!\r\n"};
const char ESCString[48] = {"Please press 'ESC' to Quit this testing ...\r\n"};
data_pattern DataPattern;			// That pattern that we use in all MOXA BIOS

int tftp_upgrade_start = 0; 
extern unsigned  int fw_tftp_size; 
int link_vaild = 0;

void diag_do_nothing(void){printf("\r\nNot Support!\r\n");return;}
// ALL TEST ITEMS
#define BIOS_ITEM_FOR_BASIC_FUNC	1
#define BIOS_ITEM_FOR_FULL_FUNC		1


burnin_cmd BIOS_config_cmd_value[] = {	//\\ 31 characters in each item.
	{ 1,1,"TPM Setting",diag_do_tpm_config, BIOS_ITEM_FOR_BASIC_FUNC},
	{ 1,1,"Extend USB Port Control",diag_do_extend_usb_port_control, BIOS_ITEM_FOR_BASIC_FUNC},
	{ 1,1,"Fastboot mode", diag_do_set_fastboot_mode, BIOS_ITEM_FOR_BASIC_FUNC},
	{ 1,1,"Firmware Update by USB Disk", diag_do_copy_firmware_from_usb, BIOS_ITEM_FOR_BASIC_FUNC},
	{ 1,1,"Firmware Update by Tftp", diag_do_download_firmware_by_tftp, BIOS_ITEM_FOR_BASIC_FUNC}, 
 	{99,'q',"UBoot Command Line             ",diag_do_uboot, BIOS_ITEM_FOR_BASIC_FUNC},	
	{-1,'*',"",0,0}
};

void diag_do_set_fastboot_mode(void)
{
	unsigned long enable;
	unsigned long set_or_clean;
	
   	printf("\nBoot the system in ");
	enable = diag_get_env_conf_u32("fastboot");
                
	if (enable) {
		printf("Fastboot Mode.\n");
	}else {
		printf("Normal Mode.\n");
	}

	if ( diag_get_value("Change to ,0 - Disable, 1 - Enable", &set_or_clean, 0, 1, DIAG_GET_VALUE_DEC_MODE) ){
		return;
	}

	diag_set_env_conf_u32("fastboot", set_or_clean);

	return;	

}

void diag_do_extend_usb_port_control(void)
{
	unsigned long sd_protected;
	unsigned long set_or_clean;
	
   	printf("\nCurrent Extend USB Port is ");
	sd_protected = diag_get_env_conf_u32("sd_protected");                
	if (sd_protected & extend_USB_port_crtl) {
		printf("OFF.\n");
	}else {
		printf("ON.\n");
	}
	if ( diag_get_value("Change to ,0 - ON, 1 - OFF", &set_or_clean, 0, 1, DIAG_GET_VALUE_DEC_MODE) ){
		return;
	}
	if(set_or_clean){
		sd_protected |= extend_USB_port_crtl;
	}else{
		sd_protected &= ~extend_USB_port_crtl;
	}
	diag_set_env_conf_u32("sd_protected", sd_protected);
	
}


/**	\brief
 *
 *	Print Menu items
 *
 * 	\param[in]	cmd_list : command list for printing
 *
 */
void bios_print_item_msg(burnin_cmd *cmd_list)
{
	int i=0, j=0, k=0;
	char * s;
	burnin_cmd *burnin_temp = cmd_list;

	printf ("\r\n----------------------------------------------------------------------------");
	s = getenv ("modelname");
	printf ("\r\n  Model: %s",s);
	printf ("\r\n  Boot Loader Version ");
	s = getenv ("biosver");
	printf ("%s         ", s);
	printf ("\r\n  Build date: " __DATE__ " - " __TIME__);
	s = getenv ("serialnumber");
	printf ("   Serial Number: %s", s);
	s = getenv ("ethaddr");
	printf ("\r\n  LAN1 MAC: %s", s);
	s = getenv ("eth1addr");
	printf ("          LAN2 MAC: %s", s);
	s = getenv ("eth2addr");
	printf ("\r\n  LAN3 MAC: %s", s);
	//printf("\r\n  Module ID:     0x%8x", moduleid);  printf("       Module Name: "); diag_print_env_conf("modulename");
	printf ("\r\n----------------------------------------------------------------------------\r\n");

	while (burnin_temp->index >= 0) {
		if (burnin_temp->exist) {
			if ((burnin_temp->index == 99) || (burnin_temp->index == 98)) {
				/* 'q', 'a' symbol */
				printf("(%c)",burnin_temp->symbol);
			} else {
				if (k == 26) {
					k++;
				}
				if (k <= 9) {
					printf ("(%c)",k+'0');
					burnin_temp->symbol = k+'0';

				} else {
					printf ("(%c)",k-10+'a');
					burnin_temp->symbol = k-10+'a';
				}
			}
			printf (" %s",burnin_temp->string);
			for (j = strlen((char *)burnin_temp->string); j < 31; j++){
				printf(" ");
			}
			k++;
			i++;
			if((i%2)==0){
				printf("\r\n");
			}
		}
		burnin_temp++;
	}
	if ((i%2)!=0) {
		printf("\r\n");
	}
}

/**	\brief
 *
 *	Parse user input and convert to integer.
 *
 * 	\param[in]	cmd_list : command list for printing
 *
 */
int bios_parse_cmd (char* buffer)
{
	char seps[]  = " ";
	char *token;
	char cmd_buf[256];
	unsigned int i;

	token = strtok (buffer, seps);
	if (token == NULL){
		return (-1);
	}
	strcpy (cmd_buf, token);
	if ((strcmp (cmd_buf, "q") == 0) ||(strcmp (cmd_buf, "Q") == 0)){
		return (-2);
	}
	i = atoi_simple (cmd_buf);
	return i;
}

char bios_parse_cmd_char(char* buffer)
{
	char seps[]  = " ";
	char *token;
	char cmd_buf[256];

	token = strtok( buffer, seps );
	if( token == NULL ){
		return (-1);
	}
	strcpy(cmd_buf, token);
	if (cmd_buf[0] >= 'A' && cmd_buf[0] <= 'Z'){
		cmd_buf[0] += (0x20);
	}
	printf("\r\n");		
	return cmd_buf[0];
}

/**	\brief
 *
 *	Parse user input and convert to integer.
 *
 * 	\param[in]	cmd_list : command list for printing
 *
 */
unsigned char bios_check_press_ESC(void)
{
	UINT8 ch;

	if (Kbhit()) {
		ch = Getch();
		if (ch == 27){
			return DIAG_ESC;
		}else{
			return ch;
		}
	}
	return DIAG_OK;
}

/**	\brief
 *
 *	Parse parameter
 *
 */
int bios_parse_num(char *s, unsigned long *val, char **es, char *delim)
{
	int first = 1;
	int radix = 10;
	char c;
	unsigned long result = 0;
	int digit;

	while (*s == ' '){
		s++;
	}
	
	while (*s) {
		if (first && (s[0] == '0') && (_tolower(s[1]) == 'x')) {
			radix = 16;
			s += 2;
        }
        first = DIAG_FAIL;
        c = *s++;
        if (_is_hex(c) && ((digit = _from_hex(c)) < radix)) {
        	result = (result * radix) + digit;
        } else {
			if (delim != (char *)0) {
			    // See if this character is one of the delimiters
			    char *dp = delim;
			    while (*dp && (c != *dp)) {
					dp++;
			    }
			    if (*dp) {
					break;  // Found a good delimiter
			    }
			}
			return DIAG_FAIL;  // Malformatted number
        }
    }
    *val = result;
    if (es != (char **)0) {
        *es = s;
    }
    return DIAG_OK;
}

/**	\brief
 *
 *	Get input value from user and convert to the specfic format.
	mode:
		 DIAG_GET_VALUE_HEX_MODE
		 DIAG_GET_VALUE_DEC_MODE
		 DIAG_GET_VALUE_NO_ABORT
 *
*/
int diag_get_value(char *title, unsigned long *val, unsigned long min, unsigned long max, int mode)
{
	while ( 1 ) {
		printf("\r\n%s (", title);
		if ( mode == DIAG_GET_VALUE_HEX_MODE ){
			printf("0x%lX-0x%lX",  (unsigned long)min, (unsigned long)max);
		}else{
			printf("%lu-%lu", (unsigned long)min, (unsigned long)max);
		}

		if ( mode & DIAG_GET_VALUE_NO_ABORT ){
			printf("): ");
		}else{
			printf(",enter for abort): ");
		}
		if (ConGetString(CharBuf,sizeof(CharBuf)) == -1){
			printf(AbortString); return DIAG_ESC;
		}
		if(CharBuf[0] == 0){
		    return DIAG_FAIL;
		}
		if ( (bios_parse_num(CharBuf, val, 0, 0) || *val < min || *val > max ) == DIAG_FAIL) {
			printf("\r\n%ld: Invalid number !", *val);
			continue;
		}
		break;
	}
	printf("\r\n");
	return DIAG_OK;
}

/**	\brief
 *
 *	BIOS Init function. 
 *
 */
void bios_init_global_value(void)
{
	//extern rtc_time_block RtcTime;
	// 1. DataPattern
	DataPattern.pat0 = DATA_PATTERN0;
	DataPattern.pat1 = DATA_PATTERN1;
	DataPattern.pat2 = DATA_PATTERN2;
	DataPattern.pat3 = DATA_PATTERN3;
	DataPattern.pat4 = DATA_PATTERN4;
	DataPattern.pat5 = DATA_PATTERN5;
	/*
	// 2. RTC Time block
	RtcTime.t_year = IXP_RTC_BASE_YEAR;
	RtcTime.t_mon = 1;
	RtcTime.t_mday = 1;
	*/
	return;
}

void diag_do_uboot(void)
{
	printf("\r\n\r\n");
	ReturnUboot = 1;
}

/**	\brief
 *
 *	Show the BIOS menu.
 *
 */
int bios_manual_testing(burnin_cmd *cmd_list)
{
	unsigned long ret=0;
	while(1){
		burnin_cmd *burnin_temp = cmd_list;
		bios_print_item_msg(burnin_temp);
		printf("---------------------------------------------------------------------------\r\n");
		printf("Command>>");

		if(ConGetString(CmdMsg,sizeof(CmdMsg)) == -1){
			printf("\r\n");
			break;
		}

		ret = bios_parse_cmd_char(CmdMsg);
		if (ret == (-1)){
			continue;
		}else if ((ret == 'q' || ret == 'Q')  && burnin_temp!=BIOS_config_cmd_value){
			printf("\r\n");
			break;
		}
		while(burnin_temp->index != (-1)){
			if((ret==burnin_temp->symbol ) && (burnin_temp->exist)){
				(*burnin_temp->burnin_routine)();
				break;
			}
			burnin_temp++;
		}
		if (ReturnUboot){
			break;
		}
	}
	return ret;
}

int bios_manual_config(burnin_cmd *cmd_list)
{
	unsigned long ret=0;
	while(1){
		burnin_cmd *burnin_temp = cmd_list;
		bios_print_item_msg(burnin_temp);
		printf("---------------------------------------------------------------------------\r\n");
		printf("Command>>");

		if(ConGetString(CmdMsg,sizeof(CmdMsg)) == -1){
			printf("\r\n");
			break;
		}

		ret = bios_parse_cmd_char(CmdMsg);
		if (ret == (-1)){
			continue;
		}else if ((ret == 'q' || ret == 'Q') && burnin_temp!=BIOS_config_cmd_value){
			printf("\r\n");
			break;
		}
		while(burnin_temp->index != (-1)){
			if((ret==burnin_temp->symbol ) && (burnin_temp->exist)){
				(*burnin_temp->burnin_routine)();
				break;
			}
			burnin_temp++;
		}
		if (ReturnUboot){
			break;
		}
	}
	return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////
unsigned long diag_get_env_conf_u32(const char *name)
{
	char *s;
	unsigned long value=0;

	s = getenv (name);
	bios_parse_num (s, &value, 0, 0);
	return value;
}

unsigned long diag_get_env_conf_u32_mem(const char *name)
{
	char sbuf[32];
	unsigned long value=0;
	
	sprintf(sbuf,"%s",getenv(name));
	bios_parse_num(sbuf, &value, 0, 0);
	return value;
}

void diag_set_env_conf_u32(const char *name, unsigned long value)
{
	char cmd_msg[64];
	int ret = DIAG_OK;

   	sprintf(cmd_msg, "setenv %s %lu", name, value);
   	if ((ret = run_command(cmd_msg, 0)) != 0){
		printf("Set %s Fail [%d] \r\n",name, ret);
		return;
	}
	run_command("saveenv", 0);		
	return;
}

void diag_print_env_conf(const char *name)
{
	int j, k, nxt;

	for (j=0; env_get_char(j) != '\0'; j=nxt+1) {
		for (nxt=j; env_get_char(nxt) != '\0'; ++nxt){
        	;
    	}
		k = envmatch((uchar *)name, j);
		if (k < 0) {
			continue;
		}
		while (k < nxt){
			putc(env_get_char(k++));
		}
		break;
	}
}


/* ----- DOWNLOAD/UPLOAD MENU - START ----- */
int do_usb_copy_file_to_mmc0 (char *fw_name, u32 fw_size, int fw_blk, unsigned int mmc_blk_len)
{

	int res = 0;
	char cmd[512];
	u32 rlen = 0xC000000;
	u32 wlen = rlen / mmc_blk_len;
	u32 roffset = 0;
	u32 woffset = 0;
	u32 remain_len = fw_size;
	u32 finish_len = 0;
	int retry = 0;

	while (remain_len > 0) {

		if (retry > 3) {
			printf ("Copy file ERROR...\n");
			res = (-1);
			break;
		}

		sprintf (cmd, "mmc rescan && mmc dev 0 && fatload usb 0 0x80000000 %s 0x%x 0x%x && mmc write 0x80000000 0x%x 0x%x", fw_name, rlen, roffset, woffset, wlen);

		res = run_command (cmd, 0);
		
		if (res != 0) {
			retry++;
			continue;
		}

		finish_len += rlen;
		roffset += rlen;
		woffset += wlen;
		remain_len -= rlen;

		if (remain_len < rlen) {
			rlen = remain_len;
			wlen = remain_len / mmc_blk_len;
			if (remain_len % mmc_blk_len) {
				wlen++;
			}
		}
	}

	return res;

}

void diag_do_copy_firmware_from_usb (void)
{
	char *fw_name = "firmware.img";
	int res = -1;
	signed long long tmp;
	struct mmc *mmc;
	u32 fw_blk = 0;
	u32 fw_size = 0;
	int i = 0;

	printf ("\r\nFirmware File Name (%s): ", fw_name);
	if ((res = ConGetString (CharBuf, sizeof (CharBuf))) == -1) {
		printf ("\r\n");
		return;
	} else if (res == 0) {
		sprintf (CharBuf, "%s", fw_name);
	}

	printf ("\n");
	run_command("usb reset", 0); 

	res = fs_set_blk_dev ("usb", "0", 1);
	if (res < 0) {
		printf ("no usb device at usb1...\n");
		return;
	}

	for (i = 0; i < sizeof(CharBuf); i++){
		if(CharBuf[i] == '\0'){
			break;
		}
		TOLOWER(CharBuf[i]);
	}

	tmp = do_fat_get_file_size (CharBuf);

	if (tmp == (-1)) {
		printf ("Firmware File %s not exist...\n", CharBuf);
		return;
	}

	fw_size = tmp;


	mmc = find_mmc_device (0);

	if (mmc) {
		mmc_init (mmc);
		fw_blk = fw_size / mmc->read_bl_len;


		res=do_usb_copy_file_to_mmc0 (CharBuf, fw_size, fw_blk, mmc->read_bl_len);
    if(res!=0){
  		printf ("Upgrade Fail\n");      
    }else{
  		printf ("Upgrade OK\n");      
    }
	} else {
		printf ("no mmc device at MMC0\n");
	}

	return;


}

int do_copy_file_to_emmc (unsigned int fw_size)
{
        int res = 0;
        char cmd[512];
        u32 wlen = 0;
        unsigned int w_size = 0;
        wlen = fw_size % EMMC_COPY_LIMIT_SIZE;

        if (fw_size > EMMC_COPY_LIMIT_SIZE){
                w_size = fw_size - EMMC_COPY_LIMIT_SIZE;
        }

        if (wlen == 0){
                w_size = (fw_size - EMMC_COPY_LIMIT_SIZE) / 512;
                wlen = (EMMC_COPY_LIMIT_SIZE / 512);
        }else{
                w_size = (fw_size - wlen) / 512;
                wlen = (wlen / 512) ;
        }

        printf("fw_size:%d\n", fw_size);
        
	sprintf (cmd, "mmc rescan");
        res = run_command (cmd, 0);
        sprintf (cmd, "mmc dev 2");
        res = run_command (cmd, 0);
        sprintf (cmd, "mmc write 0x81000000 0x%x 0x%x", w_size, wlen);
        res = run_command (cmd, 0);
        printf("cmd:%s, w_size:%d, wlen:%x\n", cmd, w_size, wlen);

        return res;
}

void diag_do_copy_download_firmware_to_emmc (void)
{
	do_copy_file_to_emmc (fw_tftp_size);
	return;
}

void diag_do_tftp_download_firmware (void)
{
	char *fw_name = "firmware.img";
	int res = -1;
	char cmd [256] = {0};
	char buf_1 [256] = {0};
	char buf_2 [256] = {0};
	unsigned long set_or_clean = 0;


	printf("\r\n Current IP Address \n");
	diag_do_show_ip();

	printf("\nDo you set your ip address?\n");

	diag_get_value("0 - No, 1 - Yes", &set_or_clean, 0, 1, DIAG_GET_VALUE_DEC_MODE);

	if (set_or_clean == 1){
		diag_do_change_ip();
	}
                

	printf ("\r\nFirmware File Name (%s): ", fw_name);

	if ((res = ConGetString (buf_1, sizeof (buf_1))) == -1) {
		printf ("\r\n");
		return;
	} else if (res == 0) {
		sprintf (buf_1, "%s", fw_name);
	}

	printf("download firmware name:%s\n", buf_1);

	printf ("\n");

	memset (buf_2, 0, sizeof (buf_2));
	sprintf(buf_2, "ping %s", getenv("serverip"));

	if (run_command(buf_2, 0)){
		printf("Destination Net Unreachable\n");
		return;
	}
	

	tftp_upgrade_start = 1;
	link_vaild = 1;
	
	sprintf (cmd, "tftp 0x81000000 %s", buf_1);

	if ((res = run_command (cmd, 0)) != 0) {
                printf ("TFTP BIOS file transfer fail.\r\n");
		fw_tftp_size = 0;
                tftp_upgrade_start = 0;
                return;
        }

	fw_tftp_size = 0;
        tftp_upgrade_start = 0;

	if(link_vaild == 0){
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*          TFTP FIRMWARE file transfer fail.     *\n");
		printf("*                                                *\n");
		printf("**************************************************\n");
	} else {
		printf("**************************************************\n");
		printf("*                                                *\n");
		printf("*          TFTP FIRMWARE file transfer success   *\n");
		printf("*                                                *\n");
		printf("**************************************************\n");
	}
        return ;

}

void diag_do_download_firmware_by_tftp(void){

	diag_do_tftp_download_firmware();

}



#define TFTP_DEFAULT_LOCAL_IP	"192.168.30.174"
#define TFTP_DEFAULT_SERVER_IP	"192.168.30.71"

void diag_do_change_ip(void)
{
	int ret, i;

LOCAL_IP:
	printf("\r\nLocal IP Address : ");
	if((i=ConGetString(CharBuf,sizeof(CharBuf))) == -1){
		printf("\r\n");
		return;
	}else if (i == 0){
		goto LOCAL_IP;
	}

	if (inet_addr(CharBuf) == 0){
    	printf("\r\nIP Value Error!\r\n");
    	goto LOCAL_IP;
    }else{
    	printf("\r\n");
    	sprintf(CmdMsg, "setenv ipaddr %s", CharBuf);
    	if ((ret = run_command(CmdMsg, 0)) != 0){
			printf("Set IP Fail(setenv ipaddr) [%d] \r\n", ret);
			return;
		}
    }

SERVER_IP:
	printf("\r\nServer IP Address : ");
	if((i=ConGetString(CharBuf,sizeof(CharBuf))) == -1){
			printf("\r\n");
			return;
	}else if (i == 0){
		goto SERVER_IP;
	}

	if (inet_addr(CharBuf) == 0){
    	printf("\r\nIP Value Error!\r\n");
    	goto SERVER_IP;
    }else{
    	printf("\r\n");
    	sprintf(CmdMsg, "setenv serverip %s", CharBuf);
    	if ((ret = run_command(CmdMsg, 0)) != 0){
			printf("Set IP Fail(setenv serverip) [%d] \r\n", ret);
			return;
		}
    }
	printf("\r\n");
	sprintf(CmdMsg, "saveenv");
    if ((ret = run_command(CmdMsg, 0)) != 0){
		printf("Set IP Fail(saveenv) [%d] \r\n", ret);
		return;
	}
	return;
}

void diag_do_show_ip(void)
{
	printf("\r\nLocal IP Address : ");
	sprintf(CmdMsg, "printenv ipaddr");
    run_command(CmdMsg, 0);

    printf("\r\nServer IP Address : ");
	sprintf(CmdMsg, "printenv serverip");
    run_command(CmdMsg, 0);

	return;
}


int diag_do_tpm_disabled_func(unsigned char flag)
{
	int ret=0;
	uchar enable,active;
	
   	if ((ret = run_command("tpm init", 0)) != 0){
		printf("TPM Init Fail![%d]\n",ret);
		return ret;
	}else{
		printf("Currenn TPM status check..");		
	}
	
	udelay(1000*1000);                       

   	if ((ret = run_command("tpm startup TPM_ST_CLEAR", 0)) != 0){
		printf("TPM Startup Fail![%d]\n",ret);
		return ret;
	}else{
		printf("..");		
	}
	udelay(1000*1000);                       
	
   	if ((ret = run_command("tpm tsc_physical_presence 0x0020", 0)) != 0){
		printf("TPM TSC Physical Presence CMD Enable Fail![%d]\n",ret);
		return ret;
	}else{
		printf("..");		
	}
	udelay(1000*1000);                       
	
   	if ((ret = run_command("tpm get_capability 0x04 0x108 0x81000000 0x16", 0)) != 0){
		printf("TPM Get Capability Fail![%d]\n",ret);
		return ret;
	}else{
		printf("..");		
	}
	udelay(1000*1000);                       
	
	enable = VPchar(0x81000002);
	if(enable){
		printf("is disabled ");
	}else{
		printf("is enabled ");		
	}
	active = VPchar(0x81000004);
	if(active){
		printf("and deactivated\n");
	}else{
		printf("and activated\n");		
	}
	if((enable == 0) || (active == 0)){

	   	if ((ret = run_command("tpm tsc_physical_presence 0x0008", 0)) != 0){
			printf("TPM TSC Physical Presence Present Fail![%d]\n",ret);
			return ret;
		}	
		udelay(1000*1000);
	
	
	   	if ((ret = run_command("tpm physical_set_deactivated 1", 0)) != 0){
			printf("TPM Physical Set Deactivated Fail![%d]\n",ret);
			return ret;
		}	
	
		udelay(1000*1000);
	
	   	if ((ret = run_command("tpm physical_disable", 0)) != 0){
			printf("TPM Physical Disableed Fail![%d]\n",ret);
			return ret;
		}
	
		udelay(1000*1000);
	
	   	if ((ret = run_command("tpm get_capability 0x04 0x108 0x81000000 0x16", 0)) != 0){
			printf("TPM Get Capability Fail![%d]\n",ret);
			return ret;
		}else{
			printf("\n***Current TPM status change to ");		
		}
		udelay(1000*1000);                       
	
		enable = VPchar(0x81000002);
		if(enable){
			printf("disabled ");
		}else{
			printf("enabled ");		
		}
		active = VPchar(0x81000004);
		if(active){
			printf("and deactivated***\n");
		}else{
			printf("and activated***\n");		
		}
	}
	if(flag){
		printf("\r\n### Please reboot the system to complete the operation ###\n");
		while(1);
	}
	return ret;
}

int diag_do_tpm_enabled_func(unsigned char flag)
{
	int ret=0;
	uchar enable,active;
	
   	if ((ret = run_command("tpm init", 0)) != 0){
		printf("TPM Init Fail![%d]\n",ret);
		return ret;
	}else{
		printf("TPM status check..");		
	}
	
	udelay(1000*1000);                       

   	if ((ret = run_command("tpm startup TPM_ST_CLEAR", 0)) != 0){
		printf("TPM Startup Fail![%d]\n",ret);
		return ret;
	}else{
		printf("..");		
	}
	
	udelay(1000*1000);
	
   	if ((ret = run_command("tpm tsc_physical_presence 0x0020", 0)) != 0){
		printf("TPM TSC Physical Presence CMD Enable Fail![%d]\n",ret);
		return ret;
	}else{
		printf("..");		
	}
	udelay(1000*1000);                       
	
	
   	if ((ret = run_command("tpm get_capability 0x04 0x108 0x81000000 0x16", 0)) != 0){
		printf("TPM Get Capability Fail![%d]\n",ret);
		return ret;
	}else{
		printf("..");		
	}
	
	udelay(1000*1000);                       
	
	enable = VPchar(0x81000002);
	if(enable){
		printf("is disabled ");
	}else{
		printf("is enabled ");		
	}
	active = VPchar(0x81000004);
	if(active){
		printf("and deactivated\n");
	}else{
		printf("and activated\n");		
	}
	if((enable != 0) || (active != 0)){
	   	if ((ret = run_command("tpm tsc_physical_presence 0x0008", 0)) != 0){
			printf("TPM TSC Physical Presence Present Fail![%d]\n",ret);
			return ret;
		}	
		udelay(1000*1000);
	
	   	if ((ret = run_command("tpm physical_enable", 0)) != 0){
			printf("TPM Physical Enabled Fail![%d]\n",ret);
			return ret;
		}	
		udelay(1000*1000);
	
   		if ((ret = run_command("tpm physical_set_deactivated 0", 0)) != 0){
			printf("TPM Physical Set Activated Fail![%d]\n",ret);
			return ret;
		}
	
		udelay(1000*1000);
	
	   	if ((ret = run_command("tpm get_capability 0x04 0x108 0x81000000 0x16", 0)) != 0){
			printf("TPM Get Capability Fail![%d]\n",ret);
			return ret;
		}else{
			printf("\n***Current TPM status change to ");		
		}
		udelay(1000*1000);                       
	
		enable = VPchar(0x81000002);
		if(enable){
			printf("disabled ");
		}else{
			printf("enabled ");		
		}
		active = VPchar(0x81000004);
		if(active){
			printf("and deactivated***\n");
		}else{
			printf("and activated***\n");		
		}
	}
	if(flag){
		printf("\r\n### Please reboot the system to complete the operation ###\n");
		while(1);
	}
	return ret;
}

void diag_do_set_tpm_enabled_func(void)
{
	diag_do_tpm_enabled_func(1);
}

void diag_do_set_tpm_disabled_func(void)
{
	diag_do_tpm_disabled_func(1);
}


burnin_cmd tpmconfig_cmd_value[] = {
	{ 0,'0',"TPM Function is Enable",diag_do_set_tpm_enabled_func, 1},
	{ 1,'1',"TPM Function is Disable",diag_do_set_tpm_disabled_func, 1},
    	{ -1,'*',"",0,0}
};

void diag_do_tpm_config(void)
{
		burnin_cmd *burnin_temp=tpmconfig_cmd_value;
		bios_manual_config(burnin_temp);
}
/* ----- TPM ENABLED/DISABLED SETTING - END ----- */


void mmc_status_check(void)
{
	unsigned long enable = 0;
	enable = diag_get_env_conf_u32("fastboot");
	if (enable){
		run_command("setenv bootargs \"console=ttyS0,115200 root=/dev/mmcblk0p2 ver=${biosver} rootfstype=ext4 rootwait fsck.mode=force fsck.repair=yes quiet\"", 0);
	}else{
		run_command("setenv bootargs \"console=ttyS0,115200 root=/dev/mmcblk0p2 ver=${biosver} rootfstype=ext4 fsck.mode=force fsck.repair=yes rootwait\"", 0);
	}
		if(run_command("fatload mmc 0 0x80000000 ls1021a-moxa-uc-8410a.dtb", 0)==0){      
		  if(run_command("fatload mmc 0 0x81000000 uimage", 0)==0){
    		run_command("bootm 0x81000000 - 0x80000000", 0);
		  }
		}  
    printf("Boot to Linux Fail\n");
    Halt(0);    
}

void moxa_init_gpio_led(void)
{
	VPlong(0x01570400) = 0x00000055;		//Change CLK09/10/11 to GPIO4_19/20/21
	FSL_gpio_direction_output(4,PIO_MPE_POWER,1);	//Mini PCIe card Power ON 
	FSL_gpio_direction_output(2,PIO_SD_RESET,1);
	ShowLED	(6);
}

int do_jump_bios_config(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	burnin_cmd *burnin_temp=BIOS_config_cmd_value;

	ReturnUboot = 0;
	bios_init_global_value();							// Init all global values of MOXA BIOS
	while(1){
		if (ReturnUboot){
			break;
		}
		bios_manual_testing(burnin_temp);
	}
	return 1;
}

U_BOOT_CMD(
	bios,     1,     0,      do_jump_bios_config,
	"bios      - Jump into BIOS config menu.",
	"Type \"bios\" to jump into BIOS config menu.\n"
);

