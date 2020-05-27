#include <stdio.h>
#include <stdlib.h>

#include "data.h"


/* printTree() afiseaza nodurile, alaturi de indexul acestuia (numarul de ordine) */
void printTree(struct treeNode* node, unsigned int* index)
{
    if(node != NULL)
    {
        printf("%d, %s\n", *index, node->key);
        (*index)++;

        printTree(node->kid, index);
        printTree(node->bro, index);
    }
}

/* printParsedData() afiseaza intr-un fisier fisierul JSON parsat */
void printParsedData(FILE* fout , struct treeNode* node)
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
            fprintf(fout, "\t Continut -> ");
            ///cazuri elemente simple
            if (node->data->type == 0)
                fprintf(fout, "Elementul contine un INT: %d\n", node->data->intVal);
            else if (node->data->type == 1)
                fprintf(fout, "Elementul contine un DOUBLE: %.2f\n", node->data->doubleVal);
            else if (node->data->type == 2)
                fprintf(fout, "Elementul contine un STRING: %s\n", node->data->String);
            else if (node->data->type == 3)
            {
                if(node->data->boolVal == 1)
                    fprintf(fout, "Elementul contine un BOOL: true\n");
                else
                    fprintf(fout, "Elementul contine un BOOL: null\n");
            }
            else if (node->data->type == 4)
                fprintf(fout, "Elementul contine un NULL: null\n");

            ///cazuri vectori simpli
            else if (node->data->type == 5)
            {
                fprintf(fout, "Elementul contine un VECTOR DE INT :");

                for(int i = 0; i < node->data->sSize ; i++)
                    fprintf(fout, "%d, ", node->data->intArray[i]);
            }
            else if (node->data->type == 6)
            {
                fprintf(fout, "Elementul contine un VECTOR DE DOUBLE:");

                for(int i = 0; i < node->data->sSize ; i++)
                    fprintf(fout, "%.2f, ", node->data->doubleArray[i]);
            }
            else if (node->data->type == 7)
            {
                fprintf(fout, "Elementul contine un VECTOR DE STRING:");

                for(int i = 0; i < node->data->sSize ; i++)
                    fprintf(fout, "\"%s\"; ", node->data->stringArray[i]);
            }
            else if (node->data->type == 8)
            {
                fprintf(fout, "Elementul contine un VECTOR DE BOOL: ");

                for(int i = 0; i < node->data->sSize ; i++)
                    if(node->data->boolArray[i] == 1)
                        fprintf(fout, "true, ");
                    else
                        fprintf(fout, "false, ");
            }
            else if (node->data->type == 9)
            {
                fprintf(fout, "Elementul contine un VECTOR DE NULL: ");

                for(int i = 0; i < node->data->sSize ; i++)
                    fprintf(fout, "null, ");
            }
        }

        fprintf(fout, "\n");
        printParsedData(fout, node->kid);
        printParsedData(fout, node->bro);
    }
}
