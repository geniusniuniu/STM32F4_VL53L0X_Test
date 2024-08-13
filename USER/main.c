#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "vl53l0x.h"

/************************************************
 ALIENTEK 探索者STM32F407开发板扩展实验21
 ATK-VL53L0X激光测距模块 综合测试实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);                               //初始化延时函数
	uart_init(115200);	                           //初始化串口波特率为115200	
	LED_Init();					                   //初始化LED 
	
	while(vl53l0x_init(&vl53l0x_dev))//vl53l0x初始化
	{
		printf("VL53L0X Error!!!\n\r");
		delay_ms(250);
		LED0=!LED0;//DS0闪烁
	}
	printf("VL53L0X OK\r\n");

	while(1)
	{
		vl53l0x_test();//vl53l0x测试
	} 	    
}
