#include "stm32f10x.h"
#include "Delay.h"

#define KEY_PIN GPIO_Pin_6

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉輸入
	GPIO_InitStructure.GPIO_Pin = KEY_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 在輸入模式沒用
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	
	if(GPIO_ReadInputDataBit(GPIOA, KEY_PIN) == 0)
	{
		Delay_ms(20);// 剛按下會有抖動，所以需要 delay 一段時間
		while(GPIO_ReadInputDataBit(GPIOA, KEY_PIN) == 0);
		Delay_ms(20); // 等待鬆開
		KeyNum = 1;
	}
	return KeyNum;
}
