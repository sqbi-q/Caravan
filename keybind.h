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

#ifndef btco_aewan_keybind_h
#define btco_aewan_keybind_h

/* Initializes the keybindings to "factory default". This must be called
 * on startup, since the keymap will contain trash unless it is explicitly
 * initialized. */
void keybind_init(void);

/* TODO: insert functions for loading user's custom keybinding from
 * his .aewanrc file or something */

/* Returns which command the given key corresponds to. Returns
 * COMMAND_UNDEFINED if it does not correspond to any command. */
int keybind_translate(int key);

#endif

