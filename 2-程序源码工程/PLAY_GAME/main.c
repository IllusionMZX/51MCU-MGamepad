/*********参考资料****************
游戏设计
https://space.bilibili.com/189153447
https://www.bilibili.com/video/BV1bL4y1N77D/?spm_id_from=333.788.player.switch&vd_source=1e593f21abb33e274077202520cf0b80
WS2812彩灯底层代码
https://www.bilibili.com/video/BV1jE411Q7GN?spm_id_from=333.788.player.switch&vd_source=1e593f21abb33e274077202520cf0b80&p=2
MPU6050底层代码
https://gitee.com/gerhardt1024/mpu6050/tree/master
********************************/
#include <STC15F2K60S2.h>
#include <stdlib.h>
#include <intrins.h>
#include <math.h>
#include "oled.h"
#include "bluetooth.h"
#include "all.h"
#include "USART.h"
#include "MPU6050.h"
#include "DMP.h"
#include "tetris.h"
#include "snake.h"

static unsigned long timestamp = 0;

int brightness = 0;           // 当前亮度
int direction = 1;            // 亮度调整方向 (1: 增加亮度, -1: 减少亮度)
unsigned int tick = 0;       // 用于计时
unsigned char breathing_speed = 10;     // 呼吸速度（定时器间隔的倍数，可调节）

unsigned int seed = 1; // 随机数种子

unsigned char state_flag = 0;
unsigned char bluetooth_control = 0;
unsigned char handle = 0;

int metx = 0;
int mety = 0;
int postoji = 0;
int nep = 8;
int smjer = 0;
int go = 0;
int rx = 95;
int ry = 0;
int rx2 = 95;
int ry2 = 0;
int rx3 = 95;
int ry3 = 0;
int bodovi = 0;

int brzina = 3;
int bkugle = 1;
int najmanja = 600;
int najveca = 1200;
int promjer = 10;

int rx4 = 95;
int ry4 = 0;
int zivoti = 5;
int poc = 0;
int ispaljeno = 0;
int nivo = 1;
int centar = 95;
unsigned char key_num = 0;
unsigned long pocetno = 0;
unsigned long odabrano = 0;
unsigned long trenutno = 0;
unsigned long nivovrije = 0;
int pozicija = 0;
unsigned long tt = 0;
float Pitch, Roll, Yaw;
int poz = 30;

unsigned char get_key_val()
{
    if(up_key == 0)
        return 1;
    else if(fn2_key == 0)
        return 0;
    else if(down_key == 0)
        return 2;
    else return -1;
}


void Timer0_Init(void)		//1毫秒@27.000MHz
{
    AUXR |= 0x80;			//定时器时钟1T模式
    TMOD &= 0xF0;			//设置定时器模式
    TL0 = 0x88;				//设置定时初始值
    TH0 = 0x96;				//设置定时初始值
    TF0 = 0;				//清除TF0标志
    TR0 = 1;				//定时器0开始计时
    ET0 = 1;				//使能定时器0中断
    EA = 1;
}


unsigned long millis()
{
    return timestamp;
}


/**
 * ponovo函数用于重置游戏状态，将所有游戏相关变量初始化为起始值。
 * 这包括位置、速度、得分、生命值等，以便游戏可以在每次开始或重新开始时处于一致的状态。
 */
void ponovo()
{
    // 重置玩家位置和状态
    metx = 0;
    mety = 0;
    postoji = 0;
    nep = 8;
    smjer = 0;
    go = 0;
    
    // 初始化敌人的位置
    rx = 95;
    ry = 0;
    rx2 = 95;
    ry2 = 0;
    rx3 = 95;
    ry3 = 0;

    // 重置玩家得分为0
    bodovi = 0;

    // 设置游戏速度和球的属性
    brzina = 3;
    bkugle = 1;
    najmanja = 600;
    najveca = 1200;
    promjer = 12;

    // 初始化另一个敌人的位置
    rx4 = 95;
    ry4 = 0;

    // 重置生命值和游戏进度相关变量
    zivoti = 5;
    poc = 0;
    ispaljeno = 0;
    nivo = 1;
    pocetno = 0;
    odabrano = 0;
    trenutno = 0;
    nivovrije = 0;
}

//WS2812RGB灯带
/**
 * ws2812_allot函数用于根据蓝牙控制信号分配WS2812灯珠的颜色。
 * 该函数根据蓝牙_control变量的不同值来设置WS2812灯珠的红色分量，
 * 并固定绿色和蓝色分量的值。
 */
void ws2812_allot()
{
    unsigned char i, j;
    // 遍历所有WS2812灯珠
    for(i = 0; i < WSCOUNT; i++)
        // 遍历每个灯珠的RGB分量
        for(j = 0; j < 3; j++) {
            // 当处理红色分量时
            if(j == 0) {
                // 根据蓝牙控制信号设置红色分量的值
                switch(bluetooth_control) {
                case 0:
                    WS2812_BUffer[i][j] = 114; //R
                    break;
                case 1:
                    WS2812_BUffer[i][j] = brightness;
                    break;
                case 2:
                    WS2812_BUffer[i][j] = 255;
                    break;
                case 3:
                    WS2812_BUffer[i][j] = 0;
                    break;
                default:
                    break;
                }
            // 当处理绿色分量时，固定其值为179
            } else if(j == 1)
                WS2812_BUffer[i][j] = 179; //G
            // 当处理蓝色分量时，将其值设置为brightness变量的值
            else
                WS2812_BUffer[i][j] = brightness; //B
        }
}



void update_brightness()
{
    // 调整亮度值
    brightness += direction * STEP;

    // 如果达到边界值，则反向调整
    if(brightness >= MAX_BRIGHTNESS) {
        brightness = MAX_BRIGHTNESS;
        direction = -1;
    } else if(brightness <= MIN_BRIGHTNESS) {
        brightness = MIN_BRIGHTNESS;
        direction = 1;
    }
}

// 简单的伪随机数生成函数
unsigned char rand_51()
{
    seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF; // LCG算法
    return (seed >> 16) & 0xFF; // 返回0-255之间的值
}

void ws2812_random_colors()
{
    u8 i, j;
    for(i = 0; i < WSCOUNT; i++) {
        for(j = 0; j < 3; j++) {
            WS2812_BUffer[i][j] = rand_51(); // 随机生成0-255之间的颜色值
        }
    }
}
void Timer0_Isr(void) interrupt 1
{
    timestamp ++;
    tick++;

    if(tick >= breathing_speed) {
        tick = 0;
        update_brightness(); // 更新亮度
    }
}

//蓝牙模块用使用串口2实现
void Uart2() interrupt 8
{
    unsigned char recv_data;
    if(S2CON & S2RI) {
        S2CON &= ~S2RI;         //清除S2RI位
        recv_data = S2BUF;
        if(recv_data == '1') {
            bluetooth_control = 1;
        } else if(recv_data == '2') {
            bluetooth_control = 2;
        } else if(recv_data == '3') {
            bluetooth_control = 3;
        } else if(recv_data == '4') {
            bluetooth_control = 4;
        } else if(recv_data == '5') {
            bluetooth_control = 5;
        } else if(recv_data == 'A') {
            state_flag = 1;
        } else if(recv_data == 'B') {
            state_flag = 2;
        } else if(recv_data == 'C') {
            state_flag = 3;
        } else if(recv_data == 'D') {
            state_flag = 4;
        } else {
            bluetooth_control = 0;
        }
        S2BUF = recv_data;
        while(!(S2CON & S2TI));
        S2CON &= ~S2TI;

    }
}

// Dino游戏主循环
void DinoGame()
{
    // 初始化按键值，用于后续的按键检测
    unsigned char key_num = 0;
    // 初始化仙人掌类别，用于随机生成仙人掌
    unsigned char cactus_category = 0;
    // 定义仙人掌的初始长度
    unsigned char cactus_length = 8;
    // 初始化得分和最高得分
    unsigned int score = 0;
    unsigned int highest_score = 0;
    // 初始化跳跃高度
    int height = 0;
    // 初始化仙人掌的位置
    int cactus_pos = 128;
    // 定义当前速度，用于控制游戏难度
    unsigned char cur_speed = 30;
    // 初始化失败标志
    char failed = 0;
    // 初始化重置标志
    char reset = 0;

    // 显示游戏封面
    OLED_ShowImage(0, 0, 128, 64, COVER);
    OLED_Update();
    // 等待玩家按下开始键
    while(fn2_key != 0) {
        if(state_flag != 2)
            break;
    }
    // 延时后清除屏幕，准备开始游戏
    delay_ms(100);
    OLED_Clear();
    OLED_Update();
    // 游戏主循环
    while(1) {
        // 检查游戏状态，如果游戏未处于进行中，则退出循环
        if(state_flag != 2)
            break;
        // 如果游戏失败，处理失败逻辑
        if(failed == 1) {
            OLED_DrawRestart();
            //OLED_Update();
            key_num = get_key_val();
            // 如果玩家按下重置键，重置游戏状态
            if(key_num == 2) {
                OLED_Clear();
                OLED_Update();
                if(score > highest_score) highest_score = score;
                score = 0;
                failed = 0;
                height = 0;
                reset = 1;
                OLED_DrawDinoJump(reset);
                //OLED_Update();
                OLED_DrawCactusRandom(cactus_category, reset);
                //OLED_Update();

            }
            continue;
        }

        // 更新得分
        score ++;
        // 如果恐龙不在空中或者玩家按下跳跃键，更新恐龙的高度
        if(height <= 0) key_num = get_key_val();

        // 绘制地面和云朵
        OLED_DrawGround();
        OLED_DrawCloud();

        // 根据恐龙的高度或玩家的输入更新恐龙的状态
        if(height > 0 || key_num == 1) height = OLED_DrawDinoJump(reset);
        else OLED_DrawDino();
        //OLED_Update();

        // 更新仙人掌的位置和类别
        cactus_pos = OLED_DrawCactusRandom(cactus_category, reset);
        if(cactus_category == 0) cactus_length = 8;
        else if(cactus_category == 1) cactus_length = 16;
        else cactus_length = 24;

        // 如果仙人掌移出屏幕，随机生成新的仙人掌
        if(cactus_pos + cactus_length < 0) {
            cactus_category = rand() % 4;
            OLED_DrawCactusRandom(cactus_category, 1);
        }

        // 检查恐龙是否碰到仙人掌，如果碰到，标记游戏失败
        if((height < 16) && ((cactus_pos >= 16 && cactus_pos <= 32) || (cactus_pos + cactus_length >= 16 && cactus_pos + cactus_length <= 32))) {
            failed = 1;
        }

        //OLED_ShowString(35, 0, "HI:", OLED_6X8);
        //OLED_ShowNum(58, 0, highest_score, 1, OLED_6X8);
        //OLED_ShowNum(98, 0, score, 1, OLED_6X8);
        //OLED_Update();

        // 重置重置标志
        reset = 0;

        // 根据得分更新游戏速度
        cur_speed = score / 20;
        if(cur_speed > 29) cur_speed = 29;
        delay_ms(30 - cur_speed);
        // 重置按键值
        key_num = 0;
    }
}


void Star_War()
{
    // 清除OLED屏幕
    OLED_Clear();
    // 显示封面图像
    OLED_ShowImage(0, 0, 128, 64, COVER2);
    // 更新OLED显示
    OLED_Update();
    // 等待按键释放
    while(fn2_key != 0) {
        if(state_flag != 1)
            break;
    };

    // 游戏主循环
    while(1) {
        // 如果游戏状态改变，退出循环
        if(state_flag != 1)
            break;
        // 获取当前时间
        tt = millis();
        // 游戏进行中
        if(go == 0) {
            // 清除OLED屏幕
            OLED_Clear();

            // 绘制初始星星图案
            OLED_DrawPoint(50, 30);
            OLED_DrawPoint(30, 17);
            OLED_DrawPoint(60, 18);
            OLED_DrawPoint(55, 16);
            OLED_DrawPoint(25, 43);
            OLED_DrawPoint(100, 43);
            OLED_DrawPoint(117, 52);
            OLED_DrawPoint(14, 49);
            OLED_DrawPoint(24, 24);
            OLED_DrawPoint(78, 36);
            OLED_DrawPoint(80, 57);
            OLED_DrawPoint(107, 11);
            OLED_DrawPoint(150, 11);
            OLED_DrawPoint(5, 5);
            OLED_DrawPoint(8, 7);
            OLED_DrawPoint(70, 12);
            OLED_DrawPoint(10, 56);
            OLED_DrawPoint(70, 25);

            // 初始化射击计时器
            if(poc == 0) {
                pocetno = millis();
                odabrano = rand() % 800 + 400;
                poc = 1;
            }
            // 获取当前时间
            trenutno = millis();

            // 每50秒提升一个等级
            if((trenutno - nivovrije) > 50000) {
                nivovrije = trenutno;
                nivo = nivo + 1;

                brzina = brzina + 1;
                if(nivo % 2 == 0) {
                    bkugle = bkugle + 1;
                    promjer = promjer - 1;
                }
                najmanja = najmanja - 50;
                najveca = najveca - 50;
            }

            // 发射子弹
            if((odabrano + pocetno) < trenutno) {
                poc = 0;
                ispaljeno = ispaljeno + 1;
                if(ispaljeno == 1) {
                    rx = 95;
                    ry = nep;
                }
                if(ispaljeno == 2) {
                    rx2 = 95;
                    ry2 = nep;
                }
                if(ispaljeno == 3) {
                    rx3 = 95;
                    ry3 = nep;
                }

                if(ispaljeno == 4) {
                    rx4 = 95;
                    ry4 = nep;
                }
            }

            // 绘制子弹
            if(ispaljeno > 0) {
                OLED_DrawCircle(rx, ry, 2, 0);
                rx = rx - brzina;
            }

            if(ispaljeno > 1) {
                OLED_DrawCircle(rx2, ry2, 1, 0);
                rx2 = rx2 - brzina;
            }

            if(ispaljeno > 2) {
                OLED_DrawCircle(rx3, ry3, 4, 0);
                rx3 = rx3 - brzina;
            }

            if(ispaljeno > 3) {
                OLED_DrawCircle(rx4, ry4, 2, 0);
                rx4 = rx4 - brzina;
            }

            // 处理上移按键
            if((up_key == 0 || bluetooth_control == 2) && poz >= 2) {
                bluetooth_control = 0;
                poz = poz - 2;
            }

            // 处理下移按键
            if((down_key == 0 || bluetooth_control == 3) && poz <= 46) {
                bluetooth_control = 0;
                poz = poz + 2;
            }

            // 处理射击按键
            if((fn2_key == 0 || bluetooth_control == 1) && postoji == 0) {
                bluetooth_control = 0;
                postoji = 1;
                metx = 6;
                mety = poz + 8;
                // 发射声音 tone(9, 1200, 20);
            }
            // 绘制子弹轨迹
            if(postoji == 1) {
                metx = metx + 8;

                OLED_DrawLine(metx, mety, metx + 4, mety);
            }

            // 绘制飞机
            OLED_ShowImage(4, poz,  16, 16, dioda16); // 飞机
            // 绘制目标
            OLED_DrawCircle(centar, nep, promjer, 0);
            OLED_DrawCircle(centar + 2, nep + 3, promjer / 3, 1);

            // 显示得分
            OLED_ShowString(33, 57, "score:", OLED_6X8);
            OLED_ShowNum(68, 57, bodovi, 3, OLED_6X8);

            // 显示生命值
            OLED_ShowString(33, 0, "lives:", OLED_6X8);
            OLED_ShowNum(68, 0, zivoti, 1, OLED_6X8);

            // 显示等级
            OLED_ShowString(110, 0, "L:", OLED_6X8);
            OLED_ShowNum(122, 0, nivo, 1, OLED_6X8);
            // 显示时间
            OLED_ShowNum(108, 57, trenutno / 1000, 3, OLED_6X8);

            // 更新OLED显示
            OLED_Update();

            // 子弹出界处理
            if(metx > 128)
                postoji = 0;

            // 目标移动
            if(smjer == 0) {
                nep = nep + bkugle;
            } else {
                nep = nep - bkugle;
            }

            // 目标边界处理
            if(nep >= (64 - promjer))
                smjer = 1;
            if(nep <= promjer)
                smjer = 0;

            // 子弹击中目标
            if(mety >= nep - promjer && mety <= nep + promjer)
                if(metx > (centar - promjer) && metx < (centar + promjer)) {
                    metx = -20;
                    // 击中声音 tone(9, 500, 20);
                    bodovi = bodovi + 1;
                    postoji = 0;
                }

            // 子弹击中飞机
            pozicija = poz + 8;
            if(ry >= pozicija - 8 && ry <= pozicija + 8)
                if(rx < 12 && rx > 4) {
                    rx = 95;
                    ry = -50;
                    // 击中声音 tone(9, 100, 100);
                    zivoti = zivoti - 1;
                }

            if(ry2 >= pozicija - 8 && ry2 <= pozicija + 8)
                if(rx2 < 12 && rx2 > 4) {
                    rx2 = -50;
                    ry2 = -50;
                    // 击中声音 tone(9, 100, 100);
                    zivoti = zivoti - 1;
                }

            if(ry3 >= pozicija - 8 && ry3 <= pozicija + 8)
                if(rx3 < 12 && rx3 > 4) {
                    rx3 = -50;
                    ry3 = -50;
                    // 击中声音 tone(9, 100, 100);
                    zivoti = zivoti - 1;
                }

            if(ry4 >= pozicija - 8 && ry4 <= pozicija + 8)
                if(rx4 < 12 && rx4 > 4) {
                    rx4 = 200;
                    ry4 = -50;
                    ispaljeno = 0;
                    // 击中声音 tone(9, 100, 100);
                    zivoti = zivoti - 1;
                }

            // 子弹出界处理
            if(rx4 < 1) {
                ispaljeno = 0;
                rx4 = 200;
            }

            // 生命值为零时结束游戏
            if(zivoti == 0)
                go = 1;
        }

        // 游戏结束处理
        if(go == 1) {
            // 重置生命值
            if(zivoti == 0) {
                zivoti = 5;
            }
            // 清除OLED屏幕
            OLED_Clear();

            // 显示游戏结束信息
            OLED_ShowString(7, 10, "Game Over!", OLED_8X16);

            // 显示得分
            OLED_ShowString(7, 30, "score:", OLED_6X8);
            OLED_ShowNum(44, 30, bodovi, 3, OLED_6X8);

            // 显示等级
            OLED_ShowString(7, 40, "level:", OLED_6X8);
            OLED_ShowNum(44, 40, nivo, 1, OLED_6X8);
            // 显示时间
            OLED_ShowString(7, 50, "time(s):", OLED_6X8);
            OLED_ShowNum(60, 50, trenutno / 1000, 3, OLED_6X8);

            // 更新OLED显示
            OLED_Update();

            // 重新开始游戏
            if(fn2_key == 0 || bluetooth_control == 1) {
                bluetooth_control = 0;
                ponovo();
            }
        }
    }
}

// Tetris游戏主循环函数
void TetrisGame()
{
    // 定义旋转方块变量
    unsigned char Rot_TTRIS = 0;
    // 定义跳过帧变量
    unsigned char SKIP_FRAME = 0;
    // 重置方块游戏的相关值
    Reset_Value_TTRIS();
    // 游戏主循环
    while(1) {
        // 初始化所有变量
        INIT_ALL_VAR_TTRIS();
        // 开始游戏玩法
        Game_Play_TTRIS();
        // 确定方块的位置
        Ou_suis_Je_TTRIS(xx_TTRIS, yy_TTRIS);

        // 游戏介绍界面
        INTRO_MANIFEST_TTRIS();

        // 设置新的预览方块
        SETUP_NEW_PREVIEW_PIECE_TTRIS(&Rot_TTRIS);
        // 刷新屏幕
        Tiny_Flip_TTRIS(128);
        // 延时1秒
        JOY_DLY_ms(1000);
        // 初始化方块的起始位置
        xx_TTRIS = 55;
        yy_TTRIS = 5;

        // 游戏内部循环
        while(1) {
            // 检查游戏状态，如果不为游戏进行中，则跳出循环
            if(state_flag != 3) {
                break;
            }
            // 控制方块的旋转和移动
            CONTROLE_TTRIS(&Rot_TTRIS);
            // 检查方块是否已经到底部
            if(DROP_BREAK_TTRIS == 6) {
                // 结束方块的下落
                END_DROP_TTRIS();
                // 如果游戏结束
                if(End_Play_TTRIS()) {
                    // 刷新屏幕
                    Tiny_Flip_TTRIS(128);
                    // 发出声音
                    SND_TTRIS(3);
                    // 延时2秒
                    JOY_DLY_ms(2000);
                    // 检查是否打破记录
                    Check_NEW_RECORD();
                    break;
                }
                // 重置方块的位置和形状
                yy_TTRIS = 2;
                xx_TTRIS = 55;
                PIECEs_TTRIS = PIECEs_TTRIS_PREVIEW;
                SETUP_NEW_PREVIEW_PIECE_TTRIS(&Rot_TTRIS);
                // 设置下降速度
                DOWN_DESACTIVE_TTRIS = 1;
                // 刷新屏幕
                Tiny_Flip_TTRIS(128);
                Game_Play_TTRIS();
                Tiny_Flip_TTRIS(128);
            }

            // 如果有按键按下并且没有按键抖动
            if((JOY_act_pressed()) && (Ripple_filter_TTRIS == 0)) {
                // 产生伪随机数
                PSEUDO_RND_TTRIS();
                // 设置按键抖动过滤
                Ripple_filter_TTRIS = 1;
            }

            // 移动方块
            Move_Piece_TTRIS();
            // 控制游戏帧率
            if(SKIP_FRAME == 6) {
                Tiny_Flip_TTRIS(82);
                SKIP_FRAME = 0;
            } else {
                SKIP_FRAME++;
            }
        }
    }
}

void main()
{

    Timer0_Init();
    Uart2Init();
    Uart1Init();
    MPU6050_DMP_Init();
    OLED_Init();
    OLED_ShowImage(0, 0, 128, 64, COVER_PLAY_HANDLE);
    OLED_Update();
    while(fn2_key != 0) {
        while((handle_key != 0) && (handle == 0)) {
            ws2812_allot();
            WS2812_Ser();
        }
        handle = 1;
        ///*******MPU6050*******/
        MPU6050_Refresh_DMP();

        Pitch = asin(2 * Q[1] * Q[3] - 2 * Q[0] * Q[2]) * 57.3;	// pitch
        Roll  = atan2(2 * Q[2] * Q[3] + 2 * Q[0] * Q[1], -2 * Q[1] * Q[1] - 2 * Q[2] * Q[2] + 1) * 57.3;	// roll
        Yaw   = atan2(2 * (Q[1] * Q[2] + Q[0] * Q[3]), Q[0] * Q[0] + Q[1] * Q[1] - Q[2] * Q[2] - Q[3] * Q[3]) * 57.3;	//yaw

        SendFloat(&Pitch);//发送
        SendFloat(&Roll);
        SendFloat(&Yaw);
        SendEnd();
    }
    while(1) {
        OLED_ShowImage(0, 0, 128, 64, COVER_PLAY_GAME);
        OLED_Update();
        switch(state_flag) {
        case 1:
            Star_War();
            break;
        case 2:
            DinoGame();
            break;
        case 3:
            TetrisGame();
            break;
        case 4:
            SnakeGame();
            break;
        default:
            break;
        }

    }
}


