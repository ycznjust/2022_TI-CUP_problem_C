#include "ycz_communicate.h"
float others_speed;
//每辆车上报自己的实时速度
//入口参数，每个周期的速度，单位cm/周期，大概每几百微秒调用一次
void speed_post(uint8 speed_cm)
{
	uint8 send_buffer[4];

	send_buffer[0] = 0x55;
	send_buffer[1] = 0xbb; // 0xbb表示这是速度

	if (speed_cm == 0x55) //避开帧头
		send_buffer[2] = 0x56;
	else
		send_buffer[2] = speed_cm;

	send_buffer[3] = 0xdd;

	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[0]);
	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[1]);
	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[2]);
	MAP_UART_transmitData(EUSCI_A1_BASE, send_buffer[3]);
}

void task_post(uint8 pos)
{
	MAP_UART_transmitData(EUSCI_A1_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xaa);
	MAP_UART_transmitData(EUSCI_A1_BASE, pos);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xdd);
}

void task_and_speed_post(uint8 task_number, uint8 speed)
{
	MAP_UART_transmitData(EUSCI_A1_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A1_BASE, task_number);
	MAP_UART_transmitData(EUSCI_A1_BASE, speed);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xdd);
}

void task_stop(void)
{
	MAP_UART_transmitData(EUSCI_A1_BASE, 0x55);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xcc);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xcc);
	MAP_UART_transmitData(EUSCI_A1_BASE, 0xdd);
}


extern int buzzer_bi_flag;
extern float basic_speed;
extern uint8 task_number;
extern uint8 stop_flag ;
extern float control_speed;
extern uint8 task_state;
void communicate_handler(unsigned char ucData)
{
	static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;
	ucRxBuffer[ucRxCnt++] = ucData; //将收到的数据存入缓冲区中
	

	if (ucRxBuffer[0] != 0x55)		//数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt = 0;
		return;
	}
	if (ucRxCnt < 4)
	{
		return;
	} //数据不满4个，则返回
	else
	{
		
		if (ucRxBuffer[3] != 0xdd) //帧尾校验
		{
			ucRxCnt = 0;
			return;
		}

		if (ucRxBuffer[1] == 0xaa) //控制字节
		{
			 task_state = ucRxBuffer[2];
		}

		if (ucRxBuffer[1] == 0xbb) //速度字节
		{
			others_speed = ucRxBuffer[2];
		}
		
		if (ucRxBuffer[1] == 0xcc) //停车字节
		{
			basic_speed = 0;
			control_speed = 0;
			stop_flag = 1;
			buzzer_bi_flag = 1;
			led_blink_flag = 100;
		}
		
		if ((ucRxBuffer[1] >= 0x01)&&(ucRxBuffer[1] <= 0x06)) //设定速度和任务序号
		{
			task_number = ucRxBuffer[1];
			basic_speed = (float)ucRxBuffer[2];
			buzzer_bi_flag = 1;
			
		}

		ucRxCnt = 0; //清空缓存区
	}
}
