# matrix-row-major

matrix operations written in c to find the rref form and  nullspace
____

- use example in A.txt and b.txt to least square regression of second degree
  - for easy testing use in .txt
  - ```shell ./main.out < in.txt```

- use example in test.txt to test linear equation solver

____

## Least Square Regression (current main.c)

### To Run LSR

- Open folder matrix-row-major and run make.
- To execute run main.out.
- To test on give data run command

  ```shell
  ./main.out < in.txt
  ```

### Details of LSR

Performs Least Square Regression on data of the form (A.x=b).

Method:

- we know At.A.x=At.b
- therefore x=(At.A)-1.At.b

About main:

- takes input A
- takes input b
- performs least squares regression of second degree
- prints a vector with coeffiecients of equation or the vector x.

____

## System of Linear Equations Solver (main in main_Linear_Equation_Solver.c)

### To Run SoLES

- Open folder matrix-row-major and run make.
- To execute run main.out.

### Details of SoLES

The program uses a matrix structure which contains an array(accessed as a row major matrix) and matrix dimensions

some basic functions related to matrices are defined in matrix.c which are related to matrix operations such as row col swap,drop,subtract, generation of identity matrix and so on along with this rref() is also defined in matrix.c

Functions related to finding the nullspace of a matrix from its rref form are defined in nullspace.c . In null space it extracts I and F and merges them according to pivot and free variables to produce a Nullspace matrix which contain vectors that span the nullspace.

Finally Function related to solving a system linear equations by taking rref of its augmented form are defined in solve.c

main.c is the file that contains main function and is currently used to solve 1 system of equations and then exits.

All functions have comments over them that give brief idea of its functionality

The following Algorithm was referenced to compute and build the rref() function

- [rref algorithm](https://www.math.purdue.edu/~shao92/documents/Algorithm%20REF.pdf)
