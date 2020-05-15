#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "data.h"
#inclde "tempFunctions.h"

struct dataTypes* createArray(FILE* fin,int* size)
{
    struct dataTypes* temp;
    temp=(struct dataTypes*)malloc(1*sizeof(struct dataTypes));
    assert(temp != NULL);
    char c;
    while((c = fgetc(fin)) != ']')
    {
        if(c == '"')
        {
            if(*size == 0)
            {
                temp->stringArray=(char **)malloc(1*sizeof(char*));
                temp->stringArray[*size]=(char*)malloc(1000*sizeof(char));
                temp->stringArray[*size]=createWord(fin);
                printf("%s\n",temp->stringArray[*size]);
                (*size)++;
            }
            else
            {
                temp->stringArray=(char**)realloc(temp->stringArray,((*size)+1)*sizeof(char*));
                assert(temp->stringArray != NULL);
                temp->stringArray[*size]=(char*)malloc(1000*sizeof(char));
                temp->stringArray[*size]=createWord(fin);
                printf("%s\n",temp->stringArray[*size]);
                (*size)++;
            }
        }
    }
    return temp;
};
