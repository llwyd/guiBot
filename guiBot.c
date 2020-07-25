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



int main( void )
{
	/* Initialise and open X11 display */
	Display * d = XOpenDisplay( 0 );

	/* Current window we want to attach */
	Window c;

	/* Current focus state */
	int focusState;

	XGetInputFocus( d, &c, &focusState );
	
	Desktop_GetWindows( d, &c);

	return 0;
}
