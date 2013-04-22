#include "stdafx.h"
#include "Hash.h"
#include "Hashfkt.h"
#include "HashDlg.h" 
#include "AusgDlg.h"

C_list ueberlauf;								 // Deklaration globaler Ueberlaufliste	
C_list eingabe;									 // Deklaration globaler Eingabeliste


int p = ADDRESSRANGE;                            // Deklaration globaler Variable (für Größe des Adressbereichs)
int kolission = 0;                               // Deklaration globaler Variable (für Anzahl der Kollissionen)
int *arr = 0;                                    // Deklaration globaler int-Zeiger (Zeiger auf die Speicherstellen)


void ausgabe (int *arr)
{
    CAusgDlg dlg;
	dlg.DoModal();
}


int read_file(char *dat)                         // Einlesen der Schluesselwertmenge aus einer Datei          
{   
 char buffer[KEYLENGTH + 1];                     // Puffer
 int count = 0;                                  // Anzahl der eingelesenen Werte

 ifstream C_xlong_in;                            // Eingabestrom anlegen
 
 C_xlong_in.open(dat , ios::in | ios::nocreate);
                                                 // Datei fuer Eingabestrom oeffnen
 if(!C_xlong_in)                                 // falls Datei nicht zu oeffnen
 {                                               // bzw. nicht existent
   AfxMessageBox("Angegebene Datei konnte nicht geoeffnet werden !",MB_OK|MB_ICONEXCLAMATION);
   return 0;
 }

 while(C_xlong_in.getline(buffer, KEYLENGTH + 1))            // Werte aus Datei einlesen
 {                                               // eingelesenen Wert in verketteter
  if (eingabe.contain(buffer) == 0)
  {
	C_xstrlong tmp(buffer);
	eingabe.append(tmp);                         // Eingabeliste ablegen
    count++;                                     // Zaehler inkrementieren
  }  
 } 
 
 C_xlong_in.close();                             // Eingabestrom schliessen
 
 AfxMessageBox("Einlesevorgang erfolgreich abgeschlossen !",MB_OK|MB_ICONEXCLAMATION);
 
 return count;
}


void save_file(char *dat)                        // Speichern der Schluesselwertmenge          
{   
 ofstream fout;                                  // Ausgabestrom anlegen
 
 fout.open(dat , ios::out);
                                                 // Datei fuer Ausgabestrom oeffnen
 if(!fout)                                       // falls Datei nicht zu oeffnen
  {                                      
	AfxMessageBox("Angegebene Datei konnte nicht geschrieben werden !",MB_OK|MB_ICONEXCLAMATION);
    return;
  }
                                         
 eingabe.output(fout);                  
                  
 fout.close();                                   // Ausgabestrom schliessen
 
 AfxMessageBox("Schreibvorgang erfolgreich abgeschlossen !",MB_OK|MB_ICONINFORMATION);
}


void divisionsrest (int anzahl)
{ 
 kolission = 0;

 char divisor[20];

 sprintf(divisor,"%d",p);

 ueberlauf.remove();  // Loeschen der Kolissionsliste
 
 // Anlegen eines dynamischen Arrays von int-Werten fuer den Adressraum

 arr = new int[p];
 if (arr == 0)
	speicher();

 // Vorbelegen des Arrays mit -1

 for (int j = 0; j < p; j++)
  arr[j] = -1;  
 
 /* Durchfuehrung der Zuordnung mit Hilfe der Divisions-Rest-Methode */

 for (j = 0; j < anzahl; j++)
 {
   
   // Berechnung des jeweiligen Adressregisters durch Modulo-Division des
   // Schluesselwertes durch die Groesse des Adressraumes
   
   C_xlong dwarf = eingabe[j].finput % divisor;
   
   long index = tolong(dwarf);
  
   // Um zu verhindern, dass das errechnete Ergebnis den gewaehlten
   // Adressraum verlaesst, Modulo-Division des Ergebnisses durch die
   // Groesse des Adressraumes

   index = index % p;

   // Falls das ermittelte Register noch unbesetzt ist (Eintrag -1),
   // so wird, um Speicherplatz zu sparen, nur der Laufindex des jeweiligen
   // Schluesselwertes in dem erstellten Adressraum gespeichert

   if (arr[index] == -1)
	   arr[index] = j;

   // Falls das ertmittelte Register bereits belegt ist, so wird der
   // Schluesselwert an die Kolissionsliste angefuegt

   else
   {
     kolission++;
	 
	 C_xstrlong tmp(eingabe[j].keystr);
	
	 ueberlauf.append(tmp);
   }
 }

  ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Berechnung beendet!!!");

  // Aufruf der Ausgabefunktion

 ausgabe(arr);

 p = ADDRESSRANGE;

 return;
}

void quadrat (int anzahl, int zugriff)
{
 int start;

 kolission = 0;
 
 C_xlong quad;

 ueberlauf.remove();   // Loeschen der Kolissionsliste

 // Anlegen eines dynamischen Arrays von int-Werten fuer den Adressraum

 p = (int) pow(10, zugriff);
 arr = new int[p];
 
 if (arr == 0)
	speicher();
 
 // Vorbelegen des Arrays mit -1

 for(int j=0 ; j<p ; j++)
	 arr[j] = -1;

 /* Durchfuehrung der Zuordnung mit Hilfe der Mitte-des-Quadrats-Methode */
 
 for (int i = 0; i < anzahl; i++)
 {

  // Berechnung des Adressregisters durch quadrieren des jeweiligen
  // Schluesselwertes und anschliessendem herausgreifen der vom Benutzer
  // gewaehlten Anzahl von Ziffern aus der Quadratzahl.
  // Die so gewonnene Zahl gibt das Adressregister an.

  quad = eingabe[i].finput * eingabe[i].finput;
  start = quad.getLength()/2 - zugriff/2;
  
  C_xlong dwarf = quad(start,zugriff);
  
  unsigned int index = tolong(dwarf);

  // Um zu verhindern, dass das errechnete Ergebnis den gewaehlten
  // Adressraum verlaesst, Modulo-Division des Ergebnisses durch die
  // Groesse des Adressraumes

  index = index % p;

  // Falls das ermittelte Register noch unbesetzt ist (Eintrag -1),
  // so wird, um Speicherplatz zu sparen, nur der Laufindex des jeweiligen
  // Schluesselwertes in dem erstellten Adressraum gespeichert

  if (arr[index] == -1)
    arr[index] = i;

  // Falls das ertmittelte Register bereits belegt ist, so wird der
  // Schluesselwert an die Kolissionsliste angefuegt

  else
    {
     kolission++;
	 
	 C_xstrlong tmp(eingabe[i].keystr);
	
	 ueberlauf.append(tmp);
    }
 }

 ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Berechnung beendet!!!");

 // Aufruf der Ausgabefunktion
 ausgabe(arr);

 p = ADDRESSRANGE;	

 return;
}

void schiebefaltung (int anzahl, int zugriff)
{
 kolission = 0;

 ueberlauf.remove();   // Loeschen der Kolissionsliste

 // Anlegen eines dynamischen Arrays von int-Werten fuer den Adressraum

 arr = new int[p];
   
 if (arr == 0)
	speicher();

 // Vorbelegen des Arrays mit -1

 for(int j=0 ; j<p ; j++)
     arr[j] = -1;
   
 /* Durchfuehrung der Zuordnung mit Hilfe der Schiebefaltungs-Methode */
 
 // Um mit dieser Methode das Adressregister zu erhalten, wird jeder
 // Schluesselwert in Abschnitte unterteilt, deren Laenge der Benutzer
 // vorgeben kann. Diese werden anschliessend addiert und ergeben somit
 // das Adressregister.

 for (int i = 0; i < anzahl; i++)
 {
  long index = 0;
  int laufen = 0;

  for(int l=1 ; l<=((eingabe[i].finput.getLength() + (zugriff-1))/zugriff) ; l++)
              // Ermittlung der Anzahl der Abschnitte mit der vom
              // Benutzer gewaehlten Laenge
  {

   // Aufsummierung der Abschnitte

   index += tolong(eingabe[i].finput(laufen, zugriff));
   
   // Inkrementierung des Laufindex, um auf den naechsten Abschnitt
   // zugreifen zu koennen.

   laufen += zugriff;
  }
  
  // Um zu verhindern, dass das errechnete Ergebnis den gewaehlten
  // Adressraum verlaesst, Modulo-Division des Ergebnisses durch die
  // Groesse des Adressraumes
   
  index = index % p;
   
  // Falls das ermittelte Register noch unbesetzt ist (Eintrag -1),
  // so wird, um Speicherplatz zu sparen, nur der Laufindex des jeweiligen
  // Schluesselwertes in dem erstellten Adressraum gespeichert

  if (arr[index] == -1)
    arr[index] = i;

  // Falls das ertmittelte Register bereits belegt ist, so wird der
  // Schluesselwert an die Kolissionsliste angefuegt

  else
  {
     kolission++;
	 
	 C_xstrlong tmp(eingabe[i].keystr);
	
	 ueberlauf.append(tmp);
  }
 }

 // Aufruf der Ausgabefunktion

 ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Berechnung beendet!!!");

 ausgabe(arr);

 p = ADDRESSRANGE;

 return;
}

void grenzfaltung (int anzahl, int zugriff)
{
 kolission = 0;
 
 ueberlauf.remove();   // Loeschen der Kolissionsliste
 
 // Anlegen eines dynamischen Arrays von int-Werten fuer den Adressraum

 arr = new int[p];
  
 if (arr == 0)
	speicher();

 // Vorbelegen des Arrays mit -1

 for(int j=0 ; j<p ; j++)
   arr[j] = -1;

 /* Durchfuehrung der Zuordnung mit Hilfe der Schiebefaltungs-Methode */
 
 // aehnlich der vorangegangenen Methode wird hier ebenfalls jeder
 // Schluesselwert in Abschnitte mit beliebiger Laenge zerlegt. Allerdings
 // wird vor dem Aufsummieren jeder zweite Abschnitt invertiert.

 for (int i = 0; i < anzahl; i++)
 {
  C_xlong invers;
  long index = 0;
  int laufen = 0;

  for(int l=1 ; l<=((eingabe[i].finput.getLength() + (zugriff-1))/zugriff) ; l++)
              // Ermittlung der Anzahl der Abschnitte mit der vom
              // Benutzer gewaehlten Laenge

  {
   // Aufsummierung der "ungeraden" Abschnitte

   if(l%2 > 0)
     index += tolong(eingabe[i].finput(laufen, zugriff));

   // Invertierung aller "geraden" Abschnitte und anschliessendes Aufsummieren

   else
     {
	  invers = (eingabe[i]).finput.invert(laufen, zugriff);
      index = index + tolong(invers(0, zugriff));
     }

   // Inkrementierung des Laufindex um auf den naechsten Abschnitt
   // zugreifen zu koennen

   laufen += zugriff;
  }
  
  // Um zu verhindern, dass das errechnete Ergebnis den gewaehlten
  // Adressraum verlaesst, Modulo-Division des Ergebnisses durch die
  // Groesse des Adressraumes

  index = index % p;
  
  // Falls das ermittelte Register noch unbesetzt ist (Eintrag -1),
  // so wird, um Speicherplatz zu sparen, nur der Laufindex des jeweiligen
  // Schluesselwertes in dem erstellten Adressraum gespeichert
  
  if (arr[index] == -1)
    arr[index] = i;

  // Falls das ertmittelte Register bereits belegt ist, so wird der
  // Schluesselwert an die Kolissionsliste angefuegt

  else
    {
     kolission++;
	 
	 C_xstrlong tmp(eingabe[i].keystr);
	
	 ueberlauf.append(tmp);
    }
 }

 ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Berechnung beendet!!!");

 // Aufruf der Ausgabefunktion

 ausgabe(arr);

 p = ADDRESSRANGE;

 return;
}

void transform (int anzahl, int basis)
{
	int exp;
	long ind;
	char range[20];

    sprintf(range,"%d",p);

	kolission = 0;
 
    ueberlauf.remove();   // Loeschen der Kolissionsliste
  	     
 // Anlegen eines dynamischen Arrays von int-Werten fuer den Adressraum

 arr = new int[p];
  
 if (arr == 0)
	speicher();
 
 // Vorbelegen des Arrays mit -1

 for(int j=0 ; j<p ; j++)
   arr[j] = -1;

 /* Durchfuehrung der Zuordnung mit Hilfe der Basis-Transformations-Methode */
 
 // Hierbei wird jeder Schluesselwert in eine neue, vom Benutzer waehlbare
 // Basis transformiert (nach dem ueblichen Transformationsverfahren).

 for (int i = 0; i < anzahl; i++)
 {
  exp = 0;
  C_xlong index = 0;

  for(int l=(eingabe[i]).finput.getLength() - 1 ; l>=0 ; l--)
  {
   char str[20];
   sprintf(str,"%lu",(unsigned long) pow(basis, exp));
   index = index + ((eingabe[i]).finput(l, 1) * C_xlong(str)); 
  
   // Um zu verhindern, dass das errechnete Ergebnis den gewaehlten
   // Adressraum verlaesst, Modulo-Division des Ergebnisses durch die
   // Groesse des Adressraumes
   
   index = index % C_xlong(range);
   
   exp++;
  }

  ind = tolong(index);
  
  // Falls das ermittelte Register noch unbesetzt ist (Eintrag -1),
  // so wird, um Speicherplatz zu sparen, nur der Laufindex des jeweiligen
  // Schluesselwertes in dem erstellten Adressraum gespeichert

  if (arr[ind] == -1)
    arr[ind] = i;

  // Falls das ertmittelte Register bereits belegt ist, so wird der
  // Schluesselwert an die Kolissionsliste angefuegt

  else
  {
     kolission++;
	 
	 C_xstrlong tmp(eingabe[i].keystr);
	
	 ueberlauf.append(tmp);
  }
 }

 // Aufruf der Ausgabefunktion

 ((CHashDlg *) (theApp.m_pMainWnd))->setStatus("Status: Berechnung beendet!!!");
 
 ausgabe(arr);

 p = ADDRESSRANGE;

 return;
}


