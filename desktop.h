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
#include <stdbool.h>

bool Desktop_IsFocused( Display  * d, Window * selected );
void Desktop_GetWindows( Display * d, Window * win, Window * out, int * activeWindows, int buffer_size );
void Desktop_ListWindows( Display  * d, Window * win, int num );
