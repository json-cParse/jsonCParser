#pragma once

/* printTree() afiseaza nodurile, alaturi de indexul acestuia (numarul de ordine) */
void printTree(struct treeNode*, unsigned int*);

/* printParsedData() afiseaza intr-un fisier fisierul JSON parsat */
void printParsedData(FILE*, struct treeNode*);

