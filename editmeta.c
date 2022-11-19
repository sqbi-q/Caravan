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

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ncurses.h>
#include <unistd.h>

#include "document.h"
#include "psd.h"
#include "ui.h"

void edit_metainfo(void) {
   char *editor;
   FILE *f;
   int fd, ret, size, i;
   static char tmpname[64];
   static char buf[128];
   mode_t oldumask;
   
   editor = getenv("VISUAL");
   if (!editor) editor = getenv("EDITOR");
   if (!editor) editor = "vi";

   /* create a temporary file */
   strcpy(tmpname, "/tmp/aewan-XXXXXX");
   oldumask = umask(077);  /* so that mkstemp creates a file with perms=700 */
   fd = mkstemp(tmpname);
   umask(oldumask);

   /* check for error */
   if (fd < 0) {
      sprintf(buf, "ERROR creating temp file: %s", strerror(errno));
      ui_message(buf, UIMSG_ERROR);
      return;
   }

   /* do an fdopen so we can manipulate it via FILE* structure */
   f = fdopen(fd, "w");
   
   /* write current contents of metainfo string to the file */
   if (_doc->metainfo) fputs(_doc->metainfo, f);

   /* close file */
   fclose(f);
   close(fd);  /* is this necessary? */

   /* fire up editor */
   sprintf(buf, "%s %s", editor, tmpname);
   clear();
   refresh();
   endwin();  /* temporarily stop curses */
   if ( (ret = system(buf)) ) {
      /* error code returned */
      sprintf(buf, "ERROR: editor (%s) returned error code %d.", editor, ret);
      ui_message(buf, UIMSG_ERROR);
      return;
   }

   /* restore curses */
   touchwin(stdscr); /* force full redraw */
   refresh();

   /* ok, now read back file contents into metainfo string */
   f = fopen(tmpname, "r");
   if (!f) {
      ui_message("ERROR: Failed to read back temp file.", UIMSG_ERROR);
      return;
   }

   /* calculate file size */
   fseek(f, 0, SEEK_END);
   size = ftell(f) + 2;  /* +1 b/c size is one more than last position.
                            We add another byte for the null terminator */
   fseek(f, 0, SEEK_SET);

   /* allocate appropriately */
   dstrset(&_doc->metainfo, NULL);
   _doc->metainfo = zalloc(size);

   /* read file data */
   i = fread(_doc->metainfo, 1, size, f);

   /* put the null terminator where it should be */
   _doc->metainfo[i] = 0;

   /* delete temp file */
   unlink(tmpname);
}

