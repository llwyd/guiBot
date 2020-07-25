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
	
	Window w, x,*y;
	int num;

	c = DefaultRootWindow( d);

	while(1){
	
	if( XQueryTree( d, c, &w, &x, &y, &num) > 0)
	{
		printf("Found %d windows\n", num);
		/* print names */
		

		Window a, b, *c;
		int childNum;

		for(int i = 0;i < num; i++)
		{
			if( XQueryTree(d, y[i], &a, &b, &c, &childNum))
			{
				printf("\tFound %d windows\n", childNum);
				for( int j=0; j < childNum;j++)
				{
					
			memset( &text, 0x00, sizeof(XTextProperty));
			error = XGetWMName( d, c[j], &text);
			if( error != 0 )
			{
				printf("\t\t%s\n", text.value);
			}
				}
			}
		}


		for(int i=0; i < num; i++)
		{
			memset( &text, 0x00, sizeof(XTextProperty));
			error = XGetWMName( d, y[i], &text);
			if( error != 0 )
			{
				printf("%s\n", text.value);
			}
		}
	}
		/*
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
			
		}*/
	sleep(4);
	}

	return 0;
}
