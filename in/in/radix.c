#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *c;
    int len;
} String;

typedef struct
{
    String *s;
    int index;
} Suffix;

typedef String *Item;
#define less(A, B) (compare(A, B) < 0)
#define less_from(A, B, d) (compare_from(A, B, d) < 0)
#define exch(A, B)  \
    {               \
        Item t = A; \
        A = B;      \
        B = t;      \
    }

int compare_from(String *s, String *t, int d)
{
    int min = s->len < t->len ? s->len : t->len;
    for (int i = d; i < min; i++)
    {
        if (s->c[i] < t->c[i])
        {
            return -1;
        }
        if (s->c[i] > t->c[i])
        {
            return 1;
        }
    }
    return s->len - t->len;
}

int compare(String *s, String *t)
{
    return compare_from(s, t, 0);
}

int compareSuffix(const void *a, const void *b)
{
    Suffix *as = *(Suffix **)a;
    Suffix *bs = *(Suffix **)b;

    return compare(as->s, bs->s);
}

int main(int argc, char *argv[])
{
    int N;
    FILE *entrada = fopen(argv[1], "r");
    fscanf(entrada, " %d\n", &N);

    String *string = malloc(sizeof(String));
    string->c = malloc(sizeof(char) * (N + 1));
    string->len = N;

    char string2[100];
    while (fscanf(entrada, " %s", string2) == 1)
    {
        strcat(string->c, string2);
        strcat(string->c, " ");
    }
    // printf("%s", string->c);
    Suffix **suffix = malloc(sizeof(Suffix) * N);
    for (int i = 0; i < N; i++)
    {
        suffix[i] = malloc(sizeof(Suffix));
        suffix[i]->index = i;
    }
    // qsort(suffix, N, sizeof(Suffix), &compareSuffix);
    for (int i = 0; i < N; i++)
    {
        printf("%s\n", suffix[i]->s->c);
    }

    fclose(entrada);
    free(string->c);
    free(string);
    for (int i = 0; i < N; i++)
    {
        free(suffix[i]);
    }
    free(suffix);
    return 0;
}