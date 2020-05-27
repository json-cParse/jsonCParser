#pragma once
#include<stdbool.h>

/* stringToInt() transforma un string intr-un numar intreg */
int stringToInt(char*);

/* stringToDouble() transforma un string intr-un numar real */
double stringToDouble(char*);

/* createNumber() formeaza un string cu numarul prezent in fisierul JSON
   b=0 => int; b=1 => double */
char* createNumber(char, bool*, FILE*);

/* createBoolAndNull() formeaza un bool sau un null cu valoarea prezenta in fisierul JSON */
char* createBoolAndNull(char, FILE*);

/* createWord() formeaza un string cu datele din fisierul JSON */
char* createWord(FILE*);
