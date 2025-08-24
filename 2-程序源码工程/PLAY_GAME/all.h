#ifndef _ALL_H
#define _ALL_H
#include<STC15F2K60S2.H>
#include<intrins.h>
#include<stdio.h>
#include<stdlib.h>
typedef unsigned char u8;
typedef unsigned short u16;
sbit fn2_key = P0^4;
sbit up_key = P0^6;
sbit down_key = P2^5;
sbit LED = P1^3;
sbit Mode_key = P0^5;
sbit right_key = P2^6;
sbit left_key = P2^7;
sbit handle_key = P0^7;


#include"WS2812.h"
#endif