#ifndef __AIR780E_H
#define __AIR780E_H

#define Success 1
#define Failure 0

int remove_FirstSubstring(char *str, char *sub);
uint8_t AT_SendCommand(char* command,char *Response, uint16_t timeout, uint8_t Retry) ;
uint8_t AT_SendCommand_2(char* command,char *Response, char *Response2, uint16_t timeout, uint8_t Retry) ;
void AIR780E_Init(void);

#endif
