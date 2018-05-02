#include<stdio.h>
FILE *leitura;

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
