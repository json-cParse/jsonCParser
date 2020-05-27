#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "array.h"

#define stringSize 30

///Afiseaza datele intr-un fisier
void printJSON (FILE* fout , struct treeNode* node)
{
    fprintf(fout , "Structura si relatiile din fisierul JSON:\n\n");
    printInfo(fout, node);

}
