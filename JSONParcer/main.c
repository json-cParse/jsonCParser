#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "data.h"
#include "conversion.h"
#include "array.h"
#include "readJSON.h"
#include "tempFunctions.h"


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
   // int i = 0;
   // printInfo(root);
   //addData(root,fin);
   //printJSON(fout, root);
   struct dataTypes* data;
   data->intVal = 1;
    addJSON(&root, data, "info");
    printJSON(fout, root);
   fclose(fin);
   fclose(fout);
    return 0;
}
