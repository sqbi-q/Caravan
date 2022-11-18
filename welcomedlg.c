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
                                                                                
#include "welcomedlg.h"
#include "psd.h"

#define LOGO_WIDTH 14
#define LOGO_HEIGHT 5

static char* logo[] = {
   "7--9          ",
   "|  3          ",
   "| 797979977979",
   "| 4||34|||4|||",
   "1-2231|1133131",
   NULL
};

static int logo_colors[LOGO_HEIGHT] = { 1, 1+8, 3+8, 3, 1 };   //Caravan Carmel color theme

void show_welcome_dlg(void) {
   int x0, y0, x, y, ch, *clr;
   char **p, *q;
   int acschars[10] = {
      ACS_CKBOARD,      /* 0 */
      ACS_LLCORNER,     /* 1 */
      ACS_BTEE,         /* 2 */ 
      ACS_LRCORNER,     /* 3 */
      ACS_LTEE,         /* 4 */
      ACS_PLUS,         /* 5 */
      ACS_RTEE,         /* 6 */
      ACS_ULCORNER,     /* 7 */
      ACS_TTEE,         /* 8 */
      ACS_URCORNER      /* 9 */
   };

   kurses_color(3, 0);
   draw_centered_window(46, 18, " Welcome to Caravan! ", &x0, &y0);
   x = x0 + 23 - LOGO_WIDTH / 2 - 1;
   y = y0;

   /* draw logo */
   for (p = logo, clr = logo_colors; *p; p++, clr++) {
      kurses_color(*clr, 0);
      kurses_move(x, y++);
      for (q = *p; *q; q++) {
         if (*q >= '0' && *q <= '9') ch = acschars[*q - '0'];
         else if (*q == '-')         ch = ACS_HLINE;
         else if (*q == '|')         ch = ACS_VLINE;
         else                        ch = ' ';
         addch(ch);
      }
   }

   /* draw version next to logo */
   y=y0; x = x0 + 23;

   kurses_move(x, y++);
   kurses_color(0+8, 0);
   addstr("Program version: ");
   x+=1;
   kurses_move(x, y);
   kurses_color(0+8, 0);
   addstr(AEWAN_PROGRAM_VERSION " (" AEWAN_PROGRAM_VERSION_NAME ")");


   /* draw program name below logo */
   x = x0 + 6;
   y = y0 + LOGO_HEIGHT;
   
   kurses_move(x, y++);
   kurses_color(3+8, 0);
   addstr("Caravan - ");   kurses_color(1+8, 0);
   addstr("Cool ");
   addstr("ASCII ");
   addstr("Art ");
   addstr("Editor");

   x = x0 + 2;

   kurses_move(x, y++);
   kurses_color(7, 0);
   addstr("Copyright (c) 2022 Caravan contributors");

   y++;
   kurses_move(x, y++);
   addstr("Fork of Aewan (Bruno T. C. de Oliveira)");

   y++;
   kurses_move(x, y++);
   addstr("This program is licensed under the GNU");

   kurses_move(x, y++);
   addstr("General Public License. Please refer to");

   kurses_move(x, y++);
   addstr("the COPYING file for more information.");

   y++;
   kurses_move(x, y++);
   addstr("Press RETURN to continue. When in the");
   kurses_move(x, y++);
   addstr("program, press <F1> to display a menu.");

   getch();
}

