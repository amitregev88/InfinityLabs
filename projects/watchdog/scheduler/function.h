/******************************************************************************/
/*	Project:   function 	                         						  */
/*  Name:      HRD25        		                                    	  */
/*	Date:      21.06.2022 						                              */
/*  File:	   function.h													  */
/*	Version:   1.0											                  */
/*	Reviewer:  Rina                                                     	  */
/******************************************************************************/

#ifndef	__ILRD_FUNC_H__
#define	__ILRD_FUNC_H__	


/****************************************************************************
* Function Description: Compare between params priority. 
*Arguments: priority function.
*Return value: Returns 1 if data priority is higher or equal than new_data,
			   else, return 0. 
*Notes:
*Time complexity: O(1)
*****************************************************************************/		
typedef int (*is_higher_priority)(const void *data, void *new_data);

/****************************************************************************
* Function Description: Checks if data and user param is the same. 
*Arguments: priority function.
*Return value: Returns 1 if true, otherwise 0.
*Notes: 
*Time complexity: O(1)
*****************************************************************************/
typedef int (*match_func_ty)(const void *data, void *param);

/****************************************************************************
* Function Description: Preform the command function on data1. Data2 is an 
						optional parameter you can use it in the command 
						function.  
*Arguments: command function.
*Return value: Returns 0 if successful, otherwise 1.
*Notes: 
*Time complexity: O(1)
*****************************************************************************/
typedef int (*cmd_func_ty)(void *data1, void *data2);

/****************************************************************************/
 #endif     /* __ILRD_FUNC_H__                                              */ 
/****************************************************************************/
