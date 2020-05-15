#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

///Tipurile de date prezentate in JSON

struct dataTypes
{
    int intVal; ///valoare int
    double doubleVal; ///valoare double
    char* String; ///valoare string
    bool boolVal; ///valoare bool
    bool nullVal; ///valoare null (daca elementul este de tip null, nullVal=1)

    int Size;
    int* intArray; ///vector int
    double* doubleArray; ///vector double
    char** stringArray; ///vector string
    bool* boolArray; ///vector bool
    bool* nullArray; ///vector null
};

struct tree
{
    int Size; ///dimensiunea totala a arborelui
    struct treeNode** arr; ///vector de pointeri catre nodurile arborelui
};

/// nod =obiect JSON

struct treeNode
{
    char* key; ///cheia elementului JSON

    struct dataTypes* data;

    struct treeNode* kid;
    struct treeNode* bro;
};

///newNode creeaza un nod nou

struct treeNode* newNode();

///addBro adauga un nod frate

struct treeNode addBro(struct treeNode*);

///addKid adauga un nod copil

struct treeNode* addKid(struct treeNode*);

///isFileEmpty verifica daca fisierul este gol

bool isFileEmpty(FILE*);
