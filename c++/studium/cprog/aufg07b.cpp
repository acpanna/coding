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
    Teilaufgabe   	: b)

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

  test = 0.0;
  test2 = 50.0;


  printf("\nBitte drücken Sie RETURN um die größte darstellbare Double-Zahl zu ermitteln !");
  scanf("%c",&enter);

  for(test = 0.0 ;; test = test + 10000000000000000000000000000.0)
    {
      if (test2 == pow(test,10))
        break;
      test2 = pow(test,10);
      printf("      %g\n",test2);
    }
  
  printf("\nBitte drücken Sie RETURN um die kleinste darstellbare Double-Zahl zu ermitteln !");   
  scanf("%c",&enter);
  
  for(test = 1.0 ;; test = test + 10000000000000000000000000000.0) 
    { 
      if (test2 ==0)
        break;
      test2 = 1.0/pow(test,10); 
      printf("      %g\n",test2); 
    } 

  printf("\n");
  return 0;

}
