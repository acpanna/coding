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
    Teilaufgabe   	: a)

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
  float test;
  float test2;

  test = 0.0f;
  test2 = 50.0f;


  printf("\nBitte drücken Sie RETURN um die größte darstellbare Float-Zahl zu ermitteln !");
  scanf("%c",&enter);

  for(test = 0.0f ;; test = test + 10.0f)
    {
      if (test2 == (float) pow(test,10))
        break;
      test2 = (float) pow(test,10);
      printf("      %g\n",test2);
    }
  
  printf("\nBitte drücken Sie RETURN um die kleinste darstellbare Float-Zahl zu ermitteln !");   
  scanf("%c",&enter);
  
  for(test = 1.0f ;; test = test + 10.0f) 
    { 
      if (test2 ==0)
        break;
      test2 = 1.0f/((float) pow(test,10)); 
      printf("      %g\n",test2); 
    } 
  
  printf("\n");
  return 0;

}
