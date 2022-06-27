#include <ncurses.h>

#include "widechar.h"

void getch_widechar(char* dest_wch) {
   dest_wch[0] = getch(); /* call still blocking getch */ 
   nodelay(stdscr, TRUE); /* now cause non-blocking getch calls */ 
   
   unsigned int i=1;
   dest_wch[i] = getch();
   while (dest_wch[i] != ERR) { /* getch until input queue is empty */
     i++;
     dest_wch[i] = getch();
   }
   
   dest_wch[i] = '\0';
   nodelay(stdscr, FALSE);
}
