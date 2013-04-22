/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 06
    Aufgabennr.   	: 18
    Teilaufgabe   	: --

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
#include <math.h>

int check(int pattern, int answer, int wert);
                                  
int main(void)
{
  
  unsigned short muster;       
  unsigned short antwort;

  int fehler, test1, test2, test3, test4, test5, test6, test7, test8;

  printf("\nBitte geben Sie die Musterlösung als Bytewert ein (0 - 255): ");
  scanf("%hu",&muster);
  printf("\nBitte geben Sie eine Prüfungsantwort als Bytewert ein : ");
  scanf("%hu",&antwort);

  printf("\n");

  test1 = check(muster, antwort, 128);
  test2 = check(muster, antwort, 64);
  test3 = check(muster, antwort, 32);
  test4 = check(muster, antwort, 16);
  test5 = check(muster, antwort, 8);
  test6 = check(muster, antwort, 4);
  test7 = check(muster, antwort, 2);
  test8 = check(muster, antwort, 1);

  fehler = test1 + test2 + test3 + test4 + test5 + test6 + test7 + test8;


  printf("\n\nDie Prüfungsantwort enthielt %d Fehler !",fehler);

  return 0;
}                   


int check(int pattern, int answer, int wert)
{
  int check1, check2;

  check1 = pattern & wert;
  check2 =  answer & wert;

  if (check1==check2)
    return 0;

  else
    return 1;
}
      
/*
------------------------------------------------------------------------

    Beantwortung der Fragen:

a) Man vergleicht jeweils das Muster mit 1,2,4,8,... mittels dem & Operator
   und die Antwort mit 1,2,4,8,... mittels dem & Operator.
   Die beiden resultierenden Ergebnisse werden verglichen, sind diese gleich,
   so sind sowohl im Muster, als auch in der Antwort die Bits gesetzt.
   Sind die Ergebnisse versch., so sind die Bits an der jeweiligen Stelle
   verschieden, d.h. ein Fehler wurde erkannt.

b) 106 entspricht 01101010
   Ja-Nein-Ja-Nein-Ja-Nein-Ja-Nein entspricht 10101010
   Nein-Ja-Nein-Ja-Nein-Ja-Nein-Ja entspricht 01010101

   Wie man sofort sieht, stimmen für den 1.Fall mehr Bits mit der
   Musterlösung überein, d.h. eine Beantwortung analog dem 1.Fall ist besser ! 
                                                                              
========================================================================
*/

