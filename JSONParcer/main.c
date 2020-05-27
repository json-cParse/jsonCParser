#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "data.h"
#include "conversion.h"
#include "array.h"
#include "readJSON.h"
#include "printJSON.h"


int main()
{
    struct treeNode* root = newNode();
    root->key = "root";

    char c;
    FILE* fin = fopen("test.txt" , "r");
    FILE* fout = fopen("afisare.txt" , "w");
    c = fgetc(fin);

   readJSON(root , fin);
    fseek(fin,0,SEEK_SET);
   // printf("\n%s\n\n", root->kid->kid->key);
   // printf("\n\n\nNODURI\n");
    unsigned int i = 0;
   //printTree(root, &i);
   addData(&root, fin);
   //printf("%s, %s", root->kid->kid->kid->kid->key, root->kid->kid->kid->kid->data->String);
   printParsedData(fout, root);
   /*//addData(root,fin);
   printParsedData(fout, root);
   struct dataTypes* data;
   data->intVal = 1;
    //addJSON(&root, data, "info");
    printParsedData(fout, root);*/
   fclose(fin);
   fclose(fout);
    return 0;
    return 0;
}

