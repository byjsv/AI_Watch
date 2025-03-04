#ifndef __AIR780E_H
#define __AIR780E_H

#define Success 1
#define Failure 0

int remove_FirstSubstring(char *str, char *sub);
uint8_t AT_SendCommand(char* command,char *Response, uint16_t timeout, uint8_t Retry) ;
uint8_t AT_SendCommand_2(char* command,char *Response, char *Response2, uint16_t timeout, uint8_t Retry) ;
void AIR780E_Init(void);

uint8_t AT_WaitResponse(char *Response, uint16_t timeout, uint8_t Retry) ;
void Sys_Soft_Reset(void);

void errorLog(void);

void AT_TCPConnect(char *TCPServer,char* Port);

void AT_TCPSendData(char* send_buf);
void set_AImodel(const char* model,const char* key,const char* url);
void Air780E_AIRequest(char* userContent, char* sysContent);
char* Air780E_AIRecive(char* userContent, char* sysContent);



#endif
