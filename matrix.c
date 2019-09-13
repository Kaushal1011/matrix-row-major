#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//datatype for matrix usage
#define dtype double
//row major memory for matrix implementation
#define elem(m, i, j) (m->arr[(i * m->col) + j])

typedef struct matrix
{
    dtype *arr;
    long row;
    long col;
} matrix;

typedef struct pivotdata
{
    long num_pivot;
    long *pivotindex;
} pivotdata;

void constructmatrix(matrix *m, long row1, long col1)
{

    m->row = row1;
    m->col = col1;
    m->arr = calloc(m->row * m->col, sizeof(dtype));
}

matrix *init(long row, long col)
{
    matrix *m = calloc(1, sizeof(matrix));
    constructmatrix(m, row, col);
    return m;
}

void eye(matrix *m)
{
    long dim = (m->row <= m->col) ? m->row : m->col;
    for (long i = 0; i < dim; i++)
    {
        elem(m, i, i) = 1;
    }
}

void swap(dtype *a, dtype *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void rowswap(matrix *m, long r1, long r2)
{
    for (long i = 0; i < m->col; i++)
    {
        swap(&elem(m, r1, i), &elem(m, r2, i));
    }
}

matrix *input_matrix(matrix *m)
{
    char buf[BUFSIZ] = {0};
    char *token = NULL;
    const long NUMBASE = 10;
    long row, col;
    printf("Enter row and column of matrix seperated by space: ");
    fgets(buf, BUFSIZ, stdin);
    token = buf;
    row = strtol(strtok(token, " "), NULL, NUMBASE);
    col = strtol(strtok(NULL, " "), NULL, NUMBASE);
    m = init(row, col);
    // constructmatrix(m,m->row,m->col);
    printf("constructed matrix of %d %d\n", m->row, m->col);
    printf("Enter values in matrix in the form \na00 a01 a02 .. a0n\n... ... ... ... ...\nan0 an1 an2 .. ann\n");
    for (long i = 0; i < m->row; i++)
    {
        fgets(buf, BUFSIZ, stdin);
        token = buf;
        elem(m, i, 0) = (double)strtol(strtok(token, " "), NULL, NUMBASE);
        // elem(m,i,0) = 1;
        for (long j = 1; j < m->col; j++)
        {
            elem(m, i, j) = (double)strtol(strtok(NULL, " "), NULL, NUMBASE);
            //    elem(m,i,j)=1;
        }
    }
    return m;
}

void printmat(matrix *m)
{
    for (long i = 0; i < m->row; i++)
    {
        for (long j = 0; j < m->col; j++)
        {
            printf("%8.2lf  ", elem(m, i, j));
        }
        printf("\n");
    }
}

void subrow(matrix *m, long r1, long r2)
{
    double mul = elem(m, r2, r1) / elem(m, r1, r1);
    double arr[m->col];
    for (long i = 0; i < m->col; i++)
    {
        arr[i] = elem(m, r1, i) * mul;
    }
    for (long i = 0; i < m->col; i++)
    {
        elem(m, r2, i) -= arr[i];
    }
    // return m;
}

void subrowR(matrix *m, long r1, long r2,long piv)
{
    double mul = elem(m, r2, piv) / elem(m, r1, piv);
    double arr[m->col];
    for (long i = 0; i < m->col; i++)
    {
        arr[i] = elem(m, r1, i) * mul;
    }
    for (long i = 0; i < m->col; i++)
    {
        elem(m, r2, i) -= arr[i];
    }
    // return m;
}

void rowmulconst(matrix *m, long row, double scalar)
{
    for (long i = 0; i < m->col; i++)
    {
        elem(m, row, i) *= scalar;
    }
}

long iszerorow(matrix *m, long row,long aug)
{
    long flag=0;
    for (long i=0;i<m->col-aug;i++)
    {
        if(elem(m,row,i)!=0)
        {
            flag=1;
        }
    }
    return flag;
}
pivotdata *rref(matrix *m,long aug)
{
    pivotdata *ret;
    ret = calloc(1, sizeof(pivotdata));
    long dim = (m->row <= m->col) ? m->row : m->col;
    ret->pivotindex = calloc(dim, sizeof(long));

    // matrix *I = mat_init();
    // printf("Enter b:\n");
    // mat_input(I);
    for (long i = 0; i < m->row - 1; i++)
    {
        if (elem(m, i, i) == 0)
        {
            long j = 0;
            for (j = i + 1; j < m->row; j++)
            {
                if (elem(m, j, i) != 0)
                {
                    break;
                }
            }

            if (j == m->row)
            {
                break;
            }
            else
            {
                rowswap(m, j, i);
            }
        }

        ret->pivotindex[ret->num_pivot] = i;
        ret->num_pivot++;
        for (long j = i + 1; j < m->row; j++)
        {
            if (elem(m, i, j) != 0)
            {
                subrow(m, i, j);
            }
        }

        for (long i = 0; i < m->row; i++)
        {
            if (elem(m, i, i) != 0 && elem(m, i, i) != 1)
            {
                double common = 1 / elem(m, i, i);
                rowmulconst(m, i, common);
            }
        }
    }
    if (elem(m, (m->row - 1), (m->row) - 1) != 0)
    {
        ret->pivotindex[ret->num_pivot] = (m->row) - 1;
        ret->num_pivot++;
    }
    // U calculation is complete
    // check for last pivot
    printmat(m);
    printf("\n printed U");
    // start calculation for R

    long rstart=0;
    for(long i=m->row-1;i>0;i--)
    {
        // printf("\n %d \n",iszerorow(m,i,aug));
        if(iszerorow(m,i,aug)==1)
        {
            rstart=i;
            break;
        }

    }
    long piv;
    for(long i=0;i<m->col-aug;i++)
    {
        if(elem(m,rstart,i)!=0)
        {
            piv=i;
            break;
        }
    }
    printf("\n %d %d\n ",rstart,piv);
  for (long i = rstart; i > 0; i--)
    {
        for (long j = i-1; j >= 0; j--)
        {
                if(elem(m,j,piv)!=0)
                {subrowR(m, i, j,piv);}
                // printf("\ninside rref\n");
                // printmat(m);
                // printf("\n\n");
                ret->pivotindex[ret->num_pivot]=i;
                ret->num_pivot++;

        }
        while(iszerorow(m,i,aug)!=1)
        {
            if (i<=1)
             break;
            i--;
            // printf("\nsubtracted i\n");


        }
        if(i==0)
        {
            break;
        }

        for(long k=piv-1;k>0;k--)
        {
            if(elem(m,i,k)!=0)
            {
                piv=k;
            }
        }

    }

    return ret;
}
matrix *augmented_matrix(matrix *m, dtype *a)
{

    matrix *new_m = init(m->row, m->col + 1);
    for (long i = 0; i < new_m->row; i++)
    {
        for (long j = 0; j < new_m->col; j++)
        {
            elem(new_m, i, j) = elem(m, i, j);
        }
    }
    for (long i = 0; i < new_m->row; i++)
    {
        elem(new_m, i, new_m->col - 1) = a[i];
    }
    free(m->arr);
    free(m);
    return new_m;
}

matrix *input_augmentcolumn(matrix *m)
{
    matrix *ret;
    dtype *col = calloc(m->row, sizeof(dtype));
    printf("enter b in column form like\nb0\nb1\n.\nbn\n");
    for (long i = 0; i < m->row; i++)
    {
        scanf("%lf", &col[i]);
    }
    ret = augmented_matrix(m, col);
    free(col);
    return ret;
}
void print_pivdata(pivotdata *aa)
{
    printf("\n %d \n", aa->num_pivot);
    for (long i = 0; i < aa->num_pivot; i++)
    {
        printf("%d ", aa->pivotindex[i]);
    }
    printf("\n");
}
matrix *dropcol(matrix *m, long colindex)
{
    long k = 0;
    matrix *newm = init(m->row, m->col - 1);
    for (long i = 0; i < m->row; i++)
    {
        k = 0;
        for (long j = 0; j < m->col; j++)
        {

            if (j != colindex)
            {
                elem(newm, i, k) = elem(m, i, j);
                k++;
            }
        }
    }
    free(m->arr);
    free(m);
    return newm;
}

matrix *dropcol_Fmaker(matrix *m, pivotdata *p)
{
    matrix *newm = init(m->row, (m->col - (p->num_pivot)));

    long k = 0;

    for (long i = 0; i < m->row; i++)
    {
        k = 0;
        for (long j = 0; j < m->col; j++)
        {
            long flag = 1;
            for (long z = 0; z < p->num_pivot; z++)
            {
                if (j == p->pivotindex[z])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
            {
                elem(newm, i, k) = elem(m, i, j);
                k++;
            }
        }
    }
    newm = dropcol(newm, newm->col - 1);

    // free(m->arr);
    // free(m);
    return newm;
}

matrix *droprow(matrix *m, long row)
{
    matrix *newm = init(m->row - 1, m->col);
    long k = 0;
    long flag = 0;
    for (long i = 0; i < m->row; i++)
    {
        for (long j = 0; j < m->col; j++)
        {
            if (i != row)
            {
                elem(newm, k, j) = elem(m, i, j);
                flag = 1;
            }
        }
        if (flag == 1)
        {
            k++;
            flag = 0;
        }
    }
    free(m->arr);
    free(m);

    return newm;
}

matrix *drop_zerorows(matrix *m)
{
    long flag=0;
    long *arr;
    long arrindex=0;
    long initialrows=m->row;
    arr=calloc(m->row,sizeof(long));
    for(long i=0;i<m->row;i++)
    {
        flag=0;
        for(long j=0;j<m->col;j++)
        {
            if(elem(m,i,j)!=0)
            {
                flag=1;
            }

        }
        if (flag==0)
        {
            arr[arrindex]=i;
            arrindex++;

        }


    }
    // for(long i=0;i<arrindex;i++)
    // {
    //     printf("\n %d %d\n",arr[i]);
    // }
    for(long i=0;i<arrindex;i++)
    {

       m= droprow(m,arr[i]-i);
    }
    free(arr);

    return m;


}

matrix make_nullspacematrix(matrix *r){;}

matrix *nullspace(matrix *r,pivotdata *p)
{
    matrix *f;
    f =drop_zerorows(r);
    f=dropcol_Fmaker(f,p);
    // multiplying all of F with -1 scalar
    for(long i=0;i<f->row;i++)
    {
        rowmulconst(f,i,-1.0);
    }

    return f;


}
// void makeF(matrix *m, pivotdata *p)
// {
//

// }

long main(long argc, char const *argv[])
{
    /* code */
    matrix *m;
    pivotdata *aa;
    m = input_matrix(m);
    m = input_augmentcolumn(m);
    aa = rref(m,1);
    printmat(m);
    print_pivdata(aa);
    matrix *f;
    f = nullspace(m, aa);
    // matrix *e=init(f->col,f->col);
    // eye(e);
    printf("\n");
    printmat(f);
    // printmat(e);

    free(m->arr);
    free(m);
    free(f->arr);
    free(f);
    free(aa->pivotindex);
    free(aa);
    // free(e);
    return 0;
}
