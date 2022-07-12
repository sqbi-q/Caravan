#include <ncurses.h>

#include "widechar.h"

#define MAX_WCHAR_SIZE 4

void getch_wint(int* dest_wint) {
   dest_wint[0] = getch(); /* call blocking getch */ 
   nodelay(stdscr, TRUE); /* now cause non-blocking getch calls */ 
   
   unsigned ch_len = MAX_WCHAR_SIZE-1;
   /* https://www.fileformat.info/info/unicode/utf8.htm 
    * The value of each individual byte indicates its UTF-8 function, as follows:
    *    00 to 7F hex (0 to 127): first and only byte of a sequence.
    *    80 to BF hex (128 to 191): continuing byte in a multi-byte sequence.
    *    C2 to DF hex (194 to 223): first byte of a two-byte sequence.
    *    E0 to EF hex (224 to 239): first byte of a three-byte sequence.
    *    F0 to FF hex (240 to 255): first byte of a four-byte sequence. */
   if (dest_wint[0] <= 0x7F) ch_len = 1; 
   else if (dest_wint[0] <= 0xBF) ch_len = MAX_WCHAR_SIZE-1;  
   else if (dest_wint[0] <= 0xDF) ch_len = 2;
   else if (dest_wint[0] <= 0xEF) ch_len = 3;
   /* TODO Implement four-byte or/and multi-byte wide character (currently is limited to three bytes) */
   
   unsigned i=1;
   while (i < ch_len && i < MAX_WCHAR_SIZE-1) { /* getch until input queue is empty */
     dest_wint[i] = getch();
     if (dest_wint[i] == ERR) break;
     i++;
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

