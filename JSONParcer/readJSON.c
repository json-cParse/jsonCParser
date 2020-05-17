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
                root->dad = tempDad;
                curr = root;
                tempDad = curr;

                //printf("%s ----- \n ", curr->key);
            }
            else
            {

                curr->kid = addKid(curr);
                curr = curr->kid;
                curr->key = word;
                curr->dad = tempDad;
                tempDad = curr;
                isKey = false;
                //printf("%s --------- \n", curr->key);
                printf("%s are parinte pe %s\n", curr->key, curr->dad->key);
            }
        }
        if (c == '"')
        {
            word = createWord(fin);
            isKey = true;
            printf("%s \n",word);
        }

        if (c == '[')
        {
            unsigned int arrS=0;
            unsigned int dimS=0;
            curr->data = createArray(fin, &arrS, &dimS);
            curr->data->sSize = arrS;
            curr->data->dSize = dimS;
        }

    }
    fclose(fin);
}
