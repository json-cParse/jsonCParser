#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/* dataTypes - structura ce reprezinta tipurile de date prezente in fisierele JSON */
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

    int type; /// 0-int, 1-double, 2-bool, 3-null

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

/* addJSON() adauga un nou element intr-un fisier JSON, pentru editare */
void addJSON (struct treeNode** dad, struct dataTypes* data, char* key)
{
    if ((*dad)->kid == NULL )
    {
        (*dad)->kid = newNode();
        (*dad)->kid->key = key;
        (*dad)->kid->data = data;
        return;
    }

    *dad = (*dad)->kid;

    while ((*dad)->bro)
        *dad = (*dad)->bro;

    (*dad)->bro = newNode();
    (*dad)->bro->key = key;
    (*dad)->bro->data = data;
}
