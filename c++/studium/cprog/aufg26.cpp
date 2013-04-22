/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 09
    Aufgabennr.   	: 26
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
#include <string.h>

#define MMAX 10
#define NMAX 10
#define MAX_STRING_LAENGE 100

struct PersonData
{
  char name[MAX_STRING_LAENGE+1];
  double einkommen;
};

void rotate(int m, int n, 
            double A[MMAX][NMAX], double A_rot[MMAX][NMAX]);
void besetze_array(int m, int n, double wert, double A[MMAX][NMAX]);
void besetze_struktur(char * name, double wert, struct PersonData * person);
void show_matrix(int zeilen, int spalten, double A[MMAX][NMAX]);
void show_struktur(struct PersonData person);

int main(void)
{
  int fehler = 0, zeilen, spalten;
  double A[MMAX][NMAX] = { 0.0 };
  struct PersonData chef = { "Hans Meier", 123456.99 };

  do
  {
    printf("Zeilenzahl der Matrix A: ");
    scanf("%d", &zeilen);
    if (zeilen < 1 || zeilen > MMAX)
    {
      fehler = 1;
      printf("Falsche Eingabe! Eingabe: %d, Grenzen sind: [%d, %d]\n",
             zeilen, 1, MMAX);
    }
    else
      fehler = 0;
  }
  while (fehler);

  printf("\n");
  do
  {
    printf("Spaltenzahl der Matrix A: ");
    scanf("%d", &spalten);
    if (spalten < 1 || spalten > NMAX)
    {
      fehler = 1;
      printf("Falsche Eingabe! Eingabe: %d, Grenzen sind: [%d, %d]\n",
             spalten, 1, NMAX);
    }
    else
      fehler = 0;
  }
  while (fehler);

  printf("\nMatrix A vor der Besetzung:\n");
  show_matrix(zeilen, spalten, A);
  printf("\nStruktur chef vor der Besetzung:\n");
  show_struktur(chef);

  besetze_array(zeilen, spalten, 1.0, A);
  besetze_struktur("Hans Meier-Schmidtke", 234567.99, &chef);

  printf("\nMatrix A nach der Besetzung:\n");
  show_matrix(zeilen, spalten, A);
  printf("\nStruktur chef nach der Besetzung:\n");
  show_struktur(chef);

  printf("\nRotieren der Spalten von Matrix A:\n");
  rotate(zeilen, spalten, A, A);
  show_matrix(zeilen, spalten, A);

  return 0;
}

void besetze_array(int m, int n, double wert, double A[MMAX][NMAX])
{
  int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      A[i][j] = i + j + wert;
}

void besetze_struktur(char * name, double wert, struct PersonData * person)
{
  strcpy((*person).name, name);
  (*person).einkommen = wert;
}

void rotate(int m, int n, 
            double A[MMAX][NMAX], double A_rot[MMAX][NMAX])
{
  int i, j;
  double temp[MMAX];

  for (i=0; i<m; i++)
    temp[i] = A_rot[i][0];

  for (j = 0; j < n-1; j++)
    for (i = 0; i < m; i++)
      A_rot[i][j] = A[i][j+1];

  for (i=0; i<m; i++)
    A_rot[i][n-1] = temp[i];
           
}

void show_matrix(int zeilen, int spalten, double A[MMAX][NMAX])
{
  int i, j;

  for (i = 0; i < zeilen; i++)
  {
    for (j = 0; j < spalten; j++)
      printf("  %.3e", A[i][j]);
    printf("\n");
  }
}

void show_struktur(struct PersonData person)
{
  printf("  Name der Person: %s\n", person.name);
  printf("  Jahreseinkommen: %f\n", person.einkommen);
}

/*
---------------------------------------------------------------------------------------

    Vorgenommene Änderungen :

Zeile 46 : Es wird nun ein Pointer auf die Struktur übergeben, vorher wurde
	   lediglich eine Kopie der Struktur an die Funktion übergeben, folglich
	   wirkten sich Änderungen (z.B. strcpy) nur auf die Kopie aus, das
	   Original aus der main() - Funktion blieb unberührt. Nun wird jedoch
	   beim Aufruf der Funktion die Adresse der Struktur übergeben, d.h.
	   das Original wird an die Funktion ausgehändigt und kann dort auch
	   "wirklich" verändert werden.

Zeile 93 : Die Funktion wird nun mit &chef aufgerufen (d.h. Adresse der Struktur
	   wird übergeben)
           
Zeile 118 : Da nun mit Pointern gearbeitet wird, muß der * vor person stehen,
	   da der * außerdem geringere Priorität wie . besitzt muß geklammert werden.

Zeile 119 : analog Zeile 118

rotate() - Funktion : Es wurde die erste Spalte nicht temporär abgespeichert und ging
	              somit verloren, nun erfolgt jedoch eine Abspeicherung der ersten
		      Spalte und abschließend wird der letzten Spalte diese temporäre
		      Spalte zugewiesen.

=======================================================================================
*/
