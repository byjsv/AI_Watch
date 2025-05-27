#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "sys.h"
#include "OLED.h"
#include "string.h" 	
#include "max30102.h"

#include "freeRTOS.h"
#include "task.h"

// 使用max30102.h中定义的BUFFER_SIZE，而不是重新定义
// #define BUFFER_SIZE 500 // 已移除，使用头文件中的定义
#define MAX_BRIGHTNESS 255
#define SAMPLE_RATE 100 // 100 samples per second

// 数据结构体
typedef struct {
    uint32_t ir_buffer[BUFFER_SIZE];   // 红外光数据
    uint32_t red_buffer[BUFFER_SIZE];  // 红光数据
    int32_t length;                    // 数据长度
    uint32_t min_val;                  // 最小值
    uint32_t max_val;                  // 最大值
    uint32_t prev_data;                // 前一个数据
} SensorData;

// 测量结果结构体
typedef struct {
    int32_t spO2;
    int32_t heart_rate;
    int8_t spO2_valid;   // 改为int8_t以匹配函数参数
    int8_t hr_valid;      // 改为int8_t以匹配函数参数
} MeasurementResult;

// 全局变量
SensorData sensor_data;
MeasurementResult current_result;
uint8_t display_hr = 0, display_spO2 = 0;

// 函数声明


//int main(void) 
//{
//    System_Init();
//    Sensor_Init();
//    Collect_Initial_Samples();
//    
//    while(1) {
//        Process_Sensor_Data();
//		//display_hr-20;
//		//display_spO2;
//        delay_ms(10); // 适当延时
//    }
//}

void System_Init(void) 
{
    delay_init();
}

void Sensor_Init(void) 
{
    MAX30102_Init();
    sensor_data.length = BUFFER_SIZE;
    sensor_data.min_val = 0x3FFFF;
    sensor_data.max_val = 0;
}

void Collect_Initial_Samples(void) 
{
    uint8_t temp[6];
    
    for(int i=0; i<sensor_data.length; i++) {
        while(MAX30102_INT == 1); // 等待中断
        
        max30102_FIFO_ReadBytes(REG_FIFO_DATA, temp);
        
        // 处理红光数据 - 修正括号匹配
        sensor_data.red_buffer[i] = (long)(((long)(temp[0]&0x03)<<16) | ((long)temp[1]<<8) | (long)temp[2]);
        
        // 处理红外光数据 - 修正括号匹配
        sensor_data.ir_buffer[i] = (long)(((long)(temp[3]&0x03)<<16) | ((long)temp[4]<<8) | (long)temp[5]);
        
        // 更新最小最大值
        if(sensor_data.min_val > sensor_data.red_buffer[i])
            sensor_data.min_val = sensor_data.red_buffer[i];
        if(sensor_data.max_val < sensor_data.red_buffer[i])
            sensor_data.max_val = sensor_data.red_buffer[i];
    }
    
    sensor_data.prev_data = sensor_data.red_buffer[sensor_data.length-1];
    
    // 计算初始心率和血氧
    maxim_heart_rate_and_oxygen_saturation(
        sensor_data.ir_buffer, sensor_data.length, 
        sensor_data.red_buffer, 
        &current_result.spO2, &current_result.spO2_valid, 
        &current_result.heart_rate, &current_result.hr_valid
    );
}

void Process_Sensor_Data(void) 
{
    uint8_t temp[6];
    float f_temp;
    int32_t n_brightness = 0;
    
    // 移动数据缓冲区
    for(int i=100; i<BUFFER_SIZE; i++) {
        sensor_data.red_buffer[i-100] = sensor_data.red_buffer[i];
        sensor_data.ir_buffer[i-100] = sensor_data.ir_buffer[i];
        
        // 更新信号范围
        if(sensor_data.min_val > sensor_data.red_buffer[i])
            sensor_data.min_val = sensor_data.red_buffer[i];
        if(sensor_data.max_val < sensor_data.red_buffer[i])
            sensor_data.max_val = sensor_data.red_buffer[i];
		vTaskDelay(pdMS_TO_TICKS(2));
    }
    
    // 采集新数据
    for(int i=400; i<BUFFER_SIZE; i++) {
		vTaskDelay(pdMS_TO_TICKS(2));
        sensor_data.prev_data = sensor_data.red_buffer[i-1];
        
        while(MAX30102_INT == 1); // 等待中断
        
        max30102_FIFO_ReadBytes(REG_FIFO_DATA, temp);
        
        // 处理红光数据 - 修正括号匹配
        sensor_data.red_buffer[i] = (long)(((long)(temp[0]&0x03)<<16) | ((long)temp[1]<<8) | (long)temp[2]);
        
        // 处理红外光数据 - 修正括号匹配
        sensor_data.ir_buffer[i] = (long)(((long)(temp[3]&0x03)<<16) | ((long)temp[4]<<8) | (long)temp[5]);
        
        // 计算亮度值
        if(sensor_data.red_buffer[i] > sensor_data.prev_data) {
            f_temp = (sensor_data.red_buffer[i] - sensor_data.prev_data);
            f_temp /= (sensor_data.max_val - sensor_data.min_val);
            f_temp *= MAX_BRIGHTNESS;
            n_brightness -= (int)f_temp;
            if(n_brightness < 0) n_brightness = 0;
        } else {
            f_temp = (sensor_data.prev_data - sensor_data.red_buffer[i]);
            f_temp /= (sensor_data.max_val - sensor_data.min_val);
            f_temp *= MAX_BRIGHTNESS;
            n_brightness += (int)f_temp;
            if(n_brightness > MAX_BRIGHTNESS) n_brightness = MAX_BRIGHTNESS;
        }
    }
    
    // 计算心率和血氧
    maxim_heart_rate_and_oxygen_saturation(
        sensor_data.ir_buffer, sensor_data.length, 
        sensor_data.red_buffer, 
        &current_result.spO2, &current_result.spO2_valid, 
        &current_result.heart_rate, &current_result.hr_valid
    );
    
    // 验证结果
    if(current_result.hr_valid && current_result.heart_rate < 120) {
        display_hr = current_result.heart_rate;
        display_spO2 = current_result.spO2;
    } else {
        display_hr = 0;
        display_spO2 = 0;
    }
}
