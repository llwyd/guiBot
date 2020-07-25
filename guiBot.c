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
	
	Window rootReturn, parentReturn, *childrenReturn;
	int num;

	/* start from the top */
	c = DefaultRootWindow( d);
	
	if( XQueryTree( d, c, &rootReturn, &parentReturn, &childrenReturn, &num) > 0)
	{
		/* print names */
		Window a, b, *c;
		int childNum;

		/* Free unused pointers */

		for(int i = 0;i < num; i++)
		{
			if( XQueryTree(d, childrenReturn[i], &a, &b, &c, &childNum))
			{
				if( childNum == 16 )
				{
					for( int j=0; j < childNum;j++)
					{
						memset( &text, 0x00, sizeof(XTextProperty));
						error = XGetWMName( d, c[j], &text);
						if( error != 0 )
						{
							printf("%s\n", text.value);
						}
					}
				}
			}
		}
		XFree(childrenReturn);
		XFree(c);
	}

	return 0;
}
