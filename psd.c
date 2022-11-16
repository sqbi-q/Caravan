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

#include "psd.h"
#include "document.h"

/* global program state data definitions */
struct _Document *_doc;
char *_filename;
int _lyr;
int _x, _y; 
int _svx, _svy;
int _fg, _bg;
int _selmode;
int _ax, _ay;
bool _insmode;
bool _lgmode;
bool _compmode;
struct _Layer *_clipboard; 


void get_norm_sel(int *x0, int *y0, int *x1, int *y1) {
   sort_two(_x, _ax, x0, x1);
   sort_two(_y, _ay, y0, y1);
}

bool doc_empty() { return 0 >= _doc->layer_count; }

void zero_state() {
   _doc = document_create();
   _filename = 0;
   _lyr = _x = _y = _svx = _svy = _ax = _ay = 0;
   _selmode = SM_NONE;
   _fg = 7;
   _bg = 0;
   _insmode = false;
   _clipboard = 0;
   _lgmode = false;
   _compmode = false;
}

void switch_to_layer(int l) {
   Layer *lyr;
   if (l < 0 || l >= _doc->layer_count) return;

   lyr = _doc->layers[_lyr = l];
   if (_x >= lyr->width)  _x = lyr->width - 1;
   if (_y >= lyr->height) _y = lyr->height - 1;
}

