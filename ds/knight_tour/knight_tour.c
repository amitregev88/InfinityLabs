/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 13/7/22 
* OL124 KNIGHT TOUR project
*******************************************************************/
#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/
#include "knight_tour.h"
#include "bit_array.h"


#define NUM_OF_ROWS 8
#define NUM_OF_COLUMNS 8
#define BOARD_SIZE  NUM_OF_ROWS * NUM_OF_COLUMNS
#define NUM_OF_DIRECTIONS 8

static void InitKnightLut(char _knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS]);
static int KnightPathRec(char _path[BOARD_SIZE], int curr_position, char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS],bit_arr_ty board);
static void PrintKnightMoves(char knight_tour[BOARD_SIZE]);
static int GetNextStepWithMinOptionsToMove(bit_arr_ty board, char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS], int index, int checkarr[]);
static int CountValidSteps(size_t index, char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS],bit_arr_ty board);
static int IsValid_2U_1R_NextStep(size_t index);
static int IsValid_1U_2R_NextStep(size_t index);
static int IsValid_1D_2R_NextStep(size_t index);
static int IsValid_2D_1R_NextStep(size_t index);
static int IsValid_2D_1L_NextStep(size_t index);
static int IsValid_1D_2L_NextStep(size_t index);
static int IsValid_1U_2L_NextStep(size_t index);
static int IsValid_2U_1L_NextStep(size_t index);


/***********************************************************
 * --- InitKnightLut ---
 * Function init lut  size [64][8] for Knight steps -
 * to be provided to function KnightPath.
 ***********************************************************/
static void InitKnightLut(char _knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS])
{   
    size_t i = 0;
    
    for(i = 0; i < BOARD_SIZE; ++i)
    {
        _knight_lut[i][2] = IsValid_1D_2R_NextStep(i); /*3*/
        _knight_lut[i][3] = IsValid_2D_1R_NextStep(i); /*4*/
        _knight_lut[i][4] = IsValid_2D_1L_NextStep(i); /*5*/
        _knight_lut[i][5] = IsValid_1D_2L_NextStep(i); /*6*/
        _knight_lut[i][6] = IsValid_1U_2L_NextStep(i); /*7*/
        _knight_lut[i][7] = IsValid_2U_1L_NextStep(i); /*8*/
        _knight_lut[i][0] = IsValid_2U_1R_NextStep(i); /*1*/
        _knight_lut[i][1] = IsValid_1U_2R_NextStep(i); /*2*/
    }  
}

/***********************************************************
 * --- KnightPath ---
 * Function find path of the night result in _path  - array in size 64.
 *	ndex of x,y are defined in range: 0-7 
 * 	(other values provided to function are undefined)
 ***********************************************************/
void KnightPath(char _path[], char x_start_pos, char y_start_pos)
{
    bit_arr_ty chess_board = 0;

    int i = 0;

    char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS]={0};

    InitKnightLut(knight_lut);

    if(!KnightPathRec(_path, NUM_OF_ROWS * (x_start_pos) + y_start_pos, knight_lut,chess_board))
    {  
        PrintKnightMoves(_path);
    }   
}

static int KnightPathRec(char _path[BOARD_SIZE], int curr_position_index, char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS],bit_arr_ty board)
{

    int status = 1, i = 0, index_next_step = 0;
    int check_arr[8]= {1,1,1,1,1,1,1,1};

    
    if((curr_position_index == -1) || (BitArrayGetVal(&board,curr_position_index)))
    {
        /*char str[BOARD_SIZE]={0};
        BitArrayString(&board,str);
        printf("%s   Max Steps %d\n", str, BitArrayCountBitsOn(&board));*/
        return 1;
    }

    _path[curr_position_index] = BitArrayCountBitsOn(&board);
    BitArraySetOn(&board, curr_position_index);
    
    if(BitArrayCountBitsOn(&board) == BOARD_SIZE)
    {
        return 0;
    }

    index_next_step = GetNextStepWithMinOptionsToMove(board,knight_lut,curr_position_index,check_arr);
    
    while(index_next_step != -1)
    {
        /*PrintKnightMoves(_path);*/
        status = KnightPathRec(_path, index_next_step,knight_lut,board);

        if(status)
        {
            index_next_step = GetNextStepWithMinOptionsToMove(board,knight_lut,curr_position_index,check_arr);
        }

        else
        {
            return 0;
        }
    }

    return status;
}

static int IsValid_1U_2R_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8 ;

    if ((row + 1 < 8 && col + 2 < 8 ))
    {
        return (8 * (row+1) + (col+2));
    }

    return -1;
}

static int IsValid_1U_2L_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if((row + 1 < 8 && col - 2 >= 0 ))
    {
        return (8 * (row + 1) + (col - 2));
    }

    return -1;
}

static int IsValid_2U_1L_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if (row + 2 < 8 && col - 1 >= 0 )
    {
        return (8 * (row + 2 ) + (col - 1));
    } 

    return -1;
}

static int IsValid_2U_1R_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if (row + 2 < 8 && col + 1 < 8)
    {
        return (8 * (row + 2 ) + (col + 1));
    } 

    return -1;
}

static int IsValid_2D_1R_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if (row - 2 >= 0 && col + 1 < 8)
    {
        return (8 * (row - 2 ) + (col + 1));
    } 

    return -1;
}

static int IsValid_2D_1L_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if (row - 2 >= 0 && col - 1 >= 0 )
    {
        return (8 * (row - 2 ) + (col - 1));
    } 

    return -1;
}

static int IsValid_1D_2L_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if (row - 1 >= 0 && col - 2 >= 0)
    {
        return (8 * (row - 1) + (col - 2));
    } 

    return -1;
}

static int IsValid_1D_2R_NextStep(size_t index)
{
    int row = index / 8 , col = index % 8;

    if (row - 1 >= 0 && col + 2 < 8)
    {
        return (8 * (row - 1) + (col + 2));
    } 

    return -1;
}

static int GetNextStepWithMinOptionsToMove(bit_arr_ty board, char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS], int curr_pos_index, int checkarr[])
{
    int i = 0, min_steps = 9, index_to_return = 0, min_i = 0;

    for(;i < NUM_OF_DIRECTIONS ; ++i)
    {
        if(knight_lut[curr_pos_index][i] == -1 || BitArrayGetVal(&board,knight_lut[curr_pos_index][i]) == 1)
        {
            continue;       
        }

        if(BitArrayCountBitsOn(&board) == 63)
        {
            index_to_return = knight_lut[curr_pos_index][i];
            return index_to_return;
        }
        
        if(CountValidSteps(knight_lut[curr_pos_index][i],knight_lut,board) == 0)
        {
           /* return -1;*/
            continue;
        }
            
        if(CountValidSteps(knight_lut[curr_pos_index][i],knight_lut,board) < min_steps && checkarr[i]==1)
        {
            min_steps = CountValidSteps(knight_lut[curr_pos_index][i],knight_lut,board);
            index_to_return = knight_lut[curr_pos_index][i];
            min_i = i;   
        }
    }
    checkarr[min_i] = 0;
    /*index_to_return = knight_lut[curr_pos_index][min_i];*/
    return index_to_return;    
}


static void PrintKnightMoves(char knight_tour[BOARD_SIZE])
{
    int i = 0;
    static int j = 1; 

    printf("starting from row %d col %d\n\n", (j/8)+1, j%8);

    for (i = 0; i < 64; i++)
    {
        
        printf("%d\t", (int)knight_tour[i]);
        if (0 == ((i + 1) % 8))
        {
            printf("\n\n\n");
        }
    }

    printf("\n\n");

    ++j;
}

static int CountValidSteps(size_t index, char knight_lut[BOARD_SIZE][NUM_OF_DIRECTIONS],bit_arr_ty board)
{

    int i = 0, status = 0 , valid_steps_counter = 0;

    for(i = 0; i < NUM_OF_DIRECTIONS; ++i)
    {
        status = knight_lut[index][i];

        if (status != -1 && BitArrayGetVal(&board,(unsigned char)status) == 0)
        {
            ++valid_steps_counter;
        }
    }

    

    /*if(valid_steps_counter == 0 && BitArrayCountBitsOn(&board) < BOARD_SIZE )
    {
        valid_steps_counter = -1;
    }*/

    return valid_steps_counter;
}

