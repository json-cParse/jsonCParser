#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "data.h"
#include "array.h"

#define stringSize 30

void printTree(struct treeNode *node)
{
    if(node != NULL)
    {
        printf("%s\n", node->key);
        printTree(node->kid);
        printTree(node->bro);
    }
}

void printInfo(FILE* fout , struct treeNode *node)
{
    if(node != NULL)
    {
        fprintf(fout , "Obiectul %s are: \n" , node->key);
        if (node->dad != NULL)
            fprintf(fout , "\t Tatal: %s \n", node->dad->key);
        if (node->kid != NULL)
            fprintf(fout , "\t Copilul: %s \n", node->kid->key);
        if (node->bro != NULL)
            fprintf(fout , "\t Fratele: %s \n", node->bro->key);
        if (node->kid == NULL)
        {
            ///cazuri elemente simple
            if (node->data->type == 0)
                fprintf(fout, "Elementul contine un INT:\n");
            if (node->data->type == 1)
                fprintf(fout, "Elementul contine un DOUBLE\n");
            if (node->data->type == 2)
                fprintf(fout, "Elementul contine un BOOL\n");
            if (node->data->type == 3)
                fprintf(fout, "Elementul contine un NULL\n");
            if (node->data->String != NULL)
                fprintf(fout, "Elementul contine un STRING\n");

            ///cazuri vectori simpli
            if (node->data->intArray != NULL)
                fprintf(fout, "Elementul contine un VECTOR DE INT\n");
            if (node->data->doubleArray != NULL)
                fprintf(fout, "Elementul contine un VECTOR DE DOUBLE\n");
            if (node->data->stringArray != NULL)
                fprintf(fout, "Elementul contine un VECTOR DE STRING\n");
            if (node->data->boolArray != NULL)
                fprintf(fout, "Elementul contine un VECTOR DE BOOL\n");
            if (node->data->nullArray != NULL)
                fprintf(fout, "Elementul contine un VECTOR DE NULL\n");
        }
        fprintf(fout, "\n");
        printInfo(fout, node->kid);
        printInfo(fout, node->bro);
    }
}

///Afiseaza datele intr-un fisier
void printJSON (FILE* fout , struct treeNode* node)
{
    fprintf(fout , "Structura si relatiile din fisierul JSON:\n\n");
    printInfo(fout, node);

}
