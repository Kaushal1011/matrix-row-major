
#if !defined(MATRIX_H)
#define MATRIX_H

// datatype for matrix usage
#define dtype double
// row major memory for matrix implementation
#define elem(m, i, j) ((m)->arr[((i) * (m)->col) + (j)])
#define debug 1

// Struct Matrix
typedef struct matrix {
    dtype *arr;
    long row;
    long col;
} matrix;

// Struct pivotdata to manage data about pivots in rref()
typedef struct pivotdata {
    long num_pivot;
    long *pivotindex;
} pivotdata;


void swap(dtype *a, dtype *b);
void constructmatrix(matrix *m, long row1, long col1);
matrix *init(long row, long col);
matrix *copy(matrix *m);
void eye(matrix *m);
matrix *eyeinit(long row, long col);
void rowswap(matrix *m, long r1, long r2);
matrix *input_matrix(matrix *m);
void printmat(matrix *m);
matrix *dropcol(matrix *m, long colindex);
void subrow(matrix *m, long r1, long r2);
matrix *droprow(matrix *m, long row);
void subrowR(matrix *m, long r1, long r2, long piv);
void rowmulconst(matrix *m, long row, double scalar);
long iszerorow(matrix *m, long row, long aug);
long iszerocol(matrix*m,long i,long from);
void normalizepivotdata(pivotdata *p);
void scalerref(matrix *m, long aug);
pivotdata *rref(matrix *m, long aug);
void mat_rowcopy(matrix *m, long rm, matrix *n, long rn);
matrix *augmented_matrix(matrix *m, const dtype *a);
matrix *input_augmentcolumn(matrix *m);
matrix *dropcol_Fmaker(matrix *m, pivotdata *p);
matrix *drop_zerorows(matrix *m);
matrix *nullspace(matrix *r, pivotdata *p, long aug);
void print_pivdata(pivotdata *aa);
matrix *solve(matrix *m);
dtype *extractsol(matrix *m,pivotdata *p);
long checkconsitency(matrix *m, pivotdata *p);
void printXn(matrix *m);
void printXp(dtype *sol,long len);

matrix *solvegeneral(matrix *m);

#endif // MATRIX_H
