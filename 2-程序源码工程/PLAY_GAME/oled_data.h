#ifndef __OLED_DATA_H
#define __OLED_DATA_H
#include "stdint.h"

	
/*中文字符字节宽度*/
#define OLED_CHN_CHAR_WIDTH			3		//UTF-8编码格式给3，GB2312编码格式给2

/*字模基本单元*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//汉字索引
	uint8_t Data[32];						//字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t code OLED_F8x16[][16];
extern const uint8_t code OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t code OLED_CF16x16[];

/*图像数据声明*/

//星球大战
extern const uint8_t code Diode[];
extern const unsigned char code dioda16[32];

//小恐龙
extern const unsigned char code GROUND[200];
extern const unsigned char code CLOUD[24];
extern const unsigned char code DINO[2][32];
extern const unsigned char code DINO_JUMP[8][48];
extern const unsigned char code CACTUS_1[];
extern const unsigned char code CACTUS_2[];
extern const unsigned char code CACTUS_3[];
extern const unsigned char code CACTUS_4[];
extern const unsigned char code RESTART[];
extern const unsigned char code COVER[];
extern const unsigned char code COVER2[];
extern const unsigned char code COVER3[];
extern const unsigned char code COVER_PLAY_HANDLE[];
extern const unsigned char code COVER_PLAY_GAME[];

//贪吃蛇
extern const unsigned char code body[8];
extern const unsigned char code food_good[8];

//俄罗斯
extern const unsigned char  H_Grid_TTTRIS[];
extern const unsigned char code Pieces_TTRIS1[];
extern const unsigned char  tiny_PREVIEW_block_TTTRIS[] ;
extern const unsigned char  tinyblock_TTTRIS[];
extern const unsigned char  tinyblock2_TTTRIS[];
extern const unsigned char code police_TTRIS [];
extern const unsigned char code start_button_1_TTRIS [];
extern const unsigned char code start_button_2_TTRIS [] ;
extern const unsigned char code chateau_TTRIS [] ;
extern const unsigned char code  BACKGROUND_TTRIS [];

#endif
