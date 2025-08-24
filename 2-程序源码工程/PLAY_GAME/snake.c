#include "snake.h"

struct snake Pos[20]; //�ߵ������������ݣ�
struct snake food ;//ʳ�������λ�ã�

void delay_snake(unsigned char i)
{
    while(i--);
}

bit moveflag = 0, foodflag = 0, giveup = 0, start = 0, fun = 0;
//giveup��ʳ�ﱻ������־λ��foodflag��ʳ��ˢ�±�־λ��moveflag���ƶ���־λ
unsigned char count = 0, page = 0, mode = 0, snake_time = 150, point = 1;
//page������ʾ��ͬ��ҳ�棬������Ϸ����ҳ�棬��ʼҳ��ȣ�mode����ʶ���ߵ��˶�״̬
unsigned char head = 3, tail = 0; //������


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


/*     ��������      */
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
        //�����ж��Ƿ�ײǽ��
        if(Pos[head - 1].x == 0)
            page = 2;
        //���ж��Ƿ�ҧ���Լ������壻
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x - 1) == Pos[i].x && Pos[head - 1].y == Pos[i].y)
                    page = 2;
            }
        if(page == 1) {
            //�Ե�ʳ��������
            if((Pos[head - 1].x - 1) == food.x && Pos[head - 1].y == food.y) {
                head++;//���ȼ�һ��
                foodflag = 0; //ˢ����һ��ʳ�
                Pos[head - 1].x = Pos[head - 2].x - 1;
                Pos[head - 1].y = Pos[head - 2].y;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            } else {

                OLED_CLR_Body(Pos[tail].x, Pos[tail].y); //���Ͼ�β�ͣ�
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
        //�����ж��Ƿ�ײǽ��
        if(Pos[head - 1].x == 15)
            page = 2;
        //���ж��Ƿ�ҧ���Լ������壻
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x + 1) == Pos[i].x && Pos[head - 1].y == Pos[i].y)
                    page = 2;
            }
        //�����û��ײǽҲû��ҧ���Լ��Ļ����Ϳ��ǳԵ�ʳ���û�гԵ��������
        if(page == 1) {
            //�Ե�ʳ��������
            if((Pos[head - 1].x + 1) == food.x && Pos[head - 1].y == food.y) {
                head++;//���ȼ�һ��
                foodflag = 0; //ˢ����һ��ʳ�
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
        //�����ж��Ƿ�ײǽ��
        if(Pos[head - 1].y == 0)
            page = 2;
        //���ж��Ƿ�ҧ���Լ������壻
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x) == Pos[i].x && Pos[head - 1].y - 1 == Pos[i].y)
                    page = 2;
            }
        if(page == 1) {
            //�Ե�ʳ��������
            if(Pos[head - 1].x == food.x && (Pos[head - 1].y - 1) == food.y) {
                head++;//���ȼ�һ��
                foodflag = 0; //ˢ����һ��ʳ�
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
        //�����ж��Ƿ�ײǽ��
        if(Pos[head - 1].y == 7)
            page = 2;
        //���ж��Ƿ�ҧ���Լ������壻
        if(page == 1)
            for(i = 0; i < head - 1; i++) {
                if((Pos[head - 1].x) == Pos[i].x && Pos[head - 1].y + 1 == Pos[i].y)
                    page = 2;
            }
        //�����û��ײǽҲû��ҧ���Լ�  ���ǾͿ��ǳԵ�ʳ���û�гԵ��������
        if(page == 1) {
            //�Ե�ʳ��������
            if(Pos[head - 1].x == food.x && (Pos[head - 1].y + 1) == food.y) {
                head++;//���ȼ�һ��
                foodflag = 0; //ˢ����һ��ʳ�
                Pos[head - 1].x = Pos[head - 2].x;
                Pos[head - 1].y = Pos[head - 2].y + 1;
                OLED_SnakeBody(Pos[head - 1].x, Pos[head - 1].y);
            } else { //û�Ե�ʳ������

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

void Snake_Over(void)//������������������֮����ʾgame over,ͬʱ���ϼ�⸴ԭ���Ƿ񱻰���;
{
    if(page == 2) {
        mode = 0; //�������㣬����ͻ�����һ����Ϸ��ʼʱ����ߵ����ƶ���
        TR0 = 0; //�رն�ʱ����
        OLED_Clear();//��������
        while(page == 2) {
            OLED_ShowString(0, 0, "game over", OLED_6X8);
            OLED_ShowString(30, 3, "press left to restart", OLED_6X8);
            OLED_Update();
            Game_Restart();
        }
    }
}



// ʳ���ʼ����������������Ϸ��ͼ������ʳ���λ��
void Food_Init(void)
{
    unsigned char i;
    // ��û��ʳ������ʱ������ѭ��������ʳ��
    while(!foodflag) {
        // ʹ��count������ģ����������ʳ���x��y����
        food.x = count % 16;
        food.y = count % 8;
        // �����ߵ����岿λ�����ʳ���Ƿ������������ϻ��ͼ��Ե
        for(i = 0; i < head; i++) {
            // һ������������������ʳ�����ݾ�Ӧ�ñ���������Ϊ����������ڵ�ͼ��
            if((food.x == Pos[i].x && food.y == Pos[i].y) || food.x >= 15 || food.y >= 7 || food.x <= 1 || food.y <= 1)
                giveup = 1;
        }
        // ���ʳ�����ݱ�������������ʳ���־�ͷ�����־��׼����һ������
        if(giveup == 1) {
            foodflag = 0;
            giveup = 0;
        } else {
            // ���ʳ��������Ч������ʳ���־����ʾʳ������÷�����־
            foodflag = 1;
            OLED_SnakeBody_food(food.x, food.y);
            giveup = 0;
            // �ɹ�����ʳ�������ѭ��
            break;
        }
    }
}

/**
 * ��ʼ���ߵ�λ��
 * 
 * �˺������ߵĳ�ʼλ����������Ϸ������ض������ϣ�������Ļ�ϻ����ߵ�����
 * ����������ͷ������ĳ�ʼ���֣�����Ϸ��ʼʱ�Ľ�����г�ʼ��
 */
void Snake_Init(void)
{
    // ����ѭ�������ߵ����岿��
    unsigned char i;

    // ������ͷ�ĳ�ʼλ��
    Pos[0].x = 6;
    Pos[0].y = 3;

    // ���õ�һ�������λ��
    Pos[1].x = 7;
    Pos[1].y = 3;

    // ���õڶ��������λ��
    Pos[2].x = 8;
    Pos[2].y = 3;

    // �����������ߵ����岿��
    for(i = 0; i < head; i++) {
        // ��ָ��λ�û����ߵ�����
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
 * SnakeGame������������Ϸ����ѭ����
 * �����ݵ�ǰҳ��(page)��״̬��ִ�в�ͬ����Ϸ�߼���
 * �ú���û�в�����Ҳ�������κ�ֵ��
 */
void SnakeGame(void)
{
    // ��ҳ��Ϊ0ʱ��������ʾҳ��0������
    while(page == 0) {
        page0();
    }
    
    // ����choice���������������û�����ĳ��ѡ��
    choice();
    
    // ��ҳ��Ϊ1ʱ������Ϸ������
    while(page == 1) {
        // �����Ϸ��ʼ��־������Ϊ1
        if(start == 1) {
            // ���OLED��Ļ��������ʾ����
            OLED_Clear();
            OLED_Update();
            
            // ������ʱ��0
            TR0 = 1;
            
            // ��ʼ����ͷ��λ��
            head = 3;
            
            // ��ʼ���ߵ�����
            Snake_Init();
            
            // ������Ϸ��ʼ��־
            start = 0;
        }
        
        // ��ʼ��ʳ���λ��
        Food_Init();
        
        // �����������
        keypros();
    }
    
    // ��ҳ��Ϊ2ʱ������Ϸ����
    while(page == 2) {
        // ֹͣ��ʱ��0
        TR0 = 0;
        
        // ��ʾ��Ϸ�������߼�
        Snake_Over();
    }
}
