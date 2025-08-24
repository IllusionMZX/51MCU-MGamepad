#ifndef _TETRIS_H
#define _TETRIS_H
#include "STC15F2K60S2.H"
#include "oled.h"
#include "oled_data.h"
#include "all.h"

extern unsigned char Grid_TTRIS[12][3];
extern unsigned char MEM_TTTRIS[16];
extern unsigned char Level_TTRIS;
extern unsigned int Scores_TTRIS;
extern unsigned int Nb_of_line_F_TTRIS;
extern unsigned char Level_Speed_ADJ_TTRIS; 
extern unsigned char Nb_of_line_TTRIS[3];
extern unsigned char RND_VAR_TTRIS;
extern unsigned char LONG_PRESS_X_TTRIS;
extern unsigned char DOWN_DESACTIVE_TTRIS;
extern unsigned char DROP_SPEED_TTRIS;
extern unsigned char SPEED_x_trig_TTRIS;
extern unsigned char DROP_TRIG_TTRIS;
extern int xx_TTRIS, yy_TTRIS;
extern unsigned char Piece_Mat2_TTRIS[5][5];
extern unsigned char Ripple_filter_TTRIS;
extern unsigned char PIECEs_TTRIS;
extern unsigned char PIECEs_TTRIS_PREVIEW;
extern unsigned char PIECEs_rot_TTRIS;
extern unsigned char DROP_BREAK_TTRIS;
extern int OU_SUIS_JE_X_TTRIS;
extern int OU_SUIS_JE_Y_TTRIS;
extern unsigned char OU_SUIS_JE_X_ENGAGED_TTRIS;
extern unsigned char OU_SUIS_JE_Y_ENGAGED_TTRIS;
extern int DEPLACEMENT_XX_TTRIS;
extern int DEPLACEMENT_YY_TTRIS;

void JOY_DLY_ms(int ms) ;
void reset_Score_TTRIS(void);
unsigned char PSEUDO_RND_TTRIS(void);
void SND_TTRIS(unsigned char Snd_TTRIS);
void INTRO_MANIFEST_TTRIS(void);
void END_DROP_TTRIS(void);
void SETUP_NEW_PREVIEW_PIECE_TTRIS(unsigned char *Rot_TTRIS);
void CONTROLE_TTRIS(unsigned char *Rot_TTRIS);
void Game_Play_TTRIS(void);
unsigned char End_Play_TTRIS(void);
void DELETE_LINE_TTRIS(void);
unsigned char Calcul_of_Score_TTRIS(unsigned char Tmp_TTRIS);
void FLASH_LINE_TTRIS(unsigned char *PASS_LINE);
void PAINT_LINE_TTRIS(unsigned char VISIBLE, unsigned char *PASS_LINE);
void Clean_Grid_TTRIS(unsigned char *PASS_LINE);
unsigned char CHECK_if_Rot_Ok_TTRIS(unsigned char *Rot_TTRIS);
unsigned char Check_collision_x_TTRIS(int x_Axe);
unsigned char Check_collision_y_TTRIS(int y_Axe);
void Move_Piece_TTRIS(void);
void Ou_suis_Je_TTRIS(int xx_, int yy_);
void Select_Piece_TTRIS(unsigned char Piece_);
void rotate_Matrix_TTRIS(unsigned char ROT);
unsigned char Scan_Piece_Matrix_TTRIS(int x_Mat, int y_Mat);
unsigned char GRID_STAT_TTRIS(int X_SCAN, int Y_SCAN);
unsigned char CHANGE_GRID_STAT_TTRIS(int X_SCAN, int Y_SCAN, unsigned char VALUE);
unsigned char blitzSprite_TTRIS(int xPos, int yPos, unsigned char xPASS, unsigned char yPASS, unsigned char FRAME, const unsigned char *SPRITES);
unsigned char H_grid_Scan_TTRIS(unsigned char xPASS);
unsigned char Recupe_TTRIS(unsigned char xPASS, unsigned char yPASS);
unsigned char NEXT_BLOCK_TTRIS(unsigned char xPASS, unsigned char yPASS);
unsigned char RECUPE_BACKGROUND_TTRIS(unsigned char xPASS, unsigned char yPASS);
unsigned char DropPiece_TTRIS(unsigned char xPASS, unsigned char yPASS);
unsigned char SplitSpriteDecalageY_TTRIS(unsigned char decalage, unsigned char Input, unsigned char UPorDOWN);
unsigned char RecupeLineY_TTRIS(unsigned char Valeur);
unsigned char RecupeDecalageY_TTRIS(unsigned char Valeur);
void Tiny_Flip_TTRIS(unsigned char HR_TTRIS);
void Flip_intro_TTRIS(unsigned char *TIMER1);
unsigned char intro_TTRIS(unsigned char xPASS, unsigned char yPASS, unsigned char *TIMER1);
unsigned char Recupe_Start_TTRIS(unsigned char xPASS, unsigned char yPASS, unsigned char *TIMER1);
unsigned char recupe_Chateau_TTRIS(unsigned char xPASS, unsigned char yPASS);
unsigned char recupe_SCORES_TTRIS(unsigned char xPASS, unsigned char yPASS);
void Convert_Nb_of_line_TTRIS(void);
unsigned char recupe_Nb_of_line_TTRIS(unsigned char xPASS, unsigned char yPASS);
unsigned char recupe_LEVEL_TTRIS(unsigned char xPASS, unsigned char yPASS);
void INIT_ALL_VAR_TTRIS(void);
void recupe_HIGHSCORE_TTRIS(void);
void Reset_Value_TTRIS(void);
void save_HIGHSCORE_TTRIS(void);
void Check_NEW_RECORD(void);
unsigned char checksum(unsigned char Byte_);
long map(long x, long in_min, long in_max, long out_min, long out_max);

// Additional Defines
#define abs(n) ((n>=0)?(n):(-(n)))

#endif