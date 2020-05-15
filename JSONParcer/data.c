#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


///Tipurile de date prezente in JSON

struct dataTypes
{
    int intVal; /// valoare int
    double doubleVal; ///valoare double
    char* string; ///valoare string
    bool boolVal; ///valoare bool
    bool nullVal; ///valoare null ( daca elementul este de tip null, nullVal=1)

    int Size;
    int* intArray; ///vector int
    double* doubleArray; ///vector de double
    char** stringArray; ///vector string
    bool* boolArray; ///vector bool
    bool* nullArray; ///vector null

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

    return temp;
}

///addBro adauga un nod frate

struct treeNode* addBro(struct treeNode* node)
{
 if (node == NULL)
        return NULL;

 while (node->bro)
    node = node->bro;

 node->bro = newNode();

 return node->bro;
}

///addKid adauga un nod copil

struct treeNode* addKid(struct treeNode* node)
{
 if (node ==NULL)
        return NULL;

 if (node->kid != NULL )
    return addBro(node->kid);

 node->kid=newNode();
 return node->kid;
}


///isFileEmpty verifica daca fisierul este gol

bool isFileEmpty(FILE* fin)
{
     if (feof(fin)) return true;
     return false;
}
