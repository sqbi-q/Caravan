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

#ifndef _btco_aewan_handlekey_h
#define _btco_aewan_handlekey_h

/* Reacts to keypress. <ch> is the code of the key that was pressed */
void handle_key(int ch);

/* Similar to handle_key(). <wch> is wide character representation 
 * (int[4], null-terminated) of pressed key.  */
void handle_wchkey(int* wch);

/* Reacts to the command <cmd>. Called from handle_key. */
void handle_command(int cmd);

/* Interacts with the user in order to allow him to load a file into
 * the editor. If the supplied_filename parameter is not NULL, the
 * user will not be asked for the filename; rather, the supplied
 * filename will identify the file to be loaded */
void u_load_file(const char *supplied_filename);

#endif

