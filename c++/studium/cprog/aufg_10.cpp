/* veraltet, aber viele Compiler verstehen es nur so:
  #include <fstream.h>

  // keine Zeile mit "using namespace std;"
*/

/* neuer C++-Standard: 
  #include <fstream>
  using namespace std;
*/

// Versuch einer automatischen Erkennung
#ifdef __GNUC__
#if (__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 8)
  #include <fstream>
  using namespace std;
#endif
  #include <fstream.h>
#else
#ifdef __WATCOMC__
  #include <fstream.h>
#else
  #include <fstream>
  using namespace std;
#endif
#endif

int main(void)
{
  ifstream fcin;
  char bezeich[81], name[256];
  bool weiter;
  /* hier fehlen Deklarationen */

  cout << "Name des Eingabefiles: ";
  cin >> name;

  /* Oeffnen des Files zum Lesen */
  fcin.open(name);
  if (fcin.fail())
  {
    cout << "Datei mit Namen \"" << name 
         << "\" konnte nicht geoeffnet werden!" << endl;
    return 1;
  }

  weiter = true;

  /* Ende des Files noch nicht erreicht und kein Abbruch */
  while (!fcin.eof() && weiter)
  {

    // ... Ueberlesen der Bezeichnung
    fcin >> bezeich;
    // ... Einlesen von blz
    // fcin ueberliest Leerzeichen zwischen Doppelpunkt und Wert automatisch        fcin >> blz;
    weiter = !fcin.fail();

    if (weiter)
    {
      cout << bezeich << " ";
      // ... Ausgabe von blz

      // ... Ueberlesen der Bezeichnung
      fcin >> ??; 
      // ... Einlesen von kontonr
      fcin >> ??; 
      cout << bezeich << " ";
      // ... Ausgabe von kontonr
      //...

      // ... Ueberlesen der Bezeichnung, Einlesen von bearb_kuerzel
      fcin >> bezeich;                   
      fcin >> bearb_kuerzel;                   
      // ... Ausgabe von bearb_kuerzel                    

      // ... Ueberlesen der Bezeichnung, Einlesen des unsigned char-Wertes
      //     fuer letzter_tag (Wie macht man das am besten?)
      fcin >> bezeich;                   
      fcin >> ??;                   
      // ... Ausgabe von letzter_tag                    
      //...
    }
  }
  cout << endl;
  /* Schliessen des Files */
  fcin.close();

  return 0;
}
