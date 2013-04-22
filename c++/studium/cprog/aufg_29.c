
/* hier fehlen Include-Files, Prototypen ... */

int main(void)
{
  int color;
  
  /* hier fehlen Definition von Variablen, ... */

  /* Definition eines Filepointers zum Umgang mit anzulegender Datei */
  FILE * fp;

  /* Versuch, Datei "fraktneu.dat" zum Schreiben zu oeffnen */
  fp = fopen("fraktneu.dat", "w");
  if (fp == NULL)
  {
    printf("Konnte Datei \"fraktneu.dat\" nicht zum Schreiben oeffnen!\n"
           "Abbruch!\n");
    exit(1);
  }
  
    /* ... in for-Schleife */                 
    /* Farbe speichern in einer Zeile der Datei */
    fprintf(fp, "%d ", color);

    /* ... Zeile abschliessen mit Newline */
    fprintf(fp, "\n");

  /* ... Datei schliessen */  
  fclose(fp);   

  printf("Fraktal wurde in \"fraktneu.dat\" gespeichert!\n");
  
  return 0;
}
