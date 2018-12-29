#include <stdio.h>

/* Basic Function */
double** addMatrix(double** A, double** B, int n);
double** subMatrix(double** A, double** B, int n);
double** mulMatrix(double** A, double** B, int n);
double detA(double** A, int n);
double** inverseA(double** A, int n);

/* Additional Function */
double** inverseA55(double** A);
double** inverseA_gaussian(double** A,int n);
double** matrix_LU(double** A,double ** U,double **L,int n);
/* Use this proto-type if you need */
 double** transposeA(double** A, int n);
 double** getMijFromA(double** A, int i, int j, int n);
 double detA44(double** A);
// ...
