/*
*
*	Desktop.c
*
*	Module for interfacing with desktop
*	T.Lloyd
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void Desktop_GetWindows( Display * d, Window * win )
{
	XTextProperty text;
	int error;
	
	Window rootReturn, parentReturn, *childrenReturn;
	int num;

	/* start from the top */
	win = DefaultRootWindow( d );
	
	if( XQueryTree( d, win, &rootReturn, &parentReturn, &childrenReturn, &num) > 0)
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
}

void Desktop_ListWindows( Window * win, int num );
