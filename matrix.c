
#include "matrix.h"
#include "pch.h"
// Utility Func

// Swap data of two variables
void swap(dtype *a, dtype *b) {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

// Matrix Management Function

// Initialise Data inside Matrix
void constructmatrix(matrix *m, long row1, long col1) {

    m->row = row1;
    m->col = col1;
    m->arr = calloc(m->row * m->col, sizeof(dtype));
}

// Initialise Matrix in memory
matrix *init(long row, long col) {
    if (row > 0 && col > 0) {
        matrix *m = calloc(1, sizeof(matrix));
        constructmatrix(m, row, col);
        return m;
    } else {
        if (debug == 1) {
            printf("\nWarning:Tried to Init Matrix zero rows or zero cols\n\n");
            printf("\nYoure seeing this warning because debug is defined to be "
                   "1\n\n");
        }

        return NULL;
    }
}

// Function to return a copy of matrix
matrix *copy(matrix *m) {
    matrix *ret = init(m->row, m->col);
    for (long i = 0; i < m->row; i++) {
        for (long j = 0; j < m->col; j++) {
            elem(ret, i, j) = elem(m, i, j);
        }
    }
    return ret;
}

// create  Identity matrix from zero matrix
void eye(matrix *m) {
    long dim = (m->row <= m->col) ? m->row : m->col;
    for (long i = 0; i < dim; i++) {
        elem(m, i, i) = 1;
    }
}

// Intialise and return an identity matrix of size NxM
matrix *eyeinit(long row, long col) {
    matrix *ret = init(row, col);
    eye(ret);
    return ret;
}

// Row Swap Operation
void rowswap(matrix *m, long r1, long r2) {
    for (long i = 0; i < m->col; i++) {
        swap(&elem(m, r1, i), &elem(m, r2, i));
    }
}

// Input Function For Matrix
matrix *input_matrix(matrix *m) {
    /**
     * takes String input of rows
     * tokenises it converts string to dtype(double as
     * of now) saves it in Matrix->arr(row Major type)
     */
    char buf[BUFSIZ] = {0};
    char *token = NULL;
    const long NUMBASE = 10;
    long row;
    long col;
    printf("Enter row and column of matrix seperated by space: ");
    fgets(buf, BUFSIZ, stdin);
    token = buf;
    row = strtol(strtok(token, " "), NULL, NUMBASE);
    col = strtol(strtok(NULL, " "), NULL, NUMBASE);
    m = init(row, col);
    // constructmatrix(m,m->row,m->col);
    printf("constructed matrix of %ld %ld\n", m->row, m->col);
    printf("Enter values in matrix in the form \na00 a01 a02 .. a0n\n... ... "
           "... ... ...\nan0 an1 an2 .. ann\n");
    for (long i = 0; i < m->row; i++) {
        fgets(buf, BUFSIZ, stdin);
        token = buf;
        elem(m, i, 0) = (double)strtol(strtok(token, " "), NULL, NUMBASE);
        // elem(m,i,0) = 1;
        for (long j = 1; j < m->col; j++) {
            elem(m, i, j) = (double)strtol(strtok(NULL, " "), NULL, NUMBASE);
            //    elem(m,i,j)=1;
        }
    }
    return m;
}

// Function to Print Data of Matrix
void printmat(matrix *m) {
    for (long i = 0; i < m->row; i++) {
        for (long j = 0; j < m->col; j++) {
            printf("%8.2lf  ", elem(m, i, j));
        }
        printf("\n");
    }
}

// Matrix Function to drop Cols
matrix *dropcol(matrix *m, long colindex) {

    long k = 0;
    matrix *newm = init(m->row, m->col - 1);
    if (newm != NULL) {
        for (long i = 0; i < m->row; i++) {
            k = 0;
            for (long j = 0; j < m->col; j++) {

                if (j != colindex) {
                    elem(newm, i, k) = elem(m, i, j);
                    k++;
                }
            }
        }
    }
    free(m->arr);
    free(m);
    return newm;
}

// Subtract Rows r2=r2-r1 with pivot on diagonal (for U)
void subrow(matrix *m, long r1, long r2) {
    double mul = elem(m, r2, r1) / elem(m, r1, r1);
    double arr[m->col];
    for (long i = 0; i < m->col; i++) {
        arr[i] = elem(m, r1, i) * mul;
    }
    for (long i = 0; i < m->col; i++) {
        elem(m, r2, i) -= arr[i];
    }
    // return m;
}

// Matrix function to drop rows
matrix *droprow(matrix *m, long row) {
    matrix *newm = init(m->row - 1, m->col);
    if (newm != NULL) {
        long k = 0;
        long flag = 0;
        for (long i = 0; i < m->row; i++) {
            for (long j = 0; j < m->col; j++) {
                if (i != row) {
                    elem(newm, k, j) = elem(m, i, j);
                    flag = 1;
                }
            }
            if (flag == 1) {
                k++;
                flag = 0;
            }
        }
    }
    free(m->arr);
    free(m);

    return newm;
}

// Subtract Rows r2=r2-r1 with pivot not on diagonal (for R)
void subrowR(matrix *m, long r1, long r2, long piv) {
    double mul = elem(m, r2, piv) / elem(m, r1, piv);
    double arr[m->col];
    for (long i = 0; i < m->col; i++) {
        arr[i] = elem(m, r1, i) * mul;
    }
    for (long i = 0; i < m->col; i++) {
        elem(m, r2, i) -= arr[i];
    }
    // return m;
}

// Scalar Multiplication on Rows Of Matrix
void rowmulconst(matrix *m, long row, double scalar) {
    for (long i = 0; i < m->col; i++) {
        elem(m, row, i) *= scalar;
    }
}

// Check If a Row is zero return 1 if row is not 0
long iszerorow(matrix *m, long row, long aug) {
    long flag = 0;
    for (long i = 0; i < m->col - aug; i++) {
        if (elem(m, row, i) != 0) {
            flag = 1;
        }
    }
    return flag;
}

// Delete duplicate pivots in pivotindex array and reduce the value of num_pivot
void normalizepivotdata(pivotdata *p) {
    for (long i = 0; i < p->num_pivot; i++) {
        for (long j = i + 1; j < p->num_pivot; j++) {
            /* If any duplicate found */
            if (p->pivotindex[i] == p->pivotindex[j]) {
                /* Delete the current duplicate element */
                for (long k = j; k < p->num_pivot; k++) {
                    p->pivotindex[k] = p->pivotindex[k + 1];
                }

                /* Decrement size after removing duplicate element */
                p->num_pivot--;

                /* If shifting of elements occur then don't increment j */
                j--;
            }
        }
    }
}

// divide all rows by 1/pivot[row]
void scalerref(matrix *m, long aug) {
    for (long i = 0; i < m->row; i++) {
        for (long j = 0; j < m->col - aug; j++) {
            if (elem(m, i, j) != 0) {
                rowmulconst(m, i, 1 / elem(m, i, j));
                break;
            }
        }
    }
}

// Check for Zero Column returns 1 if col is not zero
long iszerocol(matrix *m, long i) {
    long zero = 0;
    for (int j = 0; j < m->row; j++) {
        if (elem(m, j, i) != 0) {
            return 1;
        }
    }
    return 0;
}

// Function to Compute RREF of a Matrix and return number of pivots and position
// of pivots
pivotdata *rref(matrix *m, long aug) {
    // initialise Pivotdata pointer in the memory
    pivotdata *ret;
    ret = calloc(1, sizeof(pivotdata));
    long dim = m->col;
    ret->pivotindex = calloc(dim * 2, sizeof(long));

    // Logic to compute U.
    long ndim = (m->row > m->col - aug) ? m->col - aug : m->row;
    long pivstart = 0;
    for (long z = 0; z < m->col; z++) {
        if (iszerocol(m, z) == 1) {
            pivstart = z;
            break;
        }
    }

    for (long i = 0; i < ndim; i++) {

        for (long z = i; z < m->col-aug; z++) {
            if (iszerocol(m, z) == 1) {
                pivstart = z;
                break;
            }else
            {
                pivstart=i;
            }

        }

        if (elem(m, i, pivstart) == 0) {
            long j = 0;
            long flag = 0;
            for (j = i + 1; j < m->row; j++) {
                if (elem(m, j, pivstart) != 0) {
                    break;
                    flag = 1;
                }
            }

            if (j == m->row && flag == 0) {
                break;
            }

            rowswap(m, j, i);

            // debug comments
            // printf("\n printed u debug %d %d \n",j,i);
            // printmat(m);
            // printf("\n\n ");
        }

        // Save Pivots
        ret->pivotindex[ret->num_pivot] = pivstart;
        ret->num_pivot++;
        // printf("\nnum_pivot %d pivindes %d\n  ",ret->num_pivot,i);

        for (long k = i + 1; k < m->row; k++) {
            // printf("\n printed u debug %d %d %d %lf\n
            // ",i,k,m->row,elem(m,k,i));
            if (elem(m, k, i) != 0) {
                subrowR(m, i, k, pivstart);
                // printf("\n printed u debug %d %d %d %lf\n
                // ",i,k,m->row,elem(m,k,i)); printmat(m); printf("\n\n");
            }
        }
    }
    // printf("\n printed u debug\n");
    // printmat(m);
    // printf("\n\n");
    // printmat(m);
    // start calculation for R

    // find first non zero row from botton and it first non zero element from
    // left
    long rstart = 0;
    for (long i = m->row - 1; i > 0; i--) {
        // printf("\n %d \n",iszerorow(m,i,aug));
        if (iszerorow(m, i, aug) == 1) {
            rstart = i;
            break;
        }
    }
    long piv = 0;
    for (long i = 0; i < m->col - aug; i++) {
        if (elem(m, rstart, i) != 0) {
            // printf("\nrstart %d piv %d\n  ",rstart,i);
            piv = i;
            ret->pivotindex[ret->num_pivot] = piv;
            ret->num_pivot++;
            break;
        }
    }
    // printf("\n %d %d\n", rstart, piv);

    long i = 0;
    long j = 0;
    long k = 0;

    // keep finding non zero pivots in non zero rows above
    for (i = rstart; i > 0; i--) {
        if (iszerorow(m, i, aug) != 1) {
            // if (i < 1)
            //     break;
            continue;
            // printf("\nsubtracted i\n");
        }

        for (k = 0; k < piv; k++) {
            if (elem(m, i, k) != 0) {
                piv = k;
                // printf("\nrref calculation debug \n%d\n",piv);
                // printf("\nrstart %d piv %d\n  ",i,piv);
                ret->pivotindex[ret->num_pivot] = piv;
                ret->num_pivot++;
                break;
            }
        }

        for (j = i - 1; j >= 0; j--) {
            // printf("\ninside rref %d %d  elem\n",i,piv);
            if (elem(m, j, piv) != 0) {
                subrowR(m, i, j, piv);
            }
            // printf("\ninside rref %d %d elem\n",i,piv);
            // printmat(m);
            // printf("\n\n");
        }
    }

    normalizepivotdata(ret);
    scalerref(m, aug);

    return ret;
}

// Matrix function to create an augmented matrix
matrix *augmented_matrix(matrix *m, const dtype *a) {

    matrix *new_m = init(m->row, m->col + 1);
    if (new_m != NULL) {

        for (long i = 0; i < new_m->row; i++) {
            for (long j = 0; j < new_m->col; j++) {
                elem(new_m, i, j) = elem(m, i, j);
            }
        }
        for (long i = 0; i < new_m->row; i++) {
            elem(new_m, i, new_m->col - 1) = a[i];
        }
    }
    free(m->arr);
    free(m);
    return new_m;
}

// Matrix utilty function to take input into augmented matrix
matrix *input_augmentcolumn(matrix *m) {
    matrix *ret;
    dtype *col = calloc(m->row, sizeof(dtype));
    printf("enter b in column form like\nb0\nb1\n.\nbn\n");
    for (long i = 0; i < m->row; i++) {
        scanf("%lf", &col[i]);
    }
    ret = augmented_matrix(m, col);
    free(col);
    return ret;
}

// Matrix Function to copy rows from one matrix into other matrix
void mat_rowcopy(matrix *m, long rm, matrix *n, long rn) {
    if (m->col != n->col) {
        return;
    }
    for (long i = 0; i < m->col; i++) {
        elem(m, rm, i) = elem(n, rn, i);
    }
}
