/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 13/7/22 
* OL124 KNIGHT TOUR project
*******************************************************************/
#include <stdio.h>		/*	printf	*/
#include <stddef.h>		/*	size_t  */
#include <assert.h>		/*  assert  */

#include "bit_array.h"	
#include "knight_tour.h"

 
#define NUM_OF_ROWS 8
#define NUM_OF_COLUMNS 8
#define BOARD_SIZE  NUM_OF_ROWS * NUM_OF_COLUMNS
#define NUM_OF_DIRECTIONS 8


static const int MoveRowLUT[8] = {1, 2, 2, 1, -1, -2, -2, -1};
static const int MoveColLUT[8] = {2, 1, -1, -2, -2, -1, 1, 2};


typedef enum possibilities_lut_status
{
	NOT_INITIALIZED,
	INITIALIZED
} possibilities_lut_status_ty;


static int possible_moves_lut[64] = {0};
static int next_positions_lut[64][8] = {0};

static possibilities_lut_status_ty possible_moves_lut_status = NOT_INITIALIZED;

static void InitValidStepsLut(void);

/*	creates a LUT of 512 : 8 possible moves for each position (64 positions).
 *	creates a LUT of 64: each index will store the amount of legitimate moves,
 *	which keep the knight in bounds of the board.			*/												
static void CreatePossibleMovesLutIMP(void);

/*	the huristic solution to find a path in the fastest way based on
 *	moving each time to the location with the minimum 
 *	number of unvisited adjacent										*/															
static int KnightPathHeuristicRec(unsigned char path[BOARD_SIZE], int position,bit_arr_ty *board);
																		
/*	direction is 0-7, position is 0-63.
 *	Returns -1 if move in direction takes you out of the board			*/
static int GetNextPositionIMP(int current_position, int direction);

/*	converts a given index to x and y coordinates of 0-7 each one 		*/
static void IndexToCartesianIMP(int index, int *x_coordinate, int *y_coordinate);

/*	converts x and y coordinates into an index of 0-63					*/
static int CartesianToIndexIMP(int x_coordinate, int y_coordinate);

/*	checks if a given position is out of bounds of the board.
 *	returns 1 if the given position is out of the board, 0 otherwise.	*/
static int IsPositionOutOfBound(int x_coordinate, int y_coordinate);

/*	checks if a given position has been marked as visited 				*/
static int HaveYouVisitedThisPositionYet(bitsarr_ty board, int position);

/*	marks a given position on the board as visited						*/
static bitsarr_ty MarkPositionAsVisitedIMP(bitsarr_ty board, int position);

/*	compares two given positions. Returns:
 *	Positive value if the first position has more legitimate available moves
 	than the other position.
 *	0 if both positions have the same amount of legitimate available moves.
 *	Negative value otherwise.	*/
static int ComparePositionsIMP(const void *data1, const void *data2);


void KnightPath(char _path[], char x_start_pos, char y_start_pos)
{

	bit_arr_ty board = 0;

    int i = 0;	
	
    assert(x_start_pos > -1 && x_start_pos < 8);
    assert(y_start_pos > -1 && y_start_pos < 8);
	assert(_path);

	InitValidStepsLut();

    if(!KnightPathHeuristicRec(_path, 8 * (x_start_pos) + y_start_pos, knight_lut,board))
    {
        for(i = 0; i < BOARD_SIZE; ++i)
        {
            printf("%d ", _path[i]);
            if(i == BOARD_SIZE - 1)
            {
                printf("\n\n");
            }

        }
    }
}

int TourIMP(unsigned char path[BOARD_SIZE], int position, bitsarr_ty board,
																time_t timer)
{	
	int direction_to_go = 0;
	
	int position_x_coordinate = 0, position_y_coordinate = 0;
	
	time_t curr_time = time(&curr_time);
	
	IndexToCartesianIMP(position, &position_x_coordinate,
														&position_y_coordinate);
	

	
	/* if each location at the board has been visited */
	if (BitArrayCountOnLUT(board) == BOARD_SIZE)
	{
		return (0);
	}
	
	/*	verify the position is valid: */
		/*	-	is not out of the bounds of the board	*/
		/*	-	has not been visited before				*/	
	if (IsPositionOutOfBound(position_x_coordinate, position_y_coordinate)
							|| HaveYouVisitedThisPositionYet(board, position))
	{
		return (1);
	}
	

	/*	tick curr position at the board*/	
	board = MarkPositionAsVisitedIMP(board, position);

	/*	recursively call 8 available positions 	*/
	for (direction_to_go = 0; direction_to_go < NUM_OF_DIRECTIONS;
															 ++direction_to_go)
    {
        /* if TourIMP(path+1,...) in direction succeeds*/
        if (!TourIMP(path + 1, GetNextPositionIMP(position, direction_to_go),
         														board, timer))
        {
            /* save the position that's correct in path array before exiting*/
            *path = position;
            
            return (0);
        }
    }
	
	return (1);
}
/******************************************************************************/
static int GetNextPositionIMP(int curr_position, int direction)
{

	
	int new_position_x = 0, new_position_y = 0;
	int curr_position_x = 0, curr_position_y = 0;
	
		
	IndexToCartesianIMP(curr_position, &curr_position_x, &curr_position_y);
	
	/*	update position as the rule of the direction says */
	new_position_x = curr_position_x + MoveColLUT[direction];
	new_position_y = curr_position_y + MoveRowLUT[direction];
	
	/*	check if the new position is out of bounds and if not, return it */
	return (IsPositionOutOfBound(new_position_x, new_position_y) ? (-1) :
						CartesianToIndexIMP(new_position_x, new_position_y));
}
/******************************************************************************/

/******************************************************************************/
int IsPositionOutOfBound(int col, int row)
{							
	return (col >= NUM_OF_COLUMNS || row >= NUM_OF_ROWS || col < 0 || row < 0);
}

/******************************************************************************/
void IndexToCartesianIMP(int index, int *x_coordinate, int *y_coordinate)
{
	assert(x_coordinate && y_coordinate);
	
	*x_coordinate = index % NUM_OF_COLUMNS;
	*y_coordinate = index / NUM_OF_ROWS;
}
/******************************************************************************/
int CartesianToIndexIMP(int x_coordinate, int y_coordinate)
{
	assert(x_coordinate >= 0 && y_coordinate >= 0 && 
				y_coordinate < NUM_OF_ROWS && x_coordinate < NUM_OF_COLUMNS);
	
	return ((y_coordinate * NUM_OF_ROWS) + x_coordinate);
}
/******************************************************************************/
void InitValidStepsLut(void)
{
	if (NOT_INITIALIZED == possible_moves_lut_status)
	{
		CreatePossibleMovesLutIMP();
		possible_moves_lut_status = INITIALIZED;
	}
}
/*----------------------------------------------------------------------------*/
void CreatePossibleMovesLutIMP(void)
{
	int i = 0, direction = 0, next_position = 0;
		
	/*	creates a LUT of 512 : 8 possible moves for each position.
	 *	some of the 8 possible moves may be invalid and out of bounds. */
	for (i = 0; i < BOARD_SIZE; ++i)
	{
		for (direction = 0; direction < NUM_OF_DIRECTIONS; ++direction)
		{
			 next_position = GetNextPositionIMP(i, direction);
			 
			 next_positions_lut[i][direction] = next_position;
			 
			 /*	creates a LUT of 64: each index will store the amount of 
			  *	legitimate moves, which keep the knight in
			  *	bounds of the board.			*/
			 if (-1 != next_position)
			 {
			 	++possible_moves_lut[i];
			 }
		}
	}
	
	/*	for each position, sort the possible future positions based on the
	 *	amount of their future legitimate moves. The array will be sorted from
	 *	the minimum to the maximum legitimate future positions.		*/ 
	 
	for (curr_position = 0; curr_position < BOARD_SIZE; ++curr_position)
	{
		qsort(next_positions_lut + curr_position, NUM_OF_DIRECTIONS, 
											sizeof(int), ComparePositionsIMP);
	}
}
/******************************************************************************/
static int KnightPathHeuristicRec(char _path[BOARD_SIZE], int row, int col, bit_arr_ty board)															
{	
	
	int direction = 0, num_of_possible_directions = 0, position_index  = NUM_OF_ROWS * row + col ;
	
	if (BitArrayCountOnLUT(board) == BOARD_SIZE)
	{
		return 0;
	}
	
	    /*	verify the position is valid: */
		/*	-	is not out of the bounds of the board	*/
		/*	-	has not been visited before				*/	
	if (IsPositionOutOfBound(col, row) || (BitArrayGetVal(&board,position_index)))
	{
		return 1;
	}
	

    BitArraySetOn(board, position_index);
    _path[position_index] = BitArrayCountBitsOn(&board);
    
	/*	count the number of legitimate possible moves out of 8 */
	num_of_possible_directions = NUM_OF_DIRECTIONS - possible_moves_lut[position_index];
	
	/*	try each location from the sorted array but after skipping all the
	 *	invalid locations which indicated by (-1), which means they will
	 *	be shown in the beginning of the array and the first valid location
	 *	will appear on index of (num_of_directions - legitimate_future_moves) */
	 
	for (direction = num_of_possible_directions; direction < NUM_OF_DIRECTIONS;++direction)
	{
		if (!KnightPathHeuristicRec(_path + 1, next_positions_lut[position][direction],board))
		{
			/* save the position that's correct in path array before exiting*/
			*_path = position;

			return (0);
		}
	}

	return (1);
}
/******************************************************************************/
int ComparePositionsIMP(const void *data1, const void *data2)
{
	int position1 = 0, position2 = 0;
	
	assert(data1);
	assert(data2);
	
	position1 = *(int*)data1;
	position2 = *(int*)data2;
	
	return (possible_moves_lut[position1] - possible_moves_lut[position2]);
}
/******************************************************************************/