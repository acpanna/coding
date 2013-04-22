#include "stdafx.h"
#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include "xlong.h"

C_xlong::C_xlong(const char *string)             // C_xlong-Konstruktor fuer
{                                                // Initialisierung mit 
 flength = strlen(string);                       // Zifferfolge 
 fval = new char[flength+1];                     // (gespeichert in Form 
                                                 //  eines Strings)
 if (fval == 0)
	speicher();
	 
 strcpy(fval, string);
}


C_xlong::C_xlong(int num_digits)                 // C_xlong-Konstruktor fuer
{                                                // C_xlong-Objekt mit
 flength = num_digits;                           // <num_digits> Stellen
 fval = new char[flength +1];                    // (vorbesetzt mit Nullen) 
 
 if (fval == 0)
 	speicher();
   
 for(int i=0 ; i<flength ; i++)                  // Initialisierung mit 0
   fval[i] = '0';
 fval[flength] = '\0';
}


C_xlong::C_xlong(void)                           // Standardkonstruktor
{
 flength = 0;
 fval = 0;
}


C_xlong::C_xlong(const C_xlong& value)           // C_xlong-Konstruktor fuer
{                                                // Initialisierung durch
 flength = value.flength;                        // C_xlong-Objekt
 fval = new char[flength+1];
 
 if (fval == 0)
 	speicher();
   
 strcpy(fval, value.fval);
}


C_xlong& C_xlong::operator =(const C_xlong& value)      
{                                              
 if(this == &value)                              // falls identische  
   return *this;                                 // Objekte
 
 flength = value.flength;                        // neue Groesse
 delete [] fval;                                 // altes Objekt loeschen
 fval = new char[flength+1];                     // neues Objekt anlegen
 
 if (fval == 0)
 	speicher();
   
 strcpy(fval, value.fval);                       // Zuweisung durchfuehren
 return *this;
}


C_xlong& C_xlong::operator =(const char *string)
{                                            
 flength = strlen(string);                       // neue Groesse
 delete [] fval;                                 // altes Objekt loeschen
 fval = new char[flength+1];                     // neues Objekt anlegen
 
 if (fval == 0)
 	speicher();
   
 strcpy(fval, string);                           // Zuweisung durchfuehren
 return *this;
}


C_xlong C_xlong::operator +(const C_xlong& value) const
{ 
 int new_length = flength >= value.flength ? flength+1 : value.flength+1;
                                                 // neue Groesse
 C_xlong result(new_length);                     // neues Objekt anlegen
 
 int uebertrag = 0;                              // Hilfsvariablen
 int index_1  = flength-1;
 int index_2  = value.flength-1;
 int index_re = new_length-1;

 while(index_1 >= 0 && index_2 >= 0)             // Addition der bei beiden  
                                                 // Objekten vorhandenen Stellen
 {
  int prov = fval[index_1--] + value.fval[index_2--] - 96 + uebertrag;
  uebertrag = prov/10;
  result.fval[index_re--] = 48 + prov%10;
 }

 while(index_1 >= 0)                             // sowie der nur beim ersten
                                                 // Objekt vorhandenen Stellen
 {
  int prov = (fval[index_1--]-48) + uebertrag;
  uebertrag = prov/10;
  result.fval[index_re--] = 48 + prov%10;
 }
 while(index_2 >= 0)                             // bzw. der nur beim zweiten 
                                                 // Objekt vorhandenen Stellen
 {
  int prov = (value.fval[index_2--]-48) + uebertrag;
  uebertrag = prov/10;
  result.fval[index_re--] = prov%10 + 48;
 }

 if(uebertrag)                                   // falls noch Uebertrag zu 
   result.fval[0] = uebertrag + 48;              // beruecksichtigen

 result.mini();                                  // fuehrende Nullen beseitigen
 return result;
}


C_xlong C_xlong::operator -(const C_xlong& value) const
{ 
 if(*this < value)
   return C_xlong("NEG");                        // falls negatives Ergebnis
   
 C_xlong tmp(value.compl(flength));              // 1-Komplement
 tmp = tmp + (C_xlong) "1";                      // 2-Komplement
 tmp = tmp + (*this);

 tmp.fval[0] = '0';                              // Ueberlauf beseitigen
 
 tmp.mini();                                     // fuehrende Nullen beseitigen
 return tmp;
}


C_xlong C_xlong::operator *(int factor) const    // Multiplikation mit
{                                                // EINSTELLIGER Zahl    
 if (factor<0 || factor>9)
 {
	 AfxMessageBox("Fehler in Funktion: Multiplikation von C_xlong mit Integer !",MB_OK|MB_ICONEXCLAMATION);
	 exit(1);
 }

 C_xlong result(flength+1);                      // neues Objekt anlegen 
 
 int uebertrag = 0;
 for(int index=flength-1 ; index>=0 ; index--)   // Stellenweise
 {                                               // Multiplikation mit factor
  int prov = factor * (fval[index]-48) + uebertrag;
  uebertrag = prov/10;
  result.fval[index+1] = prov%10 + 48;
 }
 if(uebertrag)                                   // falls noch Uebertrag zu
   result.fval[0] = uebertrag + 48;              // beruecksichtigen
 
 result.mini();                                  // fuehrende Nullen beseitigen
 return result;
}


C_xlong C_xlong::operator *(const C_xlong& value) const
{ 
 C_xlong result = 0;
 for(int i=flength-1 ; i>=0 ; --i)              
 {
  result = result + (value * (fval[i]-48)).shift(flength-1-i);
 }
 return result;
}


C_xlong C_xlong::operator %(const C_xlong& value) const 
{ 
 int test;
 char str[20];
 C_xlong tmp = value;
 tmp.mini();                                   
 
 if (strcmp(tmp.fval, "0") == 0)                 
    return C_xlong("0");
 
 C_xlong divident = *this;                       

 test = flength - tmp.flength + 1;

 if (test < 0)
	 test = 0;

 C_xlong result(test);
  
 int maximum = divident.flength - tmp.flength + 1;
 
 for(int start=maximum-1 ; start>=0 ; start--)   // Startposition fuer Zugriff
  {
   int j=0;
   tmp = value; tmp.mini();
   
   if(divident.flength-start > 0)
   { 
    while(tmp<(divident(0,divident.flength-start)+(C_xlong)"1"))
     { 
      tmp = tmp + value;
      j++;
     }
	sprintf(str,"%d",j);
	divident = divident - (value * C_xlong(str)).shift(start);
   }
   result.fval[maximum-1-start] = j+48;  
  }
 return divident;
}


ostream& operator <<(ostream& OS, const C_xlong& value)  
{  
 if(value.flength == 0) 
   return OS << "";                              // falls leeres C_xlong-Objekt
 return OS << value.fval;
}


C_xlong& C_xlong::shift(int num_digits)              
{                                     
 if (num_digits < 0)                             // Stellenverschiebung mgl.?
 {                   
 	AfxMessageBox("Fehler in Funktion: Shift eines C_xlong - Objekts !",MB_OK|MB_ICONEXCLAMATION);
	exit(1);
 }
                          
 C_xlong tmp(flength+num_digits);                // Hilfs-Objekt anlegen  
 for(int i=0 ; i<flength ; i++)                  // Stellenverschiebung
   tmp.fval[i] = fval[i];                        // durchfuehren
 delete [] fval;                                 // altes Objekt loeschen
 flength += num_digits;
 fval = new char[flength+1];                     // neues Objekt anlegen 
 
 if (fval == 0)
	speicher();
   
 strcpy(fval, tmp.fval);                         // Kopieren des Hilfs-Objekts

 return *this;
}


C_xlong& C_xlong::mini(void)                     // Beseitigung fuehrender
{                                                // Nullen
 int i = 0;
 while(fval[i] == '0' && i<flength-1)            // Anzahl der zu streichenden 
   i++;                                          // Nullen bestimmen,
                                                 // mind. eine Ziffer muss
                                                 // erhalten bleiben!!!
 if(i>0)                                         // falls Nullen zu streichen
   {
    C_xlong tmpo(fval+i);                        // Zeigerarithmetik : 
    *this = tmpo;                                // Nullen abschneiden
   }
 return *this;
}


int C_xlong::operator ==(const C_xlong& value) const 
{                                               
 if(this == &value)                              // falls identische Objekte
   return 1; 
 
 C_xlong val_1 = *this;   val_1.mini();          // Hilfsobjekte ohne 
 C_xlong val_2 = value;   val_2.mini();          // fuehrende Nullen
 

 return(!strcmp(val_1.fval, val_2.fval));        // (String-)vergleich
}


int C_xlong::operator !=(const C_xlong& value) const
{ 
 if(*this == value)                              // Test auf Gleichheit
   return 0;
 return 1;
} 


int C_xlong::operator <(const C_xlong& value) const  
{                                           
 if(this == &value)                              // falls identische Objekte
   return 0;
 
 C_xlong val_1 = *this;   val_1.mini();          // Hilfsobjekte ohne 
 C_xlong val_2 = value;   val_2.mini();          // fuehrende Nullen anlegen

 if(val_1.flength > val_2.flength)               // falls unterschiedliche
   return 0;                                     // Laengen (Groesser-Vergl.)

 if(val_1.flength < val_2.flength)               // falls unterschiedliche
   return 1;                                     // Laengen (Kleiner-Vergleich)
                                                 // bei gleichen Laengen
 if(strcmp(val_1.fval, val_2.fval) < 0)          // (String-)Vergleich
   return 1;

 return 0;      
}


C_xlong C_xlong::operator() (int position, int num_digits) const
{
 if (position<0 || position>=flength)            // Zugriffsposition muss 
 {
	AfxMessageBox("Fehler in Funktion: SubString - Zugriff auf C_xlong - Objekt !",MB_OK|MB_ICONEXCLAMATION);
    exit(1);
 }                                               // innerhalb des Objekts 
                                                 // liegen
 if(num_digits+position > flength)               // Ende des Zugriffs 
 {                                               // spaetestens mit Stringende  
	num_digits = flength - position;     
    //AfxMessageBox("WARNUNG: C_xlong::operator(), Substring abgeschnitten !",MB_OK|MB_ICONEXCLAMATION);
 }                                                             
 
 C_xlong tmp(num_digits);                        // Zielobjekt anlegen
 for(int i=position, j=0 ; j<num_digits ; ++i, ++j)
   tmp.fval[j] = fval[i];                        // Substring herauskopieren
 tmp.fval[j] = '\0';                             // Stringendezeichen anfuegen

 return tmp;
}


C_xlong C_xlong::invert(int position, int num_digits) const
{
 if (position<0 || position>=flength || num_digits<=0 || num_digits>=9)            // Zugriffsposition muss 
 {
	AfxMessageBox("Fehler in Funktion: Invertieren eines SubStrings von C_xlong - Objekt !",MB_OK|MB_ICONEXCLAMATION);
    exit(1);
 }
                                                 // Zugriff muss korrekt erfolgen, max. 8 Stellen herausgreifen
 if(num_digits+position > flength)               // Ende des Zugriffs
   {                                             // spaetestens mit Stringende
    num_digits = flength - position; 
    //AfxMessageBox("WARNUNG: C_xlong::operator(), Substring abgeschnitten !",MB_OK|MB_ICONEXCLAMATION);
   }
 
 C_xlong tmp(num_digits);                        // Zielobjekt anlegen
 for(int i=position+num_digits-1, j=0 ; j<num_digits ; --i, ++j)
   tmp.fval[j] = fval[i];                        // invertierten Substring
                                                 // umkopieren
 tmp.fval[j] = '\0';                             // Stringendezeichen anfuegen

 return tmp;
}


C_xlong C_xlong::compl(int size) const     
{                                             
 if (size <= 0)                                  // Zugriffsposition muss 
 {
	AfxMessageBox("Fehler in Funktion: Komplementbildung eines SubStrings von C_xlong - Objekt !",MB_OK|MB_ICONEXCLAMATION);
    exit(1);
 }                                               // korrekten Zugriff pruefen
 
 if(size < flength)                              // Zugriff mind. auf
   {                                             // gesamtes Objekt
    size = flength; 
    //AfxMessageBox("WARNUNG: C_xlong::compl(), zu wenig Stellen !",MB_OK|MB_EXCLAMATION);
   }
 
 C_xlong tmp(size);                              // Zielobjekt anlegen
 for(int i=flength-1, j=size-1 ; i>=0 ; --i, --j)
   tmp.fval[j] = 9-fval[i]+96;                   // 1-Komplement des Objekts
 for( ; j>=0 ; --j)                              // sowie der zusaetzlichen
   tmp.fval[j] = 9+48;                           // Stellen 

 tmp.mini();                                     // fuehrende Nullen beseitigen
 return tmp;
}


int C_xlong::getLength() const                   // Anzahl der Stellen eines
{                                                // C_xlong-Objekts ermitteln
 return flength;
}


long tolong(const C_xlong& value)                // C_xlong-Objekt in
{                                                // long-Objekt umwandeln
 if (value.flength<=0 || value.flength>=9)       // Zugriffsposition muss 
 {
	AfxMessageBox("Fehler in Funktion: Umwandlung eines C_xlong - Objekts in long - Zahl !",MB_OK|MB_ICONEXCLAMATION);
    exit(1);
 } 
	                                             // Abbruch bei Ueberlaufgefahr
                                                 // (bei mehr als 8 Stellen)
 long result = atol(value.fval);                 // Umwandlung durchfuehren
 return result;
}

