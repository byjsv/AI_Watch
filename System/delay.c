#include "stm32f10x.h"
#include "freeRTOS.h"
#include "Task.h"

// TIM2 初始化
void Delay_Init(void) {
    // 1. 使能 TIM2 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 2. 配置 TIM2 为向上计数模式
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF;          // 自动重装值，最大值
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;       // 预分频器，72MHz / 72 = 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;        // 时钟分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 3. 启动 TIM2
    TIM_Cmd(TIM2, ENABLE);
}

   // 微秒级延时函数

/**
  * @brief  微秒级延时
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
void Delay_us(uint32_t us) {
    TIM2->CNT = 0;               // 清空计数器
    while (TIM2->CNT < us);      // 等待计数器达到指定值
}


/**
  * @brief  毫秒级延时
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 无
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 

void delay_ms(uint32_t xms)
{
	Delay_ms(xms);
}

void delay_us(uint32_t us)
{
	Delay_us(us);
}

void delay_init(void)
{
	Delay_Init();
}

void TaskDelay_ms(uint32_t xms)
{
	vTaskDelay(pdMS_TO_TICKS(xms));
}


