#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define wordSize 1000

/* dataTypes - structura ce reprezinta tipurile de date prezente in fisierele JSON */
struct dataTypes
{
    int intVal; /// valoare int (type = 0)
    double doubleVal; ///valoare double (type = 1)
    char* String; ///valoare string (type = 2)
    bool boolVal; ///valoare bool (type = 3)
    bool nullVal; ///valoare null ( daca elementul este de tip null, nullVal=1) (type = 4)

    unsigned int sSize; /// size pentru vectori
    int* intArray; ///vector int (type = 5)
    double* doubleArray; ///vector de double (type = 6)
    char** stringArray; ///vector string (type = 7)
    bool* boolArray; ///vector bool (type = 8)
    bool* nullArray; ///vector null (type = 9)

    int** intArrayArr; ///vector de vectori int (type = 10)
    double** doubleArrayArr; ///vector de vectori de double (type = 11)
    char*** stringArrayArr; ///vector de vectori string (type = 12)
    bool** boolArrayArr; ///vector de vectori bool (type = 13)
    bool** nullArrayArr; ///vector de vectori null (type = 14)

    unsigned int dSize; /// size pentru numarul de vectori
    unsigned int* dsSize; /// size pentru fiecare vector din vectorul mare

    int type; /// determina tipul de date al elementului JSON curent

};

/* treeNode - structura ce reprezinta un element/obiect JSON */
struct treeNode
{
    char* key; ///cheia elementului JSON

    struct dataTypes* data;

    struct treeNode* kid;
    struct treeNode* bro;
    struct treeNode* dad;
};

/* newNode() initializeaza un nou nod */
struct treeNode* newNode()
{
    struct treeNode* temp = (struct treeNode*)malloc(sizeof(struct treeNode));
    assert(temp != NULL);

    temp->kid = NULL;
    temp->bro = NULL;
    temp->dad = NULL;

    return temp;
}

/* addBro() adauga un nou frate nodului dat */
void addBro(struct treeNode** node, char* word, struct treeNode* DAD)
{
    if (*node == NULL)
        return;

    while ((*node)->bro)
        *node = (*node)->bro;

    (*node)->bro = newNode();
    (*node)->bro->key = word;
    (*node)->bro->dad = DAD;
}

/* addKid() adauga un nou copil nodului dat */
void addKid(struct treeNode** node, char* word, struct treeNode* DAD)
{
    if (*node ==NULL)
        return;

    (*node)->kid = newNode();
    (*node)->kid->key = word;
    (*node)->kid->dad = DAD;
}


/* isFileEmpty() verifica daca fisierul este gol */
bool isFileEmpty(FILE* fin)
{
    if (feof(fin))
        return true;
    return false;
}

struct treeNode* getNode(struct treeNode* node, unsigned int index, unsigned int* currIndex, bool* cond)
{
    if(node != NULL)
    {
        if(index == *currIndex && node->kid != NULL && *cond == 0)
        {
            *cond = 1;
            return node;
        }
        if(node->kid != NULL)
            (*currIndex)++;

        getNode(node->kid, index, currIndex, cond);
        getNode(node->bro, index, currIndex, cond);
    }
}

/* addJSON() adauga un nou element intr-un fisier JSON, pentru editare */
void addJSON (struct treeNode* root)
{
    unsigned int index = 0;
    bool cond = 0;
    struct treeNode* dad;
    struct treeNode* temp;

    printTree(root, &index);

    unsigned int cod;
    printf("\nTasteaza codul: ");
    scanf("%u", &cod);

    index = 0;

    dad = getNode(root, cod, &index, &cond);
    printf("%s\n", dad->key);

    /// NEFUNCTIONAL

    /*printf("\nTe rugam sa introduci cheia elementului JSON: ");
    char* tempKey = (char*)malloc(wordSize * sizeof(char));
    fflush(stdin);
    fgets(tempKey, wordSize, stdin);


    temp = dad;
    printf("%s\n", temp->key);

    dad = dad->kid;
    printf("%s\n", dad->key);
    addBro(&dad, tempKey, temp);

    struct dataTypes* data;
    readData(&data);
    dad->data = data;*/
}


void freeData(struct dataTypes* data)
{
    if(data->String != NULL)
        free(data->String);

    if(data->sSize != 0)
    {
        if(data->intArray != NULL) free(data->intArray);
        if(data->doubleArray != NULL) free(data->doubleArray);

        if(data->stringArray != NULL)
        {
            for(unsigned int i = 0 ; i < data->sSize ; i++)
                free(data->stringArray[i]);
            free(data->stringArray);
        }

        if(data->boolArray != NULL) free(data->boolArray);
        if(data->nullArray != NULL) free(data->nullArray);
    }
    if(data->dSize != 0)
    {
        if(data->intArrayArr != NULL)
        {
            for(unsigned int i = 0 ; i < data->dSize ; i++)
                free(data->intArrayArr[i]);
            free(data->intArrayArr);
        }
        if(data->doubleArrayArr != NULL)
        {
            for(unsigned int i = 0 ; i < data->dSize ; i++)
                free(data->doubleArrayArr[i]);
            free(data->doubleArrayArr);
        }
        if(data->stringArrayArr != NULL)
        {
            for(unsigned int i = 0 ; i < data->dSize ; i++)
            {
                for(unsigned int j = 0 ; j < data->dsSize[i] ; j++)
                    free(data->stringArrayArr[i][j]);
                free(data->stringArrayArr[i]);
            }
            free(data->stringArrayArr);
        }
        if(data->boolArrayArr != NULL)
        {
            for(unsigned int i = 0 ; i < data->dSize ; i++)
                free(data->boolArrayArr[i]);
            free(data->boolArrayArr);
        }
        if(data->nullArrayArr != NULL)
        {
            for(unsigned int i = 0 ; i < data->dSize ; i++)
                free(data->nullArrayArr[i]);
            free(data->nullArrayArr);
        }

        free(data->dsSize);
    }
}

/* freeTree() elibereaza memoria ocupata de catre arbore */
void freeTree(struct treeNode* node)
{
    if(node == NULL) return;
    freeTree(node->kid);
    freeTree(node->bro);

    if(node->kid == NULL)
    {
        freeData(node->data);
        free(node->data);
    }

    free(node);
}
