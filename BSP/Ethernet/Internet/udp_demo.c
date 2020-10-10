/**
******************************************************************************
* @file   		udp_demo.c
* @author  		WIZnet Software Team 
* @version 		V1.0
* @date    		2015-02-14
* @brief   		UDP��ʾ����
******************************************************************************
**/
#include <stdio.h>
#include <string.h>
#include "w5500_conf.h"
#include "w5500.h"
#include "socket.h"
#include "utility.h"
#include "udp_demo.h"
#include "main.h"

/**
*@brief		UDP���Գ���
*@param		��
*@return	��
*/
void do_udp(void)
{                                                              
	uint16 len = 0;
	uint8 buff[2048];    // 2048                                                    /*����һ��2KB�Ļ���*/	
	switch(getSn_SR(SOCK_UDPS))                                               /*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:                                                       /*socket���ڹر�״̬*/
			socket(SOCK_UDPS, Sn_MR_UDP, local_port, 0);                          /*��ʼ��socket*/
		  break;
		case SOCK_UDP:                                                           /*socket��ʼ�����*/
   
//			HAL_Delay(10);
			if(getSn_IR(SOCK_UDPS) & Sn_IR_RECV)
			{
				setSn_IR(SOCK_UDPS, Sn_IR_RECV);                                     /*������ж�*/
			}
			if((len = getSn_RX_RSR(SOCK_UDPS)) > 0)                                 /*���յ�����*/
			{
				recvfrom(SOCK_UDPS, buff, len, remote_ip, &remote_port);              /*W5500���ռ����������������*/
				buff[len-8]=0x00;                                                     /*����ַ���������*/
				printf("%s\r\n", buff);                                               /*��ӡ���ջ���*/ 
				sendto(SOCK_UDPS, buff, len-8, remote_ip, remote_port);               /*W5500�ѽ��յ������ݷ��͸�Remote*/
			}
			break;
	}
}

