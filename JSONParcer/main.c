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

    c = fgetc(fin);

   readJSON(root , fin);
    fseek(fin,0,SEEK_SET);
   // printf("\n%s\n\n", root->kid->kid->key);
   // printf("\n\n\nNODURI\n");
    int i = 0;
    printInfo(root);
   // addData(root,fin);
    return 0;
}
