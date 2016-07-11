#include <stdio.h>
#include <conio.h>
#include "matrix.h"

//DOSYA ÝÞLEMLERÝ

void bmpBinaryFile( int ** matrix , int heightF , int widthF , char * fileName );

// RESMÝN PÝXELLERÝNÝ WÝDTH * HEÝGHT MATRÝSE YAZMA 
unsigned char * bmpDataHeader( char * fileName );
int width( char * fileName );
int height( char * fileName );
int perMet( char * fileName );
int ** bmpDataInfo( char * fileName );

// BINARY OLAN MATRÝSÝ KOVARYANS MATRÝSÝNE DÖKME 

int ** covaryansMatrix( int ** matrix , int heightF , int widthF , int num);


unsigned char * bufferHeader = new unsigned char [54];
int a = 0;

int main()
{
	char * fileName = new char [50];
	int ** imagesBinary;
	int numHeight;
	int ** covaryansBinary;
	int widthBmp , heightBmp , perMetBmp;
	printf("Lutfen dosya ismini giriniz : ");
	gets( fileName );
	printf("Kacinci resim : ");
	scanf("%d" , &numHeight);
	
	widthBmp = width( fileName );
	heightBmp = height( fileName );
	perMetBmp = perMet( fileName );
	
	printf("Width = %d px \n" , widthBmp);
	printf("Height = %d px \n" , heightBmp);
	
	covaryansBinary = new int * [ widthBmp * heightBmp ];
	imagesBinary = new int * [widthBmp];
	for( int i = 0; i < heightBmp; i++ )
		imagesBinary[i] = new int [widthBmp];
	for( int i = 0; i < numHeight; i++ )
		covaryansBinary[i] = new int [ widthBmp * heightBmp ];
		
	imagesBinary = bmpDataInfo(fileName);
	
	bmpBinaryFile( imagesBinary , heightBmp , widthBmp , "bmpFile/images.txt" );
	covaryansBinary = covaryansMatrix( imagesBinary , heightBmp , widthBmp , numHeight );
	bmpBinaryFile( covaryansBinary , numHeight , heightBmp * widthBmp , "bmpFile/covaryans.txt");
	/*for( int i = 0; i < numHeight; i ++ )
	{
		for( int j = 0; j < widthBmp * heightBmp; j++ )
			printf("%3d" , covaryansBinary[i][j]);
		printf("\n");
	}*/
	getch();
	return 0;
}

// RESMÝN PÝXELLERÝNÝ WÝDTH * HEÝGHT MATRÝSE YAZMA
unsigned char * bmpDataHeader( char * fileName )
{
	unsigned char * bmpHeader = new unsigned char [54];
	
	FILE * bmpData_header;
	bmpData_header = fopen( fileName , "r+b");
	
	fread( bmpHeader , sizeof(unsigned char) , 54 , bmpData_header);
	
	fclose(bmpData_header);
	return bmpHeader;
}
// RESMÝN WÝDTH ÝNÝ DÖNDÜRÜR.. 
int width( char * fileName )
{
	int width;
	bufferHeader = bmpDataHeader( fileName );
	
	width = bufferHeader[18];
	return width;	
}
// RESMÝN HEÝGHT ÝNÝ DÖNDÜRÜR..
int height( char * fileName )
{
	int height;
	bufferHeader = bmpDataHeader( fileName );
	
	height = bufferHeader[22];
	return height;
}
// PER MET Ý DÖNDÜRÜR..
int perMet( char * fileName )
{
	int perMet;
	bufferHeader = bmpDataHeader( fileName );
	
	perMet = bufferHeader[28];
	return perMet;
}
// DERSÝM 54. BAYTTAN SONRAKÝ RENK DEÐERLERÝNÝN ORTALAMASI..
int ** bmpDataInfo( char * fileName )
{
	
	int ** bmpData;
	int row_size;
	int buffer;
	unsigned char * bmpBufferData;
	unsigned char tmp;
	int widthB = width( fileName );
	int heightB = height( fileName );
	int perMetB = perMet( fileName );
	
	bmpData = new int * [widthB];
	for( int i = 0; i < heightB; i++ )
		bmpData[i] = new int [widthB];
	
	row_size = ( ( ( perMetB * widthB ) + 31 ) / 32 ) * 4;
	bmpBufferData = new unsigned char [ heightB * row_size ]; 
	
	FILE * readBmp = fopen( fileName , "r+b");
	
	fseek( readBmp , 54 , SEEK_SET );
	int a;
	for( int i = heightB - 1; i >= 0; i-- )
	{
		a = 0;
		fread( bmpBufferData , sizeof(unsigned char) , row_size , readBmp);
		for( int j = 0; j < widthB * 3; j += 3 )
		{
			tmp = bmpBufferData[j];
            bmpBufferData[j] = bmpBufferData[j+2];
            bmpBufferData[j+2] = tmp;
            
            buffer = ( bmpBufferData[j] + bmpBufferData[j+1] + bmpBufferData[j+2] ) / 3;
            
            bmpData[i][a] = buffer;
            a++;
		}
	}
	fclose( readBmp );
	return bmpData;
}

//DOSYA ÝÞLEMLERÝ
void bmpBinaryFile( int ** matrix , int heightF , int widthF , char * fileName )
{
	FILE * write = fopen(fileName ,"w");
	
	for( int i = 0; i < heightF; i++ )
	{
		for( int j = 0; j < widthF; j++ )
			fprintf( write , "%3d" , matrix[i][j]);
		fprintf(write , "\n");
	}
	fprintf(write , "\n\n\n\n");
	fclose(write);
}
// EÐÝTÝM MATRÝSÝNE ATAMALAR YAPILIR.. 
int ** covaryansMatrix( int ** matrix , int heightF , int widthF , int num )
{
	int ** matrixCo;
	int sum = heightF * widthF;
	int buf = 0;
	matrixCo = new int * [ sum ];
	for( int i = 0; i < num; i++ )
		matrixCo[i] = new int [ sum ];
	
	for( int i = 0; i < heightF; i++ )
	{
		for( int j = 0; j < widthF; j++ )
		{
			matrixCo[num - 1][buf] = matrix[i][j];
			buf++;
		}
		//fprintf(covaryansFile , "\n");
	}
	return matrixCo;
}


