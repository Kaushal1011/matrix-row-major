#include "matrix.h"
#include "pch.h"

// Extracts solution from augmented rref
dtype *extractsol(matrix *m, pivotdata *p) {
    dtype *ret = calloc(m->col -1, sizeof(dtype));

    for (long i = 0; i < p->num_pivot; i++) {
        long zerocolcount = 0;
        for (long k = 0; k < p->pivotindex[i]; k++) {
            if (iszerocol(m, k,0) == 0) {
                zerocolcount++;
            }
        }
        if (p->pivotindex[i] - zerocolcount < m->row) {
            ret[p->pivotindex[i]] =
                elem(m, i - zerocolcount, m->col - 1);
                // printf("\n %lf %d %lf \n",ret[p->pivotindex[i]],p->pivotindex[i],elem(m, i - zerocolcount, m->col - 1));
        }
    }
    return ret;
}

// checks if zero solution has zero rows
long checkconsitency(matrix *m, pivotdata *p) {
    long rowindex[m->row];
    for(long i=0;i<m->row;i++)
    {
        rowindex[i]=1;
    }
    // printf("\n");
    for (long i = 0; i < m->row; i++) {
        if(iszerorow(m,i,1))
        {
            rowindex[i]=0;
        }
        // printf("%d ",p->pivotindex[i]);
    }
    printf("\n");
    for (long i = 0; i < m->row; i++) {
        if (rowindex[i] != 1) {
            if (iszerorow(m, i, 0) == 1) {
                return 0;
            }
        }
    }
    return 1;
}

// prints particular solution of given system  of equations
void printXp(dtype *sol, long len) {
    printf("Xp(particular solution) of the Equation is :\n");
    for (long i = 0; i < len; i++) {
        printf("x%d %8.2lf\n", i, sol[i]);
    }
}

// prints nullspace matrix
void printXn() {
    printf("Xn(nullspace solution) of the equation is :\n");
}

// function that solves Ax=B prints no of solution(and solutions) and returns
// nullspace matrix
matrix *solve(matrix *m) {
    m = input_augmentcolumn(m);

    // dont forget to free
    matrix *rref_m = copy(m);

    pivotdata *pivotdata_m;
    // dont forget to free
    pivotdata_m = rref(rref_m, 1);

    printf("RREF form of A augment b is \n");
    printmat(rref_m);
    print_pivdata(pivotdata_m);

    // return this
    matrix *temp = copy(rref_m);
    matrix *nullspace_m = nullspace(temp, pivotdata_m, 1);

    // printf("\n\n Immediate Nullspace\n\n");
    // printmat(nullspace_m);
    // free(temp->arr);
    // free(temp);

    long rank = pivotdata_m->num_pivot;

    // dont forget to free
    dtype *solution = extractsol(rref_m, pivotdata_m);
    // Check for Number Of Solutions
    if (rank == m->row && rank == m->col - 1) {
        printf("\nAx=B has a Unique Solution \n");
        // Extract Augmented Col
        printXp(solution, m->col - 1);
    } else if (rank == m->row) {
        printf("\nAx=b has infinitely many solutions \n");
        // Extract Augmented col and Print it with Nullspace
        printXp(solution, m->col - 1);
        printXn();
        printmat(nullspace_m);

    } else if (rank == m->col - 1) {
        // Extract Augmented col and check consitency of zeros
        // if consistent
        if (checkconsitency(rref_m, pivotdata_m) == 1) {
            printf("\nAx=B has a Unique Solution\n");
            printXp(solution, m->col - 1);
        }
        // else
        else {
            printf("\nAx=B has No Solution\n");
        }

    } else {
        // Extract Augmented col and check consitency of zeros
        // Take Nullspace also
        // if consistent
        // printf("\n%d\n",checkconsitency(rref_m, pivotdata_m));
        if (checkconsitency(rref_m, pivotdata_m) == 1) {
            printf("\nAx=b has infinitely many solutions\n");
            printXp(solution, m->col - 1);
            printXn();
            printmat(nullspace_m);
        } else {
            printf("\nAx=B has No Solution\n");
        }
        // else
    }
    // free(rref_m->arr);
    // free(rref_m);
    // FREE(rref_m);
    free(pivotdata_m->pivotindex);
    free(pivotdata_m);

    free(solution);
    // free(temp->arr);
    // free(temp);
    // FREE(temp);
    return nullspace_m;
}
