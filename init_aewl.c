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

#include "aewl/aewl.h"
#include <ncurses.h>
#include <stdbool.h>

static int curses_attr_for_pair(int fg, int bg, bool bold) {
   short int cp = bg * 8 + 7 - fg;
   if (!cp) return bold ? A_BOLD : A_NORMAL;
   return COLOR_PAIR(cp) | (bold ? A_BOLD : 0);
}

void init_aewl() {
   AewlAttrSettings ats = {
      {
         curses_attr_for_pair(7, 0, false), /* text */
         curses_attr_for_pair(7, 0, true),  /* text focus */
         curses_attr_for_pair(1, 0, false), /* text shortcut */
         curses_attr_for_pair(1, 0, true)   /* text shortcut focus */
      },

      {
         curses_attr_for_pair(7, 4, false), /* button */
         curses_attr_for_pair(7, 2, true),  /* button focus */
         curses_attr_for_pair(1, 4, false), /* button shortcut */
         curses_attr_for_pair(1, 2, true)   /* button shortcut focus */
      },

      {
         curses_attr_for_pair(7, 0, false), /* frame */
         curses_attr_for_pair(7, 0, true),  /* frame focus */
         curses_attr_for_pair(1, 0, false), /* frame shortcut */
         curses_attr_for_pair(1, 0, true)   /* frame shortcut focus */
      },

      {
         curses_attr_for_pair(7, 0, false), /* field */
         curses_attr_for_pair(7, 0, true),  /* field focus */
         curses_attr_for_pair(7, 4, false), /* field selection */
         curses_attr_for_pair(7, 1, true)   /* field selection focus */
      },

      curses_attr_for_pair(0, 0, true)      /* field pad char */
   };

   aewl_init(&ats);
}

