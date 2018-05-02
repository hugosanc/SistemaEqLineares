#include<stdio.h>

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
