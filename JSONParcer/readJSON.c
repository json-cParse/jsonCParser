#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "conversion.h"
#include "array.h"
#include "printJSON.h"

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

    int type = 0;
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

            type = -1;
            (*node)->data = createArray(fin, &type);
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


/* readData() citeste elementul sub forma unui tip de data pentru a fi adaugat intr-un nou element JSON */
struct dataTypes* readData()
{
    struct dataTypes* tempData = (struct tempData*)malloc(sizeof(struct dataTypes));
    assert(tempData != NULL);

    printf("Mai jos este o lista cu toate tipurile de date pe care le poti adauga in fisierele JSON.\nTe rugam sa selectezi tipul pe care doresti sa il adaugi!\n");
    printf("Valori simple:\n\t0 - int; 1 - double; 2 - string; 3 - bool; 4 - null.\nVectori:\n\t5 - int; 6 - double; 7 - string; 8 - bool; 9 - null.\n\n");

    printf("Tasteaza codul tipului de date dorit: ");
    scanf("%u", &(tempData)->type);

    switch(tempData->type)
    {
        case 0:
        {
            printf("Valoarea int este: ");
            scanf("%d", &(tempData)->intVal);
            break;
        }
        case 1:
        {
            printf("Valoarea double este: ");
            scanf("%f", &(tempData)->doubleVal);
            break;
        }
        case 2:
        {
            printf("Stringul este: ");
            fflush(stdin);

            (tempData)->String = (char*)malloc(wordSize * sizeof(char));
            assert((tempData)->String);

            fgets((tempData)->String, wordSize, stdin);
            tempData->String[strlen(tempData->String) - 1] = NULL;
            break;
        }
        case 3:
        {
            printf("Valoarea bool(tasteaza 0/1) este: ");
            scanf("%d", &(tempData)->boolVal);
            break;
        }
        case 4:
        {
            printf("Valoarea null este a fost adaugata!");
            (tempData)->nullVal = 1;
            break;
        }
        case 5:
        {
            printf("Numarul de elemente este: ");
            scanf("%u", &(tempData)->sSize);

            (tempData)->intArray = (int*)malloc((tempData)->sSize * sizeof(int));
            printf("\nCiteste cele %u elemente: ", (tempData)->sSize);
            for(unsigned int i = 0 ; i < (tempData)->sSize ; i++)
                scanf("%d", &(tempData)->intArray[i]);
            break;
        }
        case 6:
        {
            printf("Numarul de elemente este: ");
            scanf("%u", &(tempData)->sSize);

            (tempData)->doubleArray = (double*)malloc((tempData)->sSize * sizeof(double));
            printf("\nCiteste cele %u elemente: ", (tempData)->sSize);
            for(unsigned int i = 0 ; i < (tempData)->sSize ; i++)
                scanf("%f", &(tempData)->doubleArray[i]);
            break;
        }
        case 7:
        {
            printf("Numarul de elemente este: ");
            scanf("%u", &(tempData)->sSize);

            (tempData)->stringArray = (char**)malloc((tempData)->sSize * sizeof(char*));
            printf("\nCiteste cele %u elemente (!cu Enter dupa fiecare string!):", (tempData)->sSize);
            for(unsigned int i = 0 ; i < (tempData)->sSize ; i++)
            {
                (tempData)->stringArray[i] = (char*)malloc(wordSize * sizeof(char));
                fflush(stdin);
                fgets((tempData)->stringArray[i], wordSize, stdin);
                tempData->stringArray[i][strlen(tempData->stringArray[i]) - 1] = NULL;
            }
            break;
        }
        case 8:
        {
            printf("Numarul de elemente este: ");
            scanf("%u", &(tempData)->sSize);

            (tempData)->boolArray = (bool*)malloc((tempData)->sSize * sizeof(bool));
            printf("\nCiteste cele %u elemente (tasteaza 0/1): ", (tempData)->sSize);
            for(unsigned int i = 0 ; i < (tempData)->sSize ; i++)
                scanf("%d", &(tempData)->boolArray[i]);
            break;
        }
        case 9:
        {
            printf("Numarul de elemente este: ");
            scanf("%u", &(tempData)->sSize);

            (tempData)->nullArray = (bool*)malloc((tempData)->sSize * sizeof(bool));
            printf("\nCele %u elemente au fost adaugate!", (tempData)->sSize);
            for(unsigned int i = 0 ; i < (tempData)->sSize ; i++)
                (tempData)->nullArray[i] = 1;
            break;
        }
    }

    return tempData;
}

/* getNode() returneaza nodul cu un un index dat */
void getNode(struct treeNode* node, struct dataTypes* data, char* key, unsigned int index, unsigned int* currIndex, bool* cond)
{
    if(node != NULL)
    {
        if(index == *currIndex && node->kid != NULL && *cond == 0)
        {
            *cond = 1;
            addBro(&(node->kid), key, node);
            node = node->kid;
            while(node->bro)
                node = node->bro;
            node->data = data;
            return;
        }
        if(node->kid != NULL)
            (*currIndex)++;

        getNode(node->kid, data, key, index, currIndex, cond);
        getNode(node->bro, data, key, index, currIndex, cond);
    }
}

/* addJSON() adauga un nou element intr-un fisier JSON, pentru editare */
void addJSON (struct treeNode* root)
{
    unsigned int index = 0;
    bool cond = 0;

    printTree(root, &index);

    unsigned int cod;
    printf("\nTasteaza codul: ");
    scanf("%u", &cod);

    index = 0;



    printf("\nTe rugam sa introduci cheia elementului JSON: ");
    char* tempKey = (char*)malloc(wordSize * sizeof(char));
    fflush(stdin);
    fgets(tempKey, wordSize, stdin);
    tempKey[strlen(tempKey) - 1] = NULL;

    struct dataTypes* data = readData();
    getNode(root, data, tempKey, cod, &index, &cond);
}
