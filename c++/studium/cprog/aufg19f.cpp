/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 07
    Aufgabennr.   	: 19
    Teilaufgabe   	: falsche Version

    verwendeter
    Compiler
    m. Version    	: Borland Turbo C++ for Windows V3.1 (c) 1991,92
                        
    verwendetes
    Betriebssystem	: Windows98

*/

/*
------------------------------------------------------------------------
*/

#include <stdio.h>

int main(void)
{
  int m, n, sum;


  /* 1 */

  n = 1;
  sum = 0;
  while(n <= 100)
    n++;
    sum += n;
  
  printf("\n1. Summe: %d",sum);


  /* 2 */

  n = 1;
  sum = 0;
  do
  {
    sum += n;
    n++;
  } while(n <= 101);

  printf("\n2. Summe: %d",sum);


  /* 3 */

  sum = 0;
  for (n=1; n<=100; n++)
  {
    sum += n;
    n++;
  }

  printf("\n3. Summe: %d",sum);


  /* 4 */

  n = 1;
  sum = 0;
  for (n=1; n<=m; n++)
  {
    m = 100;
    sum += n;
  }

  printf("\n4. Summe: %d",sum);


  /* 5 */

  for (n=1, sum=0; n<101; sum += ++n);

  printf("\n5. Summe: %d",sum);


  /* 6 */

  for (n=1, sum=0; n<101; sum += n++);

  printf("\n6. Summe: %d",sum);


  /* 7 */

  for (n=1, sum=0; n<101; sum +=n, n++);

  printf("\n7. Summe: %d",sum);

  return 0;
}