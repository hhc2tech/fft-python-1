#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#define cplx double complex
#define PI 3.14159265358979323846

//-----------
//fast fourier transform
//-----------

void le_fft(cplx buf[], int n)
{
    cplx fo[n];
    cplx fe[n];
    if (n != 1) {
        for (int i = 0; i < n/2; i++)
		{
			cplx t = cexp(-I * 2 * PI * i / n);
			fe[i] = buf[i] +  buf[i + n/2];
			fo[i] = (buf[i] - buf[i + n/2])*t;
		}
        le_fft(fe, n/2);
        le_fft(fo, n/2);
        for (int i = 0; i < n/2; i++)
		{
			buf[2*i] = fe[i];
			buf[(2*i)+1] = fo[i];
		}
	}
}

int main() {

    float o;
    int k,size=0;

    //-----------
    //data input from file
    //-----------

    FILE *F;
    F=fopen("CHIRP2.txt", "r");
    while ((k=fscanf(F,"%f",&o))!=EOF)
    {
        size+=k;
    }
    printf("number of values = %d\n\n",size);
    rewind(F);
    double *a = malloc(size*sizeof(double));
    int i,j;
    for (i = 0; i < size; i++)
    {
        fscanf(F,"%lf",&a[i]);
    }
    fclose(F);

    //-----------
    //array input/slide
    //-----------

    int N=2000;
    int W=256;
    int num;
    num = 2*(N-W)/W+1;
    printf("number of windows = %d\n",num);
    printf("window width = %d\n",W);
    cplx **le_array = (cplx **)malloc(N*sizeof(cplx *));
    for(i = 0; i < N; i++)
        {
            le_array[i] = (cplx *)malloc(W*sizeof(cplx));
        }
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < W; j++)
        {
            le_array[i][j] = a[j+i*W/2];
        }
    }

    //-----------
    //fft implementation
    //-----------

    cplx buf[2048];
    for ( i = 0; i < num; i++ )
    {
        for ( j = 0; j < W; j++ )
        {
            buf[j] = le_array[i][j];
        }
        le_fft(buf, W);
        for ( j = 0; j < W; j++ )
        {
            le_array[i][j] = buf[j];
        }
    }
    printf( "\nfft done!\n" );

    //-----------
    //array output to file
    //-----------

    FILE *g = fopen("CHIRP2_OUT.txt", "w");
	if (g == NULL)
	{
            printf("could not open file\n");
    }
    else
    {
        for ( i = 0; i < num; i++ )
        {
            for (int j = 0; j < W/2; j++)
            {
                fprintf(g, "%g, ", cabs(le_array[i][j]));
            }
            fprintf(g, "\n" );
        }
	}
    fclose(g);
    printf( "\narray with fft printed!\n" );

    //-----------
    //memory free
    //-----------

    free(a);
    for(int i = 0; i < N; i++)
        {
            free(le_array[i]);
        }
    free(le_array);
    printf("\nDONE!\n");
    return 0;
}
