#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<linalg.h>

#define E 1e-3

void main(int argc, char **argv)
{
	double **L, *a, **LI, **I, **M, *x1, *x2, erro;
	int NL, NC, i, cont = 0;
	
	L = ler(argv[1],&NL,&NC);
	printf("\nMatriz lida\n");
	imprime(L,NL,NC);	
	
	printf("\nTriangularização\n");
	triangularizacao(L,NL,NC);
	imprime(L,NL,NC);
	
	printf("\nDeterminante: %lf\n", determinante(L,NL,NC));
/*
	L = ler(argv[1],&NL,&NC);
	printf("\nPivoteamento\n");
	pivoteamento(L,NL,NC);
	imprime(L,NL,NC);

	printf("\nMétodo de Gauss com pivotamento\n");
	subreversa(L,a,NL);

	L = ler(argv[1],&NL,&NC);
	x1 = malloc( NL *sizeof(double *));
	x2 = malloc( NL *sizeof(double *));
	for( i = 0; i < NL; i++ )
		x1[i] = 0;

	do
	{	cont++;
		if( cont%2 == 1 )
			erro = jacobi(L,x1,x2,NL,NC);
		else
			erro = jacobi(L,x2,x1,NL,NC);
	}while( erro > E );
	
	printf("\nMétodo Jacobi\n");
	if( cont%2 == 1 )
	{	for( i = NL-1; i >= 0; i-- )
			printf("a[%d]: %lf\n", i, x2[i]);
	}	
	else
	{	for( i = NL-1; i >= 0; i-- )
			printf("a[%d]: %lf\n", i, x1[i]);
	}
	*/
	L = ler(argv[1],&NL,&NC);
	printf("\nMatriz inversa\n");
	LI = inversa(L,NL,NC);
	imprime(LI,NL,NC);
	
	printf("\nMatriz produto ( matriz lida por sua inversa )\n");
	M = produto(L,LI,NL,NC,NC); //NC1 deve ser igual NL2
	imprime(M,NL,NC);
}
