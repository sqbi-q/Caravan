#ifndef _aewan_widechar_h
#define _aewan_widechar_h

#define ENABLE_WIDECHAR 1

/* Sets dest_wint (int[4]) to wide character that was input.
 * Multiple getch() functions (each returning int value) are called 
 * with nodelay to get characters from input queue. */
void getch_wint(int* dest_wint);

/* Converts src_wint (int[4]) to char[5] representation  
 * and assigns it to dest_wch (char[5], null-terminated).
 * char[5] representation helps with writing wide char using printw() 
 * with %s format. */
void winttwch(char* dest_wch, const int* src_wint);

/* Copies characters from src (wint) to dest (wint). 
 * Return pointer to dest. */
int* wintcpy(int* dest, const int* src);

#endif
