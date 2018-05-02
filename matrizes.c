#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define E 1e-3

FILE *leitura;
//1- leitura m[a][b]
double **ler( char *nome, int *NL, int *NC)
{	
	int i, j;
        double **M, a;
	leitura = fopen(nome,"r");
	i = fscanf(leitura,"%d, %d",NL, NC);

	M = malloc( *NL *sizeof(double *));
	for( i = 0 ; i < *NL ; i++ )
		M[i] = malloc((*NC)*sizeof(double) );
	    
	i = j = 0;

	while ( fscanf(leitura,"%lf",&a) != EOF) 
	{
		M[i][j] = a;
		j++;
		if (j == *NC) 
		{	j = 0;
			i++;
		}
	}		
	return M;
}
//2- impressão m[a][b]
void imprime( double **M, int NL, int NC)
{
	int i, j;
	for(i = 0; i < NL; i++)
	{
		for( j = 0; j < NC; j++)
			printf("%lf\t ",M[i][j]);  
		puts("");
	}	
}
//3- triangularizacao m[a][b]
void **triangularizacao( double **M, int NL, int NC)
{
        double l;
        int i,j,k;
        
        for( j = 0; j < NL-1; j++)
        {	for( i = j+1; i < NL; i++ )
		{
			l = M[i][j]/M[j][j];       
			for( k = 0; k < NC; k++ )
				M[i][k] -= l*M[j][k]; 
		}
	}       
}
//4- pivoteamento método de gauss 
void **pivoteamento( double **M, int NL, int NC)
{
        double l, pivo, maior, aux;
        int i,j,k,m,n;
        
        for( j = 0; j < NL-1; j++)
        {	
		pivo = M[j][j];
		maior = pivo;

		for( k = j; k < NL; k++)
		{	if( fabs(maior) < fabs(M[k][j]))
			{	maior = M[k][j];
				m = k;
			}
		}

		if( maior != pivo)
		{	for( n = 0; n < NC; n++)
			{	aux = M[m][n];
				M[m][n] = M[j][n];
				M[j][n] = aux;
			}
			
		}

		for( i = j+1; i < NL; i++)
		{
			l = M[i][j]/M[j][j];       
			for( k = 0; k < NC; k++ )
				M[i][k] -= l*M[j][k]; 
		}
	}       
}

void subreversa( double **M, double *x, int dim)
{
	int i,j;
	double sum;

	x = malloc( dim* sizeof(double));
	for( i=dim-1; i>=0; i-- )
	{
		sum=0;
		for( j=i+1; j<dim; j++)
			sum += M[i][j]* x[j];

		x[i] = ( M[i][dim] - sum )/M[i][i];
		printf("a[%d]: %lf\n",i,x[i]);
	}
}
//5- produto duas matrizes m1[a][b] x m2[b][c]
double **produto( double **M1, double **M2, int NL1, int NC1, int NC2 )
{
	double **M, sum;
	int i, j, k;
	
	M = malloc( NL1 *sizeof(double *));
	for( i = 0 ; i < NL1 ; i++ )
		M[i] = malloc((NC2)*sizeof(double) );
	
	for( i = 0; i < NL1; i++ )
	{	for( j = 0; j < NC2; j++ )
		{	sum = 0;
			for( k = 0; k < NC1; k++ )
				sum += M1[i][k]* M2[k][j];
			M[i][j] = sum;
		}
	}
	return M;
}
//6- m[a][b] , no problema a=b
double determinante( double **L, int NL, int NC )
{
	double det = 1;
	int i, j;

	pivoteamento(L,NL,NC);
		
	for( i = 0; i < NL; i++ )
	{	for( j = 0; j < NC; j++ )
		{	if( i==j )
				det *= L[i][j];
		}
	}
	return det;
}
//7- inversa matriz quadrada
double **inversa( double **L, int NL, int NC )
{
	int i,j,k;
	double sum, **aux, **LI, **newL;

	//inicialização matriz combinada
	newL = malloc( NL *sizeof(double *));
	for( i = 0 ; i < NL ; i++ )
		newL[i] = malloc((2*NC)*sizeof(double) );

	//matriz combinada
	for( i = 0; i < NL; i++ )
	{	for( j = 0; j < 2*NC; j++ )
		{	if( j < NC )
				newL[i][j] = L[i][j];
			else
			{	if( j== (i+NC))
					newL[i][j] = 1;
				else
					newL[i][j] = 0;
			}
		}
	}
	pivoteamento(newL,NL,2*NC);

	//inicialização matriz aux
	aux = malloc( NL *sizeof(double *));
	for( i = 0 ; i < NL ; i++ )
		aux[i] = malloc((NC+1)*sizeof(double) );

	//inicialização matriz inversa
	LI = malloc( NL *sizeof(double *));
	for( i = 0 ; i < NL ; i++ )
		LI[i] = malloc((NC)*sizeof(double) );

	//matriz inversa
	for( k = 0; k < NL; k++ )
	{	//matrizes auxiliares
		for( i = 0; i < NL; i++ )
		{	for( j = 0; j < NC+1; j++ )
			{	if( j < NC )
					aux[i][j] = newL[i][j];
				else
					aux[i][j] = newL[i][k+j];
			}
		}
		//substituição reversa
		for( i = NL-1; i >= 0; i-- )
		{
			sum = 0;
			for( j = i+1; j < NL; j++ )
				sum += aux[i][j]* LI[j][k];

			LI[i][k] = ( aux[i][NL] - sum )/aux[i][i];
		}
	}
	free(aux);
	free(newL);
	return LI;
}
//7- utilizando dois vetores x1 e x2
double jacobi( double **M, double *x1, double *x2, int NL, int NC )
{
	int i,j;
	double sum, s1, s2, erro;

	for( i = 0; i < NL; i++ )
	{	sum = 0;
		for( j = 0; j < NC-1; j++ )
		{	if( j!=i )
				sum += -M[i][j]* x1[j];
		}
		x2[i] = ( sum + M[i][NC-1] )/ M[i][i];
	}
	for( i = 0; i < NL; i++ )
	{	s1 += pow( x2[i]-x1[i], 2);
		s2 += pow( x2[i], 2 );
	}
	erro = sqrt(s1)/sqrt(s2);
	return erro;
}

void main(int argc, char **argv)
{
	double **L, *a, **LI, **I, **M, *x1, *x2, erro;
	int NL, NC, i, cont = 0;
	
	L = ler(argv[1],&NL,&NC);
	printf("\nMatriz lida\n");
	imprime(L,NL,NC);	
	
	/*printf("\nTriangularização\n");
	triangularizacao(L,NL,NC);
	imprime(L,NL,NC);
	
	printf("\nPivoteamento\n");
	pivoteamento(L,NL,NC);
	imprime(L,NL,NC);

	printf("\nMétodo de Gauss com pivotamento\n");
	subreversa(L,a,NL);

	printf("\nDeterminante: %lf\n", determinante(L,NL,NC));*/

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
	{	for( i = 0; i < NL; i++ )
			printf("a[%d]: %lf\n", i, x2[i]);
	}	
	else
	{	for( i = 0; i < NL; i++ )
			printf("a[%d]: %lf\n", i, x1[i]);
	}
	/*
	printf("\nMatriz inversa\n");
	LI = inversa(L,NL,NC);
	imprime(LI,NL,NC);
	
	printf("\nMatriz produto\n");
	M = produto(L,LI,NL,NC,NC); //NC1 deve ser igual NL2
	imprime(M,NL,NC);*/
}
