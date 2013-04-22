#include <stdio.h>      

int main(void)
{
  FILE * fp;
  char bezeich[81], name[256];
  int weiter;
  /* hier fehlen Deklarationen */

  printf("Name des Eingabefiles: ");
  scanf("%s", name);

  /* Oeffnen des Files zum Lesen */
  fp = fopen(name, "r");
  if (fp == NULL)
  {
    printf("Datei mit Namen \"%s\" konnte nicht geoeffnet werden!\n",
	   name);
    return 1;
  }

  weiter = 1;
  /* Ende des Files noch nicht erreicht und kein Abbruch */
  while (!feof(fp) && weiter)
  {
    weiter = fscanf(fp, "%s %??", bezeich, &blz);
    /* 2 Variablen einlesen koennen? */
    weiter = (weiter == 2);
    if (weiter)
    {
      printf("%s %lu\n", bezeich, blz);

      fscanf(fp, "%s %??", bezeich, &kontonr);
      printf("%s %??\n", bezeich, kontonr);
      ...

      /* %*c ueberliest Leerzeichen zwischen Doppelpunkt und Zeichen */
      fscanf(fp, "%s%*c%??", bezeich, &bearb_kuerzel);
      printf("%s %??\n", bezeich, bearb_kuerzel);
  
      fscanf(fp, "%s %??", bezeich, &letzter_tag);
      printf("%s %??\n", bezeich, letzter_tag);
      ...
    }
  }
  printf("\n");
  /* Schliessen des Files */
  fclose(fp);

  return 0;
}
