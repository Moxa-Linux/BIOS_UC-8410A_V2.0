/*  Copyright (C) MOXA Inc. All rights reserved.

    This software is distributed under the terms of the
    MOXA License.  See the file COPYING-MOXA for details.
*/
/*
    cmd_bios.h

    MM Menu

    2014-08-11	Sun Lee				Created it.
*/

#ifndef _CMD_BIOS_H_
#define _CMD_BIOS_H_

#define DIAG_OK		0
#define DIAG_FAIL	1
#define DIAG_ESC	2

#define DIAG_GET_VALUE_HEX_MODE		0
#define DIAG_GET_VALUE_DEC_MODE		1
#define DIAG_GET_VALUE_NO_ABORT		0x80000000L

#define extend_USB_port_crtl		(0x1 << 2)	

// *** Be careful ! ......... You must modify struct _data_pattern and bios_init_global_value() , too.
#define DATA_PATTERN0	(0x5AA55AA5L)
#define DATA_PATTERN1	(0xA55AA55AL)
#define DATA_PATTERN2	(0xAAAAAAAAL)
#define DATA_PATTERN3	(0x55555555L)
#define DATA_PATTERN4	(0x00000000L)
#define DATA_PATTERN5	(0xFFFFFFFFL)		// *** Be careful !

#define EMMC_COPY_LIMIT_SIZE 0x1E00000        //30MB 

/*------------------------------------------------------ Structure ----------------------------------*/

struct burnin_cmd_T{
	int     index;
	char	symbol;
	char	*string;		/* command name */
	void    (*burnin_routine)(void);		/* implementing routine */
	char    exist;          /* IP exist */
};//__attribute__((packed));
typedef struct burnin_cmd_T burnin_cmd;


struct _packet_info {
	long length;
	unsigned char	wbuf[2048];
	unsigned char rbuf[2048];
}__attribute__((packed));
typedef struct _packet_info packet_info;
typedef struct _packet_info *packet_info_p;


typedef struct _data_pattern{
	unsigned long pat0;
	unsigned long pat1;
	unsigned long pat2;
	unsigned long pat3;
	unsigned long pat4;
	unsigned long pat5;
}data_pattern, *data_pattern_p;

// ----------- Utilities ---------------
void bios_print_item_msg(burnin_cmd *cmd_list);
int bios_parse_cmd(char* Buffer);
char bios_parse_cmd_char(char* buffer);
unsigned char bios_check_press_ESC(void);  
int bios_parse_num(char *s, unsigned long *val, char **es, char *delim);
int diag_get_value(char *title, unsigned long *val, unsigned long min, unsigned long max, int mode);
void bios_init_global_value(void);
int bios_manual_testing(burnin_cmd *cmd_list);

// ----------- Function --------------
void diag_do_set_clear_flag_func(void);
void diag_do_download_upload_func(void);
void diag_do_tftp_setting_func(void);
void diag_do_uboot(void);



// ----------- FLAG Menu --------------
unsigned long diag_get_env_conf_u32(const char *name);
void diag_set_env_conf_u32(const char *name, unsigned long value);

void diag_do_tpm_config(void);			
void diag_do_extend_usb_port_control(void);
void diag_do_set_fastboot_mode(void); 
void moxa_init_gpio_led(void);
void mmc_status_check(void);
void diag_do_copy_firmware_from_usb (void); 
void diag_do_download_firmware_by_tftp(void); 
void diag_do_show_ip(void); 
void diag_do_change_ip(void); 
void diag_do_copy_download_firmware_to_emmc(void);	
void diag_do_tftp_download_firmware (void);


#endif

