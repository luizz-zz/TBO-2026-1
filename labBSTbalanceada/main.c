#include "bst.h"
#include <time.h>

int main()
{
    int N = 1000000;
    //scanf(" %d", &N);
    srand(time(NULL));
    Bst *bst = criaBstVazia();
    for(int i = 0; i < N; i++)
    {
        int r = rand();
        bst = insereBst(r, bst);
    }
    int alturaBst = calculaAlturaBst(bst);
    bst = balanceiaBst(bst);
    int alturaBalanceada = calculaAlturaBst(bst);
    FILE *saida = fopen("sequencia_de_alturas3.txt", "a");
    fprintf(saida, "%d %d\n", alturaBst, alturaBalanceada);
    printf("%d %d\n", alturaBst, alturaBalanceada);
    liberaBst(bst);

    return 0;
}