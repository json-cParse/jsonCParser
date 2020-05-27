#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "data.h"
#include "conversion.h"
#include "array.h"
#include "readJSON.h"
#include "printJSON.h"

void printOptions()
{
    printf("OPTIUNI:\n");
    printf("\t 1) Citire fisier JSON si parsarea lui intr-un fisier .txt;\n");
    printf("\t 2) Adauagare date intr-u fisier JSON;\n");
    printf("\t 3) Salavare in format JSON;\n");
}

void app(struct treeNode* root)
{
    unsigned int opt;
    printf("SELECTEAZA OPTIUNEA: ");
    scanf("%u", &opt);

    if(opt == 1)
    {
        char *inputFile, *outputFile;
        inputFile = (char*)malloc(30 * sizeof(char));
        outputFile = (char*)malloc(30 * sizeof(char));

        printf("TASTEAZA NUMELE FISIERULUI JSON: ");
        scanf("%s", inputFile);
        printf("TASTEAZA NUMELE FISIERULUI TXT: ");
        scanf("%s", outputFile);

        FILE* fin = fopen(inputFile, "r");
        assert(fin != NULL);

        FILE* fout = fopen(outputFile, "w");
        assert(fout != NULL);

        readJSON(root, fin);
        //addData(&root, fin);
        //printParsedData(fout, root);

        fclose(fin);
        fclose(fout);

    }
    else if(opt == 2)
    {
        ///
    }
    else
    {
        ///
    }


}

void initApp()
{
    struct treeNode* root = newNode();
    root->key = "root";
    printf(" ****** JSON -> C Parser ****** \n\n");
    printf("Te rugam sa tastezi optiunea dorita si urmeaza pasii afisati pe ecran:\n");
    printOptions();

    app(root);

}
