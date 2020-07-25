/*
*
*	A template framework for interfacing X11 with opencv
*
*	T.L 2020
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "desktop.h"

#define WINDOWS_LIST_SIZE ( 32U )

int main( void )
{
	printf("\nguiBot automation engine\n\n");
	
	/* Initialise and open X11 display */
	Display * d = XOpenDisplay( 0 );

	/* Current window we want to attach */
	Window c;

	/* buffer for number of windows to store and list */
	Window win[ WINDOWS_LIST_SIZE ];
	int activeWindows = 0;

	/* Current focus state */
	int focusState;

	XGetInputFocus( d, &c, &focusState );
	
	Desktop_GetWindows( d, &c, win, &activeWindows, WINDOWS_LIST_SIZE);

	Desktop_ListWindows( d, win, activeWindows );

	return 0;
}
