#include "snake.h"

struct snake Pos[20]; //蛇的身体坐标数据；
struct snake food ;//食物的坐标位置；

void delay_snake(unsigned char i)
{
    while(i--);
}

bit moveflag = 0, foodflag = 0, giveup = 0, start = 0, fun = 0;
//giveup是食物被舍弃标志位，foodflag是食物刷新标志位，moveflag是移动标志位
unsigned char count = 0, page = 0, mode = 0, snake_time = 150, point = 1;
//page用于显示不同的页面，比如游戏结束页面，开始页面等；mode用于识别蛇的运动状态
unsigned char head = 3, tail = 0; //蛇身长度


void OLED_SnakeBody(unsigned char x, unsigned char y)
{
    unsigned char i;
    oled_set_pos(x * 8, y);
    for(i = 0; i < 8; i++) {
        OLED_I2C_SendByte(body[i]);
    }

}

void OLED_SnakeBody_food(unsigned char x, unsigned char y)
{
    unsigned char i;
    oled_set_pos(x * 8, y);
    for(i = 0; i < 8; i++) {
        OLED_I2C_SendByte(food_good[i]);
    }

}


void OLED_CLR_Body(unsigned char x, unsigned char y)
{
    unsigned char i;
    oled_set_pos(x * 8, y);
    for(i = 0; i < 8; i++) {
        OLED_I2C_SendByte(0x00);
    }

}


/*     上下左右      */
void leftkey()
{
    if(left_key == 0 && mode != 1 && mode != 2)
        delay_snake(25);
    if(left_key == 0 && mode != 1 && mode != 2)
        mode = 1;
    while(!left_key);
}
void rightkey()
{
    if(right_key == 0 && mode != 1 && mode != 2)
        delay_snake(25);
    if(right_key == 0 && mode != 1 && mode != 2)
        mode = 2;
    while(!right_key);
}
void upkey()
{
    if(up_key == 0 && mode != 3 && mode != 4)
        delay_snake(25);
    if(up_key == 0 && mode != 3 && mode != 4)
        mode = 3;
    while(!up_key);
}
void downkey()
{
    if(down_key == 0 && mode != 3 && mode != 4)
        delay_snake(25);
    if(down_key == 0 && mode != 3 && mode != 4)
        mode = 4;
    while(!down_key) ;
}


void modeleft()
{
    unsigned char i, j;
    if(mode == 1) {
        //首先判断是否撞墙；
        if(Pos[head - 1].x == 0)
            page = 2;
        //再判断是否咬到自己的身体；
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x - 1) == Pos[i].x && Pos[head - 1].y == Pos[i].y)
                    page = 2;
            }
        if(page == 1) {
            //吃到食物的情况；
            if((Pos[head - 1].x - 1) == food.x && Pos[head - 1].y == food.y) {
                head++;//长度加一；
                foodflag = 0; //刷新下一次食物；
                Pos[head - 1].x = Pos[head - 2].x - 1;
                Pos[head - 1].y = Pos[head - 2].y;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            } else {

                OLED_CLR_Body(Pos[tail].x, Pos[tail].y); //砍断旧尾巴；
                for(j = 0; j < head - 1; j++) {
                    Pos[j].x = Pos[j + 1].x;
                    Pos[j].y = Pos[j + 1].y;
                }
                Pos[head - 1].x--;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            }
        }

    }
}
void moderight()
{
    unsigned char i, j;
    if(mode == 2) {
        //首先判断是否撞墙；
        if(Pos[head - 1].x == 15)
            page = 2;
        //再判断是否咬到自己的身体；
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x + 1) == Pos[i].x && Pos[head - 1].y == Pos[i].y)
                    page = 2;
            }
        //如果既没有撞墙也没有咬到自己的话，就考虑吃到食物和没有吃到的情况；
        if(page == 1) {
            //吃到食物的情况；
            if((Pos[head - 1].x + 1) == food.x && Pos[head - 1].y == food.y) {
                head++;//长度加一；
                foodflag = 0; //刷新下一次食物；
                Pos[head - 1].x = Pos[head - 2].x + 1;
                Pos[head - 1].y = Pos[head - 2].y;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            } else {

                OLED_CLR_Body(Pos[tail].x, Pos[tail].y);
                for(j = 0; j < head - 1; j++) {
                    Pos[j].x = Pos[j + 1].x;
                    Pos[j].y = Pos[j + 1].y;
                }
                Pos[head - 1].x++;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            }
        }

    }
}
void modeup()
{
    unsigned char i, j;
    if(mode == 3) {
        //首先判断是否撞墙；
        if(Pos[head - 1].y == 0)
            page = 2;
        //再判断是否咬到自己的身体；
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x) == Pos[i].x && Pos[head - 1].y - 1 == Pos[i].y)
                    page = 2;
            }
        if(page == 1) {
            //吃到食物的情况；
            if(Pos[head - 1].x == food.x && (Pos[head - 1].y - 1) == food.y) {
                head++;//长度加一；
                foodflag = 0; //刷新下一次食物；
                Pos[head - 1].x = Pos[head - 2].x;
                Pos[head - 1].y = Pos[head - 2].y - 1;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            } else {

                OLED_CLR_Body(Pos[tail].x, Pos[tail].y);
                for(j = 0; j < head - 1; j++) {
                    Pos[j].x = Pos[j + 1].x;
                    Pos[j].y = Pos[j + 1].y;
                }
                Pos[head - 1].y--;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            }
        }

    }
}
void modedown()
{
    unsigned char i, j;
    if(mode == 4) {
        //首先判断是否撞墙；
        if(Pos[head - 1].y == 7)
            page = 2;
        //再判断是否咬到自己的身体；
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x) == Pos[i].x && Pos[head - 1].y + 1 == Pos[i].y)
                    page = 2;
            }
        //如果既没有撞墙也没有咬到自己  ，那就考虑吃到食物和没有吃到的情况；
        if(page == 1) {
            //吃到食物的情况；
            if(Pos[head - 1].x == food.x && (Pos[head - 1].y + 1) == food.y) {
                head++;//长度加一；
                foodflag = 0; //刷新下一次食物；
                Pos[head - 1].x = Pos[head - 2].x;
                Pos[head - 1].y = Pos[head - 2].y + 1;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            } else { //没吃到食物的情况

                OLED_CLR_Body(Pos[tail].x, Pos[tail].y);
                for(j = 0; j < head - 1; j++) {
                    Pos[j].x = Pos[j + 1].x;
                    Pos[j].y = Pos[j + 1].y;
                }
                Pos[head - 1].y++;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            }
        }

    }
}




void  keypros(void)
{
    leftkey();
    rightkey();
    upkey();
    downkey();
}

void snake_modepros(void)
{
    modeup();
    modeleft();
    modedown();
    moderight();
}


void  Game_Restart(void)
{
    if(left_key == 0)
        delay_snake(25);
    if(left_key == 0) {
        page = 0;
        OLED_Clear();
        OLED_Update();
    }
    while(!left_key);
}

void Snake_Over(void)//蛇死亡函数，在死亡之后显示game over,同时不断检测复原键是否被按下;
{
    if(page == 2) {
        mode = 0; //必须清零，否则就会在下一次游戏开始时造成蛇的乱移动；
        TR0 = 0; //关闭定时器；
        OLED_Clear();//先清屏；
        while(page == 2) {
            OLED_ShowString(0, 0, "game over", OLED_6X8);
            OLED_ShowString(30, 3, "press left to restart", OLED_6X8);
            OLED_Update();
            Game_Restart();
        }
    }
}



// 食物初始化函数；负责在游戏地图上生成食物的位置
void Food_Init(void)
{
    unsigned char i;
    // 当没有食物生成时，进入循环以生成食物
    while(!foodflag) {
        // 使用count变量的模运算来决定食物的x和y坐标
        food.x = count % 16;
        food.y = count % 8;
        // 遍历蛇的身体部位，检查食物是否生成在蛇身上或地图边缘
        for(i = 0; i < head; i++) {
            // 一旦满足这个条件，这个食物数据就应该被舍弃，因为在蛇身或者在地图上
            if((food.x == Pos[i].x && food.y == Pos[i].y) || food.x >= 15 || food.y >= 7 || food.x <= 1 || food.y <= 1)
                giveup = 1;
        }
        // 如果食物数据被舍弃，则重置食物标志和放弃标志，准备下一次生成
        if(giveup == 1) {
            foodflag = 0;
            giveup = 0;
        } else {
            // 如果食物数据有效，设置食物标志，显示食物，并重置放弃标志
            foodflag = 1;
            OLED_SnakeBody_food(food.x, food.y);
            giveup = 0;
            // 成功生成食物后，跳出循环
            break;
        }
    }
}

/**
 * 初始化蛇的位置
 * 
 * 此函数将蛇的初始位置设置在游戏区域的特定坐标上，并在屏幕上绘制蛇的身体
 * 它定义了蛇头和蛇身的初始布局，对游戏开始时的界面进行初始化
 */
void Snake_Init(void)
{
    // 用于循环遍历蛇的身体部分
    unsigned char i;

    // 设置蛇头的初始位置
    Pos[0].x = 6;
    Pos[0].y = 3;

    // 设置第一段蛇身的位置
    Pos[1].x = 7;
    Pos[1].y = 3;

    // 设置第二段蛇身的位置
    Pos[2].x = 8;
    Pos[2].y = 3;

    // 遍历并绘制蛇的身体部分
    for(i = 0; i < head; i++) {
        // 在指定位置绘制蛇的身体
        OLED_SnakeBody(Pos[i].x, Pos[i].y);
    }
}



void choice(void)
{
    if(left_key == 0) {
        delay_snake(20);
        if(left_key == 0) {
            point++;
            if(point > 3)
                point = 1;
        }
        while(!left_key);
    }

    if(right_key == 0) {
        delay_snake(20);
        if(right_key == 0) {

            if(point == 1) {
                snake_time = 90;
                page = 1;
                start = 1;
                foodflag = 0;
            }
            if(point == 2) {
                snake_time = 150;
                page = 1;
                start = 1;
                foodflag = 0;
            }
            if(point == 3)
                fun = 1;
        }
        while(!right_key);
    }
}


void page0(void)
{
    OLED_ShowString(10, 0, "greedy snake", OLED_6X8);
    OLED_ShowString(20, 2, "difficult", OLED_6X8);
    OLED_ShowString(20, 4, "normal", OLED_6X8);
    OLED_ShowString(20, 6, "easy", OLED_6X8) ;

    if(point == 1) {
        OLED_ShowChar(10, 2, '>', OLED_6X8);
        OLED_ShowChar(10, 4, ' ', OLED_6X8);
        OLED_ShowChar(10, 6, ' ', OLED_6X8);
    }
    if(point == 2) {
        OLED_ShowChar(10, 2, ' ', OLED_6X8);
        OLED_ShowChar(10, 4, '>', OLED_6X8);
        OLED_ShowChar(10, 6, ' ', OLED_6X8);
    }
    if(point == 3) {
        OLED_ShowChar(10, 3, ' ', OLED_6X8);
        OLED_ShowChar(10, 4, ' ', OLED_6X8);
        OLED_ShowChar(10, 6, '>', OLED_6X8);
    }
    if(fun == 1) {
        OLED_Clear();
        OLED_Update();
        while(fun == 1) {

            if(left_key == 0) delay_snake(25);
            if(left_key == 0) {
                fun = 0;
                OLED_Clear();
            }
            while(!left_key);
        }
        OLED_Clear();
        OLED_Update();
    }
    OLED_Update();
    choice();
}


/**
 * SnakeGame函数是蛇类游戏的主循环。
 * 它根据当前页面(page)的状态来执行不同的游戏逻辑。
 * 该函数没有参数，也不返回任何值。
 */
void SnakeGame(void)
{
    // 当页面为0时，持续显示页面0的内容
    while(page == 0) {
        page0();
    }
    
    // 调用choice函数，可能允许用户做出某种选择
    choice();
    
    // 当页面为1时，即游戏进行中
    while(page == 1) {
        // 如果游戏开始标志被设置为1
        if(start == 1) {
            // 清除OLED屏幕并更新显示内容
            OLED_Clear();
            OLED_Update();
            
            // 启动定时器0
            TR0 = 1;
            
            // 初始化蛇头的位置
            head = 3;
            
            // 初始化蛇的身体
            Snake_Init();
            
            // 重置游戏开始标志
            start = 0;
        }
        
        // 初始化食物的位置
        Food_Init();
        
        // 处理键盘输入
        keypros();
    }
    
    // 当页面为2时，即游戏结束
    while(page == 2) {
        // 停止定时器0
        TR0 = 0;
        
        // 显示游戏结束的逻辑
        Snake_Over();
    }
}
