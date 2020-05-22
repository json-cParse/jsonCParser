#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


///Tipurile de date prezente in JSON

struct dataTypes
{
    int intVal; /// valoare int
    double doubleVal; ///valoare double
    char* String; ///valoare string
    bool boolVal; ///valoare bool
    bool nullVal; ///valoare null ( daca elementul este de tip null, nullVal=1)

    unsigned int sSize; /// size pentru vectori
    int* intArray; ///vector int
    double* doubleArray; ///vector de double
    char** stringArray; ///vector string
    bool* boolArray; ///vector bool
    bool* nullArray; ///vector null

    int** intArrayArr; ///vector de vectori int
    double** doubleArrayArr; ///vector de vectori de double
    char*** stringArrayArr; ///vector de vectori string
    bool** boolArrayArr; ///vector de vectori bool
    bool** nullArrayArr; ///vector de vectori null

    unsigned int dSize; /// size pentru numarul de vectori
    unsigned int* dsSize; /// size pentru fiecare vector din vectorul mare

};

struct treeNode
{
    char* key; ///cheia elementului JSON

    struct dataTypes* data;

    struct treeNode* kid;
    struct treeNode* bro;
    struct treeNode* dad;
};

struct tree
{
    int Size; ///dimensiunea totala a arborelui
    struct treeNode** arr; ///vector de pointeri catre nodurile arborelui
};

///newNode creeaza un nod nou

struct treeNode* newNode()
{
    struct treeNode* temp=(struct treeNode*)malloc(sizeof(struct treeNode));
    assert(temp != NULL);

    temp->kid = NULL;
    temp->bro = NULL;
    temp->dad = NULL;

    return temp;
}

///addBro adauga un nod frate

void addBro(struct treeNode** node, char* word, struct treeNode* DAD)
{
    if (*node == NULL)
        return;

    while ((*node)->bro)
        *node = (*node)->bro;

    (*node)->bro = newNode();
    (*node)->bro->key = word;
    (*node)->bro->dad = DAD;

    //return node->bro;
}

///addKid adauga un nod copil

void addKid(struct treeNode** node, char* word, struct treeNode* DAD)
{
    if (*node ==NULL)
        return;

   /* if ((*node)->kid != NULL )
        addBro((*node)->kid);*/

    (*node)->kid=newNode();
    (*node)->kid->key = word;
    (*node)->kid->dad = DAD;
    //return node->kid;
}


void printTree(struct treeNode *node)
{
    if(node != NULL)
    {
        printf("%s\n", node->key);
        printTree(node->kid);
        printTree(node->bro);
    }
}

void printInfo(struct treeNode *node)
{
    if(node != NULL)
    {
        printf("%s : \n",node->key);
        if (node->dad != NULL)
            printf("\t dad: %s \n", node->dad->key);
        if (node->kid != NULL)
            printf("\t kid: %s \n", node->kid->key);
        if (node->bro != NULL)
            printf("\t BRUH: %s \n", node->bro->key);
        printInfo(node->kid);
        printInfo(node->bro);
    }
}
///isFileEmpty verifica daca fisierul este gol

bool isFileEmpty(FILE* fin)
{
    if (feof(fin))
        return true;
    return false;
}

/// freeTree elibereaza memoria
/*void freeTree(struct treeNode* node)
{
    if(node == NULL)
        return;
    freeTree(node->kid);
    freeTree(node->bro);
    node->dad=NULL;
    //if(node->data->stringArray != NULL)
}*/

