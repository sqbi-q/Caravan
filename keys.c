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

#include <ncurses.h>

#include "keys.h"

void keys_init() {
   int i;
   char seq[] = "\ex";
   for (i = KEY_ALT_A; i <= KEY_ALT_Z; i++) {
      seq[1] = i - KEY_ALT_A + 'a';
      define_key(seq, i);
   }

   /* xterm, support */
   define_key("\e[1;2A", KEY_UP);    /* shift + up */
   define_key("\e[1;2B", KEY_DOWN);  /* shift + down */
   define_key("\e[1;2C", KEY_RIGHT); /* shift + right */
   define_key("\e[1;2D", KEY_LEFT);  /* shift + left */

   /* rxvt support */
   define_key("\e[[a", KEY_UP);     /* shift + up */
   define_key("\e[[b", KEY_DOWN);   /* shift + down */
   define_key("\e[[c", KEY_RIGHT);  /* shift + right */
   define_key("\e[[d", KEY_LEFT);   /* shift + left */
   define_key("\e[7~", KEY_HOME);   /* home key */
   define_key("\e[8~", KEY_END);    /* end key */
   define_key("\e[11~", KEY_F(1));
   define_key("\e[12~", KEY_F(2));
   define_key("\e[13~", KEY_F(3));
   define_key("\e[14~", KEY_F(4));
}

