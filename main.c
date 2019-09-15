
#include "matrix.h"
#include "pch.h"

int main(void) {


    matrix *m ;
    m=input_matrix(m);
    matrix *a=solve(m);

    printf("\n\n\nNULLSPACE OF MATRIX IS(prints 0.00 if Nullspace only has Zero vector)\n\n\n");
    printmat(a);
    // free(a->arr);
    // free(a);
    free(m->arr);
    free(m);
    return 0;
}
