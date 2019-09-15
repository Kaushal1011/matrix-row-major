
#include "matrix.h"
#include "pch.h"

int main(void) {

    printf("| System of Linear Equations Solver Using Matrices |\n");
    printf("-Kaushal Patil\n");
    printf("AU1841040");
    printf("----------------------------------------------------------\n\n\n");
    printf("This program \n Solves Equation Ax=b and prints x if it exists and then prints nullspace\n" );
    printf("\nPlease be carefull in adding inputs to program.Before Taking input the format is specified\n");
    printf("For Example Input of A is in the Format\n");
    printf("enter one row at a time each element seperated by a space and press return/enter \n");
    printf("Format of B is enter one element and press return/enter\nExample of format can be found in test.txt\n");
    printf("This program will solve one system of equations in one run to test for another test case run again\n");
    printf("----------------------------------------------------------\n\n\n");

    matrix *m =NULL;
    m=input_matrix(m);
    matrix *a=solve(m);

    printf("\n\n\nNULLSPACE OF MATRIX IS(prints 0.00 if Nullspace only has Zero vector)\n\n\n");
    printmat(a);


    // FREE(m);
    FREE(a);
    return 0;
}
