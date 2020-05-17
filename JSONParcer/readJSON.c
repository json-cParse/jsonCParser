#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "tempFunctions.h"
#include "array.h"

#define stringSize 30

void readJSON(char* inputFile)
{
    FILE* fin;
    fin = fopen(inputFile, "r");
    assert(fin != NULL);

    char c;
    bool isRoot= false;
    bool isKey;
    char* word;

    struct treeNode* tempDad = newNode();
    tempDad->key="ROOT";
    struct treeNode* curr=newNode();
    while ( (c= fgetc(fin)) !=EOF)
    {

        if (c=='{')
        {
            if (isRoot == false)
            {

                struct treeNode* root=newNode();
                isRoot = true;

                root->key = (char*)malloc(stringSize*sizeof(char));
                root->key = "root";
                isKey = false;
                root->dad = tempDad;
                curr = root;
                tempDad = curr;

                //printf("%s ----- \n ", curr->key);
            }
            else
            {

                curr->kid = addKid(curr);
                curr = curr->kid;
                if(isKey == true)
                {
                curr->key = word;
                isKey = false;
                }
                curr->dad = tempDad;
                tempDad = curr;

                //printf("%s --------- \n", curr->key);
                printf("%s are parinte pe %s\n", curr->key, curr->dad->key);
            }
        }
        if (c == '"')
        {
            word = createWord(fin);
            printf("%s \n",word);
            if(isKey == false)
                isKey = true;
        }

        if (c == '[')
        {
            unsigned int arrS=0;
            unsigned int dimS=0;
            curr->data = createArray(fin, &arrS, &dimS);
            curr->data->sSize = arrS;
            curr->data->dSize = dimS;
            printf("SIZE: %u\n\n", curr->data->sSize);
            printf("DSIZE: %u\n\n", curr->data->dSize);
        }
        if (c == ',')
        {
            curr->bro = addBro(curr);
                curr = curr->bro;
                if(isKey == true)
                {
                curr->key = word;
                isKey = false;
                }
                curr->dad = tempDad;

                //printf("%s --------- \n", curr->key);
                printf("%s are parinte pe %s\n", curr->key, curr->dad->key);

        }
        if(c == '}')
        {
           curr = curr->dad;
        }

    }
    fclose(fin);
}
