#ifndef _aewan_widechar_h
#define _aewan_widechar_h

#define ENABLE_WIDECHAR 1

/* Sets dest_wint (int[4], null-terminated) to wide character
 * that was input.
 * Multiple getch() functions (each returning int value) are called 
 * with nodelay to get characters from input queue. */
void getch_wint(int* dest_wint);

/* Converts src_wint (int[4], null-terminated) to char[4] representation  
 * and assigns it to dest_wch (char[4], null-terminated).
 * char[4] representation helps with writing wide char using printw() 
 * with %s format. */
void winttwch(char* dest_wch, const int* src_wint);

/* Copies characters from src (wint) to dest (wint). */
int* wintcpy(int* dest, const int* src);

/* Returns length of a wint (int[4], null-terminated), excluding
 * terminating null. */
unsigned wchlength(const int* wint);

#endif
