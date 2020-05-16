#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "data.h"
#include "tempFunctions.h"
#include "conversion.h"

struct dataTypes* createArray(FILE* fin, int* size, int *dim)
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
                printf("%s ------------------\n",temp->stringArray[*size]);
                (*size)++;
            }
            else
            {
                temp->stringArray=(char**)realloc(temp->stringArray,((*size)+1)*sizeof(char*));
                assert(temp->stringArray != NULL);
                temp->stringArray[*size]=(char*)malloc(1000*sizeof(char));
                temp->stringArray[*size]=createWord(fin);
                printf("%s -----------------\n",temp->stringArray[*size]);
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
        else if ( c == 'f' || c == 't')
        {
            char* var= createBoolAndNull(c , fin);
            if ( *size == 0)
            {
                temp->boolArray = (bool *) malloc(sizeof(bool));
                assert(temp->boolArray != NULL);

                if ( var[0] == 't')
                    temp->boolArray[ *size ]= true;
                else
                     temp->boolArray[ *size ]= false;

               // printf("%d\n",temp->boolArray[*size]);
                ( * size) ++;
            }
            else
            {
                temp->boolArray = (bool *) realloc(temp->boolArray , ((*size)+1) * sizeof (bool));
                assert(temp->boolArray != NULL);

                if ( var[0] == 't')
                    temp->boolArray[ *size ]= true;
                else
                     temp->boolArray[ *size ]= false;

                printf("%d\n",temp->boolArray[*size]);
                ( * size) ++;
            }
        }
        else if ( c == 'n')
        {
            char* var = createBoolAndNull(c , fin);
            if ( *size == 0)
            {
                temp->nullArray = (bool *) malloc(sizeof(bool));
                assert(temp->nullArray != NULL);
                temp->nullArray[ *size ]= true;
                printf("%d\n",temp->nullArray[*size]);
                ( * size) ++;
            }
            else
            {
                temp->nullArray = (bool *) realloc(temp->nullArray , ((*size)+1) * sizeof (bool));
                assert(temp->nullArray != NULL);
                temp->nullArray[ *size ]= true;
                printf("%d\n",temp->nullArray[*size]);
                ( * size) ++;
            }
        }
        else if  (c == '[')
        {
            *size = 0;
            while((c = fgetc(fin)) != ']')
            {
                //printf("CAR: %c \n", c);

            if(c == '"')
        {
            if(*dim == 0)
            {
                temp->stringArrayArr = (char***)malloc(sizeof(char**));
                assert(temp->stringArrayArr != NULL);



                    if(*size == 0)
                    {
                        temp->stringArrayArr[*dim]=(char **)malloc(1*sizeof(char*));
                        assert(temp->stringArrayArr[*dim] != NULL);
                        temp->stringArrayArr[*dim][*size]=(char*)malloc(1000*sizeof(char));
                        assert(temp->stringArrayArr[*dim][*size] != NULL);
                        temp->stringArrayArr[*dim][*size]=createWord(fin);
                        printf("******%s\n",temp->stringArrayArr[*dim][*size]);
                        (*size)++;
                    }
                    else
                    {
                        temp->stringArrayArr[*dim]=(char**)realloc(temp->stringArrayArr[*dim],((*size)+1)*sizeof(char*));
                        assert(temp->stringArrayArr[*dim] != NULL);
                        temp->stringArrayArr[*dim][*size]=(char*)malloc(1000*sizeof(char));
                        temp->stringArrayArr[*dim][*size]=createWord(fin);
                        printf("******%s\n",temp->stringArrayArr[*dim][*size]);
                        (*size)++;
                    }

                (*dim)++;
            }
            else
            {
                temp->stringArrayArr = (char***)realloc(temp->stringArrayArr, ((*dim)+1) * sizeof(char**));
                assert(temp->stringArrayArr != NULL);


                    if(*size == 0)
                    {
                        temp->stringArrayArr[*dim]=(char **)malloc(1*sizeof(char*));
                        temp->stringArrayArr[*dim][*size]=(char*)malloc(1000*sizeof(char));
                        temp->stringArrayArr[*dim][*size]=createWord(fin);
                        printf("******%s\n",temp->stringArrayArr[*dim][*size]);
                        (*size)++;
                    }
                    else
                    {
                        temp->stringArrayArr[*dim]=(char**)realloc(temp->stringArrayArr[*dim],((*size)+1)*sizeof(char*));
                        assert(temp->stringArrayArr[*dim] != NULL);
                        temp->stringArrayArr[*dim][*size]=(char*)malloc(1000*sizeof(char));
                        temp->stringArrayArr[*dim][*size]=createWord(fin);
                        printf("******%s\n",temp->stringArrayArr[*dim][*size]);
                        (*size)++;
                    }

                (*dim)++;
            }

        }
    }}
    else  continue;
    //else printf("\nAlt caz");
    }
     return temp;
}
