/* veraltet, aber viele Compiler verstehen es nur so:
  #include <iostream.h>
  #include <string.h>

  // keine Zeile mit "using namespace std;"
*/

/* neuer C++-Standard:
  #include <iostream>
  #include <cstring>
  using namespace std;
*/

// Versuch einer automatischen Erkennung
#ifdef __GNUC__
#if (__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8)
  #include <iostream>
  #include <cstring>
  using namespace std;
#endif
  #include <iostream.h>
  #include <string.h>
#else
#ifdef __WATCOMC__
  #include <iostream.h>
  #include <string.h>
#else
  #include <iostream>
  #include <cstring>
  using namespace std;
#endif
#endif

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

  cout << "Name des Programmes: " << prog_name << endl;
  cout << "Dateiendung des Programmes: " << prog_endung << endl;
  cout << "Typ des Programmes: " << prog_type << endl;
  cout << "Name des Programmierers: " << programmer << endl << endl;

  cout << "Name des Eingabefiles (ohne Dateierweiterung): ";
  cin >> name_array;

  strcpy(name_zeiger, name_array);
  strcat(name_zeiger, ".ein");
  cout << "Name des Eingabefiles: " << name_zeiger << endl << endl;

  if (name_zeiger == "test.ein")
    cout << "Filename entspricht dem Eingabefile \"test.ein\"!" << endl << endl; 

  name_zeiger = name_array;
  cout << "Name des Benutzers: ";
  cin >> name_zeiger;
  cout << "Name des Benutzers: " << name_zeiger << endl << endl;

  vorname_array = vorname_zeiger;
  cout << "Vorname des Benutzers: ";
  cin >> vorname_array;
  cout << "Vorname des Benutzers: " << vorname_array << endl;
  cout << "Vorname des Benutzers: " << vorname_zeiger << endl << endl;

  vorname_array = name_array;
  cout << "Vorname des Superusers: ";
  cin >> vorname_array;
  cout << "Vorname des Superusers: " << vorname_array << endl;
  cout << "Vorname des Superusers: " << name_array << endl << endl;

  for (i = 0; i < strlen(vorname_array); i++)
    name_array[i] = vorname_array[strlen(vorname_array) - i];
  cout << "Vorname rueckwaerts: " << name_array << endl << endl;

  cout << "Password des Superusers: ";
  cin >> password;
  cout << "Password des Superusers: " << password << endl << endl;

  strncpy(password, "neu0123456789", 5);
  cout << "neues Password des Superusers: " << password << endl << endl;

  strcpy(password_zeiger, password);
  cout << "neues Password des Superusers: " << password_zeiger << endl << endl;

  cout << "zur Kontrolle: n = " << n << " (sollte 10 sein!)" << endl;

  return 0;
}
