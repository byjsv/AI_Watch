#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "Delay.h"
#include "OLED.h"

#include "Serial.h"
#include "Air780E.h"

char Send_command[128];
char Recive_command[1000];

char ai_model[100];
char api_key[100];
char base_url[200];

int remove_FirstSubstring(char *str, char *sub) 
{
    // 查找子字符串的位置
    char *pos = strstr(str, sub);

    if (pos == NULL) {
        // 如果没有找到子字符串，返回-1
        return -1;
    }

    // 计算子字符串的位置
    int position = pos - str;

    // 计算子字符串的长度
    size_t sub_len = strlen(sub);

    // 将子字符串后面的部分向前移动
    memmove(pos, pos + sub_len, strlen(pos + sub_len) + 1);

    return position;
}

uint8_t AT_SendCommand(char* command,char *Response, uint16_t timeout, uint8_t Retry) 
{
	uint8_t i=0;
    uint16_t j=0;
	
	if(!timeout)
	{
		timeout = strlen(command)*10;
	}
    
	OLED_Clear();
	OLED_ShowString_Line(0,0,command);
    
    for(i=0;i<Retry;i++)
	{
		Serial_SendString(command);
		for (j = 0; j < timeout; j++) {
			if (Serial_RxFlag == 1) {
				if (strstr(Serial_RxPacket, Response) != NULL) {
					Serial_RxFlag = 0;
					
					OLED_ShowString_Line(0,16,Serial_RxPacket);
					
					return Success; // 成功接收到 "OK"
				}
				else if (strstr(Serial_RxPacket, "ERROR") != NULL) 
				{
					Serial_RxFlag = 0;
					
					
					return Failure; // 接收到 "ERROR"
				}
				Serial_RxFlag = 0; // 清除接收标志
			}
        Delay_ms(10);
		}
	}

	OLED_ShowNum(0,48,1,1,OLED_6X8);

    return Failure; // 超时未收到有效响应
}


uint8_t AT_SendCommand_2(char* command,char *Response, char *Response2, uint16_t timeout, uint8_t Retry) 
{
	uint8_t i=0;
    uint16_t j=0;
	
	if(!timeout)
	{
		timeout = strlen(command)*10;
	}
    
	OLED_Clear();
    OLED_ShowString_Line(0,0,command);
	
    for(i=0;i<Retry;i++)
	{
		Serial_SendString(command);
		for (j = 0; j < timeout; j++) {
			if (Serial_RxFlag == 1) {
				if (strstr(Serial_RxPacket, Response) != NULL && strstr(Serial_RxPacket, Response2) != NULL)
				{
					
					OLED_ShowString_Line(0,16,Serial_RxPacket);
					Serial_RxFlag = 0;
					
					return Success; // 成功接收到 "OK"
				}
				else if (strstr(Serial_RxPacket, "ERROR") != NULL ) 
				{
					Serial_RxFlag = 0;
					
					return Failure; // 接收到 "ERROR"
				}
				Serial_RxFlag = 0; // 清除接收标志
			}
        //delay_ms(1);
		}
	}

    return Failure; // 超时未收到有效响应
}

uint8_t AT_WaitResponse(char *Response, uint16_t timeout, uint8_t Retry) 
{
	uint8_t i=0;
    uint16_t j=0;
    
    
    for(i=0;i<Retry;i++)
	{
		
		for (j = 0; j < timeout; j++) {
			if (Serial_RxFlag == 1) {
				if (strstr(Serial_RxPacket, Response) != NULL) {
					Serial_RxFlag = 0;
					return Success; // 成功接收到 "OK"
				}
				if (strstr(Serial_RxPacket, "ERROR") != NULL) {
					Serial_RxFlag = 0;
					return Failure; // 接收到 "ERROR"
				}
				Serial_RxFlag = 0; // 清除接收标志
			}
        //delay_ms(1);
		}
	}
    return Failure; // 超时未收到有效响应
}

void Sys_Soft_Reset(void)
{  
    SCB->AIRCR =0X05FA0000|(uint32_t)0x04;      
}

void errorLog()
{
	//printf("ERROR%d\r\n",num);
	while (1)
	{
		if (AT_SendCommand("AT\r\n", "OK\r\n", 100, 10) == Success)
		{
			Sys_Soft_Reset();
		}
		
	}
}

void AIR780E_Init(void)
{
	if(AT_SendCommand("AT\r\n", "OK", 3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
	
	if(AT_SendCommand("AT&F\r\n", "OK", 3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
	
	if(AT_SendCommand("AT+CSQ\r\n", "OK", 3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
	
	if(AT_SendCommand_2("AT+CPIN?\r\n", "READY","OK" ,3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
	
	if(AT_SendCommand("AT+COPS?\r\n", "OK", 3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
	
	if(AT_SendCommand_2("AT+CREG?\r\n", ",1","OK", 3000, 10)){}
	else if(AT_SendCommand_2("AT+CREG?\r\n", ",5", "OK",3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
	
	if(AT_SendCommand("AT+CIPSHUT\r\n", "OK", 5000, 10)){}
	OLED_Update();
	Delay_ms(1000);
		
	if(AT_SendCommand_2("AT+CGATT?\r\n", "+CGATT: 1","OK" ,3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
		
	if(AT_SendCommand("AT+CSTT\r\n", "OK", 3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
		
	if(AT_SendCommand("AT+CIICR\r\n", "OK", 3000, 10)){}
	//else errorLog();
	OLED_Update();
	Delay_ms(1000);
		
	if(AT_SendCommand_2("AT+CIFSR\r\n", ".","" ,3000, 10)){}
	//else errorLog();
	OLED_Update();
	
}

void AT_TCPConnect(char *TCPServer,char* Port)
{
	char send_buf[100] = {0};
	memset(send_buf, 0, 100);    
	strcpy(send_buf, "AT+CIPSTART=\"TCP\",\"");
	strcat(send_buf, TCPServer);
	strcat(send_buf, "\",\"");
	strcat(send_buf, Port);
	strcat(send_buf, "\"\r\n");
	if (AT_SendCommand(send_buf, "CONNECT OK\r\n", 10000, 5) == Success);
	else errorLog();
}

void AT_TCPSendData(char* send_buf)
{

	if (AT_SendCommand("AT+CIPSEND\r\n", ">", 3000, 5) == Success);
	else errorLog();
	
	if (AT_SendCommand(send_buf, send_buf, 3000, 1) == Success);
	else errorLog();

}

void set_AImodel(const char* model,const char* key,const char* url)
{
	strcpy(ai_model,model);
	strcpy(api_key,key);
	strcpy(base_url,url);
}

void Air780E_AIRequest(char* userContent, char* sysContent)
{
	char buf[100] = {0};
	char Body[1000];
	
    char protocol[10] = {0};  // 协议
    char host_and_port[50] = {0};  // 主机和端口
    char path[50] = {0};      // 路径

    // 分割协议
    char *protocol_end = strstr(base_url, "://");
    if (protocol_end != NULL) {
        strncpy(protocol, base_url, protocol_end - base_url);
        protocol[protocol_end - base_url] = '\0';  // 添加字符串结束符
    } else {
        //printf("无效的 URL：缺少协议\n");
        return ;
    }

    // 分割主机和端口
    char *host_start = protocol_end + 3;  // 跳过 "://"
    char *path_start = strstr(host_start, "/");

    if (path_start != NULL) {
        strncpy(host_and_port, host_start, path_start - host_start);
        host_and_port[path_start - host_start] = '\0';
    } else {
        strcpy(host_and_port, host_start);
    }

    // 分割路径
    if (path_start != NULL) {
        strcpy(path, path_start);
    } else {
        strcpy(path, "/");  // 默认路径
    }

	
	const char *Content_Type = "application/json";
	
	sprintf(Body,"{\"messages\": [{\"role\": \"system\", \"content\": \"%s\"}, {\"role\": \"user\", \"content\": \"%s\"}], \"model\": \"%s\"}",sysContent,userContent,ai_model);
	
	
	
	sprintf(buf, "POST %s/chat/completions HTTP/1.1\r\n", path);
	AT_SendCommand(buf,"",10,1);
	
	sprintf(buf, "Host: %s\r\n", host_and_port);
	AT_SendCommand(buf,"",10,1);
	
	sprintf(buf, "Content-Type: %s\r\n", Content_Type);
	AT_SendCommand(buf,"",10,1);
	
	sprintf(buf, "Authorization: Bearer %s\r\n", api_key);
	AT_SendCommand(buf,"",10,1);
	
	sprintf(buf, "Content-Length: %d\r\n\r\n", strlen(Body));
	AT_SendCommand(buf,"",10,1);
	
	AT_SendCommand(Body,"",10,1);
}

//char* Air780E_AIRecive(char* userContent, char* sysContent)
//{
//	char buf[100] = {0};
//	static char Body[1000];
//	
//	
//    char protocol[10] = {0};  // 协议
//    char host_and_port[50] = {0};  // 主机和端口
//    char path[50] = {0};      // 路径
//
//    // 分割协议
//    char *protocol_end = strstr(base_url, "://");
//    if (protocol_end != NULL) {
//        strncpy(protocol, base_url, protocol_end - base_url);
//        protocol[protocol_end - base_url] = '\0';  // 添加字符串结束符
//    } else {
//        //printf("无效的 URL：缺少协议\n");
//        return "";
//    }
//
//    // 分割主机和端口
//    char *host_start = protocol_end + 3;  // 跳过 "://"
//    char *path_start = strstr(host_start, "/");
//
//    if (path_start != NULL) {
//        strncpy(host_and_port, host_start, path_start - host_start);
//        host_and_port[path_start - host_start] = '\0';
//    } else {
//        strcpy(host_and_port, host_start);
//    }
//
//    // 分割路径
//    if (path_start != NULL) {
//        strcpy(path, path_start);
//    } else {
//        strcpy(path, "/");  // 默认路径
//    }
//
//	
//	const char *Content_Type = "application/json";
//	
//	sprintf(Body,"{\"messages\": [{\"role\": \"system\", \"content\": \"%s\"}, {\"role\": \"user\", \"content\": \"%s\"}], \"model\": \"%s\"}",sysContent,userContent,ai_model);
//	
//	
//	
//	sprintf(buf, "GET %s/chat/completions HTTP/1.1\r\n", path);
//	AT_SendCommand(buf,"",10,1);
//	
//	sprintf(buf, "Host: %s\r\n", host_and_port);
//	AT_SendCommand(buf,"",10,1);
//	
//	sprintf(buf, "Content-Type: %s\r\n", Content_Type);
//	AT_SendCommand(buf,"",10,1);
//	
//	sprintf(buf, "Authorization: Bearer %s\r\n", api_key);
//	AT_SendCommand(buf,"",10,1);
//	
//	sprintf(buf, "Content-Length: %d\r\n\r\n", strlen(Body));
//	AT_SendCommand(buf,"",10,1);
//	
//	AT_SendCommand(Body,"",10,1);
//}

