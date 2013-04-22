#include "stdafx.h"
#include <iostream.h>
#include "list.h"
#include <math.h>


C_xstrlong::C_xstrlong(char *nstring)  
{									   	
	char dualzahl[9];				   
	char *dual;						 
	int dec;
	
	dual = new char[8 * strlen(nstring) + 1];

    if (dual == 0)
		speicher();

 	dual[0] = '\0';

	for (int i = strlen(nstring)-1; i >= 0; i--)
	{
		                                         // Hier werden die einzelnen Buchstaben
		dec = nstring[i];					     // der eingegebenen/eingelesenen Strings	
												 // in ASCII - Codes umgewandelt,	
		
		for(int j=7;j>=0;j--)
		{
			if ((int) pow(j,2) & dec)			 // und in Dualzahlen umgerechnet.
				dualzahl[j] = '1';
			else
				dualzahl[j] = '0';
		}
		dualzahl[8] = '\0';

		strcat(dual,dualzahl);                   // Aneinanderreihung der Dualzahlen
	}

	for (i=strlen(dual)-1; i > 0; i--)           // Schliesslich werden die aneinandergereihten
	{									         // Dualzahlen in ein C_xlong - Objekt umgewandelt
		if (dual[i] == '1')				         // (dann wieder im Dezimalformat)
		{
			C_xlong tmp("1");
		
			for (int j=i; j > 0; j--)
				tmp = tmp + tmp;

			finput = finput + tmp;
		}
	}

    if (dual[0] == '1')
		finput = finput + C_xlong("1");

   	finput = finput.mini();

	keystr = new char[strlen(nstring)+1];

    if (keystr == 0)
		speicher();

	strcpy(keystr, nstring);
}


C_xstrlong& C_xstrlong::operator =(C_xstrlong& value)       
{											       
 if(this == &value)                                
   return *this;                                 
 
 finput = value.finput;  
 
 delete [] keystr;
 keystr = new char[strlen(value.keystr) + 1];
 
 if (keystr == 0)
	speicher();

 strcpy(keystr, value.keystr);

 return *this;
}


C_xstrlong& C_list::operator[](int index) const      
{                                                // Zugriff auf bestimmtes Element der verketteten Liste 
 C_element *act = fbasis;

 for(int i=0 ; i<index ; i++)                    // Durchlaufen der Liste bis
 {                                               // zum angegebenen Index 
   if (act->fnext == 0)
   	   break;
   
   act = act->fnext;                           
 }                                                  
 return act->xstrlong;                           
}

 
void C_list::append(C_xstrlong & value)          // Einfuegen am Ende der verketteten Liste 
{                                              
 C_element *act = new C_element(value);          // neues Listenelement anlegen
 
 if (act == 0)
	speicher();

 if (fbasis == 0)                                // neuer Listenkopf, falls
   fbasis = act;                                 // leere Liste
 else                                            // sonst
   fend->fnext = act;                            // neues Listenende
	
 fend = act;
 
 anzahl++;
	
 return;
}


void C_list::remove()                            // Loeschen der gesamten
{                                                // verketteten Liste
 C_element *act = fbasis;

 while(act)                                      // Durchlaufen der Liste
 {                                               // und Loeschen des jeweils
  C_element *tmp = act;                          // vorhergehenden Elements
  act = act->fnext;
  delete tmp;
  tmp = 0;
 }
 
 fbasis = fend = 0;                              // Zuruecksetzen der Zeiger
 anzahl = 0;
 return;                                         // fuer Listenkopf und -ende
}


int C_list::remove(C_xstrlong & value)           // Entfernen eines vorgegebenen Elements
{                                                // Rueckgabe: Anzahl der entfernten Elemente
 C_element *act = fbasis;                       
 C_element *prev = 0;

 int counter = 0;        

 if (fbasis == 0)                             
    return 0;                              
 else        
 {
	while(act != 0)
    {
		if (strcmp(act->xstrlong.keystr, value.keystr) == 0)
		{
			if (prev != 0)
			{
				if (act == fend)
					fend = prev;
				
				prev->fnext = act->fnext;
			}

			else
			{
				C_element *tmp = act->fnext;
				fbasis = tmp;
			}

			delete act;
			act = 0;
			anzahl--;
			counter++;
			break;
		}
		
		prev = act;
		act = act->fnext;
    }
 }

 return counter;
}


bool C_list::empty() const                    // Ueberpruefung auf leere Liste
{
 return fbasis==0 ? true : false;
}


bool C_list::contain(char *value)
{
  if(fbasis==0)                                  // false, falls leere Liste
   return false;
  if(strcmp( fbasis->xstrlong.keystr, value) == 0 )
   return true;                               
 
 C_element *act = fbasis->fnext;
 for( ; act!=0 ; act=act->fnext)                 // Durchsuchen der Liste
   if(strcmp(act->xstrlong.keystr, value) == 0)
	   return true;
 
 return false;
}


void C_list::output(CListBox *list)              // Ausgabe der verketteten Liste
{                                               
 for(C_element *act=fbasis ; act ; act=act->fnext)
	 list->AddString(act->xstrlong.keystr);      // Durchlaufen der kompletten verketteten Liste                   
  
 return;
}


void C_list::output(ostream &fout)
{
	 for(C_element *act=fbasis ; act ; act=act->fnext)
	   fout << act->xstrlong.keystr << "\n";     // Durchlaufen der kompletten verketteten Liste                   
  
     return;
}