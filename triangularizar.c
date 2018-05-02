#include<stdio.h>

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
