#ifndef _aewan_widechar_h
#define _aewan_widechar_h

/* Sets dest_wch to wide char (char[4], where last element is null) 
 * that was input.
 * Multiple getch() functions are called with nodelay to get 
 * characters from input queue. */
void getch_widechar(char* dest_wch);

#endif
