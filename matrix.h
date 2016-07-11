#include <stdio.h>
#include <math.h>

int ** unitMatrix( int size )		/* Birim matris oluþturur .. */
{
	int ** matrix = new int * [size];
	for( int i = 0; i < size; i++ )
		matrix[i] = new int [size];
	
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size; j++ )
		{
			if( i == j )
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
	return matrix;
}

int ** zeroMatrix( int size )		/* Girilen indislerde sýfýr matrisi oluþturur */
{
	int ** matrix_zero = new int * [size];
	for( int i = 0; i < size; i++ )
		matrix_zero[i] = new int [size];
	
	for( int i = 0; i < size; i++ )
	{
		for( int j = 0; j < size; j++ )
				matrix_zero[i][j] = 0;
	}
	return matrix_zero;
}

int equalMatrix( int ** matrix_one , int ** matrix_two , int m , int n )	/* Matrisler eþit matris mi kontrol eder .. */
{
	int count = 0;
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			if( matrix_one[i][j] == matrix_two[i][j] )
				count++;
		}
	}
	if( count == ( m * n ) )
		return 1;
	else return 0;
}

int ** sumMatrix( int ** matrix_one , int ** matrix_two , int m , int n )	/* Ýki matrisin toplamýný bulur .. */ 
{
	int ** result = new int * [m];
	for ( int i = 0; i < n; i++ )
		result[i] = new int [m];

	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			result[i][j] = matrix_one[i][j] + matrix_two[i][j];
		}
	}
	return result;
}

int ** extractMatrix( int ** matrix_one , int ** matrix_two , int m , int n )	/* Ýki matrisin farkýný bulur .. */
{
	int ** result_e = new int * [m];
	for ( int i = 0; i < n; i++ )
		result_e[i] = new int [m];
	
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			result_e[i][j] = matrix_one[i][j] - matrix_two[i][j];
		}
	}
	return result_e;
}

int ** multipSkaler( int ** matrix , int x , int m , int n )		/* Matrisin skaler sayi ile çarpýmý .. */
{
	int temp;
	for( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			temp = matrix[i][j];
			temp = temp * x;
			matrix[i][j] = temp;
		}
	}
	return matrix;
}

int **  multipMatrix( int ** matrix , int m , int n , int ** matrix_two , int t , int p )	/* Ýki matrisin çarpýmýný bulur .. */
{
	if( n != t )
	{
		printf("Bu iki matris carpýlamaz..!");
		return 0;
	}
	int ** result_m = new int * [ p ];
	for( int i = 0; i < m; i++ )
		result_m[i] = new int [p];
	
	int buf;
	for ( int i = 0; i < m; i++ ) 
	{          
    	for ( int j = 0; j < p; j++ ) 
		{          
    		for ( int k = 0; k < n; k++)            
				result_m[i][j] += matrix[i][k] * matrix_two[k][j];          
    	}
    }
	return result_m;		
}

int ** transpose( int ** matrix , int m , int n )	/* Matrisin transpozunu alma .. */
{
	int ** result_t = new int * [m];
	for ( int i = 0; i < n; i++ )
		result_t[i] = new int [m];
	
	int temp;
	for ( int i = 0; i < m; i++ )
	{
		for( int j = 0; j < n; j++ )
		{
			result_t[i][j] = matrix[j][i];
		}
	}
	return result_t;
}


