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

    FILE* fin = fopen("test_in.json" , "r");
    FILE* fout = fopen("parsedData.txt" , "w");
    FILE* jfout = fopen("test_out.json", "w");
    fgetc(fin);

    /// citire fisier JSON
    readJSON(root, fin); /// structuram arborele
    fseek(fin, 0, SEEK_SET); /// aducem pointerul la inceputul fisierului pentru noi prelucrari

    addData(&root, fin); /// adaugam datele

    /// adaugare element JSON nou
    //addJSON(root);

    /// printam datele parsate din fisierul JSON
    printParsedData(fout, root);

    /// salvare in format JSON
    unsigned int level = 1;
    saveJSON(jfout, root->kid, &level);

    /// eliberare memorie
    freeTree(root);
    root = NULL;

    fclose(fin);
    fclose(fout);
    fclose(jfout);
    return 0;
}

