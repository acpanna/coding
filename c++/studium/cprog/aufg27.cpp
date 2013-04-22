/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 09
    Aufgabennr.   	: 27
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

#include <assert.h>
#include <stdio.h>

#define TAGE 360

void cax(double CAX[10][TAGE], double matrix[10][TAGE][3], int welche);
double mittel(double matrix[10][TAGE][3], int welche);
double hoch(double matrix[10][TAGE][3], int welche);
double tief(double matrix[10][TAGE][3], int welche);

int main(void)
{
  char enter;
  size_t anzahl = 10;
  int i, j, aktie, anz_read;
  double kurs, max_tages_kurs, min_tages_kurs;

  char files[10][20] = {"apple_kurs.dat", "compaq_kurs.dat", "hp_kurs.dat",
			"ibm_kurs.dat", "intel_kurs.dat", "microsoft_kurs.dat", "novell_kurs.dat",
			"sap_kurs.dat", "sun_kurs.dat","yahoo_kurs.dat"};
    
  double Kurs[10][TAGE][3];
  double CAX[10][TAGE];
    
  FILE * fp_in;

  for (i = 0; i < (int) anzahl; i++)
  {
    j = 0;
    fp_in  = fopen(files[i], "r");
    assert(fp_in != NULL);
    printf("\n### Oeffne Datei \"%s\" zum Lesen!\n", files[i]);

    do
    {
      anz_read = fscanf(fp_in, "%lf %lf %lf", 
                        &kurs, &min_tages_kurs, &max_tages_kurs);
      if (anz_read == 3)
      {
	Kurs[i][j][0] = kurs;
	Kurs[i][j][1] = min_tages_kurs;
	Kurs[i][j][2] = max_tages_kurs;
        j++;
      }
    }
    while (anz_read == 3);

    fclose(fp_in);
  }

  for (i=0; i<10; i++)
    printf("\n%25s   %d",files[i],i);
  
  printf("\n\nDie Kurse welcher Aktie werden gewünscht : ");
  scanf("%d",&aktie);

  printf("\n                       Jahrestiefststand :  %lg",tief(Kurs,aktie));
  printf("\n                       Jahreshöchststand :  %lg",hoch(Kurs,aktie));
  printf("\nMittelwert des Schlußkurs (über 30 Tage) :  %lg",mittel(Kurs,aktie));

  printf("\n\nBitte RETURN drücken zur Ausgabe der CAX-Werte !");
  fflush(stdin);
  scanf("%c",&enter);

  cax(CAX,Kurs,aktie);

  j = 0;

  for(i=0; i<TAGE; i++)
  {
    j++;
    printf("\n%lg",CAX[aktie][i]);

    if (j==20)
    {
      printf("\n\nBitte RETURN drücken !");
      fflush(stdin);
      scanf("%c",&enter);
      j = 0;
    }

  }
   
  return 0;
}


double tief(double matrix[10][TAGE][3], int welche)
{
  int j;
  double erg = matrix[welche][0][1];

  for (j=0; j<TAGE; j++)
    if (matrix[welche][j][1] < erg)
      erg = matrix[welche][j][1];

  return erg;
}


double hoch(double matrix[10][TAGE][3], int welche)
{
  int j;
  double erg = matrix[welche][0][2];

  for (j=0; j<TAGE; j++)
    if (matrix[welche][j][1] > erg)
      erg = matrix[welche][j][2];

  return erg;
}


double mittel(double matrix[10][TAGE][3], int welche)
{
  int j;
  double erg = 0.0;

  for (j=TAGE-31; j<TAGE; j++)
    erg += matrix[welche][j][0];

  erg /= 30.0;

  return erg;
}


void cax(double CAX[10][TAGE], double matrix[10][TAGE][3], int welche)
{
  int j;

  for (j=0; j<TAGE; j++)
    CAX[welche][j] = (matrix[welche][j][0] + matrix[welche][j][1] + matrix[welche][j][2])/3.0;
}


   
