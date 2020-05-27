#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
struct treeNode* newNode();

/* addBro() adauga un nou frate nodului dat */
struct treeNode* addBro(struct treeNode**, char*, struct treeNode*);

/* addKid() adauga un nou copil nodului dat */
struct treeNode* addKid(struct treeNode**, char*, struct treeNode*);

/* isFileEmpty() verifica daca fisierul este gol */
bool isFileEmpty(FILE*);

/* addJSON() adauga un nou element intr-un fisier JSON, pentru editare */
void addJSON (struct treeNode** , struct dataTypes* , char*);
