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
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <wchar.h>

#include "layer.h"
#include "chtr.h"
#include "widechar.h"

#if ENABLE_WIDECHAR
//const Cell BLANK_CELL = {{0, 0, 0, 0}, 0x70};
const Cell BLANK_CELL = {{' ', 0, 0, 0}, 0x70};
#else
const Cell BLANK_CELL = { ' ', 0x70 };
#endif

Layer *layer_create(const char *layer_name, int width, int height) {
   int i, j;
   Layer *layer = (Layer *) zalloc(sizeof(Layer));

   layer->name = 0;
   dstrset(&layer->name, layer_name);
   layer->width = width;
   layer->height = height;
   layer->visible = true;
   layer->transp = false;   

   layer->cells = (Cell**) zalloc(width * sizeof(Cell*));
   for (i = 0; i < width; i++) {
      layer->cells[i] = (Cell*) zalloc(height * sizeof(Cell));
      for (j = 0; j < height; j++) {
         #if ENABLE_WIDECHAR
         layer->cells[i][j].ch[0] = ' ';
         #else
         layer->cells[i][j].ch   = ' ';
         #endif
         layer->cells[i][j].attr = 0x70;
      }
   }
   
   return layer;
}

void layer_destroy(Layer *layer) {
   int i;
   if (!layer) return;
   dstrset(&layer->name, 0);
   
   for (i = 0; i < layer->width; i++) free(layer->cells[i]);
   free(layer->cells);
}

bool is_cell_transp(const Cell *c) {
   #if ENABLE_WIDECHAR
   return c->ch[0] == ' ' && c->attr == 0x70;
   #else
   return c->ch == ' ' && c->attr == 0x70;
   #endif
}

void layer_blit(Layer *src, int xsrc, int ysrc, int width, int height,
                Layer *dst, int xdst, int ydst) {
   int dx, dy;
   int src_x, src_y, dst_x, dst_y;
   
   /* brace your self to read the most inefficient blit code you have
    * ever read in your life. The following algorithm makes bubble-sort
    * look blazing fast. */
   for (dx = 0; dx < width; dx++) {
      for (dy = 0; dy < height; dy++) {
         src_x = xsrc + dx;
         src_y = ysrc + dy;
         dst_x = xdst + dx;
         dst_y = ydst + dy;

         if (!layer_valid_cell(src, src_x, src_y) ||
             !layer_valid_cell(dst, dst_x, dst_y)) continue;
             
         if (src->transp && 
             is_cell_transp(&src->cells[src_x][src_y])) continue;
         
         dst->cells[dst_x][dst_y] = src->cells[src_x][src_y];
      }
   }
}


bool layer_valid_cell(Layer *layer, int x, int y) {
   return (x >= 0 && x < layer->width && y >= 0 && y < layer->height);
}

void layer_paint(Layer *layer, int x0, int y0, int xclip, int yclip,
                 int wclip, int hclip,
                 void (*modify)(int x, int y, int *ch, int *attr)) {
                 
   int x, xi, xf; int y, yi, yf; 
   #if ENABLE_WIDECHAR
   int ch[4];
   #else
   int ch;
   #endif
   int attr;

   interval_intersect(x0   , x0    + layer->width - 1, 
                      xclip, xclip + wclip        - 1,  &xi, &xf);
   interval_intersect(y0   , y0    + layer->height - 1,
                      yclip, yclip + hclip        - 1,  &yi, &yf);
   
   for (x = xi; x <= xf; x++) for (y = yi; y <= yf; y++) {
      if (!kurses_move(x, y)) continue;
      #if ENABLE_WIDECHAR
      wintcpy(ch, layer->cells[x - x0][y - y0].ch);
      #else
      ch = layer->cells[x - x0][y - y0].ch;
      #endif
      attr = layer->cells[x - x0][y - y0].attr;
      
      if (modify) 
          #if ENABLE_WIDECHAR
          (*modify)(x - x0, y - y0, ch, &attr);
          #else
          (*modify)(x - x0, y - y0, &ch, &attr);
          #endif

      if (layer->transp && 
          is_cell_transp(&layer->cells[x - x0][y - y0])) continue;
      
      kurses_color(attr >> 4, attr & 0x0F);
      #if ENABLE_WIDECHAR
      char wch[5];
      winttwch(wch, ch);
      printw("%s", wch);
      #else
      addch(chtr_a2c(ch));
      #endif
   }
}

void layer_paint_opaque(Layer *layer, int x0, int y0, int xclip, int yclip,
                 int wclip, int hclip,
                 void (*modify)(int x, int y, int *ch, int *attr)) {
   bool backup = layer->transp;
   layer->transp = false;
   layer_paint(layer, x0, y0, xclip, yclip, wclip, hclip, modify);
   layer->transp = backup;

   /* I agree, this is a monument to sloppiness.
    * But it works, and does what is promised by the documentation. */
}

Layer *layer_dup(const char *layer_name, Layer *model) {
   Layer *l;
   if (!model) return NULL;
   
   l = layer_create(layer_name, model->width, model->height);
   l->transp = model->transp;
   layer_blit(model, 0, 0, model->width, model->height, l, 0, 0);
   return l;
}

/* table is a vector of two strings. If ch is found in table[0] at position n,
 * return value is table[1][n]. Else, return value is ch. 
 * table[0] and table[1] are assumed to be of the same size. */
#if ENABLE_WIDECHAR == 0
static char tbl_lookup(char **table, int ch) {
   const char *s = table[0], *p = table[1];
   while (*s) {
      if (*(s++) == ch) return *p;
      p++;
   }
   return ch;
}
#endif

void layer_flip_x(Layer *layer, bool flipchars) {
   Layer *tmp;
   int x, y;
   #if ENABLE_WIDECHAR == 0
   static char *flip_table[2] = {
       "`'()/\\<>[]{}\x03\x05\x06\x08\x09\x0b", /* funny hex chars are line */
       "'`)(\\/><][}{\x05\x03\x08\x06\x0b\x09"  /* drawing chars (see chtr.h) */
   };
   #endif
   
   tmp = layer_dup("tmp", layer);
   for (y = 0; y < layer->height; y++) {
      for (x = 0; x < layer->width; x++) { 
         Cell c = tmp->cells[x][y];
         
         #if ENABLE_WIDECHAR == 0
         if (flipchars) c.ch = tbl_lookup(flip_table, c.ch);
         #endif

         layer->cells[layer->width - x - 1][y] = c;
      }
   }
   
   layer_destroy(tmp);
}

void layer_flip_y(Layer *layer, bool flipchars) {
   Layer *tmp;
   int x, y;
   #if ENABLE_WIDECHAR == 0 
   static char *flip_table[2] = {
      "/\\\x03\x09\x04\x0a\x05\x0b",
      "\\/\x09\x03\x0a\x04\x0b\x05"
   };
   #endif

   tmp = layer_dup("tmp", layer);
   for (y = 0; y < layer->height; y++) {
      for (x = 0; x < layer->width; x++) { 
         Cell c = tmp->cells[x][y];

         #if ENABLE_WIDECHAR == 0
         if (flipchars) c.ch = tbl_lookup(flip_table, c.ch);
         #endif

         layer->cells[x][layer->height - y - 1] = c;
      }
   }

   layer_destroy(tmp);
}

void layer_save(Layer *lyr, AeFile *f) {
   int x, y;
   #if ENABLE_WIDECHAR
   char *buf = zalloc(lyr->width * 8 + 1);
   #else
   char *buf = zalloc(lyr->width * 4 + 1);
   #endif

   aeff_write_header(f, "Layer");
   aeff_write_string(f, "name", lyr->name ? lyr->name : "unnamed");
   aeff_write_int(f, "width", lyr->width);
   aeff_write_int(f, "height", lyr->height);
   aeff_write_bool(f, "visible", lyr->visible);
   aeff_write_bool(f, "transparent", lyr->transp);
   
   for (y = 0; y < lyr->height; y++) {
      for (x = 0; x < lyr->width; x++) {
         #if ENABLE_WIDECHAR
         chr2hex(lyr->cells[x][y].ch[0], &buf[x * 8]);
         chr2hex(lyr->cells[x][y].ch[1], &buf[x * 8 + 2]);
         chr2hex(lyr->cells[x][y].ch[2], &buf[x * 8 + 4]);
         chr2hex(lyr->cells[x][y].attr,  &buf[x * 8 + 6]); 
         #else

         /* fill in buf with current line (decoded into hex duplets) */
         chr2hex(lyr->cells[x][y].ch, &buf[x * 4]);
         chr2hex(lyr->cells[x][y].attr, &buf[x * 4 + 2]);
         #endif
      }

      /* save line to file */
      aeff_write_string(f, "layer-line", buf);
   }

   aeff_write_footer(f, "Layer");
   zfree(&buf);
}

Layer *layer_load(AeFile *f) {
   int x, y;
   char *buf = 0;
   Layer *lyr = NULL;
   char *name = 0;
   int width, height;

   if (!aeff_read_header(f, "Layer")) goto exception;
   if (!aeff_read_string(f, "name", &name)) goto exception;
   if (!aeff_read_int(f, "width", &width)) goto exception;
   if (!aeff_read_int(f, "height", &height)) goto exception;
   
   lyr = layer_create(name, width, height);
   zfree(&name);

   if (!aeff_read_bool(f, "visible", &lyr->visible)) goto exception;
   if (!aeff_read_bool(f, "transparent", &lyr->transp)) goto exception;

   for (y = 0; y < lyr->height; y++) {
      if (!aeff_read_string(f, "layer-line", &buf)) goto exception;

      if (strlen(buf) != lyr->width * 8) {
         aeff_set_error("layer-line line has incorrect width");
	 goto exception;
      }

      #if ENABLE_WIDECHAR
      for (x = 0; x < lyr->width; x++) {
         lyr->cells[x][y].ch[0] = hex2chr(&buf[x * 8]);
         lyr->cells[x][y].ch[1] = hex2chr(&buf[x * 8 + 2]);
         lyr->cells[x][y].ch[2] = hex2chr(&buf[x * 8 + 4]);
         lyr->cells[x][y].attr  = hex2chr(&buf[x * 8 + 6]);
      }
      #else

      /* interpret buf as width*4 hex duplets specifying char and attribute
       * for each cell in the line */
      for (x = 0; x < lyr->width; x++) {
         lyr->cells[x][y].ch   = hex2chr(&buf[x * 4]);
	 lyr->cells[x][y].attr = hex2chr(&buf[x * 4 + 2]);
      }
      #endif
   
      zfree(&buf);
   }

   aeff_read_footer(f, "Layer");

   return lyr;

exception:
   if (lyr) layer_destroy(lyr);
   if (buf) zfree(&buf);
   return NULL;
}

Layer *layer_load_OLD(FILE *f) {
   char *lyr_name;
   char signature[3];
   int width, height, x, y;
   bool v, t;
   Layer *l;
   
   signature[0] = fgetc(f);
   signature[1] = fgetc(f);
   signature[2] = 0;

   if (strcmp(signature, "L3")) return NULL; /* unknown format */
   if ( !(lyr_name = floadstr(f)) ) return NULL;
   fread(&width, sizeof(int), 1, f);
   fread(&height, sizeof(int), 1, f);
   v = fgetc(f) ? true : false; 
   t = fgetc(f) ? true : false; 

   l = layer_create(lyr_name, width, height);
   l->visible = v;
   l->transp = t;
   
   for (x = 0; x < width; x++) for (y = 0; y < height; y++) {
      #if ENABLE_WIDECHAR
      fgetws(l->cells[x][y].ch, 4, f);
      #else 
      l->cells[x][y].ch   = fgetc(f);
      #endif
      l->cells[x][y].attr = fgetc(f);
   }
   
   return l;
}

