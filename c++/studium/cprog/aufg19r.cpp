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
    Teilaufgabe   	: richtige Version

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
  {
    sum += n;
    n++;
  }

  printf("\n1. Summe: %d",sum);


  /* 2 */

  n = 1;
  sum = 0;
  do
  {
    sum += n;
    n++;
  } while(n <= 100);

  printf("\n2. Summe: %d",sum);


  /* 3 */

  sum = 0;
  for (n=1; n<=100; n++)
  {
    sum += n;
  }

  printf("\n3. Summe: %d",sum);


  /* 4 */

  n = 1;
  m = 100;
  sum = 0;
  for (n=1; n<=m; n++)
  {
    sum += n;
  }

  printf("\n4. Summe: %d",sum);


  /* 5 */

  for (n=0, sum=0; n<100; sum += ++n);

  printf("\n5. Summe: %d",sum);


  /* 6 */

  for (n=1, sum=0; n<101; sum += n++);

  printf("\n6. Summe: %d",sum);


  /* 7 */

  for (n=1, sum=0; n<101; sum +=n, n++);

  printf("\n7. Summe: %d",sum);

  return 0;
}

/*
------------------------------------------------------------------------

    Es wurden folgende Änderungen vorgenommen:

Summe 1)  Die Zeile n++; wurde mit der Zeile sum += n; vertauscht, weil sonst
	  wäre es keine Summe von 1 bis 100, sondern von 2 bis 101 gewesen.

Summe 2)  Die 101 im while Ausdruck wurde durch eine 100 ersetzt, weil die
	  Schleife ja nur bis n = 100 durchlaufen werden soll.

Summe 3)  Die Zeile n++; wurde gelöscht, da bereits im Kopf der for-Schleife
	  diese Anweisung steht. Ansonsten hätte die resultierende Summe
	  nur die Hälfte des erwarteten Wertes.

Summe 4)  Die Zeile m=100; wurde vor die for-Schleife geschrieben. Ansonsten wäre
	  m nicht initialisiert gewesen und die Abbruchbedingung wäre mehr oder
	  weniger dem Zufall überlassen geblieben.

Summe 5)  Es wurde der Ausdruck n=1; in n=0; und die Abbruchbedingung von
	  n<101 in n<100 umgeändert. Denn im Anschluß wird der Summe der um
	  1 erhöhte Wert von n zugewiesen. Da die Anzahl der Durchläufe weiterhin
          100 bleibt erhält man somit das richtige Ergebnis. 

========================================================================
*/
