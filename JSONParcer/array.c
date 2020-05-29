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
        else if(c == '[')
        {
            /*while((c = fgetc(fin)) != ']')
            {
                temp->sSize = 0;
                while(c != ']')
                {
                    if(c == '"')
                    {

                        printf("SIZE %u DIM %u\n\n", temp->sSize, temp->dSize);
                        if(temp->dSize == 0)
                        {
                            /// alocam memorie pentru vectorul mare
                            temp->stringArrayArr = (char***)malloc(sizeof(char**));
                            assert(temp->stringArrayArr != NULL);

                            /// alocam memorie pentru vectorul de dimensiuni
                            temp->dsSize = (unsigned int*)malloc(sizeof(unsigned int));
                            assert(temp->dsSize != NULL);

                            if(c != ' ')
                                printf("CAR DIM=0 %c\n", c);
                            printf("SIZE %u DIM %u\n", temp->sSize, temp->dSize);
                            if(temp->sSize == 0)
                            {
                                /// alocam memorie pentru vectorul mic
                                temp->stringArrayArr[temp->dSize] = (char**)malloc(sizeof(char*));
                                assert(temp->stringArrayArr[temp->dSize] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[temp->dSize][temp->sSize] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[temp->dSize][temp->sSize] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[temp->dSize][temp->sSize] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[temp->dSize][temp->sSize]);

                                (temp->sSize)++;
                            }
                            else
                            {
                                /// realocam memorie pentru vectorul mic
                                temp->stringArrayArr[temp->dSize] = (char**)realloc(temp->stringArrayArr[temp->dSize], ((temp->sSize) + 1) * sizeof(char*));
                                assert(temp->stringArrayArr[temp->dSize] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[temp->dSize][temp->sSize] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[temp->dSize][temp->sSize] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[temp->dSize][temp->sSize] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[temp->dSize][temp->sSize]);

                                (temp->sSize)++;
                            }
                            c = fgetc(fin);
                        } // acolada while mic

                        temp->dsSize[temp->dSize] = temp->sSize;
                        (temp->dSize)++;

                    }   // acolada temp->dSize == 0
                    else
                    {
                        printf("Am intrat in else!!\n");
                        /// realocam memorie pentru vectorul mare
                        temp->stringArrayArr = (char***)realloc(temp->stringArrayArr, ((temp->dSize) + 1) * sizeof(char**));
                        assert(temp->stringArrayArr != NULL);

                        /// realocam memorie pentru vectorul de dimensiuni
                        temp->dsSize = (unsigned int*)realloc(temp->dsSize, ((temp->dSize) + 1) * sizeof(unsigned int));
                        assert(temp->dsSize != NULL);

                        while(c != ']')
                        {
                            if(c != ' ')
                                printf("CAR DIM!=0 %c\n", c);
                            printf("SIZE %u DIM %u\n", temp->sSize, temp->dSize);
                            if(temp->sSize == 0)
                            {
                                /// alocam memorie pentru vectorul mic
                                temp->stringArrayArr[temp->dSize] = (char**)malloc(sizeof(char*));
                                assert(temp->stringArrayArr[temp->dSize] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[temp->dSize][temp->sSize] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[temp->dSize][temp->sSize] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[temp->dSize][temp->sSize] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[temp->dSize][temp->sSize]);

                                (temp->sSize)++;
                            }
                            else
                            {
                                /// realocam memorie pentru vectorul mic
                                temp->stringArrayArr[temp->dSize] = (char**)realloc(temp->stringArrayArr[temp->dSize], ((temp->sSize) + 1) * sizeof(char*));
                                assert(temp->stringArrayArr[temp->dSize] != NULL);

                                /// alocam memorie pentru string
                                temp->stringArrayArr[temp->dSize][temp->sSize] = (char*)malloc(1000 * sizeof(char));
                                assert(temp->stringArrayArr[temp->dSize][temp->sSize] != NULL);

                                /// apelam createWord() si atribuim stringul
                                temp->stringArrayArr[temp->dSize][temp->sSize] = createWord(fin);

                                /// TEST
                                printf("\t STRING dublu: %s\n", temp->stringArrayArr[temp->dSize][temp->sSize]);

                                (temp->sSize)++;
                            }
                            c = fgetc(fin);
                        } // acolada while mic

                        temp->dsSize[temp->dSize] = temp->sSize;
                        (temp->dSize)++;
                    }
                } // acolada if(c == '"')
            } // while vector mic
            //cond = false;*/
        } // acolada if(c == '[')
    } // acolada while((c = fgetc(fin)) != ']')
    return temp;
}
