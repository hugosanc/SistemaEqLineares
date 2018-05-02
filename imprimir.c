#include<stdio.h>

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
