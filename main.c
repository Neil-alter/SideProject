#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "PWM.h"
#include "AD.h"
#include "W25Q64.h"

/*uint8_t MID;
uint16_t DID;*/
uint8_t ArrayWrite[3];
uint8_t ArrayRead[3];

uint8_t KeyNum=0;
uint16_t ADValue=0;
float Voltage=0;
uint8_t Turn=0;

int main(void)
{
	OLED_Init();
	Key_Init();
	PWM_Init();
	AD_Init();
	W25Q64_Init();
	
	/*OLED_ShowString(1,1,"MID:   DID:"); // EF 4017
	W25Q64_ReadID(&MID,&DID);
	OLED_ShowHexNum(1,5,MID,2);
	OLED_ShowHexNum(1,12,DID,4);*/
	
	OLED_ShowString(1,1,"Duty Cycle:   %");
	OLED_ShowString(2,1,"Voltage:0.00V");

	
	while(1)
	{
		ADValue=AD_GetValue();
		CCR_Value=(float)(ADValue)/4095*100;
		Voltage=(float)ADValue/4095*3.3;
		PWM_SetCompare1(CCR_Value); // 調整duty cycle
		
		KeyNum=Key_GetNum();
		if(KeyNum == 1)
		{
			ArrayWrite[0]=CCR_Value;
			ArrayWrite[1]=Voltage;
			ArrayWrite[2]=(uint8_t)(Voltage*100)%100;
			W25Q64_SectorErase(0x000000);
			W25Q64_PageProgram(0x000000,ArrayWrite,3);
			OLED_ShowString(4,1,"Saved successful");
			Delay_ms(3000);
			OLED_ShowString(4,1,"                ");
		}
		if(KeyNum == 2 && Turn == 0)
		{
			W25Q64_ReadData(0x000000,ArrayRead,3);
			OLED_Clear();
			OLED_ShowString(1,1,"Last saved:");
			OLED_ShowString(2,1,"Duty Cycle:   %");
			OLED_ShowString(3,1,"Voltage:0.00V");
			OLED_ShowNum(2,13,ArrayRead[0],2);
			OLED_ShowNum(3,9,ArrayRead[1],1);
			OLED_ShowNum(3,11,ArrayRead[2],2);
			Turn=1;
		}
		else if(KeyNum == 2 && Turn ==1)
		{
			OLED_Clear();
			OLED_ShowString(1,1,"Duty Cycle:   %");
			OLED_ShowString(2,1,"Voltage:0.00V");
			Turn=0;
		}
		if(Turn == 0)
		{
			OLED_ShowNum(1,13,CCR_Value,2);
			OLED_ShowNum(2,9,Voltage,1);
			OLED_ShowNum(2,11,(uint8_t)(Voltage*100)%100,2);
			Turn=0;
		}
		
		Delay_ms(100);
	}
}
