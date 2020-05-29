#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "conversion.h"
#include "array.h"

#define stringSize 30
#define wordSize 1000

/* readJSON() formeaza arborele structurat cu nodurile corespunzatoare */
void readJSON(struct treeNode* node, FILE* fin)
{
    char c;
    struct treeNode* DAD = node;
    struct treeNode* currNode;

    while ((c = fgetc(fin)) && c != '}')
    {
        char* word = NULL;

        if(c == '"')
        {
            word = createWord(fin);
            c = fgetc(fin);
        }

        if ( c == ':')
        {

            if(node->kid == NULL)
            {
                addKid(&node, word, DAD);
                currNode = node->kid;
            }
            else
            {
                node = node->kid;
                addBro(&node, word, DAD);
                currNode = node->bro;
                node = node->dad;
            }
        }

        if( c == '{')
            readJSON(currNode , fin);
    }
}

/* addData() adauga datele in nodurile frunza */
void addData(struct treeNode** node, FILE* fin)
{
    char c;
    char* word;
    bool cond = 0;

    int size=0, type=0;
    while((c= fgetc(fin)) != EOF)
    {
        if(c == ':')
            cond = 1 ;
        else if(c == '{')
        {
            (*node) = (*node)->kid;
            cond = 0;
        }
        else if(c == '"' && cond ==1)
        {
            (*node)->data = (struct dataTypes*)malloc(sizeof(struct dataTypes));
            (*node)->data->type = 2;
            word = createWord(fin);
            cond = 0;

            (*node)->data->String = word;

            if((*node)->bro != NULL)
                (*node) = (*node)->bro;
        }
        else if(c == 'n' && cond == 1)
        {
            (*node)->data = (struct dataTypes*)malloc(sizeof(struct dataTypes));
            (*node)->data->type = 4;
            (*node)->data->nullVal = 1;
            cond = 0;

            if((*node)->bro != NULL)
                (*node) = (*node)->bro;
        }
        else if((c == 't' || c == 'f') && cond == 1)
        {
            (*node)->data = (struct dataTypes*)malloc(sizeof(struct dataTypes));
            if ( c == 't')
                (*node)->data->boolVal = true;
            else
                (*node)->data->boolVal = false;
            (*node)->data->type = 3;
            cond = 0;

            if((*node)->bro != NULL)
                (*node) = (*node)->bro;
        }
        if(c == '[' && cond == 1)
        {
            (*node)->data = (struct dataTypes*)malloc(sizeof(struct dataTypes));

            size = 0;
            type = -1;
            (*node)->data = createArray(fin, &size, &type);
            (*node)->data->type = type;
            cond = 0;

            if((*node)->bro != NULL)
                (*node) = (*node)->bro;
        }
        else if((c >= '0' && c <= '9') && cond == 1)
        {
            (*node)->data = (struct dataTypes*)malloc(sizeof(struct dataTypes));
            bool b = 0;
            char* number = createNumber(c, &b, fin);

            if(b == 0)
            {
                (*node)->data->intVal = stringToInt(number);
                (*node)->data->type = 0;
            }
            else
            {
                (*node)->data->doubleVal = stringToDouble(number);
                (*node)->data->type = 1;
            }
            cond = 0;

            if((*node)->bro != NULL)
                (*node) = (*node)->bro;
        }
        else if(c == '}')
        {
            if((*node)->key != "root")
                (*node)= (*node)->dad;

            if((*node)->bro != NULL)
                (*node) = (*node)->bro;
            cond = 0;
        }
    }
}

/**
/* readData() citeste elementul sub forma unui tip de data pentru a fi adaugat intr-un nou element JSON *\/
void readData(struct dataTypes** tempData)
{
    *tempData = (struct tempData*)malloc(sizeof(struct dataTypes));
    assert(*tempData != NULL);

    printf("Mai jos este o lista cu toate tipurile de date pe care le poti adauga in fisierele JSON.\nTe rugam sa selectezi tipul pe care doresti sa il adaugi!\n");
    printf("Valori simple:\n\t0 - int; 1 - double; 2 - string; 3 - bool; 4 - null.\nVectori:\n\t5 - int; 6 - double; 7 - string; 8 - bool; 9 - null.\n\n");

    unsigned int type = -1;
    printf("Tasteaza codul tipului de date dorit: ");
    scanf("%u ", &type);

    switch(type)
    {
        case 0:
            {
                printf("Valoarea int este: ");
                fflush(stdout);
                scanf("%d", &(*tempData)->intVal);
                fflush(stdout);
                break;
            }
        case 1:
            {
                printf("Valoarea double este: ");
                fflush(stdout);
                scanf("%f", &(*tempData)->doubleVal);
                fflush(stdout);
                break;
            }
        case 2:
            {
                printf("Stringul este: ");
                fflush(stdout);

                (*tempData)->String = (char*)malloc(wordSize * sizeof(char));
                assert((*tempData)->String);

                fflush(stdout);
                fgets((*tempData)->String, wordSize, stdin);
                break;
            }
        case 3:
            {
                printf("Valoarea bool(tasteaza 0/1) este: ");
                scanf("%d", &(*tempData)->boolVal);
                break;
            }
        case 4:
            {
                printf("Valoarea null este a fost adaugata!");
                (*tempData)->nullVal = 1;
                break;
            }
    }
}*/

