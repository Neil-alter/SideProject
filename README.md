# SideProject Description
下方為本專案的硬體配置，使用的開發版型號為STM32F103C8T6，flash的型號為W25Q64。專案中，我利用STM32的Timer來生成PWM信號，之後通過STM32的ADC功能來讀取可變電阻的模擬輸入，以調控LED的亮度。另外兩個按鍵分別用於儲存這次的結果到flash裡，以及顯示上一次儲存的結果。這樣使用者可以根據需要調整可變電阻，從而改變LED的亮度，並在OLED上直觀地看到目前的和PWM duty cycle和模擬輸入電壓。
![SideProject2](https://github.com/user-attachments/assets/4bd10659-f4ea-43a4-854c-ebaa2eeb0fab)

* AD.c、AD.h
  * ADC初始化配置，通過可變電阻輸入的訊號，用於調整LED燈的Duty cycle。
* Key.c、Key.h
  * 按鍵初始化配置，用於儲存目前的結果，以及上一次儲存的結果。
* PWM.c、PWM.h
  * TIM定時器配置，並利用TIM的輸出比較功能輸出PWM波形至LED燈上。
* MySPI.c、MySPI.h
  * 利用GPIO輸入/輸出軟體模擬SPI的時序。
* W25Q64.c、W25Q64.h、W25Q64_Ins.h
  * 引用MySPI.h的function，用來讀取flash上的資料。
* OLED.h
  * 將可變電阻輸入的電壓、PWM波形的duty cycle顯示在OLED上。
* main.c
  * 初始化OLED、Key、ADC、PWM、W25Q64。
  * 引入上述的標頭檔，並利用函數達到本專案的目的。

# Note
[Demo](https://youtu.be/WDBnx0JZ0qc)
