#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "data.h"
#include "conversion.h"

/* createArray() realizeaza parsarea unui vector dintr-un fisier JSON */
struct dataTypes* createArray(FILE* fin, unsigned int* size, int *type)
{
    struct dataTypes* temp ;
    temp = (struct dataTypes*)malloc(sizeof(struct dataTypes));
    assert(temp != NULL);

    char c;
    bool cond = true;

    temp->sSize = 0;
    temp->dSize = 0;

    while((c = fgetc(fin)) != ']' && cond == true)
    {
        if(c == '"')
        {
            *type = 7;
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
               // printf("\t STRING simplu: %s\n", temp->stringArray[*size]);
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
               // printf("\t STRING simplu: %s\n", temp->stringArray[*size]);
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
                    //printf("\t INT simplu: %d\n", temp->intArray[*size]);
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
                    //printf("\t INT simplu: %d\n", temp->intArray[*size]);
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
                    //printf("\t DOUBLE simplu: %f\n", temp->doubleArray[*size]);
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
                    //printf("\t DOUBLE simplu: %f\n", temp->doubleArray[*size]);
                    (*size)++;
                }
            }
            if(intOrDouble == 0)
                *type = 5;
            else
                *type = 6;
        } // acolada if(c >= '0' && c <= '9')
        else if(c == 'f' || c == 't')
        {
            *type = 8;
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
                //printf("\t BOOL simplu: %d\n", temp->boolArray[*size]);
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
                //printf("\t BOOL simplu: %d\n", temp->boolArray[*size]);
                (*size)++;
            }
        } // acolada if(c == 'f' || c == 't')
        else if(c == 'n')
        {
            *type = 9;
            char* var = createBoolAndNull(c, fin);

            if(*size == 0)
            {
                /// alocam memorie
                temp->nullArray = (bool*)malloc(sizeof(bool));
                assert(temp->nullArray != NULL);

                temp->nullArray[*size] = true;

                /// TEST
                //printf("\t NULL simplu: %d\n", temp->nullArray[*size]);
                (*size)++;
            }
            else
            {
                /// realocam memorie
                temp->nullArray = (bool*)realloc(temp->nullArray, ((*size) + 1) * sizeof(bool));
                assert(temp->nullArray != NULL);

                temp->nullArray[*size] = true;

                /// TEST
                //printf("\t NULL simplu: %d\n", temp->nullArray[*size]);
                (*size)++;
            }
        } // acolada if(c == 'n')
        /*else if(c == '[')
        {
            while((c = fgetc(fin)) != ']')
            {
                if(c == '"')
                {
                    *size = 0;
                    printf("SIZE %u DIM %u\n\n", *size, *dim);
                    if(*dim == 0)
                    {
                        /// alocam memorie pentru vectorul mare
                        temp->stringArrayArr = (char***)malloc(sizeof(char**));
                        assert(temp->stringArrayArr != NULL);

                        /// alocam memorie pentru vectorul de dimensiuni
                        temp->dsSize = (unsigned int*)malloc(sizeof(unsigned int));
                        assert(temp->dsSize != NULL);

                        while((c = fgetc(fin)) != ']')
                        {
                            if(c != ' ')
                                printf("CAR DIM=0 %c\n\n", c);
                            printf("SIZE %u DIM %u\n\n", *size, *dim);
                            if(*size == 0)
                            {
                                /// alocam memorie pentru vectorul mic
                                temp->stringArrayArr[*dim] = (char**)malloc(sizeof(char*));
                                assert(temp->stringArrayArr[*dim] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[*dim][*size] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[*dim][*size] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[*dim][*size] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[*dim][*size]);

                                (*size)++;
                            }
                            else
                            {
                                /// realocam memorie pentru vectorul mic
                                temp->stringArrayArr[*dim] = (char**)realloc(temp->stringArrayArr, ((*size) + 1) * sizeof(char*));
                                assert(temp->stringArrayArr[*dim] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[*dim][*size] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[*dim][*size] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[*dim][*size] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[*dim][*size]);

                                (*size)++;
                            }
                        } // acolada while mic

                        temp->dsSize[*dim] = *size;
                        (*dim)++;

                    }   // acolada *dim == 0
                    else
                    {
                        printf("Am intrat in else!!\n");
                        /// realocam memorie pentru vectorul mare
                        temp->stringArrayArr = (char***)realloc(temp->stringArrayArr, ((*dim) + 1) * sizeof(char**));
                        assert(temp->stringArrayArr != NULL);

                        /// realocam memorie pentru vectorul de dimensiuni
                        temp->dsSize = (unsigned int*)realloc(temp->dsSize, ((*dim) + 1) * sizeof(unsigned int));
                        assert(temp->dsSize != NULL);

                        while((c = fgetc(fin)) != ']')
                        {
                            if(c != ' ')
                                printf("CAR DIM!=0 %c", c);
                            printf("SIZE %u DIM %u\n\n", *size, *dim);
                            if(*size == 0)
                            {
                                /// alocam memorie pentru vectorul mic
                                temp->stringArrayArr[*dim] = (char**)malloc(sizeof(char*));
                                assert(temp->stringArrayArr[*dim] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[*dim][*size] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[*dim][*size] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[*dim][*size] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[*dim][*size]);

                                (*size)++;
                            }
                            else
                            {
                                /// realocam memorie pentru vectorul mic
                                temp->stringArrayArr[*dim] = (char**)realloc(temp->stringArrayArr, ((*size) + 1) * sizeof(char*));
                                assert(temp->stringArrayArr[*dim] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[*dim][*size] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[*dim][*size] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[*dim][*size] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[*dim][*size]);

                                (*size)++;
                            }
                        } // acolada while mic

                        temp->dsSize[*dim] = *size;
                        (*dim)++;
                    }
                } // acolada if(c == '"')
            } // while vector mic
            cond = false;
        } // acolada if(c == '[')*/
    } // acolada while((c = fgetc(fin)) != ']')
    temp->sSize = *size;
    return temp;
}
