/*
*
*	Desktop.h
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

void Desktop_GetWindows( Display * d, Window * win );
void Desktop_ListWindows( Window * win, int num );
