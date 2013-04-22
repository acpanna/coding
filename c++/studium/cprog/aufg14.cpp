/*
========================================================================


    Vorname       	: Heiko
    Name          	: Vogel
    Matrikelnummer	: 0854794
    Uebungsgruppe 	: mittwochs

    Benutzernummer	: c06
    e-mail-Adresse	: heiko.vogel@stud.uni-bayreuth.de

    Blatt Nr.     	: 05
    Aufgabennr.   	: 14
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

int main(void)
{
  char prog_name[] = "lsg_13.c";
  char programmer[] = { 'R', 'u', 'd', 'i', ' ', 'R', 'a', 't', 'l', 'o', 's', '\0' };
  char prog_endung[3] = ".c";
  char prog_type[]="C-File";

  char name_array[260];
  char vorname_array[81];
  char password[8] = { '\0' };

  char * name_zeiger;
  char * vorname_zeiger = NULL;
  char * password_zeiger = "SehrGeheim";

  int i, n = 10;

  prog_name[5] = '4';
  
  printf("Name des Programmes: %s\n", prog_name);
  printf("Dateiendung des Programmes: %s\n", prog_endung);
  printf("Typ des Programmes: %s\n", prog_type);
  printf("Name des Programmierers: %s\n\n", programmer);

  printf("Name des Eingabefiles (ohne Dateierweiterung): ");
  scanf("%255s", name_array);
    
  strcat(name_array,".ein");
  printf("Name des Eingabefiles: %s\n\n", name_array);

  
  if (name_zeiger == "test.ein")
    printf("Filename entspricht dem Eingabefile \"test.ein\"!\n\n"); 
  

  name_zeiger = name_array;
  printf("Name des Benutzers: ");
  scanf("%259s", name_zeiger);
  printf("Name des Benutzers: %s\n\n", name_zeiger);

  vorname_zeiger = vorname_array;
  printf("Vorname des Benutzers: ");
  scanf("%80s", vorname_array);
  printf("Vorname des Benutzers: %s\n", vorname_array);
  printf("Vorname des Benutzers: %s\n\n", vorname_zeiger);

  vorname_zeiger = name_array;
  printf("Vorname des Superusers: ");
  scanf("%259s", vorname_zeiger);
  printf("Vorname des Superusers: %s\n", vorname_zeiger);
  printf("Vorname des Superusers: %s\n\n", name_array);

  for (i = 0; i < strlen(vorname_array); i++)
    name_array[i] = vorname_array[strlen(vorname_array) - i - 1];

  printf("Vorname rueckwaerts: %s\n\n", name_array);

  printf("Password des Superusers: ");
  scanf("%7s", password);
  printf("Password des Superusers: %s\n\n", password);

  strncpy(password, "neu0123456789", 5);
  printf("neues Password des Superusers: %s\n\n", password);

  password_zeiger = password;
  printf("neues Password des Superusers: %s\n\n", password_zeiger);

  printf("zur Kontrolle: n = %d (sollte 10 sein!)\n", n);

  return 0;
}

/*
-----------------------------------------------------------------------------------------

Es wurden folgende Änderungen vorgenommen:

Zeile 36: char programmer[] = {'R','u','d','i',' ','R','a't','l','o','s','\0'};
	  -- abschließende Nullzeichen hat gefehlt

Zeile 37: prog_endung[3] = ".c";
	  -- 2 mußte durch drei ersetzt werden (wegen Nullzeichen)

Zeile 38: char prog_type[] = "C-File";
	  -- Initialisierung erfolgte erst später, besser jedoch am Anfang

Die Zeile zw. 50 und 53: prog_type = "C-File";
			 -- wurde gestrichen, weil Initialisierung nun in Zeile 38

Die Zeile zw. 58 und 60: strcpy(name_zeiger,name_array);
			 -- wurde gestrichen, weil für den Zeiger kein freier Platz
			    geschafft wurde

Zeile 73: vorname_zeiger = vorname_array;
	  -- zu anfangs stand die Zuweisung andersherum da, machte jedoch keinen Sinn,
	     weil Array nur einmal initialisiert werden kann !

Zeile 79: voranme_zeiger = name_array;
	  -- es wurde vorname_array erneut eine Adresse zugewiesen, geht jedoch das aus
	     demselben Grund wie in Zeile 73 nicht.

Zeile 82: printf("Vorname des Superusers %s\n",vorname_zeiger);
	  -- vorher stand vorname_array da, da jedoch Zeile 79 verändert wurde,
             muß diese Zeile auch verändert werden.

Zeile 79: password_zeiger = password
	  -- vorher stand strcpy da, ist jedoch Platzverschwendung, da password_zeiger
	     ja gleich auf das Originalpasswort zeigen kann !

-----------------------------------------------------------------------------------------
*/