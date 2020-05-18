#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "tempFunctions.h"
#include "array.h"

#define stringSize 30

void readJSON(struct treeNode* node , FILE* fin)
{
    char c;
    while ((c = fgetc(fin)) && c != '}')
    {
        char* word;
        if ( c == '"' )
        {
            word = createWord(fin);
        }

        if ( c == ':' )
        {
            node->kid = addKid(node);
            node->kid->key = word;
            node->kid->dad = node;

            printf(" nodul %s are ca parinte nodul %s\n\n" ,  node->kid->key , node->kid->dad->key);
        }

        if( c == '{')
            readJSON(node->kid , fin);

    }
}
