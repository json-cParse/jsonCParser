#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "conversion.h"
#include "array.h"

#define stringSize 30

void readJSON(struct treeNode* node , FILE* fin)
{
    char c;
//    bool cond = false;
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

          // printf(" nodul %s are ca parinte nodul %s\n\n" ,  currNode->key , currNode->dad->key);
        }


        if( c == '{')
            readJSON(currNode , fin);


    }
}

void addData(struct treeNode* node, FILE* fin)
{
    struct treeNode* currNode;
    currNode = node;
    char c;
    char* word;
    bool cond = 0;
    int size=0,type=0;
    while ( (c= fgetc(fin)) != EOF)
       {
            //printf("%c",c);
            if ( c == ':')
                cond = 1 ;
            if ( c == '{')
             {
                 node->data = (struct dataTypes*)malloc(sizeof(struct dataTypes));
                printf("Sunt in nodul %s: \n",node->key);
                node = node->kid;
                cond=0;
                printf("M-am mutat in nodul %s: \n", node->key);
              }
            if ( c == '"' && cond ==1)
              {
                  word = createWord(fin);
                  cond = 0;

                  node->data->String= word;
                  printf("%s: STRING ~~~~~~~~~ : %s\n",node->key, node->data->String);
                  if(node->bro != NULL)
                     node= node->bro;
              }
           /* if ( c == ',')
            {  // printf("Am intrat\n");
               // printf("KUR BRO KEY : %s" , currNode->bro->key);
          //     printf(" ~~~~~~~~ KUR kid BRO KEY : %s" , currNode->bro->kid->key);
                currNode = currNode->bro;
              //  printf(" NOD :%s ", currNode->key);

            }*/
            if ( c == 'n' && cond == 1)
            {

               node->data->nullVal = 1;
               cond = 0;
               printf("%s: nullVal: %d\n",node->key, node->data->nullVal);
               if(node->bro != NULL)
                    node= node->bro;
            }
            if ( (c == 't' || c == 'f') && cond == 1)
            {

               if ( c == 't')
                    node->data->boolVal = true;
               else node->data->boolVal = false;
               cond = 0;
               printf("%s: boolVal: %d\n",node->key, node->data->boolVal);
               if(node->bro != NULL)
                    node= node->bro;
            }
            if ( c == '[' && cond == 1)
            {
                size = 0;

                node->data = createArray(fin,&size,&type);
                cond = 0;
                printf("%s: ",node->key);
                if( type == 0)
                    for(int i=0; i< size; i++)
                       printf("%s ",node->data->stringArray[i]);
                else if(type == 1)
                    for(int i=0; i< size; i++)
                       printf("%d ",node->data->intArray[i]);
                else if(type == 2)
                    for(int i=0; i< size; i++)
                       printf("%f ",node->data->doubleArray[i]);
                else if(type == 3)
                    for(int i=0; i< size; i++)
                       printf("%d ",node->data->boolArray[i]);
                else if(type == 4)
                    for(int i=0; i< size; i++)
                       printf("%d ",node->data->nullArray[i]);
                printf("\n");
                if(node->bro != NULL)
                    node= node->bro;
            }
            if ( c == '}')
            {
                if(node->key != "root")
                    node= node->dad;
                if(node->bro != NULL)
                    node= node->bro;
                cond = 0;
            }
      }
}

