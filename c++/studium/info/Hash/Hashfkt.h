#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"

#define ADDRESSRANGE 2000						 // Konstante fuer Groesse des Adressbereichs
#define KEYLENGTH      40                        // Konstante fuer maximale Laenge eines Schluesselwert - Strings

int read_file(char *dat);
void divisionsrest (int anzahl);
void quadrat (int anzahl, int zugriff);
void schiebefaltung (int anzahl, int zugriff);
void grenzfaltung (int anzahl, int zugriff);
void transform (int anzahl, int zugriff);
void save_file(char *dat);

extern C_list ueberlauf;
extern C_list eingabe;

extern int p;             
extern int kolission;     
extern int *arr;