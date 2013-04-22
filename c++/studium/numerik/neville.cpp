#include <math.h>
#include <stdio.h>

int main(void)
{
   double x[7] = {0.0 ,6.0 ,10.0 ,13.0 ,17.0 ,20.0 ,28.0 };

   double t = 2.0;

   double M[7][7];

   M[0][0] = 6.67;
   M[1][0] = 17.33;
   M[2][0] = 42.67;
   M[3][0] = 37.33;
   M[4][0] = 30.10;
   M[5][0] = 29.31;
   M[6][0] = 28.74;


   for (int i=1; i<7; i++)
   {
     for (int j=1; j<7; j++)
     {
       if (j>i)
       {
         printf(" 0");
	 break;
       }

       else
         M[i][j] = ((t - x[i-j]) * M[i][j-1] - (t - x[i]) * M[i-1][j-1]) / (x[i]-x[i-j]);

       printf(" %lf",M[i][j]);
     }

     printf("\n");
   }

  return 0;
}

    