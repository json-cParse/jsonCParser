#include <stdio.h>
#include <stdlib.h>

#include "data.h"


/* printTree() afiseaza nodurile, alaturi de indexul acestuia (numarul de ordine) */
void printTree(struct treeNode* node, unsigned int* index)
{
    if(node != NULL)
    {
        if(node->kid != NULL)
        {
            printf("Codul %d pentru nodul %s\n", *index, node->key);
            (*index)++;
        }
        else
            printf("\t%s\n", node->key);

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
                {
                    fprintf(fout, "%d", node->data->intArray[i]);
                    if(i != node->data->sSize - 1)
                        fprintf(fout, ", ");
                }
            }
            else if (node->data->type == 6)
            {
                fprintf(fout, "Elementul contine un VECTOR DE DOUBLE:");

                for(int i = 0; i < node->data->sSize ; i++)
                {
                    fprintf(fout, "%.2f", node->data->doubleArray[i]);
                    if(i != node->data->sSize - 1)
                        fprintf(fout, ", ");
                }
            }
            else if (node->data->type == 7)
            {
                fprintf(fout, "Elementul contine un VECTOR DE STRING:");

                for(int i = 0; i < node->data->sSize ; i++)
                {
                    fprintf(fout, "\"%s\"", node->data->stringArray[i]);
                    if(i != node->data->sSize - 1)
                        fprintf(fout, "; ");
                }
            }
            else if (node->data->type == 8)
            {
                fprintf(fout, "Elementul contine un VECTOR DE BOOL: ");

                for(int i = 0; i < node->data->sSize ; i++)
                {
                    if(node->data->boolArray[i] == 1)
                        fprintf(fout, "true");
                    else
                        fprintf(fout, "false");

                    if(i != node->data->sSize - 1)
                        fprintf(fout, ", ");
                }
            }
            else if (node->data->type == 9)
            {
                fprintf(fout, "Elementul contine un VECTOR DE NULL: ");

                for(int i = 0; i < node->data->sSize ; i++)
                {
                    fprintf(fout, "null");
                    if(i != node->data->sSize - 1)
                        fprintf(fout, ", ");
                }
            }
        }

        fprintf(fout, "\n");
        printParsedData(fout, node->kid);
        printParsedData(fout, node->bro);
    }
}

/* printTab() printeaza freq caractere '\t' */
void printTab(int freq, FILE* fout)
{
    for(int i = 0 ; i < freq ; i++)
        fprintf(fout, "\t");
}

/* printData() datele dintr-un nod */
void printData(struct dataTypes* data, unsigned int level, FILE* fout)
{
    switch(data->type)
    {
        case 0:
        {
            fprintf(fout, "%d", data->intVal);
            break;
        }
        case 1:
        {
            fprintf(fout, "%.2f", data->doubleVal);
            break;
        }
        case 2:
        {
            fprintf(fout, "\"%s\"", data->String);
            break;
        }
        case 3:
        {
            if(data->boolVal == 1)
                fprintf(fout, "true");
            else
                fprintf(fout, "false");
            break;
        }
        case 4:
        {
            fprintf(fout, "null");
            break;
        }
        case 5:
        {
            fprintf(fout, "[\n");
            for(int i = 0 ; i < data->sSize ; i++)
            {
                printTab(level + 2, fout);
                fprintf(fout, "%d", data->intArray[i]);

                if(i != data->sSize - 1) fprintf(fout, ",");
                fprintf(fout, "\n");
            }
            printTab(level, fout);
            fprintf(fout, "]");
            break;
        }
        case 6:
        {
            fprintf(fout, "[\n");
            for(int i = 0 ; i < data->sSize ; i++)
            {
                printTab(level + 2, fout);
                fprintf(fout, "%.2f", data->doubleArray[i]);

                if(i != data->sSize - 1) fprintf(fout, ",");
                fprintf(fout, "\n");
            }
            printTab(level, fout);
            fprintf(fout, "]");
            break;
        }
        case 7:
        {
            fprintf(fout, "[\n");
            for(int i = 0 ; i < data->sSize ; i++)
            {
                printTab(level + 2, fout);
                fprintf(fout, "\"%s\"", data->stringArray[i]);

                if(i != data->sSize - 1) fprintf(fout, ",");
                fprintf(fout, "\n");
            }
            printTab(level, fout);
            fprintf(fout, "]");
            break;
        }
        case 8:
        {
            fprintf(fout, "[\n");
            for(int i = 0 ; i < data->sSize ; i++)
            {
                printTab(level + 2, fout);

                if(data->boolArray[i] == 1)
                    fprintf(fout, "true");
                else
                    fprintf(fout, "false");

                if(i != data->sSize - 1) fprintf(fout, ",");
                fprintf(fout, "\n");
            }
            printTab(level, fout);
            fprintf(fout, "]");
            break;
        }
        case 9:
        {
            fprintf(fout, "[\n");
            for(int i = 0 ; i < data->sSize ; i++)
            {
                printTab(level + 2, fout);
                fprintf(fout, "null");

                if(i != data->sSize - 1) fprintf(fout, ",");
                fprintf(fout, "\n");
            }
            printTab(level, fout);
            fprintf(fout, "]");
            break;
        }
        case 10:
        {
            //fprintf, ""
            break;
        }

    }
}

/* saveJSON() salveaza un arbore construit in format JSON */
void saveJSON(FILE* fout, struct treeNode* node, unsigned int* level)
{
    if(node != NULL)
    {
        if(node->kid != NULL || node->dad->kid == node)
            fprintf(fout, "{\n");

        printTab(*level, fout);
        fprintf(fout,  "\"%s\": ", node->key);

        if(node->kid != NULL)
        {
            (*level)++;
            saveJSON(fout, node->kid, level);
        }
        else
            printData(node->data, *level, fout);

        if(node->bro != NULL)
        {
            if(node->kid == NULL)
                fprintf(fout, ",\n");
            saveJSON(fout, node->bro, level);

            if(node->kid != NULL || node->dad->kid == node)
            {
                node = node->dad;
                (*level)--;
                fprintf(fout, "\n");
                printTab(*level, fout);

                fprintf(fout, "}");
            }
            if(node->kid != NULL && node->bro != NULL)
                fprintf(fout, ",");
        }
    }
}
