#include <ncurses.h>

#include "widechar.h"

#define MAX_WCHAR_SIZE 4

void getch_wint(int* dest_wint) {
   dest_wint[0] = getch(); /* call blocking getch */ 
   nodelay(stdscr, TRUE); /* now cause non-blocking getch calls */ 
   
   unsigned i=1;
   dest_wint[i] = getch();
   while (dest_wint[i] != ERR && i < MAX_WCHAR_SIZE-1) { /* getch until input queue is empty */
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

int* wintcpy(int* dest, int* src) {
    unsigned i=0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
    return dest;
}

unsigned wchlength(int* wint) {
    unsigned count = 0;
    while (wint[count] != '\0') count++;
    return count;
}

