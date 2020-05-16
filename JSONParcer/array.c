#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "data.h"
#include "tempFunctions.h"
#include "conversion.h"

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
        else if ( c >= '0' && c <= '9')
        {
            bool IntOrDouble=0;
            char* number = createNumber(c , &IntOrDouble , fin);
            printf("%s *****\n" , number);
            printf("%d bool\n" , IntOrDouble);
            if ( IntOrDouble == 0)
            {
                if ( *size == 0)
                {
                    temp->intArray = (int *) malloc(sizeof(int));
                    assert(temp->intArray != NULL);
                    temp->intArray[ *size ]= stringToInt(number);
                    printf("%d int\n",temp->intArray[*size]);
                    ( * size) ++;
                }
                else
                {
                    temp->intArray = (int *) realloc(temp->intArray , ((*size)+1) * sizeof (int));
                    assert(temp->intArray != NULL);
                    temp->intArray[ *size ]= stringToInt(number);
                    printf("%d int\n",temp->intArray[*size]);
                    ( * size) ++;
                }
            }
            else
            {
                if ( *size == 0)
                {
                    temp->doubleArray = (double *) malloc(sizeof(double));
                    assert(temp->doubleArray != NULL);
                    temp->doubleArray[ *size ]= stringToDouble(number);
                    printf("%f\n",temp->doubleArray[*size]);
                    ( * size) ++;
                }
                else
                {
                    temp->doubleArray = (double *) realloc(temp->doubleArray , ((*size)+1) * sizeof (double));
                    assert(temp->doubleArray != NULL);
                    temp->doubleArray[ *size ]= stringToDouble(number);
                    printf("%f\n",temp->doubleArray[*size]);
                    ( * size) ++;
                }
            }
        }

    }
    return temp;
};
