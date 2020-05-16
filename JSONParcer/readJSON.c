#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "tempFunctions.h"

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
                curr = root;


                printf("%s ----- \n ", curr->key);
            }
            else
            {
                curr->kid = addKid(curr);
                curr->key = word;
                isKey = false;
                printf("%s --------- \n", curr->key);
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
            int arrS=0;
            curr->data = createArray(fin, &arrS);
            int i=0;
        }

    }
    fclose(fin);
}
