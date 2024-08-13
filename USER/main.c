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
        filter_buf[i] = filter_buf[i + 1]; // �����������ƣ���λ�Ե�
        filter_sum += filter_buf[i];
    }
    return (uint16_t)(filter_sum / FILTER_N);
}

static char buf[VL53L0X_MAX_STRING_LENGTH];//����ģʽ�ַ����ַ�������


//VL53L0X���Գ���
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
		if(i==20)	//0.6s��һ�ε�
		{
			 i = 0;
			 LED1=!LED1;
		} 
	 }
}



int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);                               //��ʼ����ʱ����
	uart_init(115200);	                           //��ʼ�����ڲ�����Ϊ115200	
	LED_Init();					                   //��ʼ��LED 
		
	
/******************����TOF��ʼ���ı�Ҫ���룬����ɾ��************************************/
	while(vl53l0x_init(&vl53l0x_dev))//vl53l0x��ʼ��
	{
		printf("VL53L0X Error!!!\n\r");
		delay_ms(100);
		LED0=!LED0;//DS0��˸
	}
	printf("VL53L0X OK\r\n");
	
	//�޸�TOF��ȡģʽ��������Ĭ��ģʽ�������ں궨�����ҵ����ģʽ
	if(VL53L0X_ERROR_NONE == vl53l0x_set_mode(&vl53l0x_dev,Default_Mode)) 
		printf("VL53L0X MODE SET OK\r\n");
/******************����TOF��ʼ���ı�Ҫ���룬����ɾ��************************************/

	vl53l0x_test();//vl53l0x����
 	    
}













