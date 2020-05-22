#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

///Tipurile de date prezentate in JSON

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
    struct treeNode* dad;
};

///newNode creeaza un nod nou

struct treeNode* newNode();

///addBro adauga un nod frate

struct treeNode* addBro(struct treeNode**, char*, struct treeNode*);

///addKid adauga un nod copil

struct treeNode* addKid(struct treeNode**, char*, struct treeNode*);

///isFileEmpty verifica daca fisierul este gol

bool isFileEmpty(FILE*);

void printTree(struct treeNode *);
void printInfo(struct treeNode *);
