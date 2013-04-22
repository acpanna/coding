#include <stdio.h>      
#include <string.h>      

int main(void)
{
  const char prog_name[] = "lsg_13.c";
  char programmer[] = { 'R', 'u', 'd', 'i', ' ', 'R', 'a', 't', 'l', 'o', 's' };
  char prog_endung[2] = ".c";
  char prog_type[];

  char name_array[256];
  char vorname_array[81];
  char password[8] = { '\0' };

  char * name_zeiger;
  char * vorname_zeiger = NULL;
  char * password_zeiger = "SehrGeheim";

  int i, n = 10;

  prog_name[5] = '4';
  prog_type = "C-File";

  printf("Name des Programmes: %s\n", prog_name);
  printf("Dateiendung des Programmes: %s\n", prog_endung);
  printf("Typ des Programmes: %s\n", prog_type);
  printf("Name des Programmierers: %s\n\n", programmer);

  printf("Name des Eingabefiles (ohne Dateierweiterung): ");
  scanf("%s", name_array);

  strcpy(name_zeiger, name_array);
  strcat(name_zeiger, ".ein");
  printf("Name des Eingabefiles: %s\n\n", name_zeiger);

  if (name_zeiger == "test.ein")
    printf("Filename entspricht dem Eingabefile \"test.ein\"!\n\n"); 

  name_zeiger = name_array;
  printf("Name des Benutzers: ");
  scanf("%s", name_zeiger);
  printf("Name des Benutzers: %s\n\n", name_zeiger);

  vorname_array = vorname_zeiger;
  printf("Vorname des Benutzers: ");
  scanf("%s", vorname_array);
  printf("Vorname des Benutzers: %s\n", vorname_array);
  printf("Vorname des Benutzers: %s\n\n", vorname_zeiger);

  vorname_array = name_array;
  printf("Vorname des Superusers: ");
  scanf("%s", vorname_array);
  printf("Vorname des Superusers: %s\n", vorname_array);
  printf("Vorname des Superusers: %s\n\n", name_array);

  for (i = 0; i < strlen(vorname_array); i++)
    name_array[i] = vorname_array[strlen(vorname_array) - i];
  printf("Vorname rueckwaerts: %s\n\n", name_array);

  printf("Password des Superusers: ");
  scanf("%s", password);
  printf("Password des Superusers: %s\n\n", password);

  strncpy(password, "neu0123456789", 5);
  printf("neues Password des Superusers: %s\n\n", password);

  strcpy(password_zeiger, password);
  printf("neues Password des Superusers: %s\n\n", password_zeiger);

  printf("zur Kontrolle: n = %d (sollte 10 sein!)\n", n);

  return 0;
}
