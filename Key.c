#include "stm32f10x.h"
#include "Delay.h"

#define STORE_PIN GPIO_Pin_9
#define DISPLAY_PIN GPIO_Pin_10

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // 下拉輸入
	GPIO_InitStructure.GPIO_Pin = STORE_PIN | DISPLAY_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if(GPIO_ReadInputDataBit(GPIOA, STORE_PIN) == 1)
	{
		Delay_ms(20);// 剛按下會有抖動，所以需要 delay 一段時間
		while(GPIO_ReadInputDataBit(GPIOA, STORE_PIN) == 1);
		Delay_ms(20); // 等待鬆開
		KeyNum = 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA, DISPLAY_PIN) == 1)
	{
		Delay_ms(20);// 剛按下會有抖動，所以需要 delay 一段時間
		while(GPIO_ReadInputDataBit(GPIOA, DISPLAY_PIN) == 1);
		Delay_ms(20); // 等待鬆開
		KeyNum = 2;
	}
	return KeyNum;
}
