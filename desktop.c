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
#include <stdbool.h>

void Desktop_GetWindows( Display * d, Window * win, Window * out, int *activeWindows, int buffer_size )
{
	XTextProperty text;
	int error;
	int windowsFound = 0;
	
	Window rootReturn, parentReturn, *childrenReturn;
	int num;

	/* start from the top */
	*win = DefaultRootWindow( d );
	
	if( XQueryTree( d, *win, &rootReturn, &parentReturn, &childrenReturn, &num) > 0)
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
							if( windowsFound > (buffer_size - 1) )
							{
								break;
							}
							out[ windowsFound ] = c[j];
							// printf("[%d] %s\n", windowsFound, text.value);
							windowsFound++;
						}
					}
				}
			}
		}
		XFree(childrenReturn);
		XFree(c);

		printf("%d Active Window(s) Found\n",windowsFound);
		*activeWindows = windowsFound;
	}
}

void Desktop_IsFocused( Display  * d, Window * selected )
{
	static bool wasFocused = false;
	XTextProperty currentText, selectedText;
	int error;
	Window current;
	/* Current focus state */
	int focusState;

	memset( &currentText, 0x00, sizeof(XTextProperty));
	memset( &selectedText, 0x00, sizeof(XTextProperty));

	XGetInputFocus( d, &current, &focusState);
	
	if( current == (*selected + 1))
	{
		if(!wasFocused)
		{
			printf("Window in focus!\n");
			wasFocused = true;
		}
	}	
	else
	{
		if(wasFocused)
		{
			printf("Window no longer focus!\n");
			wasFocused = false;
		}
	}
	
}

void Desktop_ListWindows( Display  * d, Window * win, int num )
{
	XTextProperty text;
	int error;

	for( int i =0; i < num; i++)
	{
		memset( &text, 0x00, sizeof(XTextProperty));
		error = XGetWMName( d, win[i],&text);
		if( error != 0 )
		{
			printf("[%d] %s\n", i, text.value);
		}
	}
}
