#pragma once
#include "data.h"

/* readJSON() formeaza arborele structurat cu nodurile corespunzatoare */
void readJSON(struct treeNode* , FILE*);

/* addData() adauga datele in nodurile frunza */
void addData(struct treeNode**  , FILE*);

/* readData() citeste elementul sub forma unui tip de data pentru a fi adaugat intr-un nou element JSON */
void readData(struct dataTypes**);

