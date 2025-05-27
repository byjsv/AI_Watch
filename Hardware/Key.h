#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* 包含必要的头文件 */
#include "stm32f10x.h"
#include "freeRTOS.h"
#include "queue.h"

/* 按键事件结构体 - 只在头文件中定义一次 */
typedef struct {
    uint8_t Enter_Pressed;  // 确认键按下
    uint8_t Up_Pressed;     // 上键按下
    uint8_t Down_Pressed;   // 下键按下
} KeyEvent_t;

/* 外部声明的队列句柄 */
extern QueueHandle_t xKeyQueue;

/* 函数声明 */
void Key_Init(void);
BaseType_t Key_GetEvent(KeyEvent_t *pxKeyEvent, TickType_t xTicksToWait);

/* 声明扫描任务函数 */
void vKeyScanTask(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif /* __KEY_H */
