
#include "matrix.h"
#include "pch.h"

int main(void) {
    /* code */
    matrix *m = input_matrix(m);
    pivotdata *aa;
    m = input_augmentcolumn(m);
    // printmat(m);
    aa = rref(m, 1);
    printmat(m);
    print_pivdata(aa);
    matrix *f=NULL;
    f = nullspace(m, aa, 1);
    // matrix *e=init(f->col,f->col);
    // eye(e);
    // printf("\n");
    printmat(f);
    // printmat(e);

    free(m->arr);
    free(m);
    free(f->arr);
    free(f);
    free(aa->pivotindex);
    free(aa);
    return 0;
}
