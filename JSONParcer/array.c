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
    } // acolada while((c = fgetc(fin)) != ']')

    return temp;
}
