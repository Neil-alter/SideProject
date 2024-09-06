#include "stm32f10x.h"                  // Device header

#define LED_PIN GPIO_Pin_0

uint8_t CCR_Value=50;

void PWM_Init(void)
{
	// 外設時鐘始能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// GPIO初始化
	GPIO_InitTypeDef GPIO_InitTypeDefStructure;
	GPIO_InitTypeDefStructure.GPIO_Mode=GPIO_Mode_AF_PP; // 復用推挽輸出
	GPIO_InitTypeDefStructure.GPIO_Pin=LED_PIN;
	GPIO_InitTypeDefStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitTypeDefStructure);
	
	// 配置時鐘源
	TIM_InternalClockConfig(TIM2);		
	
	// 時基單元配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=100-1; // ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler=720-1; // PSC
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	// 輸出比較單元配置
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=CCR_Value; // CCR
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	
	// TIM使能
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}

uint16_t PWM_GetCapture(void)
{
	return TIM_GetCapture1(TIM2);
}
