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

    FILE* fin = fopen("test.txt" , "r");
    FILE* fout = fopen("afisare.txt" , "w");
    FILE* jfout = fopen("test.json", "w");
    fgetc(fin);

    readJSON(root, fin); /// structuram arborele
    fseek(fin, 0, SEEK_SET); /// aducem pointerul la inceputul fisierului pentru noi prelucrari

    addData(&root, fin);
    printParsedData(fout, root);

    unsigned int level = 1;
    saveJSON(jfout, root->kid, &level);
    fclose(fin);
    fclose(fout);
    return 0;
}

