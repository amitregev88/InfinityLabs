/****************************************************************************
 *	Project:	TCP / UDP Ping-Pong                             			*												*
 *	Date: 		24/10/2022													*
 *	Name: 		Amit Regev													*
 *	Reviewer:	Amir Shachar										        *
 *	Version: 	1.00														*
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> /*close*/

#include "../include/utility.h"

#define PORT 55555

