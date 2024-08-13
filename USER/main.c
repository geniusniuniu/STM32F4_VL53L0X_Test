#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "vl53l0x.h"

#define FILTER_N            16

uint16_t Filter_Window(uint16_t Dis) 
{
    static uint16_t filter_buf[FILTER_N + 1];
    int i;    
    uint16_t filter_sum = 0;
    filter_buf[FILTER_N] = Dis;
    for(i = 0; i < FILTER_N; i++) 
    {
        filter_buf[i] = filter_buf[i + 1]; // 所有数据左移，低位仍掉
        filter_sum += filter_buf[i];
    }
    return (uint16_t)(filter_sum / FILTER_N);
}

static char buf[VL53L0X_MAX_STRING_LENGTH];//测试模式字符串字符缓冲区


//VL53L0X测试程序
void vl53l0x_test(void)
{   
	 u8 i=0;
	 VL53L0X_Error status = 0; 
	 while(1)
	 {
		status = vl53l0x_start_single_test(&vl53l0x_dev,&vl53l0x_data,buf);
		Filter_Window(Distance_data); 
		 
		if(status == VL53L0X_ERROR_NONE)
		{
			printf("%d\r\n",Distance_data);
		}
		
		delay_ms(30);
		
		i++;
		if(i==20)	//0.6s闪一次灯
		{
			 i = 0;
			 LED1=!LED1;
		} 
	 }
}



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);                               //初始化延时函数
	uart_init(115200);	                           //初始化串口波特率为115200	
	LED_Init();					                   //初始化LED 
		
	
/******************这是TOF初始化的必要代码，不可删除************************************/
	while(vl53l0x_init(&vl53l0x_dev))//vl53l0x初始化
	{
		printf("VL53L0X Error!!!\n\r");
		delay_ms(100);
		LED0=!LED0;//DS0闪烁
	}
	printf("VL53L0X OK\r\n");
	
	//修改TOF读取模式，现在是默认模式，可以在宏定义中找到别的模式
	if(VL53L0X_ERROR_NONE == vl53l0x_set_mode(&vl53l0x_dev,Default_Mode)) 
		printf("VL53L0X MODE SET OK\r\n");
/******************上述TOF初始化的必要代码，不可删除************************************/

	vl53l0x_test();//vl53l0x测试
 	    
}













