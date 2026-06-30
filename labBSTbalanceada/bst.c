#include "bst.h"

struct bst
{
    int chave;
    Bst *esq;
    Bst *dir;
    int size;
};

static int obtemTamanho(Bst *bst)
{
    return bst!= NULL ? bst->size : 0;
}

static void atualizaTamanho(Bst *bst)
{
    bst->size = 1 + obtemTamanho(bst->esq) + obtemTamanho(bst->dir);
}

static Bst *rotate_right(Bst *n)
{
    if (n == NULL || n->esq == NULL) return n;

    Bst *t = n->esq;
    n->esq = t->dir;
    t->dir = n;
    atualizaTamanho(n);
    atualizaTamanho(t);
    return t;
}

static Bst *rotate_left(Bst *n)
{
    if (n == NULL || n->dir == NULL) return n;

    Bst *t = n->dir;
    n->dir = t->esq;
    t->esq = n;
    atualizaTamanho(n);
    atualizaTamanho(t);
    return t;
}

Bst *criaBstVazia()
{
    return NULL;
}

Bst *insereBst(int chave, Bst *bst)
{
    if (bst == NULL)
    {
        bst = malloc(sizeof(Bst));
        bst->chave = chave;
        bst->esq = NULL;
        bst->dir = NULL;
        bst->size = 1;
    }
    else if (chave < bst->chave)
    {
        bst->esq = insereBst(chave, bst->esq);
        bst = rotate_right(bst);
    }
    else if (chave > bst->chave)
    {
        bst->dir = insereBst(chave, bst->dir);
        bst = rotate_left(bst);
    }

    return bst;
}

static int max2(int a, int b)
{
    return (a > b) ? a : b;
}

int calculaAlturaBst(Bst *bst)
{
    if (bst == NULL)
        return -1;
    else
    {
        return 1 + max2(calculaAlturaBst(bst->esq), calculaAlturaBst(bst->dir));
    }
}

void rec_preorder(Bst *t, void (*visit)(Bst *))
{
    if (t != NULL)
    {
        visit(t);
        rec_preorder(t->esq, visit);
        rec_preorder(t->dir, visit);
    }
}

void rec_postorder(Bst *t, void (*visit)(Bst *))
{
    if (t != NULL)
    {
        rec_postorder(t->esq, visit);
        rec_postorder(t->dir, visit);
        visit(t);
    }
}

void rec_inorder(Bst *t, void (*visit)(Bst *))
{
    if (t != NULL)
    {
        rec_inorder(t->esq, visit);
        visit(t);
        rec_inorder(t->dir, visit);
    }
}

void liberaBst(Bst *bst)
{
    if (bst != NULL)
    {
        liberaBst(bst->esq);
        liberaBst(bst->dir);
        free(bst);
    }
}

Bst *particionaBst(Bst *bst, int k)
{
    if(bst == NULL) return NULL;

    if (obtemTamanho(bst->esq) > k)
    {
        bst->esq = particionaBst(bst->esq, k);
        bst = rotate_right(bst);
    }
    else if (obtemTamanho(bst->esq) < k)
    {
        bst->dir = particionaBst(bst->dir, k-obtemTamanho(bst->esq)-1);
        bst = rotate_left(bst);
    }
    return bst;
}

Bst *balanceiaBst(Bst *bst)
{
    if (bst->size < 3)
        return bst;
    bst = particionaBst(bst, bst->size / 2);
    bst->esq = balanceiaBst(bst->esq);
    bst->dir = balanceiaBst(bst->dir);
    return bst;
}