#include <ncurses.h>

#include "widechar.h"

void getch_wint(int* dest_wint) {
   dest_wint[0] = getch(); /* call blocking getch */ 
   nodelay(stdscr, TRUE); /* now cause non-blocking getch calls */ 
   
   unsigned i=1;
   dest_wint[i] = getch();
   while (dest_wint[i] != ERR) { /* getch until input queue is empty */
     i++;
     dest_wint[i] = getch();
   }
   
   dest_wint[i] = '\0';
   nodelay(stdscr, FALSE);
}

void winttwch(char* dest_wch, int* src_wint) {
   unsigned i=0;
   while (src_wint[i] != '\0') {
      dest_wch[i] = (char)(src_wint[i]);
      i++;
   }
   dest_wch[i] = '\0';
}

