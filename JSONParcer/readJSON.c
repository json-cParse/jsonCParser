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
    bool cond = false;
    struct treeNode* DAD = node;
    struct treeNode* currNode;
    while ((c = fgetc(fin)) && c != '}')
    {

        /*if(c != ' ')
            printf("**CAR:%c\n", c);*/

        char* word;

        if(c == '"')
         {
             word = createWord(fin);
             //printf("\t\t CUVANT:%s\n", word);
             //printf("%s PARINTE\n", node->key);
               /* if (cond == true && currNode->kid == NULL)
                {
                    printf("AM INTRAT\n");
                    currNode->data->String = word;

                    printf("\t ++nodul %s are STRINGUL %s\n", currNode->key, currNode->data->String);
                    cond = false;
                }*/

            }


        if ( c == ':')
        {

            if(node->kid == NULL)
            {
                addKid(&node);
                currNode = node->kid;
            }
            else
            {
                addBro(&node);
                currNode = node->bro;
            }

                currNode->key = word;
                cond = true;

            currNode->dad = DAD;
            //cond = true;
            printf(" nodul %s are ca parinte nodul %s\n\n" ,  currNode->key , currNode->dad->key);
        }


        if( c == '{')
            readJSON(currNode , fin);


    }
}
