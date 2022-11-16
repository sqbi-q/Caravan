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

#include "chtr.h"

int chtr_a2c(unsigned char aewan_ch) {
   int mappings[32] = {
        ACS_CKBOARD, 
        ACS_HLINE,
        ACS_VLINE,
        ACS_ULCORNER,
        ACS_TTEE,
        ACS_URCORNER,
        ACS_LTEE,
        ACS_PLUS,
        ACS_RTEE,
        ACS_LLCORNER,
        ACS_BTEE,
        ACS_LRCORNER,
        ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, 
        ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, 
        ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, 
        ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD, ACS_CKBOARD
   };

   if (aewan_ch < 32) return mappings[aewan_ch];
   return aewan_ch;
}

