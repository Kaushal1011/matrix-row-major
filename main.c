#include "matrix.h"
#include "pch.h"

int main(void) {

    printf("| Least Square Regression Using Normal Form |\n");
    printf("| At.A.x=At.b |\n");
    printf("| Therefore x=(At.A)^-1.At.b |\n");
    printf("-Kaushal Patil\n");
    printf("AU1841040\n\n");
    printf("----------------------------------------------------------\n\n\n");

    matrix *A1;
    printf("Enter Values of Matrix A for second degree curve fit\n");
    A1 = input_matrix(A1);

    printf("Enter Values of Matrix b\n");
    matrix *b;
    b = input_vector(b);

    // FOR SECOND DEGREE CURVE WE AUGMENT A MATRIX  2ND POWER OF ELEMENTS OF A

    matrix *A2 = inplacepowermat(A1, 2);
    matrix *A3 = concatmat(A1, A2);
    matrix *ones = initones(A1->row, 1);
    matrix *A = concatmat(ones, A3);
    // printmat(A);
    matrix *x = least_square_regression(A, b);
    printf("coefficients are \nin order \nc \nm1 \nm2 \n.. \n mn \n\n");
    printf(" Therefore value of vector x is:\n\n");
    printmataccurate(x);
    matrix *A11;
    A11 = input_matrix(A11);
    printf("Enter Values of Matrix A for second degree curve prediction\n");
    matrix *A21 = inplacepowermat(A11, 2);
    matrix *A31 = concatmat(A11, A21);
    matrix *ones1 = initones(A11->row, 1);
    matrix *Ap = concatmat(ones1, A31);
    matrix *pred=predict(Ap,x);
    printf("Predicted Value/s is/are :\n");
    printmataccurate(pred);

    FREE(A);
    FREE(ones);
    FREE(A3);
    FREE(A2);
    FREE(A1);
    FREE(Ap);
    FREE(ones1);
    FREE(A31);
    FREE(A21);
    FREE(A11);

    return 0;
}
