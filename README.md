# SideProject

## SideProject Description

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
