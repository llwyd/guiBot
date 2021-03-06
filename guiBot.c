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
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

#include "desktop.h"

#define WINDOWS_LIST_SIZE ( 32U )

typedef enum
{
	state_findingWindow, /* finding the desired window */
	state_autoWindow,	/* carrying out the automation routine */
}state_t;

int main( void )
{
	printf("\nguiBot automation engine\n\n");
	
	state_t currentState = state_findingWindow;

	/* Initialise and open X11 display */
	Display * d = XOpenDisplay( 0 );

	/* Current window we want to attach */
	Window c;

	/* buffer for number of windows to store and list */
	Window win[ WINDOWS_LIST_SIZE ];
	memset(win, 0x00, sizeof(Window)*WINDOWS_LIST_SIZE);
	int activeWindows = 0;

	/* Current focus state */
	int focusState;

	XGetInputFocus( d, &c, &focusState );
	
	Desktop_GetWindows( d, &c, win, &activeWindows, WINDOWS_LIST_SIZE);

	Desktop_ListWindows( d, win, activeWindows );

	printf("\n\nSelect a window: ");
	int winIdx = 0;
	scanf("%d", &winIdx);

	/* assign current window */
	c = win[winIdx];

	XSelectInput( d, c, KeyPressMask | KeyReleaseMask );

	int keypress = XKeysymToKeycode(d, XStringToKeysym("a"));

	XTestFakeKeyEvent( d,keypress, True,0);
	XFlush(d);
	XTestFakeKeyEvent(d,keypress,False,0);
	XTestFakeMotionEvent(d,0, 100,100,0);
	XFlush(d);

	while( 1 )
	{
		/* state finding window */
		switch( currentState )
		{
			case state_findingWindow:
				if( Desktop_IsFocused( d, &c ) )
				{
					currentState = state_autoWindow;
				}
				usleep(100);
				break;
			case state_autoWindow:	
				if( !Desktop_IsFocused( d, &c ) )
				{
					currentState = state_findingWindow;
				}
				usleep(100);
		}

	}
	XCloseDisplay( d );

	return 0;
}
