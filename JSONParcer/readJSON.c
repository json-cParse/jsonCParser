#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "conversion.h"
#include "array.h"

#define stringSize 30

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

            assert((*node)->data != NULL);

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

