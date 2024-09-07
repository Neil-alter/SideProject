#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "AD.h"

uint8_t Turn=0;
uint16_t ADValue;
float Voltage;

int main(void)
{
	OLED_Init();
	Key_Init();
	PWM_Init();
	AD_Init();
	
	PWM_SetCompare1(0);
	
	OLED_ShowString(1,1,"LED_OFF");
	OLED_ShowString(2,1,"Duty Cycle:   %");
	OLED_ShowString(3,1,"Voltage:0.00V");
	
	while(1)
	{
		if(Key_GetNum()==1)
		{
			if(PWM_GetCapture()!=0) // Turn OFF
			{
				PWM_SetCompare1(0);
				OLED_ShowString(1,1,"LED_OFF");
				Turn=0;
			}
			else // Turn ON
			{
				PWM_SetCompare1(CCR_Value);
				OLED_ShowString(1,1,"LED_ON ");
				Turn=1;
			}
		}
		ADValue=AD_GetValue();
		CCR_Value=(float)(ADValue)/4095*100;
		Voltage=(float)ADValue/4095*3.3;
		if(Turn!=0)
		{
			PWM_SetCompare1(CCR_Value);
		}
		
		OLED_ShowNum(2,13,CCR_Value,2);
		OLED_ShowNum(3,9,Voltage,1);
		OLED_ShowNum(3,11,(uint16_t)(Voltage*100)%100,2);
		
		Delay_ms(100);
	}
}
