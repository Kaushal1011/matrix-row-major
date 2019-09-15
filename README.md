# matrix-row-major

matrix operations written in c to find the rref form and  nullspace
____
use examples in test.txt to test

____

## System of Linear Equations Solver

- Kaushal Patil
- AU1841040

Open folder matrix-row-major and run make.To execute run main.out.

The program uses a matrix structure which contains an array(accessed as a row major matrix) and matrix dimensions

some basic functions related to matrices are defined in matrix.c which are related to matrix operations such as row col swap,drop,subtract, generation of identity matrix and so on along with this rref() is also defined in matrix.c

Functions related to finding the nullspace of a matrix from its rref form are defined in nullspace.c.In null space it extracts I and F and merges them pivot and free variable wise to produce a Nullspace matrix which contain vectors that span the nullspace.

Finally Function related to solving a system linear equations by taking rref of its augmented form are defined in solve.c

main.c is the file that contains main function and is currently used to solve 1 system of equations and then exits.

All functions have comments over them that give brief idea of its functionality

The following Algorithm was referenced to compute and build the rref() function
[](https://www.math.purdue.edu/~shao92/documents/Algorithm%20REF.pdf)
