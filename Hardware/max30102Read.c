#include "stm32f10x.h"                  // Device header

#include "delay.h"
#include "sys.h"
#include "OLED.h"
#include "string.h" 	
#include "max30102.h"

#include "freeRTOS.h"
#include "task.h"

// ʹ��max30102.h�ж����BUFFER_SIZE�����������¶���
// #define BUFFER_SIZE 500 // ���Ƴ���ʹ��ͷ�ļ��еĶ���
#define MAX_BRIGHTNESS 255
#define SAMPLE_RATE 100 // 100 samples per second

// ���ݽṹ��
typedef struct {
    uint32_t ir_buffer[BUFFER_SIZE];   // ���������
    uint32_t red_buffer[BUFFER_SIZE];  // �������
    int32_t length;                    // ���ݳ���
    uint32_t min_val;                  // ��Сֵ
    uint32_t max_val;                  // ���ֵ
    uint32_t prev_data;                // ǰһ������
} SensorData;

// ��������ṹ��
typedef struct {
    int32_t spO2;
    int32_t heart_rate;
    int8_t spO2_valid;   // ��Ϊint8_t��ƥ�亯������
    int8_t hr_valid;      // ��Ϊint8_t��ƥ�亯������
} MeasurementResult;

// ȫ�ֱ���
SensorData sensor_data;
MeasurementResult current_result;
uint8_t display_hr = 0, display_spO2 = 0;

// ��������


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
//        delay_ms(10); // �ʵ���ʱ
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
        while(MAX30102_INT == 1); // �ȴ��ж�
        
        max30102_FIFO_ReadBytes(REG_FIFO_DATA, temp);
        
        // ���������� - ��������ƥ��
        sensor_data.red_buffer[i] = (long)(((long)(temp[0]&0x03)<<16) | ((long)temp[1]<<8) | (long)temp[2]);
        
        // ������������ - ��������ƥ��
        sensor_data.ir_buffer[i] = (long)(((long)(temp[3]&0x03)<<16) | ((long)temp[4]<<8) | (long)temp[5]);
        
        // ������С���ֵ
        if(sensor_data.min_val > sensor_data.red_buffer[i])
            sensor_data.min_val = sensor_data.red_buffer[i];
        if(sensor_data.max_val < sensor_data.red_buffer[i])
            sensor_data.max_val = sensor_data.red_buffer[i];
    }
    
    sensor_data.prev_data = sensor_data.red_buffer[sensor_data.length-1];
    
    // �����ʼ���ʺ�Ѫ��
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
    
    // �ƶ����ݻ�����
    for(int i=100; i<BUFFER_SIZE; i++) {
        sensor_data.red_buffer[i-100] = sensor_data.red_buffer[i];
        sensor_data.ir_buffer[i-100] = sensor_data.ir_buffer[i];
        
        // �����źŷ�Χ
        if(sensor_data.min_val > sensor_data.red_buffer[i])
            sensor_data.min_val = sensor_data.red_buffer[i];
        if(sensor_data.max_val < sensor_data.red_buffer[i])
            sensor_data.max_val = sensor_data.red_buffer[i];
		vTaskDelay(pdMS_TO_TICKS(2));
    }
    
    // �ɼ�������
    for(int i=400; i<BUFFER_SIZE; i++) {
		vTaskDelay(pdMS_TO_TICKS(2));
        sensor_data.prev_data = sensor_data.red_buffer[i-1];
        
        while(MAX30102_INT == 1); // �ȴ��ж�
        
        max30102_FIFO_ReadBytes(REG_FIFO_DATA, temp);
        
        // ���������� - ��������ƥ��
        sensor_data.red_buffer[i] = (long)(((long)(temp[0]&0x03)<<16) | ((long)temp[1]<<8) | (long)temp[2]);
        
        // ������������ - ��������ƥ��
        sensor_data.ir_buffer[i] = (long)(((long)(temp[3]&0x03)<<16) | ((long)temp[4]<<8) | (long)temp[5]);
        
        // ��������ֵ
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
    
    // �������ʺ�Ѫ��
    maxim_heart_rate_and_oxygen_saturation(
        sensor_data.ir_buffer, sensor_data.length, 
        sensor_data.red_buffer, 
        &current_result.spO2, &current_result.spO2_valid, 
        &current_result.heart_rate, &current_result.hr_valid
    );
    
    // ��֤���
    if(current_result.hr_valid && current_result.heart_rate < 120) {
        display_hr = current_result.heart_rate;
        display_spO2 = current_result.spO2;
    } else {
        display_hr = 0;
        display_spO2 = 0;
    }
}
