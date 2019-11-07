#include "matrix.h"
#include "pch.h"

matrix *least_square_regression(matrix *A, matrix *b) {
    //  At.A.x=At.b
    // Therefore x=(At.A)^-1.At.b

    // printf("Debug \n");

    matrix *trans = transpose(A);

    // printf("trans A \n");
    // printmat(trans);

    matrix *mul = multiplymat(trans, A);

    // printf(" mul trans  A \n");
    // printmat(mul);

    matrix *mulinv = inverse(mul);

    // printf(" mul trans  A \n");
    // printmat(mulinv);

    FREE(mul);
    matrix *mul_A = multiplymat(mulinv, trans);

    // printf("mul mul trans  A trans A \n");
    // printmat(mul_A);

    FREE(mulinv);

    matrix *x = multiplymat(mul_A, b);

    // printf(" x \n");
    // printmat(x);

    FREE(mul_A);
    FREE(trans);
    return x;
}

matrix *predict(matrix *A, matrix *x) {
    // matrix *new=transpose(x);
    matrix *pred = multiplymat(A,x );
    // FREE(new);
    return pred;
}
