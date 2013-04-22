#include <assert.h>
#include <stdio.h>

int main(void)
{
  int i, anz_read;
  size_t anzahl;
  double kurs, max_tages_kurs, min_tages_kurs;

  /* Array von String files mit den Filenamen definieren */
  /* dreidim. Array der Kurswerte definieren */
  ...

  FILE * fp_in;

  /* anzahl auf Anzahl der Filenamen setzen */
  ...

  for (i = 0; i < (int) anzahl; i++)
  {
    fp_in  = fopen(files[i], "r");
    assert(fp_in != NULL);
    printf("\n### Oeffne Datei \"%s\" zum Lesen!\n", files[i]);

    do
    {
      anz_read = fscanf(fp_in, "%lf %lf %lf", 
                        &kurs, &min_tages_kurs, &max_tages_kurs);
      if (anz_read == 3)
      {
        /* in dreidim. Array abspeichern */
        ...
      }
    }
    while (anz_read == 3);

    fclose(fp_in);
  }

  /* Aufruf der 4 Funktionen */
  ...
  return 0;
}
