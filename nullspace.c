
#include "matrix.h"
#include "pch.h"

// Matrix function Specific for NULLSPACE calculation

// drops pivot cols in F. i.e removes I from [I,F]
matrix *dropcol_Fmaker(matrix *m, pivotdata *p) {
    matrix *newm = init(m->row, (m->col - (p->num_pivot)));

    long k = 0;

    for (long i = 0; i < m->row; i++) {
        k = 0;
        for (long j = 0; j < m->col; j++) {
            long flag = 1;
            for (long z = 0; z < p->num_pivot; z++) {
                if (j == p->pivotindex[z]) {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1) {
                elem(newm, i, k) = elem(m, i, j);
                k++;
            }
        }
    }

    // free(m->arr);
    // free(m);
    return newm;
}

// drops all zero rows present in [I ,F] matrix
matrix *drop_zerorows(matrix *m) {
    long flag = 0;
    long *arr;
    long arrindex = 0;
    long initialrows = m->row;
    arr = calloc(m->row, sizeof(long));
    for (long i = 0; i < m->row; i++) {
        flag = 0;
        for (long j = 0; j < m->col; j++) {
            if (elem(m, i, j) != 0) {
                flag = 1;
            }
        }
        if (flag == 0) {
            arr[arrindex] = i;
            arrindex++;
        }
    }
    // for(long i=0;i<arrindex;i++)
    // {
    //     printf("\n %d %d\n",arr[i]);
    // }
    for (long i = 0; i < arrindex; i++) {

        m = droprow(m, arr[i] - i);
    }
    free(arr);

    return m;
}

// generates matrix w nullspace vectors using F at free rows and I at pivot cols
matrix *nullspace(matrix *r, pivotdata *p, long aug) {
    matrix *f;
    // if we want to find nullspace of augmented matrix
    if (aug == 1) {
        r = dropcol(r, r->col - 1);
    }
    f = drop_zerorows(r);
    f = dropcol_Fmaker(f, p);
    // multiplying all of F with -1 scalar
    for (long i = 0; i < f->row; i++) {
        rowmulconst(f, i, -1.0);
    }

    // intitlise NULLSPACE  matrix
    matrix *nullmat = init(2 * f->row, f->col);
    matrix *I = eyeinit(f->row, f->col);
    long trav[nullmat->row];
    for (long i = 0; i < nullmat->row; i++) {
        trav[i] = 0;
    }

    // create NULLSPACE matrix from -F and I
    for (long i = 0; i < p->num_pivot; i++) {
        mat_rowcopy(nullmat, p->pivotindex[i], f, i);
        trav[p->pivotindex[i]] = 1;
    }
    long Irow = 0;
    for (long i = 0; i < nullmat->row; i++) {
        if (trav[i] == 0) {
            mat_rowcopy(nullmat, i, I, Irow);
            Irow++;
        }
    }

    free(f->arr);
    free(f);
    free(I->arr);
    free(I);
    return nullmat;
}

// Utility for PivData
void print_pivdata(pivotdata *aa) {
    printf("\n %ld \n", aa->num_pivot);
    for (long i = 0; i < aa->num_pivot; i++) {
        printf("%ld ", aa->pivotindex[i]);
    }
    printf("\n");
}
