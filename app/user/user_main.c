/******************************************************************************
 * Copyright 2013-2014 Espressif Systems (Wuxi)
 *
 * FileName: user_main.c
 *
 * Description: entry file of user application
 *
 * Modification history:
 *     2014/1/1, v1.0 create this file.
*******************************************************************************/
#include <os_type.h>
#include <c_types.h>
#include <osapi.h>
#include <driver/uart.h>
#include <user_interface.h>
#include "push.h"


void ICACHE_FLASH_ATTR msg_recv_cb(uint8* pdata, uint32 len)
{
	os_printf("\n\nMSG_RECV_CB: [%d], [%s]\n\n", len, pdata);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void ICACHE_FLASH_ATTR user_init(void)
{
	uart_init(BIT_RATE_115200, BIT_RATE_115200);
	os_printf("\n\nready\n\n;");
	uint8 boot_ver = system_get_boot_version();
	uint8 boot_mode = system_get_boot_mode();
	uint32 user_addr = system_get_userbin_addr();

	{
		struct station_config config;
		os_strcpy(config.ssid, "your ssid");
		os_strcpy(config.password, "your ssid password");

		wifi_set_opmode(STATION_MODE);
		wifi_station_set_config(&config);
		wifi_station_set_auto_connect(1);
		wifi_station_dhcpc_start();
	}

	os_printf("boot ver: [%d], boot mode: [%d]\nuser addr: [%X]\n", boot_ver, boot_mode, user_addr);
	//�滻�����APPID��APPKEY����ȡ��ע�ͼ���
	//push_register(APPID, "APPKEY", msg_recv_cb);
}
