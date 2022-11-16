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

#include "bores/bores.h"
#include <ncurses.h>

#include "colordlg.h"
#include "psd.h"

static void paint_dlg(void) {
   int x0, y0; int i, j;
   char hexdigit[] = "0123456789abcdef";
   
   kurses_color(7, 0);
   draw_centered_window(39, 21, "Choose Color", &x0, &y0);
   
   /* draw bg color knob */
   kurses_color(12, 0);
   kurses_move(x0 + 4 + 2 * _bg, y0);
   addch('b');

   /* draw fg color knob */
   kurses_color(10, 0);
   kurses_move(x0, y0 + 2 + _fg);
   addch('f');

   /* draw horizontal (bg) ruler */
   kurses_color(7, 0);
   kurses_move(x0 + 4, y0 + 1);
   addstr("0 1 2 3 4 5 6 7 8 9 a b c d e f");
   
   /* draw vertical (fg) ruler */
   for (i = 0; i < 16; i++) {
      kurses_move(x0 + 2, y0 + 2 + i);
      addch(hexdigit[i]);
   }

   /* draw squares */
   for (i = 0; i < 16; i++) {
      kurses_move(x0 + 4, y0 + 2 + i);
      for (j = 0; j < 16; j++) {
         kurses_color(i, j);
         addstr("Aa");
      }
   }

   /* place cursor on selected square */
   kurses_move(x0 + 4 + 2 * _bg, y0 + 2 + _fg);
}

void show_color_dlg(void) {
   int ch;
   while (1) {
      paint_dlg();
      refresh();
      ch = getch();
      switch (ch) {
         case 27: case 3: case 7: case 10: return;
         case KEY_UP:    if (--_fg < 0)   _fg = 15; break;
         case KEY_DOWN:  if (++_fg >= 16) _fg = 0;  break;
         case KEY_LEFT:  if (--_bg < 0)   _bg = 15; break;
         case KEY_RIGHT: if (++_bg >= 16) _bg = 0;  break;
      }
   }
}

