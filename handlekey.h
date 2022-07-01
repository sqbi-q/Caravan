/*
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
Copyright (c) 2002 Bruno T. C. de Oliveira

INFORMA��ES DE LICEN�A:
Este programa � um software de livre distribui��o; voc� pode
redistribu�-lo e/ou modific�-lo sob os termos da GNU General
Public License, conforme publicado pela Free Software Foundation,
pela vers�o 2 da licen�a ou qualquer vers�o posterior.

Este programa � distribu�do na esperan�a de que ele ser� �til
aos seus usu�rios, por�m, SEM QUAISQUER GARANTIAS; sem sequer
a garantia impl�cita de COMERCIABILIDADE ou DE ADEQUA��O A
QUALQUER FINALIDADE ESPEC�FICA. Consulte a GNU General Public
License para obter mais detalhes (uma c�pia acompanha este
programa, armazenada no arquivo COPYING).
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

