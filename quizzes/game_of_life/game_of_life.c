/*************************************************************
* Author: Amit Regev
* Reviewer: Noam Dan Hadad
* Date: 23/6/22 
* OL124 Conway's Game of Life implementation
*******************************************************************/
#include <stddef.h> /* size_t */ 
#include <stdlib.h> /* malloc */
#include <stdio.h> /* printf */ 
#include <unistd.h> /* sleep */ 

typedef void (*SetPixel_ty)(int *matrix, size_t columns, size_t i, size_t j);

SetPixel_ty LUT_ACTION[2][9];

void SetALive(int *matrix,size_t columns, size_t i, size_t j);
void SetDead(int *matrix, size_t columns, size_t i, size_t j);

void InitRandomBoard(int *matrix, size_t num_of_rows, size_t num_of_columns)
{
    size_t i = 0;

        for(i = 0; i < num_of_columns * num_of_rows; ++i)
        {
            matrix[i] = rand() % 2;
        }
}
int NumberOfNeighbors(int *matrix, size_t r, size_t c, size_t n , size_t m)
{
    size_t counter = 0;

    counter += matrix[c * n + (m + 1) % c]; /*right*/
    counter += matrix[c * n + (m - 1 + c) % c]; /*left*/

    counter += matrix[c * ((n + 1) % r) + m]; /*down*/
    counter += matrix[c * ((n - 1 + r) % r) + m]; /*up*/

    counter += matrix[c * ((n - 1 + r) % r)+(m + 1) % c]; /*up-right*/
    counter += matrix[c * ((n - 1 + r) % r) + (m - 1 + c) % c]; /*up-left*/
    
    counter += matrix[c * ((n + 1) % r) + (m + 1) % c]; /*down-right */
    counter += matrix[c * ((n + 1) % r) + (m - 1 + c) % c];  /*down -left*/
    
    return counter;
}

void SwapPtr(int **ptr1, int **ptr2)
{
    int *tmp = NULL;
    tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;    
}

int *CreateBoard(size_t num_of_rows, size_t num_of_columns)          
{   
    int *board = (int *)malloc(num_of_rows * num_of_columns * sizeof(int));
    if(NULL == board)
    {
        return NULL;
    }

    return board;
}

void SetStatusLut(void)
{
    LUT_ACTION[0][0] = SetDead;
    LUT_ACTION[0][1] = SetDead;
    LUT_ACTION[0][2] = SetDead;
    LUT_ACTION[0][3] = SetALive;
    LUT_ACTION[0][4] = SetDead;
    LUT_ACTION[0][5] = SetDead;
    LUT_ACTION[0][6] = SetDead;
    LUT_ACTION[0][7] = SetDead;
    LUT_ACTION[0][8] = SetDead;
    LUT_ACTION[1][0] = SetDead;
    LUT_ACTION[1][1] = SetDead;
    LUT_ACTION[1][2] = SetALive;
    LUT_ACTION[1][3] = SetALive;
    LUT_ACTION[1][4] = SetDead;
    LUT_ACTION[1][5] = SetDead;
    LUT_ACTION[1][6] = SetDead;
    LUT_ACTION[1][7] = SetDead;
    LUT_ACTION[1][8] = SetDead;
}

void SetALive(int *matrix, size_t columns, size_t i, size_t j)
{
    matrix[i * columns  + j] = 1;
}

void SetDead(int *matrix, size_t columns, size_t i, size_t j)
{
    matrix[i * columns  + j] = 0;
}

int IsALive(int *matrix, size_t columns, size_t i, size_t j)
{
    return (matrix[i* columns  + j] == 1);
}

void PrintMatrix(int *matrix, size_t rows, size_t columns)
{
    size_t i = 0, j = 0;

    system("clear");
    
    for(i = 0; i < rows; ++i)
    {
        for (j = 0; j < columns; ++j)
        {
            if(matrix[columns * i + j] == 1)
            {
                putchar('*');
            }

            else
            {
                putchar(' ');
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    size_t rows = 30 , columns = 30, i = 0, j = 0, counter = 0;

    int *board1 = NULL , *board2 = NULL;

    if (argc > 2)
    {
        rows = (size_t)atol(argv[argc - 2]);
        columns = (size_t)atol(argv[argc - 1]);
    }

    board1 = CreateBoard(rows, columns);
    board2 = CreateBoard(rows, columns);
    InitRandomBoard(board1, rows, columns);
    SetStatusLut();
    
    while(1)
    {
        PrintMatrix(board1, rows, columns);

        for(i = 0; i < rows; ++i)
        {
            for(j = 0; j < columns; ++j)
            {
                counter = NumberOfNeighbors(board1, rows, columns, i, j);
                LUT_ACTION[IsALive(board1, columns, i,j)][counter](board2,columns,i,j);
            }
        }

        SwapPtr(&board1, &board2);

        sleep(1);
    }

    return 0;
}