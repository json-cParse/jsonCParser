#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define wordSize 1000
#define stringSize 30


#include "data.h"

char* createWord(FILE* fin)
{
    char* temp;
    temp = (char*)malloc(wordSize*sizeof(char));
    *temp = NULL;
    char c;
    int i=0;
    while ( (c=fgetc(fin)) && c!= '"')
        strcat(temp,&c);
    return temp;
}
