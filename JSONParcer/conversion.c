#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define wordSize 1000

/* stringToInt() transforma un string intr-un numar intreg */
int stringToInt(char* s)
{
    int n, p = 1;
    n = strlen(s);

    int number = 0;
    for(int i = n - 1 ; i >= 0 ; i--)
    {
        number = number + (s[i] - '0') * p;
        p *= 10;
    }

    return number;
}

/* stringToDouble() transforma un string intr-un numar real */
double stringToDouble(char* s)
{
    int n, p = 1;
    double number = 0, decimal = 0;
    n = strlen(s) - 1;

    /// formam partea intreaga
    while(s[n] != '.')
    {
        decimal = decimal + (s[n] - '0') * p;
        p *= 10;
        n--;
    }
    decimal /= p;

    /// formam partea fractionara
    p = 1;
    for(int i = n - 1 ; i >= 0 ; i--)
    {
        number = number + (s[i] - '0') * p;
        p *= 10;
    }

    /// formam numarul final
    number += decimal;

    return number;
}

/* createNumber() formeaza un string cu numarul prezent in fisierul JSON
   b=0 => int; b=1 => double */
char* createNumber(char s, bool* b, FILE* fin)
{
    char c;
    char *num, *sep = " ,\t\n]";

    num = (char*)malloc(wordSize * sizeof(char));
    assert(num != NULL);

    num[0] = s;

    int i = 1;
    while(strchr(sep, (c = fgetc(fin))) == NULL)
    {
        num[i] = c;
        i++;

        if(c == '.')
            *b = 1; /// am intalnit in formarea numarului '.' => double
    }
    num[i] = '\0';

    return num;
}

/* createBoolAndNull() formeaza un bool sau un null cu valoarea prezenta in fisierul JSON */
char* createBoolAndNull(char s, FILE* fin)
{
    char c;
    char *var, *sep = " \t,\n]";

    var = (char*)malloc(wordSize * sizeof(char));
    assert(var != NULL);

    var[0] = s;

    int i = 1;
    while(strchr(sep, (c = fgetc(fin))) == NULL)
    {
        var[i] = c;
        i++;
    }

    var[i] = '\0';

    return var;
}

/* createWord() formeaza un string cu datele din fisierul JSON */
char* createWord(FILE* fin)
{
    char* temp;
    temp = (char*)malloc(wordSize * sizeof(char));
    assert(temp != NULL);

    *temp = NULL;
    char c;
    int i = 0;

    while((c = fgetc(fin)) && c != '"')
    {
        temp[i] = c;
        i++;
    }

    return temp;
}
