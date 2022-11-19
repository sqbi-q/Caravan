/*
Copyright (c) 2022 the Caravan contributors
For a full list of authors, please see the CREDITS file.
Original work by
Copyright (c) 2003 Bruno T. C. de Oliveira

LICENSE INFORMATION:
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public
License along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#ifndef _btco_aewan_menubar_h
#define _btco_aewan_menubar_h

/* Shows the menu onscreen and lets the user interact with it.  
 * Returns the command number (as in command.h) of the selected item.
 * This function will restore the screen contents to their previous 
 * state before returning (a most unusual courtesy, mind you). 
 *
 * If the user cancels the menu, returns COMMAND_UNDEFINED. 
 *
 * startopen gives the index of the menu that should be rolled down
 * by default. If 0, the leftmost menu will start rolled down; if 1, 
 * the next one to the right will and so on.
 */
int menubar_show(int startopen);

#endif

