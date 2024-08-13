#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "vl53l0x.h"

/************************************************
 ALIENTEK ̽����STM32F407��������չʵ��21
 ATK-VL53L0X������ģ�� �ۺϲ���ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);                               //��ʼ����ʱ����
	uart_init(115200);	                           //��ʼ�����ڲ�����Ϊ115200	
	LED_Init();					                   //��ʼ��LED 
	
	while(vl53l0x_init(&vl53l0x_dev))//vl53l0x��ʼ��
	{
		printf("VL53L0X Error!!!\n\r");
		delay_ms(250);
		LED0=!LED0;//DS0��˸
	}
	printf("VL53L0X OK\r\n");

	while(1)
	{
		vl53l0x_test();//vl53l0x����
	} 	    
}
