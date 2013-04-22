#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int T;

struct baum {
  int wert;
  int lsohn;
  int rsohn;
} *baum, *baumsort;

void sort(int &T);

int main(void)
{
   int anzahl, hoehe, i, k=0;
   
   printf("\nBitte geben Sie die Anzahl der Knoten des Baumes ein : ");
   scanf("%d",&anzahl);
   printf("\nBitte geben Sie die Höhe des Baumes ein : ");
   scanf("%d",&hoehe);

   if ((anzahl > pow(2,hoehe+1)-1) || (anzahl < hoehe+1))
     {
       printf("\n\n-- Eingabefehler -- \n\nKnotenanzahl ist größer bzw. kleiner als es die Höhe des Baums zuläßt !");
       exit(1);
     }

   baum     = (struct baum *) malloc(       anzahl       * sizeof(struct baum));   /* Speicherreservierung für Ursprungsbaum */
   baumsort = (struct baum *) malloc( (pow(2,hoehe+1)-1) * sizeof(struct baum));   /*          ~           für sort. Baum    */
 
   if (baum == 0 || baumsort == 0)
     {
       printf("\n\n-- Speicherreservierungsfehler (malloc) --");
       exit(1);
     }

   printf("\nEinige Anmerkungen zur Eingabe:\
           \nDer erste Knoten muß die Wurzel sein, außerdem müssen die\
	   \nKnotennummern der Söhne entsprechend der Eingabereihenfolge gewählt\
	   \nwerden, d.h. das Baumelement mit Knotennummer 3 ist der Knoten, \
	   \nder als drittes eingeben wurde.\
	   \nMan beachte, daß die Eingaberoutine keine Fehlerroutine beinhaltet,\
	   \nso führen fehlerhafte Eingaben, wie z.B. einer oder beide Söhne \
	   \neines Blattes ist/sind ungleich 0, oder eine Verletzung der \
	   \nDisjunktheit von Teilbäumen auf einer Stufe, eventuell zu einer\
	   \nFehlermeldung.\n");

   for(i=0; i<anzahl; i++)
     {
       printf("\nBitte geben Sie den Wert des %2d.-ten Knotens ein : ",i+1);
       scanf("%d",&baum[i].wert);
       printf("Bitte geben Sie die Knotennummer des linken\n\t\t\tSohnes ein (0 = kein Sohn) : ");
       scanf("%d",&baum[i].lsohn);
       printf("Bitte geben Sie die Knotennummer des rechten\n\t\t\tSohnes ein (0 = kein Sohn) : ");
       scanf("%d",&baum[i].rsohn);

       if (baum[i].lsohn != 0)
	 baum[i].lsohn = baum[i].lsohn - 1;
       if (baum[i].rsohn != 0)
         baum[i].rsohn = baum[i].rsohn - 1;
     }

   if (anzahl != 0)
     T = 0;
   else
     T = -1;
      
   for(i=0 ; i < pow(2,hoehe+1)-1 ; i++)      /* Formattierung des noch leeren sort. Baumes */
     {
       baumsort[i].wert = 0;
       baumsort[i].lsohn = (i+1)*2 - 1;
       baumsort[i].rsohn = (i+1)*2;
     }


   sort(T);                                 /* Sortierung des Baumes mit Startadresse T */
   
    
   printf("\nAusgabe:\n\n");

   for (i=0; i < pow(2,hoehe+1)-1 ; i++)                  
     {                                         
       if (i>=k*2+1)
	 {                                     /* Ausgabe des sortierten Baumes */
	   printf("\n");                       /*   stufenweise am Bildschirm   */
	   k = i;
         }

       printf("%3d ",baumsort[i].wert);
     }

   return 0;
}

void sort(int &T)
{
  int vorgaenger, position, zaehler = 1;
    
  position = T;

  while (T != -1)                                        /* Wenn Baum leer, kein Sortierung nötig */
    {
      if (baum[T].lsohn == 0 && baum[T].rsohn == 0)      /*     Wenn Baum nur aus Wurzel besteht     */
        {                                                /* erstes Element von baumsort = Wurzelwert */
          baumsort[0].wert = baum[T].wert;
	  break;
        }
							 /*     Ist linker Sohn != 0, merke momentane Pos.,      */
      if (baum[position].lsohn != 0)                     /*    gehe zum linken Sohn, verdopple zaehler (nach     */
	{                                                /* links im Baum gehen heißt Verdopplung der Knotennr.) */
          vorgaenger = position;
          position = baum[position].lsohn;
          zaehler = zaehler * 2;
        }
							 /*          Ist rechter Sohn != 0, merke momentane Pos.,           */
      if (baum[position].rsohn != 0)                     /*      gehe zum rechten Sohn, verdopple zaehler und addiere 1     */
	{                                                /* (nach rechts im Baum gehen heißt Verdopplung der Knotennr. + 1) */
          vorgaenger = position; 
	  position = baum[position].rsohn;
          zaehler = zaehler * 2 + 1;
        }

      if (baum[position].lsohn == 0 && baum[position].rsohn == 0) /* Ist lsohn u. rsohn = 0 -> Blatt */
        {
	  baumsort[zaehler-1].wert = baum[position].wert;          
	  baumsort[zaehler-1].lsohn = 0;
          baumsort[zaehler-1].rsohn = 0;

	  zaehler = 1;
      
          if (baum[vorgaenger].rsohn == position)     /*   Ist der rechte Sohn des Vorgängers die momentane Position,   */
            baum[vorgaenger].rsohn = 0;               /*   so wird dieser gleich 0 gesetzt, um im nächsten Durchlauf    */
                                                      /*         diese bereits 'kopierte' Position auszulassen.         */
          if (baum[vorgaenger].lsohn == position)     /* Ansonsten wird der linke Sohn des Vorgängers gleich 0 gesetzt. */
       	    baum[vorgaenger].lsohn = 0;

	  position = T;
        }
    }

  if (T != -1)   /* T zeigt aufs erste Element des sortierten Baumes, */
    T = 0;       /*       falls ursprüngl. Baum nicht leer war !      */
  
}

              