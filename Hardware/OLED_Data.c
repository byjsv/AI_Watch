#include "OLED_Data.h"

/**
  * 数据存储格式：
  * 纵向8点，高位在下，先从左到右，再从上到下
  * 每一个Bit对应一个像素点
  * 
  *      B0 B0                  B0 B0
  *      B1 B1                  B1 B1
  *      B2 B2                  B2 B2
  *      B3 B3  ------------->  B3 B3 --
  *      B4 B4                  B4 B4  |
  *      B5 B5                  B5 B5  |
  *      B6 B6                  B6 B6  |
  *      B7 B7                  B7 B7  |
  *                                    |
  *  -----------------------------------
  *  |   
  *  |   B0 B0                  B0 B0
  *  |   B1 B1                  B1 B1
  *  |   B2 B2                  B2 B2
  *  --> B3 B3  ------------->  B3 B3
  *      B4 B4                  B4 B4
  *      B5 B5                  B5 B5
  *      B6 B6                  B6 B6
  *      B7 B7                  B7 B7
  * 
  */

/*ASCII字模数据*********************/

/*宽8像素，高16像素*/
const uint8_t OLED_F8x16[][16] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//   0
	0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x33,0x30,0x00,0x00,0x00,// ! 1
	0x00,0x16,0x0E,0x00,0x16,0x0E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// " 2
	0x40,0xC0,0x78,0x40,0xC0,0x78,0x40,0x00,
	0x04,0x3F,0x04,0x04,0x3F,0x04,0x04,0x00,// # 3
	0x00,0x70,0x88,0xFC,0x08,0x30,0x00,0x00,
	0x00,0x18,0x20,0xFF,0x21,0x1E,0x00,0x00,// $ 4
	0xF0,0x08,0xF0,0x00,0xE0,0x18,0x00,0x00,
	0x00,0x21,0x1C,0x03,0x1E,0x21,0x1E,0x00,// % 5
	0x00,0xF0,0x08,0x88,0x70,0x00,0x00,0x00,
	0x1E,0x21,0x23,0x24,0x19,0x27,0x21,0x10,// & 6
	0x00,0x00,0x00,0x16,0x0E,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// ' 7
	0x00,0x00,0x00,0xE0,0x18,0x04,0x02,0x00,
	0x00,0x00,0x00,0x07,0x18,0x20,0x40,0x00,// ( 8
	0x00,0x02,0x04,0x18,0xE0,0x00,0x00,0x00,
	0x00,0x40,0x20,0x18,0x07,0x00,0x00,0x00,// ) 9
	0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,
	0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,// * 10
	0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x00,
	0x01,0x01,0x01,0x1F,0x01,0x01,0x01,0x00,// + 11
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xB0,0x70,0x00,0x00,0x00,0x00,0x00,// , 12
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,// - 13
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,// . 14
	0x00,0x00,0x00,0x00,0x80,0x60,0x18,0x04,
	0x00,0x60,0x18,0x06,0x01,0x00,0x00,0x00,// / 15
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,// 0 16
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,// 1 17
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,
	0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,// 2 18
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,
	0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,// 3 19
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,
	0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,// 4 20
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,
	0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,// 5 21
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,
	0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,// 6 22
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,
	0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,// 7 23
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,
	0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,// 8 24
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,
	0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,// 9 25
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,// : 26
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x80,0xB0,0x70,0x00,0x00,0x00,// ; 27
	0x00,0x00,0x80,0x40,0x20,0x10,0x08,0x00,
	0x00,0x01,0x02,0x04,0x08,0x10,0x20,0x00,// < 28
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x00,// = 29
	0x00,0x08,0x10,0x20,0x40,0x80,0x00,0x00,
	0x00,0x20,0x10,0x08,0x04,0x02,0x01,0x00,// > 30
	0x00,0x70,0x48,0x08,0x08,0x08,0xF0,0x00,
	0x00,0x00,0x00,0x30,0x36,0x01,0x00,0x00,// ? 31
	0xC0,0x30,0xC8,0x28,0xE8,0x10,0xE0,0x00,
	0x07,0x18,0x27,0x24,0x23,0x14,0x0B,0x00,// @ 32
	0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,
	0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,// A 33
	0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,// B 34
	0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,
	0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,// C 35
	0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,// D 36
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
	0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,// E 37
	0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,
	0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,// F 38
	0xC0,0x30,0x08,0x08,0x08,0x38,0x00,0x00,
	0x07,0x18,0x20,0x20,0x22,0x1E,0x02,0x00,// G 39
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,// H 40
	0x00,0x08,0x08,0xF8,0x08,0x08,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,// I 41
	0x00,0x00,0x08,0x08,0xF8,0x08,0x08,0x00,
	0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,0x00,// J 42
	0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,
	0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,// K 43
	0x08,0xF8,0x08,0x00,0x00,0x00,0x00,0x00,
	0x20,0x3F,0x20,0x20,0x20,0x20,0x30,0x00,// L 44
	0x08,0xF8,0xF8,0x00,0xF8,0xF8,0x08,0x00,
	0x20,0x3F,0x00,0x3F,0x00,0x3F,0x20,0x00,// M 45
	0x08,0xF8,0x30,0xC0,0x00,0x08,0xF8,0x08,
	0x20,0x3F,0x20,0x00,0x07,0x18,0x3F,0x00,// N 46
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x0F,0x10,0x20,0x20,0x20,0x10,0x0F,0x00,// O 47
	0x08,0xF8,0x08,0x08,0x08,0x08,0xF0,0x00,
	0x20,0x3F,0x21,0x01,0x01,0x01,0x00,0x00,// P 48
	0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,
	0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00,// Q 49
	0x08,0xF8,0x88,0x88,0x88,0x88,0x70,0x00,
	0x20,0x3F,0x20,0x00,0x03,0x0C,0x30,0x20,// R 50
	0x00,0x70,0x88,0x08,0x08,0x08,0x38,0x00,
	0x00,0x38,0x20,0x21,0x21,0x22,0x1C,0x00,// S 51
	0x18,0x08,0x08,0xF8,0x08,0x08,0x18,0x00,
	0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,// T 52
	0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,
	0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,// U 53
	0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,
	0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,// V 54
	0xF8,0x08,0x00,0xF8,0x00,0x08,0xF8,0x00,
	0x03,0x3C,0x07,0x00,0x07,0x3C,0x03,0x00,// W 55
	0x08,0x18,0x68,0x80,0x80,0x68,0x18,0x08,
	0x20,0x30,0x2C,0x03,0x03,0x2C,0x30,0x20,// X 56
	0x08,0x38,0xC8,0x00,0xC8,0x38,0x08,0x00,
	0x00,0x00,0x20,0x3F,0x20,0x00,0x00,0x00,// Y 57
	0x10,0x08,0x08,0x08,0xC8,0x38,0x08,0x00,
	0x20,0x38,0x26,0x21,0x20,0x20,0x18,0x00,// Z 58
	0x00,0x00,0x00,0xFE,0x02,0x02,0x02,0x00,
	0x00,0x00,0x00,0x7F,0x40,0x40,0x40,0x00,// [ 59
	0x00,0x0C,0x30,0xC0,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x06,0x38,0xC0,0x00,// \ 60
	0x00,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,
	0x00,0x40,0x40,0x40,0x7F,0x00,0x00,0x00,// ] 61
	0x00,0x20,0x10,0x08,0x04,0x08,0x10,0x20,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// ^ 62
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,// _ 63
	0x00,0x02,0x04,0x08,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// ` 64
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x19,0x24,0x22,0x22,0x22,0x3F,0x20,// a 65
	0x08,0xF8,0x00,0x80,0x80,0x00,0x00,0x00,
	0x00,0x3F,0x11,0x20,0x20,0x11,0x0E,0x00,// b 66
	0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00,
	0x00,0x0E,0x11,0x20,0x20,0x20,0x11,0x00,// c 67
	0x00,0x00,0x00,0x80,0x80,0x88,0xF8,0x00,
	0x00,0x0E,0x11,0x20,0x20,0x10,0x3F,0x20,// d 68
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x1F,0x22,0x22,0x22,0x22,0x13,0x00,// e 69
	0x00,0x80,0x80,0xF0,0x88,0x88,0x88,0x18,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,// f 70
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x6B,0x94,0x94,0x94,0x93,0x60,0x00,// g 71
	0x08,0xF8,0x00,0x80,0x80,0x80,0x00,0x00,
	0x20,0x3F,0x21,0x00,0x00,0x20,0x3F,0x20,// h 72
	0x00,0x80,0x98,0x98,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,// i 73
	0x00,0x00,0x00,0x80,0x98,0x98,0x00,0x00,
	0x00,0xC0,0x80,0x80,0x80,0x7F,0x00,0x00,// j 74
	0x08,0xF8,0x00,0x00,0x80,0x80,0x80,0x00,
	0x20,0x3F,0x24,0x02,0x2D,0x30,0x20,0x00,// k 75
	0x00,0x08,0x08,0xF8,0x00,0x00,0x00,0x00,
	0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,// l 76
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
	0x20,0x3F,0x20,0x00,0x3F,0x20,0x00,0x3F,// m 77
	0x00,0x80,0x80,0x00,0x80,0x80,0x00,0x00,
	0x00,0x20,0x3F,0x21,0x00,0x20,0x3F,0x20,// n 78
	0x00,0x00,0x80,0x80,0x80,0x80,0x00,0x00,
	0x00,0x1F,0x20,0x20,0x20,0x20,0x1F,0x00,// o 79
	0x80,0x80,0x00,0x80,0x80,0x00,0x00,0x00,
	0x80,0xFF,0xA1,0x20,0x20,0x11,0x0E,0x00,// p 80
	0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x00,
	0x00,0x0E,0x11,0x20,0x20,0xA0,0xFF,0x80,// q 81
	0x80,0x80,0x80,0x00,0x80,0x80,0x80,0x00,
	0x20,0x20,0x3F,0x21,0x20,0x00,0x01,0x00,// r 82
	0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x33,0x24,0x24,0x24,0x24,0x19,0x00,// s 83
	0x00,0x80,0x80,0xE0,0x80,0x80,0x00,0x00,
	0x00,0x00,0x00,0x1F,0x20,0x20,0x00,0x00,// t 84
	0x80,0x80,0x00,0x00,0x00,0x80,0x80,0x00,
	0x00,0x1F,0x20,0x20,0x20,0x10,0x3F,0x20,// u 85
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
	0x00,0x01,0x0E,0x30,0x08,0x06,0x01,0x00,// v 86
	0x80,0x80,0x00,0x80,0x00,0x80,0x80,0x80,
	0x0F,0x30,0x0C,0x03,0x0C,0x30,0x0F,0x00,// w 87
	0x00,0x80,0x80,0x00,0x80,0x80,0x80,0x00,
	0x00,0x20,0x31,0x2E,0x0E,0x31,0x20,0x00,// x 88
	0x80,0x80,0x80,0x00,0x00,0x80,0x80,0x80,
	0x80,0x81,0x8E,0x70,0x18,0x06,0x01,0x00,// y 89
	0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
	0x00,0x21,0x30,0x2C,0x22,0x21,0x30,0x00,// z 90
	0x00,0x00,0x00,0x00,0x80,0x7C,0x02,0x02,
	0x00,0x00,0x00,0x00,0x00,0x3F,0x40,0x40,// { 91
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,// | 92
	0x00,0x02,0x02,0x7C,0x80,0x00,0x00,0x00,
	0x00,0x40,0x40,0x3F,0x00,0x00,0x00,0x00,// } 93
	0x00,0x80,0x40,0x40,0x80,0x00,0x00,0x80,
	0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,// ~ 94
};

/*宽6像素，高8像素*/
const uint8_t OLED_F6x8[][6] = 
{
	0x00,0x00,0x00,0x00,0x00,0x00,//   0
	0x00,0x00,0x00,0x2F,0x00,0x00,// ! 1
	0x00,0x00,0x07,0x00,0x07,0x00,// " 2
	0x00,0x14,0x7F,0x14,0x7F,0x14,// # 3
	0x00,0x24,0x2A,0x7F,0x2A,0x12,// $ 4
	0x00,0x23,0x13,0x08,0x64,0x62,// % 5
	0x00,0x36,0x49,0x55,0x22,0x50,// & 6
	0x00,0x00,0x00,0x07,0x00,0x00,// ' 7
	0x00,0x00,0x1C,0x22,0x41,0x00,// ( 8
	0x00,0x00,0x41,0x22,0x1C,0x00,// ) 9
	0x00,0x14,0x08,0x3E,0x08,0x14,// * 10
	0x00,0x08,0x08,0x3E,0x08,0x08,// + 11
	0x00,0x00,0x00,0xA0,0x60,0x00,// , 12
	0x00,0x08,0x08,0x08,0x08,0x08,// - 13
	0x00,0x00,0x60,0x60,0x00,0x00,// . 14
	0x00,0x20,0x10,0x08,0x04,0x02,// / 15
	0x00,0x3E,0x51,0x49,0x45,0x3E,// 0 16
	0x00,0x00,0x42,0x7F,0x40,0x00,// 1 17
	0x00,0x42,0x61,0x51,0x49,0x46,// 2 18
	0x00,0x21,0x41,0x45,0x4B,0x31,// 3 19
	0x00,0x18,0x14,0x12,0x7F,0x10,// 4 20
	0x00,0x27,0x45,0x45,0x45,0x39,// 5 21
	0x00,0x3C,0x4A,0x49,0x49,0x30,// 6 22
	0x00,0x01,0x71,0x09,0x05,0x03,// 7 23
	0x00,0x36,0x49,0x49,0x49,0x36,// 8 24
	0x00,0x06,0x49,0x49,0x29,0x1E,// 9 25
	0x00,0x00,0x36,0x36,0x00,0x00,// : 26
	0x00,0x00,0x56,0x36,0x00,0x00,// ; 27
	0x00,0x08,0x14,0x22,0x41,0x00,// < 28
	0x00,0x14,0x14,0x14,0x14,0x14,// = 29
	0x00,0x00,0x41,0x22,0x14,0x08,// > 30
	0x00,0x02,0x01,0x51,0x09,0x06,// ? 31
	0x00,0x3E,0x49,0x55,0x59,0x2E,// @ 32
	0x00,0x7C,0x12,0x11,0x12,0x7C,// A 33
	0x00,0x7F,0x49,0x49,0x49,0x36,// B 34
	0x00,0x3E,0x41,0x41,0x41,0x22,// C 35
	0x00,0x7F,0x41,0x41,0x22,0x1C,// D 36
	0x00,0x7F,0x49,0x49,0x49,0x41,// E 37
	0x00,0x7F,0x09,0x09,0x09,0x01,// F 38
	0x00,0x3E,0x41,0x49,0x49,0x7A,// G 39
	0x00,0x7F,0x08,0x08,0x08,0x7F,// H 40
	0x00,0x00,0x41,0x7F,0x41,0x00,// I 41
	0x00,0x20,0x40,0x41,0x3F,0x01,// J 42
	0x00,0x7F,0x08,0x14,0x22,0x41,// K 43
	0x00,0x7F,0x40,0x40,0x40,0x40,// L 44
	0x00,0x7F,0x02,0x0C,0x02,0x7F,// M 45
	0x00,0x7F,0x04,0x08,0x10,0x7F,// N 46
	0x00,0x3E,0x41,0x41,0x41,0x3E,// O 47
	0x00,0x7F,0x09,0x09,0x09,0x06,// P 48
	0x00,0x3E,0x41,0x51,0x21,0x5E,// Q 49
	0x00,0x7F,0x09,0x19,0x29,0x46,// R 50
	0x00,0x46,0x49,0x49,0x49,0x31,// S 51
	0x00,0x01,0x01,0x7F,0x01,0x01,// T 52
	0x00,0x3F,0x40,0x40,0x40,0x3F,// U 53
	0x00,0x1F,0x20,0x40,0x20,0x1F,// V 54
	0x00,0x3F,0x40,0x38,0x40,0x3F,// W 55
	0x00,0x63,0x14,0x08,0x14,0x63,// X 56
	0x00,0x07,0x08,0x70,0x08,0x07,// Y 57
	0x00,0x61,0x51,0x49,0x45,0x43,// Z 58
	0x00,0x00,0x7F,0x41,0x41,0x00,// [ 59
	0x00,0x02,0x04,0x08,0x10,0x20,// \ 60
	0x00,0x00,0x41,0x41,0x7F,0x00,// ] 61
	0x00,0x04,0x02,0x01,0x02,0x04,// ^ 62
	0x00,0x40,0x40,0x40,0x40,0x40,// _ 63
	0x00,0x00,0x01,0x02,0x04,0x00,// ` 64
	0x00,0x20,0x54,0x54,0x54,0x78,// a 65
	0x00,0x7F,0x48,0x44,0x44,0x38,// b 66
	0x00,0x38,0x44,0x44,0x44,0x20,// c 67
	0x00,0x38,0x44,0x44,0x48,0x7F,// d 68
	0x00,0x38,0x54,0x54,0x54,0x18,// e 69
	0x00,0x08,0x7E,0x09,0x01,0x02,// f 70
	0x00,0x18,0xA4,0xA4,0xA4,0x7C,// g 71
	0x00,0x7F,0x08,0x04,0x04,0x78,// h 72
	0x00,0x00,0x44,0x7D,0x40,0x00,// i 73
	0x00,0x40,0x80,0x84,0x7D,0x00,// j 74
	0x00,0x7F,0x10,0x28,0x44,0x00,// k 75
	0x00,0x00,0x41,0x7F,0x40,0x00,// l 76
	0x00,0x7C,0x04,0x18,0x04,0x78,// m 77
	0x00,0x7C,0x08,0x04,0x04,0x78,// n 78
	0x00,0x38,0x44,0x44,0x44,0x38,// o 79
	0x00,0xFC,0x24,0x24,0x24,0x18,// p 80
	0x00,0x18,0x24,0x24,0x18,0xFC,// q 81
	0x00,0x7C,0x08,0x04,0x04,0x08,// r 82
	0x00,0x48,0x54,0x54,0x54,0x20,// s 83
	0x00,0x04,0x3F,0x44,0x40,0x20,// t 84
	0x00,0x3C,0x40,0x40,0x20,0x7C,// u 85
	0x00,0x1C,0x20,0x40,0x20,0x1C,// v 86
	0x00,0x3C,0x40,0x30,0x40,0x3C,// w 87
	0x00,0x44,0x28,0x10,0x28,0x44,// x 88
	0x00,0x1C,0xA0,0xA0,0xA0,0x7C,// y 89
	0x00,0x44,0x64,0x54,0x4C,0x44,// z 90
	0x00,0x00,0x08,0x7F,0x41,0x00,// { 91
	0x00,0x00,0x00,0x7F,0x00,0x00,// | 92
	0x00,0x00,0x41,0x7F,0x08,0x00,// } 93
	0x00,0x08,0x04,0x08,0x10,0x08,// ~ 94
};
/*********************ASCII字模数据*/


/*汉字字模数据*********************/

/*相同的汉字只需要定义一次，汉字不分先后顺序*/
/*必须全部为汉字或者全角字符，不要加入任何半角字符*/

/*宽16像素，高16像素*/
const ChineseCell_t OLED_CF16x16[] = {
	
	"，",
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x58,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	"。",
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x18,0x24,0x24,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	"你",
	0x00,0x80,0x60,0xF8,0x07,0x40,0x20,0x18,0x0F,0x08,0xC8,0x08,0x08,0x28,0x18,0x00,
	0x01,0x00,0x00,0xFF,0x00,0x10,0x0C,0x03,0x40,0x80,0x7F,0x00,0x01,0x06,0x18,0x00,
	
	"好",
	0x10,0x10,0xF0,0x1F,0x10,0xF0,0x00,0x80,0x82,0x82,0xE2,0x92,0x8A,0x86,0x80,0x00,
	0x40,0x22,0x15,0x08,0x16,0x61,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,
	
	"世",
	0x20,0x20,0x20,0xFE,0x20,0x20,0xFF,0x20,0x20,0x20,0xFF,0x20,0x20,0x20,0x20,0x00,
	0x00,0x00,0x00,0x7F,0x40,0x40,0x47,0x44,0x44,0x44,0x47,0x40,0x40,0x40,0x00,0x00,
	
	"界",
	0x00,0x00,0x00,0xFE,0x92,0x92,0x92,0xFE,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,0x00,
	0x08,0x08,0x04,0x84,0x62,0x1E,0x01,0x00,0x01,0xFE,0x02,0x04,0x04,0x08,0x08,0x00,
	"哈",
	0x00,0xFC,0x04,0x04,0xFC,0x20,0x50,0x48,0x44,0x43,0x44,0x48,0x50,0x20,0x20,0x00,
	0x00,0x0F,0x04,0x04,0x0F,0x00,0xFE,0x42,0x42,0x42,0x42,0x42,0xFE,0x00,0x00,0x00,
	"喽",
	0x00,0xFC,0x04,0x04,0xFC,0x00,0x90,0x52,0x34,0x10,0x7F,0x10,0x34,0x52,0x90,0x00,
	0x00,0x0F,0x04,0x04,0x0F,0x82,0x82,0x5A,0x56,0x23,0x22,0x52,0x4E,0x82,0x02,0x00,
	"血",
	0x00,0x00,0xF8,0x08,0x08,0xF8,0x0C,0x0B,0x08,0xF8,0x08,0x08,0xF8,0x00,0x00,0x00,
	0x40,0x40,0x7F,0x40,0x40,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x7F,0x40,0x40,0x00,
	"氧",
	0x08,0x24,0x23,0x6A,0xAA,0x2A,0xAA,0x6A,0x2A,0x2A,0x2A,0xEA,0x02,0x02,0x00,0x00,
	0x10,0x11,0x15,0x15,0x15,0xFF,0x15,0x15,0x15,0x11,0x10,0x0F,0x30,0x40,0xF8,0x00,
	"体",
	0x00,0x80,0x60,0xF8,0x07,0x10,0x10,0x10,0xD0,0xFF,0xD0,0x10,0x10,0x10,0x00,0x00,
	0x01,0x00,0x00,0xFF,0x10,0x08,0x04,0x0B,0x08,0xFF,0x08,0x0B,0x04,0x08,0x10,0x00,
	"外",
	0x00,0xC0,0x30,0x1F,0x10,0x10,0xF0,0x00,0x00,0xFF,0x20,0x40,0x80,0x00,0x00,0x00,
	0x81,0x40,0x21,0x12,0x0C,0x03,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x03,0x00,0x00,
	"温",
	0x10,0x60,0x02,0x8C,0x00,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
	0x04,0x04,0x7E,0x01,0x40,0x7E,0x42,0x42,0x7E,0x42,0x7E,0x42,0x42,0x7E,0x40,0x00,
	"度",
	0x00,0x00,0xFC,0x24,0x24,0x24,0xFC,0x25,0x26,0x24,0xFC,0x24,0x24,0x24,0x04,0x00,
	0x40,0x30,0x8F,0x80,0x84,0x4C,0x55,0x25,0x25,0x25,0x55,0x4C,0x80,0x80,0x80,0x00,
	"心",
	0x00,0x00,0x80,0x00,0x00,0xE0,0x02,0x04,0x18,0x00,0x00,0x00,0x40,0x80,0x00,0x00,
	0x10,0x0C,0x03,0x00,0x00,0x3F,0x40,0x40,0x40,0x40,0x40,0x78,0x00,0x01,0x0E,0x00,
	"率",
	0x00,0x14,0xA4,0x44,0x24,0x34,0xAD,0x66,0x24,0x94,0x04,0x44,0xA4,0x14,0x00,0x00,
	0x08,0x09,0x08,0x08,0x09,0x09,0x09,0xFD,0x09,0x09,0x0B,0x08,0x08,0x09,0x08,0x00,
	"℃",
	0x00,0x0C,0x12,0x0C,0x00,0xC0,0x70,0x10,0x08,0x08,0x08,0x08,0x10,0x30,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0F,0x18,0x30,0x20,0x20,0x20,0x20,0x30,0x1C,0x00,0x00,
	"时",
	0x00,0xFC,0x84,0x84,0x84,0xFC,0x00,0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x00,
	0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,0x01,0x06,0x40,0x80,0x7F,0x00,0x00,0x00,
	"间",
	0x00,0xF8,0x01,0x06,0x00,0xF0,0x12,0x12,0x12,0xF2,0x02,0x02,0x02,0xFE,0x00,0x00,
	0x00,0xFF,0x00,0x00,0x00,0x1F,0x11,0x11,0x11,0x1F,0x00,0x40,0x80,0x7F,0x00,0x00,
	"设",
	0x40,0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x9E,0xA0,0x20,0x20,0x00,
	0x00,0x00,0x00,0x3F,0x90,0x88,0x40,0x43,0x2C,0x10,0x28,0x46,0x41,0x80,0x80,0x00,
    "置",
	0x00,0x17,0x15,0xD5,0x55,0x57,0x55,0x7D,0x55,0x57,0x55,0xD5,0x15,0x17,0x00,0x00,
	0x40,0x40,0x40,0x7F,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7F,0x40,0x40,0x40,0x00,



	
	/*按照上面的格式，在这个位置加入新的汉字数据*/
	//...
	
	
	/*未找到指定汉字时显示的默认图形（一个方框，内部一个问号），请确保其位于数组最末尾*/
	"",		
	0xFF,0x01,0x01,0x01,0x31,0x09,0x09,0x09,0x09,0x89,0x71,0x01,0x01,0x01,0x01,0xFF,
	0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x96,0x81,0x80,0x80,0x80,0x80,0x80,0x80,0xFF,

};

const Small_ChineseCell_t OLED_CF12x12[] = {
	"血",
	0x00,0xF8,0x08,0x0C,0xFB,0x08,0xF8,0x08,0x08,0xF8,0x00,0x00,0x08,0x0F,0x08,0x08,
	0x0F,0x08,0x0F,0x08,0x08,0x0F,0x08,0x00,
	"氧",
	0x08,0x24,0xAB,0xBA,0xEA,0xBA,0xAA,0x2A,0xFA,0x02,0x02,0x00,0x02,0x02,0x02,0x02,
	0x0F,0x02,0x02,0x02,0x03,0x04,0x0E,0x00,
	"饱",
	0x08,0xE7,0x14,0x2C,0x10,0xFC,0x97,0x94,0xF4,0x04,0xFC,0x00,0x00,0x0F,0x04,0x02,
	0x00,0x07,0x08,0x08,0x08,0x09,0x0D,0x00,
	"和",
	0x10,0x92,0x52,0xFE,0x51,0x90,0xFC,0x04,0x04,0x04,0xFC,0x00,0x01,0x00,0x00,0x0F,
	0x00,0x00,0x07,0x02,0x02,0x02,0x07,0x00,
	"度",
	0x00,0xFE,0x0A,0x8A,0xBE,0xAA,0xAB,0xAA,0xBE,0x8A,0x0A,0x00,0x08,0x07,0x00,0x08,
	0x09,0x0A,0x04,0x04,0x0A,0x09,0x08,0x00,
	"心",
	0x00,0xC0,0x00,0xF0,0x02,0x04,0x18,0x00,0x00,0x20,0xC0,0x00,0x02,0x01,0x00,0x07,
	0x08,0x08,0x08,0x08,0x0E,0x00,0x01,0x00,
	"率",
	0x02,0x8A,0x52,0x9A,0xD6,0xB3,0xD2,0x8A,0x52,0x8A,0x02,0x00,0x02,0x02,0x02,0x02,
	0x02,0x0F,0x02,0x02,0x02,0x02,0x02,0x00,
	"体",
	0x10,0xFC,0x03,0x88,0x48,0x28,0xFF,0x28,0x48,0x88,0x00,0x00,0x00,0x0F,0x01,0x00,
	0x02,0x02,0x0F,0x02,0x02,0x00,0x01,0x00,
	"表",
	0x40,0x44,0x54,0x54,0xD4,0x7F,0xD4,0x54,0x54,0x44,0x40,0x00,0x04,0x04,0x02,0x0F,
	0x08,0x04,0x01,0x02,0x04,0x0A,0x09,0x00,
	"温",
	0x22,0x44,0x00,0xC0,0x5F,0xD5,0x55,0xD5,0x5F,0xC0,0x00,0x00,0x04,0x02,0x09,0x0F,
	0x08,0x0F,0x08,0x0F,0x08,0x0F,0x08,0x00,
	"度",
	0x00,0xFE,0x0A,0x8A,0xBE,0xAA,0xAB,0xAA,0xBE,0x8A,0x0A,0x00,0x08,0x07,0x00,0x08,
	0x09,0x0A,0x04,0x04,0x0A,0x09,0x08,0x00,
	"步",
	0x20,0x20,0x3E,0xA0,0x20,0xBF,0x24,0x24,0x24,0xA4,0x20,0x00,0x00,0x0A,0x09,0x08,
	0x04,0x07,0x02,0x02,0x01,0x00,0x00,0x00,
	"数",
	0x48,0x2A,0x98,0x7F,0x28,0x4A,0x10,0xEF,0x08,0xF8,0x08,0x00,0x09,0x0B,0x05,0x05,
	0x0B,0x00,0x08,0x05,0x02,0x05,0x08,0x00,
	"时",
	0xFE,0x22,0x22,0xFE,0x00,0x08,0x48,0x88,0x08,0xFF,0x08,0x00,0x07,0x02,0x02,0x07,
	0x00,0x00,0x00,0x09,0x08,0x0F,0x00,0x00,
	"间",
	0x00,0xF9,0x02,0xF8,0x49,0x49,0x49,0x49,0xF9,0x01,0xFF,0x00,0x00,0x0F,0x00,0x03,
	0x02,0x02,0x02,0x02,0x0B,0x08,0x0F,0x00,
	"设",
	0x10,0x11,0xF2,0x00,0x50,0xCF,0x41,0x41,0x4F,0xD0,0x10,0x00,0x00,0x00,0x07,0x02,
	0x08,0x08,0x05,0x02,0x05,0x08,0x08,0x00,
	"置",
	0x10,0x17,0xD5,0x55,0x57,0x7D,0x57,0x55,0xD5,0x17,0x10,0x00,0x08,0x08,0x0F,0x08,
	0x08,0x0E,0x08,0x08,0x0F,0x08,0x08,0x00,
	"天",
	0x20,0x22,0x22,0x22,0xA2,0x7E,0xA2,0x22,0x22,0x22,0x20,0x00,0x08,0x08,0x04,0x02,
	0x01,0x00,0x01,0x02,0x04,0x08,0x08,0x00,
	"气",
	0x08,0x24,0x2B,0x2A,0x2A,0x2A,0x2A,0x2A,0xEA,0x0A,0x02,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x03,0x04,0x0E,0x00,


};

/*********************汉字字模数据*/


/*图像数据*********************/

/*测试图像（一个方框，内部一个二极管符号），宽16像素，高16像素*/
const uint8_t Diode[] = {
	0xFF,0x01,0x81,0x81,0x81,0xFD,0x89,0x91,0xA1,0xC1,0xFD,0x81,0x81,0x81,0x01,0xFF,
	0xFF,0x80,0x80,0x80,0x80,0x9F,0x88,0x84,0x82,0x81,0x9F,0x80,0x80,0x80,0x80,0xFF,
};


/*大型汉字图像，大小为宽16像素，高28像素    **************************************/
const uint8_t Num0[] = {
	0x00,0x00,0x00,0xC0,0xE0,0x30,0x18,0x08,0x08,0x08,0x30,0xE0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0xFE,0xFF,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,
	0x00,0x00,0x07,0x3F,0x78,0xC0,0x80,0x00,0x00,0x00,0xC0,0x70,0x3F,0x07,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,/*"0",0*/
};


const uint8_t Num1[] = {
	0x00,0x00,0x00,0x20,0x20,0x20,0x20,0xF0,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,/*"1",1*/
};

const uint8_t Num2[] = {
	0x00,0x00,0xC0,0x20,0x10,0x08,0x08,0x08,0x08,0x08,0x18,0x30,0xF0,0xC0,0x00,0x00,
	0x00,0x00,0x03,0x03,0x00,0x00,0x00,0x00,0x80,0xC0,0x60,0x38,0x1F,0x07,0x00,0x00,
	0x00,0x00,0xC0,0xA0,0x90,0x88,0x86,0x83,0x81,0x80,0x80,0x80,0xC0,0x78,0x00,0x00,
	0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,/*"2",2*/
};

const uint8_t Num3[] = {
	0x00,0x00,0xE0,0xF0,0x10,0x08,0x08,0x08,0x08,0x18,0x30,0xE0,0xC0,0x00,0x00,0x00,
	0x00,0x00,0x01,0x01,0x00,0x00,0x20,0x20,0x20,0x70,0x58,0xCF,0x87,0x00,0x00,0x00,
	0x00,0x00,0x78,0xF8,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0x7F,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,/*"3",3*/
};

const uint8_t Num4[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0xF8,0xF8,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x80,0xC0,0x30,0x0C,0x02,0x01,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,
	0x00,0x06,0x05,0x04,0x04,0x04,0x04,0x04,0x04,0xFF,0xFF,0x04,0x04,0x04,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,/*"4",4*/
};

const uint8_t Num5[] = {
	0x00,0x00,0x00,0xE0,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x00,0x00,
	0x00,0x00,0x00,0x7F,0x20,0x10,0x08,0x08,0x08,0x08,0x18,0x30,0xE0,0x80,0x00,0x00,
	0x00,0x00,0x78,0x98,0x80,0x00,0x00,0x00,0x00,0x00,0x80,0xE0,0x7F,0x1F,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,/*"5",5*/	
};

const uint8_t Num6[] = {
	0x00,0x00,0x00,0x80,0xE0,0x30,0x10,0x08,0x08,0x08,0x08,0x70,0x70,0x00,0x00,0x00,
	0x00,0x00,0xFC,0xFF,0x60,0x10,0x18,0x08,0x08,0x08,0x18,0x30,0xE0,0x80,0x00,0x00,
	0x00,0x00,0x0F,0x3F,0xF0,0xC0,0x80,0x00,0x00,0x00,0x80,0xC0,0x7F,0x1F,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,/*"6",6*/	
};

const uint8_t Num7[] = {
	0x00,0x00,0xC0,0x78,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0xD8,0x38,0x18,0x00,0x00,
	0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x80,0x60,0x1C,0x03,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"7",7*/
};

const uint8_t Num8[] = {
	0x00,0x00,0xC0,0xE0,0x30,0x18,0x08,0x08,0x08,0x08,0x18,0x30,0xE0,0xC0,0x00,0x00,
	0x00,0x00,0x87,0xCF,0x5E,0x38,0x38,0x30,0x60,0xE0,0xD0,0xC8,0x8F,0x03,0x00,0x00,
	0x00,0x3E,0x7F,0xC1,0x80,0x00,0x00,0x00,0x00,0x00,0x81,0xC3,0x7F,0x3E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,/*"8",8*/	
};

const uint8_t Num9[] = {
	0x00,0x80,0xE0,0x70,0x10,0x08,0x08,0x08,0x08,0x08,0x10,0x60,0xC0,0x00,0x00,0x00,
	0x00,0x3F,0x7F,0xE0,0x80,0x00,0x00,0x00,0x00,0x80,0xC0,0x20,0xFF,0xFF,0x00,0x00,
	0x00,0x00,0xE0,0xE0,0x01,0x01,0x01,0x01,0x81,0xC0,0x60,0x3C,0x0F,0x03,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"9",9*/
	
};


//     :号    13X28
const uint8_t spit[] = {
	0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x03,0x07,0x07,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x3C,0x3C,0x18,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*":",0*/

};

//     缺少信号     12X8
const uint8_t No_Signer[] = {
	0x00,0x3C,0x42,0xBD,0x42,0x18,0x18,0x42,0xBD,0x42,0x3C,0x00

};

//     50X50 齿轮图标
const uint8_t Setting[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xE0,0xE0,0xC0,0x80,0x0C,0xFC,
	0xFE,0xFE,0xFE,0xF8,0xE0,0xC0,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xC0,0xF0,0xFC,0xFE,
	0xFE,0xFE,0x7C,0x04,0x80,0xC0,0xE0,0xE0,0xE0,0xC0,0x80,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x60,0xF0,0xF8,0xF8,0xF8,0xF0,0xF3,0xF7,0xFF,0xFF,0xFF,0xFF,
	0x7F,0x3F,0x3F,0xFF,0xFF,0xC7,0x87,0x07,0x07,0x07,0x03,0x03,0x07,0x07,0x07,0x87,
	0xEF,0xFF,0x7F,0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFF,0xE7,0xF1,0xF0,0xF8,0xF8,0xF8,
	0x70,0x40,0x00,0x00,0x7C,0xFC,0xFC,0xF8,0xF8,0xF9,0xFF,0xFF,0xFF,0xFF,0x3F,0x07,
	0x01,0x00,0x00,0x00,0x00,0x00,0x01,0xC7,0xFF,0xFE,0xF8,0xF8,0xF8,0xF8,0xF8,0xFC,
	0xFE,0xEF,0xC7,0x01,0x00,0x00,0x00,0x00,0x00,0x03,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xF9,0xF8,0xFC,0xFC,0x7C,0x70,0xF8,0xF8,0xFC,0xFC,0xFC,0x7F,0xFF,0xFF,0xFF,0xFF,
	0xF7,0x87,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x1F,0xBF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xBF,0x1F,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x87,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFC,0xFC,0xFC,0xF8,0x78,0x00,0x00,0x18,0x3C,0x7C,0x7E,0x7F,0x3F,
	0x3F,0xBF,0xFF,0xFF,0xFE,0xF8,0xF0,0xE0,0xE0,0xF0,0xFC,0xBF,0x8F,0x83,0x00,0x00,
	0x00,0x00,0x00,0x01,0x87,0x8F,0xBE,0xF8,0xF0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,0xFF,
	0xBF,0x3F,0x3F,0x7F,0x7E,0x7C,0x38,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x04,0x0F,0x1F,0x3F,0x1F,0x0F,0x07,0xC3,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,0x1F,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x1F,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0x83,0x07,0x0F,
	0x1F,0x3F,0x1F,0x0E,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,
	0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

//     12X12 心形图标
const uint8_t HRate[] = {
	0x00,0x78,0xFC,0xFE,0xFE,0xFC,0xFC,0xFE,0xFE,0xFC,0x78,0x00,0x00,0x00,0x00,0x01,
	0x03,0x07,0x07,0x03,0x01,0x00,0x00,0x00
};
//     12X12 氧气图标
const uint8_t OxRate[] = {
	0x00,0xF0,0xEC,0xF2,0xF1,0xE1,0xC1,0xE1,0xF2,0xFC,0xF0,0x00,0x00,0x03,0x07,0x0F,
	0x0F,0x0F,0x0F,0x0F,0x0F,0x07,0x03,0x00
};
//     12X12 火焰图标
const uint8_t fire[] = {
	0x00,0xF0,0xFC,0xE0,0xFC,0x7E,0x3F,0xFC,0xE0,0xFC,0xF0,0x00,0x00,0x03,0x07,0x07,
	0x0D,0x08,0x08,0x0D,0x07,0x07,0x03,0x00
};
//     12X12 步数图标
const uint8_t step[] = {
	0x80,0x40,0x40,0x40,0x40,0x20,0x18,0x06,0x81,0x61,0x12,0x0C,0x01,0x02,0x04,0x04,
	0x08,0x08,0x04,0x03,0x00,0x00,0x00,0x00
};
//     12X12 哑铃图标
const uint8_t barbell[] = {
	0xF0,0xFC,0xFC,0x60,0x60,0x60,0x60,0x60,0x60,0xFC,0xFC,0xF0,0x00,0x03,0x03,0x00,
	0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00
};


/*按照上面的格式，在这个位置加入新的图像数据*/
//...

/*********************图像数据*/


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
