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
#include <X11/Xlib.h>
#include <X11/Xutil.h>



int main( void )
{
	/* Initialise and open X11 display */
	Display * d = XOpenDisplay( 0 );

	/* Current window we want to attach */
	Window c;

	/* Current focus state */
	int focusState;

	XGetInputFocus( d, &c, &focusState );

	XTextProperty text;
	int error;
	char previous[100] = {0};
	while(1){
		memset( &text, 0x00, sizeof(XTextProperty));
		XGetInputFocus( d, &c, &focusState );
		error = XGetWMName( d, c, &text);
		if( error!=0){
			if( strcmp(text.value,previous) )
			{
				printf("%s\n", text.value);
				memset(previous,0x00,100);
				strcat(previous, text.value);
			}
			
		}
	}

	return 0;
}
