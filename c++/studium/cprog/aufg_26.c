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
void besetze_struktur(char * name, double wert, struct PersonData person);
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
  besetze_struktur("Hans Meier-Schmidtke", 234567.99, chef);

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

void besetze_struktur(char * name, double wert, struct PersonData person)
{
  strcpy(person.name, name);
  person.einkommen = wert;
}

void rotate(int m, int n, 
            double A[MMAX][NMAX], double A_rot[MMAX][NMAX])
{
  int i, j;

  for (j = 0; j < n-1; j++)
    for (i = 0; i < m; i++)
      A_rot[i][j] = A[i][j+1];
 
  for (i = 0; i < m; i++)
    A_rot[i][n-1] = A[i][0];
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
