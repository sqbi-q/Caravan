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


#ifndef _btco_aewan_keys_h
#define _btco_aewan_keys_h

/* If you are going to change this, please keep in mind that KEY_ALT_A thru 
 * KEY_ALT_Z must have contiguous values. */
#define KEY_ALT_A 400 
#define KEY_ALT_B 401
#define KEY_ALT_C 402
#define KEY_ALT_D 403
#define KEY_ALT_E 404
#define KEY_ALT_F 405
#define KEY_ALT_G 406
#define KEY_ALT_H 407
#define KEY_ALT_I 408
#define KEY_ALT_J 409
#define KEY_ALT_K 410
#define KEY_ALT_L 411
#define KEY_ALT_M 412
#define KEY_ALT_N 413
#define KEY_ALT_O 414
#define KEY_ALT_P 415
#define KEY_ALT_Q 416
#define KEY_ALT_R 417
#define KEY_ALT_S 418
#define KEY_ALT_T 419
#define KEY_ALT_U 420
#define KEY_ALT_V 421
#define KEY_ALT_W 422
#define KEY_ALT_X 423
#define KEY_ALT_Y 424
#define KEY_ALT_Z 425

#define KEY_CTRL_A 1
#define KEY_CTRL_B 2
#define KEY_CTRL_C 3
#define KEY_CTRL_D 4
#define KEY_CTRL_E 5
#define KEY_CTRL_F 6
#define KEY_CTRL_G 7
#define KEY_CTRL_H 8
#define KEY_CTRL_I 9
#define KEY_CTRL_J 10
#define KEY_CTRL_K 11
#define KEY_CTRL_L 12
#define KEY_CTRL_M 13
#define KEY_CTRL_N 14
#define KEY_CTRL_O 15
#define KEY_CTRL_P 16
#define KEY_CTRL_Q 17
#define KEY_CTRL_R 18
#define KEY_CTRL_S 19
#define KEY_CTRL_T 20
#define KEY_CTRL_U 21
#define KEY_CTRL_V 22
#define KEY_CTRL_W 23
#define KEY_CTRL_X 24
#define KEY_CTRL_Y 25
#define KEY_CTRL_Z 26


/* register keys in curses */
void keys_init(void); 

#endif

