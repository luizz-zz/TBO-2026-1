#ifndef _BST_H
#define _BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct bst Bst;

Bst *criaBstVazia();

Bst *insereBst(int chave, Bst *bst);

int calculaAlturaBst(Bst *bst);

void rec_preorder(Bst *t, void (*visit)(Bst*));

void rec_postorder(Bst *t, void (*visit)(Bst*));

void rec_inorder(Bst *t, void (*visit)(Bst*));

void liberaBst(Bst *bst);

Bst *particionaBst(Bst *bst, int k);

Bst *balanceiaBst(Bst *bst);

#endif