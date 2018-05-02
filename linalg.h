#ifndef linalg_h__
#define linalg_h__
//ler
extern double **ler( char *nome, int *NL, int *NC);
//imprimir
extern void imprime( double **M, int NL, int NC);
//triangularizar
extern void **triangularizacao( double **M, int NL, int NC);
//determinante
extern double determinante( double **L, int NL, int NC );
//método pivoteamento Gauss
extern void **pivoteamento( double **M, int NL, int NC);
extern void subreversa( double **M, double *x, int dim);
//método de Jacobi
extern double jacobi( double **M, double *x1, double *x2, int NL, int NC );
//matriz inversa
extern double **inversa( double **L, int NL, int NC );
//matriz produto
extern double **produto( double **M1, double **M2, int NL1, int NC1, int NC2 );

#endif
