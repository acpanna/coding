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
   printf("\nBitte geben Sie die H�he des Baumes ein : ");
   scanf("%d",&hoehe);

   if ((anzahl > pow(2,hoehe+1)-1) || (anzahl < hoehe+1))
     {
       printf("\n\n-- Eingabefehler -- \n\nKnotenanzahl ist gr��er bzw. kleiner als es die H�he des Baums zul��t !");
       exit(1);
     }

   baum     = (struct baum *) malloc(       anzahl       * sizeof(struct baum));   /* Speicherreservierung f�r Ursprungsbaum */
   baumsort = (struct baum *) malloc( (pow(2,hoehe+1)-1) * sizeof(struct baum));   /*          ~           f�r sort. Baum    */
 
   if (baum == 0 || baumsort == 0)
     {
       printf("\n\n-- Speicherreservierungsfehler (malloc) --");
       exit(1);
     }

   printf("\nEinige Anmerkungen zur Eingabe:\
           \nDer erste Knoten mu� die Wurzel sein, au�erdem m�ssen die\
	   \nKnotennummern der S�hne entsprechend der Eingabereihenfolge gew�hlt\
	   \nwerden, d.h. das Baumelement mit Knotennummer 3 ist der Knoten, \
	   \nder als drittes eingeben wurde.\
	   \nMan beachte, da� die Eingaberoutine keine Fehlerroutine beinhaltet,\
	   \nso f�hren fehlerhafte Eingaben, wie z.B. einer oder beide S�hne \
	   \neines Blattes ist/sind ungleich 0, oder eine Verletzung der \
	   \nDisjunktheit von Teilb�umen auf einer Stufe, eventuell zu einer\
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

  while (T != -1)                                        /* Wenn Baum leer, kein Sortierung n�tig */
    {
      if (baum[T].lsohn == 0 && baum[T].rsohn == 0)      /*     Wenn Baum nur aus Wurzel besteht     */
        {                                                /* erstes Element von baumsort = Wurzelwert */
          baumsort[0].wert = baum[T].wert;
	  break;
        }
							 /*     Ist linker Sohn != 0, merke momentane Pos.,      */
      if (baum[position].lsohn != 0)                     /*    gehe zum linken Sohn, verdopple zaehler (nach     */
	{                                                /* links im Baum gehen hei�t Verdopplung der Knotennr.) */
          vorgaenger = position;
          position = baum[position].lsohn;
          zaehler = zaehler * 2;
        }
							 /*          Ist rechter Sohn != 0, merke momentane Pos.,           */
      if (baum[position].rsohn != 0)                     /*      gehe zum rechten Sohn, verdopple zaehler und addiere 1     */
	{                                                /* (nach rechts im Baum gehen hei�t Verdopplung der Knotennr. + 1) */
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
      
          if (baum[vorgaenger].rsohn == position)     /*   Ist der rechte Sohn des Vorg�ngers die momentane Position,   */
            baum[vorgaenger].rsohn = 0;               /*   so wird dieser gleich 0 gesetzt, um im n�chsten Durchlauf    */
                                                      /*         diese bereits 'kopierte' Position auszulassen.         */
          if (baum[vorgaenger].lsohn == position)     /* Ansonsten wird der linke Sohn des Vorg�ngers gleich 0 gesetzt. */
       	    baum[vorgaenger].lsohn = 0;

	  position = T;
        }
    }

  if (T != -1)   /* T zeigt aufs erste Element des sortierten Baumes, */
    T = 0;       /*       falls urspr�ngl. Baum nicht leer war !      */
  
}

              