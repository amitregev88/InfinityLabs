/*******************************************************************************/
/*	PROJECT:    Watchdog                     							       */
/*	FILE:		wd.h														   */
/*	DATE: 		30/08/2022													   */
/*	NAME: 		HRD25														   */
/*	REVIEWER:	Evald														   */
/*	VERSION: 	1.1														  	   */
/******************************************************************************/
#ifndef __WD_H__
#define __WD_H__


#include <stddef.h>
#include <time.h>
/****************************************************************************
* Function Description: Makes the program immortal when called, restarts the
                        program if failed.

* Arguments: frequency of checking the program 'interval' in seconds.
             max number of checks to miss before restarting the program
             'max_misses'
             main's argv passing prgoram's path (to be revived in case of fail)

* Return value: 0 (SUCCESS) on success.
				1 (FAIL) on faiure.
                
* Notes: SIGUSR1 and SIGUSR2 singals are being used in the program.

* Time complexity: 
*****************************************************************************/
int MMI(const size_t max_misses, const time_t interval, char *argv[]);


/****************************************************************************
* Function Description: Stops the program from being immortal.

* Arguments: none

* Return value: 0 (SUCCESS) on success.
				1 (FAIL) on faiure.
                
* Notes:

* Time complexity: 
*****************************************************************************/
int DNR(void);


#endif /*__WD_H__*/
