#include <ncurses.h>

#include "widechar.h"

void getch_wint(int* dest_wint) {
    dest_wint[0] = getch(); /* call blocking getch */ 
    nodelay(stdscr, TRUE); /* now cause non-blocking getch calls */ 

    unsigned i=1;
    int ch;
    while ((ch=getch()) != -1) {
        dest_wint[i] = ch;
        i++;
    }
    nodelay(stdscr, FALSE);
}

void winttwch(char* dest_wch, const int* src_wint) {
    for (unsigned i=0; i<4; i++) {
        dest_wch[i] = (char)(src_wint[i]);
    }
    dest_wch[4] = '\0';
}

int* wintcpy(int* dest, const int* src) {
    for (unsigned i=0; i<4; i++) {
        dest[i] = src[i];
    }
    return dest;
}
