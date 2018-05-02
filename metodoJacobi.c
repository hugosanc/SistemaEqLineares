#include<stdio.h>
#include<math.h>

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

