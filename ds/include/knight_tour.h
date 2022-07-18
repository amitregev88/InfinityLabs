/***************************
 * OL124 KNIGHT TOUR PROJECT
 * knight_tour.h
 * knight_tour.c
 * knight_tour_test.c
 *
 * version 1.2
 ***************************/


#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__


/***********************************************************
 * --- KnightPath ---
 * Function find path of the knight provided in _path - array in size 64.
 * index of x,y are defined in range: 0-7 
 * (other values provided to function are undefined)
 ***********************************************************/
void KnightPath(char _path[], char x_start_pos, char y_start_pos);

#endif /* __KNIGHT_TOUR_H__ */
