
#include "matrix.h"
#include "pch.h"

int main(void) {


    matrix *m ;
    m=input_matrix(m);
    solve(m);
    free(m->arr);
    free(m);
    return 0;
}
