#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "data.h"
#include "conversion.h"

/* createArray() realizeaza parsarea unui vector dintr-un fisier JSON */
struct dataTypes* createArray(FILE* fin, int* type)
{
    struct dataTypes* temp ;
    temp = (struct dataTypes*)malloc(sizeof(struct dataTypes));
    assert(temp != NULL);

    char c;
    //bool cond = true;

    temp->sSize = 0;
    temp->dSize = 0;

    while((c = fgetc(fin)) != ']')
    {
        if(c == '"')
        {
            *type = 7;
            if(temp->sSize == 0)
            {
                /// alocam memorie
                temp->stringArray = (char**)malloc(sizeof(char*));
                assert(temp->stringArray != NULL);

                /// alocam memorie pentru fiecare char*
                temp->stringArray[temp->sSize] = (char*)malloc(1000 * sizeof(char));
                assert(temp->stringArray[temp->sSize] != NULL);

                /// apelam createWord() si il atribuim
                temp->stringArray[temp->sSize] = createWord(fin);

                ///TEST
               // printf("\t STRING simplu: %s\n", temp->stringArray[temp->sSize]);
                (temp->sSize)++;
            }
            else
            {
                /// realocam memorie
                temp->stringArray = (char**)realloc(temp->stringArray, ((temp->sSize) + 1) * sizeof(char*));
                assert(temp->stringArray != NULL);

                /// alocam memorie pentru fiecare char*
                temp->stringArray[temp->sSize] = (char*)malloc(1000 * sizeof(char));
                assert(temp->stringArray[temp->sSize] != NULL);

                /// apelam createWord() si il atribuim
                temp->stringArray[temp->sSize] = createWord(fin);

                ///TEST
               // printf("\t STRING simplu: %s\n", temp->stringArray[temp->sSize]);
                (temp->sSize)++;

            }
        } // acolada if(c == '"')
        else if(c >= '0' && c <= '9')
        {
            /// in intOrDouble verificam daca numarul este int or double (intOrDouble == 0 -> int / intOrDouble == 1 -> double)
            bool intOrDouble = 0;
            char* number = createNumber(c, &intOrDouble, fin); /// stocam numarul sub forma unui string
            if(intOrDouble == 0) /// avem numere de tipul int
            {
                if(temp->sSize == 0)
                {
                    /// alocam memorie
                    temp->intArray = (int*)malloc(sizeof(int));
                    assert(temp->intArray != NULL);

                    /// apelam stringToInt() si atribuim numarul
                    temp->intArray[temp->sSize] = stringToInt(number);

                    /// TEST
                    //printf("\t INT simplu: %d\n", temp->intArray[temp->sSize]);
                    (temp->sSize)++;
                }
                else
                {
                    /// realocam memorie
                    temp->intArray = (int*)realloc(temp->intArray, ((temp->sSize) + 1) * sizeof(int));
                    assert(temp->intArray != NULL);

                    /// apelam stringToInt() si atribuim numarul
                    temp->intArray[temp->sSize] = stringToInt(number);

                    /// TEST
                    //printf("\t INT simplu: %d\n", temp->intArray[temp->sSize]);
                    (temp->sSize)++;
                }
            }
            else
            {
                if(temp->sSize == 0)
                {
                    /// alocam memorie
                    temp->doubleArray = (double*)malloc(sizeof(double));
                    assert(temp->doubleArray != NULL);

                    /// apelam stringToDouble() si atribuim numarul
                    temp->doubleArray[temp->sSize] = stringToDouble(number);

                    /// TEST
                    //printf("\t DOUBLE simplu: %f\n", temp->doubleArray[temp->sSize]);
                    (temp->sSize)++;
                }
                else
                {
                    /// realocam memorie
                    temp->doubleArray = (double*)realloc(temp->doubleArray, ((temp->sSize) + 1) * sizeof(double));
                    assert(temp->doubleArray != NULL);

                    /// apelam stringToDouble() si atribuim numarul
                    temp->doubleArray[temp->sSize] = stringToDouble(number);

                    /// TEST
                    //printf("\t DOUBLE simplu: %f\n", temp->doubleArray[temp->sSize]);
                    (temp->sSize)++;
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

            if(temp->sSize == 0)
            {
                /// alocam memorie
                temp->boolArray = (bool*)malloc(sizeof(bool));
                assert(temp->boolArray != NULL);

                if(var[0] == 't')
                    temp->boolArray[temp->sSize] = true;
                else
                    temp->boolArray[temp->sSize] = false;

                /// TEST
                //printf("\t BOOL simplu: %d\n", temp->boolArray[temp->sSize]);
                (temp->sSize)++;
            }
            else
            {
                temp->boolArray = (bool*)realloc(temp->boolArray, ((temp->sSize) + 1) * sizeof(bool));
                assert(temp->boolArray != NULL);

                if(var[0] == 't')
                    temp->boolArray[temp->sSize] = true;
                else
                    temp->boolArray[temp->sSize] = false;

                /// TEST
                //printf("\t BOOL simplu: %d\n", temp->boolArray[temp->sSize]);
                (temp->sSize)++;
            }
        } // acolada if(c == 'f' || c == 't')
        else if(c == 'n')
        {
            *type = 9;
            char* var = createBoolAndNull(c, fin);

            if(temp->sSize == 0)
            {
                /// alocam memorie
                temp->nullArray = (bool*)malloc(sizeof(bool));
                assert(temp->nullArray != NULL);

                temp->nullArray[temp->sSize] = true;

                /// TEST
                //printf("\t NULL simplu: %d\n", temp->nullArray[temp->sSize]);
                (temp->sSize)++;
            }
            else
            {
                /// realocam memorie
                temp->nullArray = (bool*)realloc(temp->nullArray, ((temp->sSize) + 1) * sizeof(bool));
                assert(temp->nullArray != NULL);

                temp->nullArray[temp->sSize] = true;

                /// TEST
                //printf("\t NULL simplu: %d\n", temp->nullArray[temp->sSize]);
                (temp->sSize)++;
            }
        } // acolada if(c == 'n')

        /*else if(c == '[')
        {
            while (c = fgetc(fin) && c != ']')
            {
                printf("%c", c);
                temp->sSize = 0;
                if (c >= '0'  && c <= '9')
                {
                    bool IntOrDouble = 0;
                    char *number = createNumber(c, &IntOrDouble, fin);

                    if (IntOrDouble == 1)
                    {
                        temp->type = 11;
                        if (temp->dSize == 0)
                        {
                            temp->doubleArrayArr = (double **)malloc(sizeof(double*));
                            assert(temp->doubleArrayArr != NULL);
                            temp->dsSize = (unsigned double *) malloc(sizeof(unsigned double));
                            assert(temp->dsSize != NULL);
                            if (temp->sSize == 0)
                            {
                                temp->doubleArrayArr[temp->dSize] = (double *) malloc(sizeof(double));
                                assert(temp->doubleArrayArr[temp->dSize] != NULL);
                                temp->doubleArrayArr[temp->dSize][temp->sSize] = stringTodouble(number);
                                printf("double: %f \n", temp->doubleArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            else
                            {
                                temp->doubleArrayArr[temp->dSize] = (double *) realloc(temp->doubleArrayArr[temp->dSize], (temp->sSize + 1) * sizeof(double));
                                assert(temp->doubleArrayArr[temp->dSize] != NULL);
                                temp->doubleArrayArr[temp->dSize][temp->sSize] = stringTodouble(number);
                                printf("double: %f \n", temp->doubleArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            temp->dsSize[temp->dSize] = temp->dSize;
                            temp->dSize++;
                        }
                        else
                        {
                            temp->doubleArrayArr = (double **) realloc(temp->doubleArrayArr, (temp->dSize + 1) * sizeof(double *));
                            assert(temp->doubleArrayArr != NULL);
                            temp->dsSize = (unsigned double *) realloc(temp->dsSize, (temp->dSize+1) * sizeof(unsigned double));
                            assert(temp->dsSize != NULL);

                            if (temp->sSize == 0)
                            {
                                temp->doubleArrayArr[temp->dSize] = (double *) malloc(sizeof(double));
                                assert(temp->doubleArrayArr[temp->dSize] != NULL);
                                temp->doubleArrayArr[temp->dSize][temp->sSize] = stringTodouble(number);
                                printf("double: %f \n", temp->doubleArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            else
                            {
                                temp->doubleArrayArr[temp->dSize] = (double *) realloc(temp->doubleArrayArr[temp->dSize], (temp->sSize + 1) * sizeof(double));
                                assert(temp->doubleArrayArr[temp->dSize] != NULL);
                                temp->doubleArrayArr[temp->dSize][temp->sSize] = stringTodouble(number);
                                printf("double: %f \n", temp->doubleArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            temp->dsSize[temp->dSize] = temp->dSize;
                            temp->dSize++;
                        }
                    }//ItOrDouble == 1
                    else
                    {
                        temp->type = 10;
                        if (temp->dSize == 0)
                        {
                            temp->intArrayArr = (int **)malloc(sizeof(int*));
                            assert(temp->intArrayArr != NULL);
                            temp->dsSize = (unsigned int *) malloc(sizeof(unsigned int));
                            assert(temp->dsSize != NULL);
                            if (temp->sSize == 0)
                            {
                                temp->intArrayArr[temp->dSize] = (int *) malloc(sizeof(int));
                                assert(temp->intArrayArr[temp->dSize] != NULL);
                                temp->intArrayArr[temp->dSize][temp->sSize] = stringToInt(number);
                                printf("INT: %d \n", temp->intArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            else
                            {
                                temp->intArrayArr[temp->dSize] = (int *) realloc(temp->intArrayArr[temp->dSize], (temp->sSize + 1) * sizeof(int));
                                assert(temp->intArrayArr[temp->dSize] != NULL);
                                temp->intArrayArr[temp->dSize][temp->sSize] = stringToInt(number);
                                printf("INT: %d \n", temp->intArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            temp->dsSize[temp->dSize] = temp->dSize;
                            temp->dSize++;
                        }
                        else
                        {
                            temp->intArrayArr = (int **) realloc(temp->intArrayArr, (temp->dSize + 1) * sizeof(int *));
                            assert(temp->intArrayArr != NULL);
                            temp->dsSize = (unsigned int *) realloc(temp->dsSize, (temp->dSize+1) * sizeof(unsigned int));
                            assert(temp->dsSize != NULL);

                            if (temp->sSize == 0)
                            {
                                temp->intArrayArr[temp->dSize] = (int *) malloc(sizeof(int));
                                assert(temp->intArrayArr[temp->dSize] != NULL);
                                temp->intArrayArr[temp->dSize][temp->sSize] = stringToInt(number);
                                printf("INT: %d \n", temp->intArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            else
                            {
                                temp->intArrayArr[temp->dSize] = (int *) realloc(temp->intArrayArr[temp->dSize], (temp->sSize + 1) * sizeof(int));
                                assert(temp->intArrayArr[temp->dSize] != NULL);
                                temp->intArrayArr[temp->dSize][temp->sSize] = stringToInt(number);
                                printf("INT: %d \n", temp->intArrayArr[temp->dSize][temp->sSize]);
                                temp->sSize++;
                            }
                            temp->dsSize[temp->dSize] = temp->dSize;
                            temp->dSize++;
                        }
                    }
                }//if INT
            } //while principal
        } // acolada if(c == '[')*/

    } // acolada while((c = fgetc(fin)) != ']')
    return temp;
}
