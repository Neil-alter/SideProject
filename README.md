# SideProject Description
下方為本專案的硬體配置，使用的開發版型號為STM32F103C8T6。專案中，我利用STM32的定時器來生成PWM信號，並且透過按鍵來控制LED開關。之後通過STM的ADC功能來讀取電位器的模擬輸入，以調控LED的亮度。這樣使用者可以根據需要調整電位器，從而改變LED的亮度，並在OLED上直觀地看到目前的LED開關狀態和PWM占空比。
![SideProject](https://github.com/user-attachments/assets/d78f8c4a-429f-4678-8547-93eb4a8bf8a4)

## Files
* AD.c、AD.h
  * ADC初始化配置，通過電位器輸入的訊號，用於調整LED燈的占空比大小。
* Key.c、Key.h
  * 按鍵初始化配置，用於開關LED燈。
* PWM.c、PWM.h
  * TIM定時器配置，並利用TIM的輸出比較功能輸出PWM波形至LED燈上。
* OLED.h
  * 將LED燈的開關狀態、電位器輸入的電壓、PWM波形的占空比顯示在OLED上。
* main.c
  * 初始化OLED、按鍵、ADC、PWM。
  * 利用函數達到本專案的目的。
