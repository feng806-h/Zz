#include "ADC.h"






/***************************电感采集通道初始化****************************
函数：  void ADC_int(void)  
功能：  电感采值进行初始化
参数：  void
说明：  电感采集初始化
返回值；无
日期：  
作者：  
************************************************************************/
void ADC_int(void)
{
	adc_init(Left_ADC_Pin,ADC_8BIT);     //初始化左电感ADC功能
  adc_init(Right_ADC_Pin,ADC_8BIT);    //初始化右电感为ADC功能 
	adc_init(LeftShu_ADC_Pin,ADC_8BIT); //初始化左竖电感为ADC功能
  adc_init(RightShu_ADC_Pin,ADC_8BIT); //初始化右竖电感为ADC功能 
}