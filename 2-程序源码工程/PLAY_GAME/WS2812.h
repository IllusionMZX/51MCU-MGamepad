#ifndef WS2812
#define WS2812
/*******单片机主频=晶振频率/分频系数
WSCASE=1 30 29 28 27 26 25 24 
WSCASE=2 24 23 22 21 20 19
WSCASE=3 19 18 17 16 15
WSCASE=4 15 14 13 12
WSCASE=5 12 11
WSCASE=6 11 10
WSCASE=7 10  9  8
*/
#define WSCASE 1//查表修改频率
#define WSCOUNT 8
sbit WS2812_DI=P0^0;
#define MAX_BRIGHTNESS 255 // 最大亮度
#define MIN_BRIGHTNESS 0   // 最小亮度
#define STEP 1             // 每次调整的亮度步长
extern void WS2812_Ser();
extern u8 WS2812_BUffer[WSCOUNT][3];
#endif