#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

int main()
{
    vector_t *a = newVector(8);
    int *test;
    for (int i = 0; i < 88; i += 1)
    {
        test = malloc(sizeof(int));
        *test = i;
        vectorAdd(a, test);
    }

    for (size_t i = 0; i < vectorLength(a); i += 1)
    {
        test = vectorGet(a, i);
        printf("Index %3lu: Got %3d back\n",i, *test);
    }

    

    test = malloc(sizeof(int));
    *test = 0xDEAD;
    vectorInsertAt(&a, test, 2);


    test = malloc(sizeof(int));
    *test = 0xBEEF;
    vectorInsertAt(&a, test, 2);

    free(vectorGet(a,2));
    vectorRemoveAt(&a,2);

    for (size_t i = 0; i < vectorLength(a); i += 1)
    {
        test = vectorGet(a, i);
        printf("Index %3lu: Got %3x back\n",i, *test);
        free(test);
    }


    freeVector(&a);
    return 0;
}
