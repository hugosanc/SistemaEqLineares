#include<stdio.h>

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
