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
    struct dataTypes* temp ;
    temp =(struct dataTypes*)malloc(sizeof(struct dataTypes));
    assert(temp != NULL);

    char c;

    while((c = fgetc(fin)) != ']')
    {
        if(c == '"')
        {
            if(*size == 0)
            {
                /// alocam memorie
                temp->stringArray = (char**)malloc(sizeof(char*));
                assert(temp->stringArray != NULL);

                /// alocam memorie pentru fiecare char*
                temp->stringArray[*size] = (char*)malloc(1000 * sizeof(char));
                assert(temp->stringArray[*size] != NULL);

                /// apelam createWord() si il atribuim
                temp->stringArray[*size] = createWord(fin);

                ///TEST
                printf("\t STRING simplu: %s\n", temp->stringArray[*size]);
                (*size)++;
            }
            else
            {
                /// realocam memorie
                temp->stringArray = (char**)realloc(temp->stringArray, ((*size) + 1) * sizeof(char*));
                assert(temp->stringArray != NULL);

                /// alocam memorie pentru fiecare char*
                temp->stringArray[*size] = (char*)malloc(1000 * sizeof(char));
                assert(temp->stringArray[*size] != NULL);

                /// apelam createWord() si il atribuim
                temp->stringArray[*size] = createWord(fin);

                ///TEST
                printf("\t STRING simplu: %s\n", temp->stringArray[*size]);
                (*size)++;

            }
        } // acolada if(c == '"')
        else if(c >= '0' && c <= '9')
        {
            /// in intOrDouble verificam daca numarul este int or double (intOrDouble == 0 -> int / intOrDouble == 1 -> double)
            bool intOrDouble = 0;
            char* number = createNumber(c, &intOrDouble, fin); /// stocam numarul sub forma unui string

            if(intOrDouble == 0) /// avem numere de tipul int
            {
                if(*size == 0)
                {
                    /// alocam memorie
                    temp->intArray = (int*)malloc(sizeof(int));
                    assert(temp->intArray != NULL);

                    /// apelam stringToInt() si atribuim numarul
                    temp->intArray[*size] = stringToInt(number);

                    /// TEST
                    printf("\t INT simplu: %d\n", temp->intArray[*size]);
                    (*size)++;
                }
                else
                {
                    /// realocam memorie
                    temp->intArray = (int*)realloc(temp->intArray, ((*size) + 1) * sizeof(int));
                    assert(temp->intArray != NULL);

                    /// apelam stringToInt() si atribuim numarul
                    temp->intArray[*size] = stringToInt(number);

                    /// TEST
                    printf("\t INT simplu: %d\n", temp->intArray[*size]);
                    (*size)++;
                }
            }
            else
            {
                if(*size == 0)
                {
                    /// alocam memorie
                    temp->doubleArray = (double*)malloc(sizeof(double));
                    assert(temp->doubleArray != NULL);

                    /// apelam stringToDouble() si atribuim numarul
                    temp->doubleArray[*size] = stringToDouble(number);

                    /// TEST
                    printf("\t DOUBLE simplu: %f\n", temp->doubleArray[*size]);
                    (*size)++;
                }
                else
                {
                    /// realocam memorie
                    temp->doubleArray = (double*)realloc(temp->doubleArray, ((*size) + 1) * sizeof(double));
                    assert(temp->doubleArray != NULL);

                    /// apelam stringToDouble() si atribuim numarul
                    temp->doubleArray[*size] = stringToDouble(number);

                    /// TEST
                    printf("\t DOUBLE simplu: %f\n", temp->doubleArray[*size]);
                    (*size)++;
                }
            }
        } // acolada if(c >= '0' && c <= '9')
        else if(c == 'f' || c == 't')
        {
            char *var = createBoolAndNull(c, fin);

            if(*size == 0)
            {
                /// alocam memorie
                temp->boolArray = (bool*)malloc(sizeof(bool));
                assert(temp->boolArray != NULL);

                if(var[0] == 't')
                    temp->boolArray[*size] = true;
                else
                    temp->boolArray[*size] = false;

                /// TEST
                printf("\t BOOL simplu: %d\n", temp->boolArray[*size]);
                (*size)++;
            }
            else
            {
                temp->boolArray = (bool*)realloc(temp->boolArray, ((*size) + 1) * sizeof(bool));
                assert(temp->boolArray != NULL);

                if(var[0] == 't')
                    temp->boolArray[*size] = true;
                else
                    temp->boolArray[*size] = false;

                /// TEST
                printf("\t BOOL simplu: %d\n", temp->boolArray[*size]);
                (*size)++;
            }
        } // acolada if(c == 'f' || c == 't')
        else if(c == 'n')
        {
            char* var = createBoolAndNull(c, fin);

            if(*size == 0)
            {
                /// alocam memorie
                temp->nullArray = (bool*)malloc(sizeof(bool));
                assert(temp->nullArray != NULL);

                temp->nullArray[*size] = true;

                /// TEST
                printf("\t NULL simplu: %d\n", temp->nullArray[*size]);
                (*size)++;
            }
            else
            {
                /// realocam memorie
                temp->nullArray = (bool*)realloc(temp->nullArray, ((*size) + 1) * sizeof(bool));
                assert(temp->nullArray != NULL);

                temp->nullArray[*size] = true;

                /// TEST
                printf("\t NULL simplu: %d\n", temp->nullArray[*size]);
                (*size)++;
            }
        } // acolada if(c == 'n')
        else if(c == '[')
        {

        } // acolada if(c == '[')
    } // acolada while((c = fgetc(fin)) != ']')

    return temp;
}
