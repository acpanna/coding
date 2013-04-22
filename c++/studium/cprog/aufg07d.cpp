/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 03
    Aufgabennr.   	: 07
    Teilaufgabe   	: d)

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

int main(void)
{
  char enter;

  double test;
  double test2;

  float fest;
  float fest2;

  test = 0.0;
  test2 = 50.0;

  fest = 0.0f;
  fest2 = 50.0f;

  printf("\nBitte drücken Sie RETURN um die Genauigkeit des Datentyps Double zu ermitteln !\n");
  scanf("%c",&enter);

  for(test = 1.0 ;; test = test + 1000000000000.0) 
    { 
      if (test2 ==1)
        break;
      test2 = 1.0 + 1.0/test; 
      printf("      %g\n",1.0/test); 
    } 

  printf("\nBitte drücken Sie RETURN um die Genauigkeit des Datentyps Float zu ermitteln !\n");
  scanf("%c",&enter);

  for(fest = 1.0f ;; fest = fest + 100000.0f)
  {
    if (fest2 ==1)
      break;
    fest2 = 1.0f + 1.0f/fest;
    printf("        %g\n",1.0f/fest);
  }

  printf("\n");
  return 0;

}
