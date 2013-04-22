#include <stdio.h>
#include <stdlib.h>

int T;
int ZB;

struct baum {
  char wert;
  int lsohn;
  int rsohn;
} * baum;

int zaehl_blaetter(struct baum *baum, int &T);

int main(void)
{
   int i, anzahl;

   printf("\nBitte geben Sie die Anzahl der Knoten des Baumes ein : ");
   scanf("%d",&anzahl);

   baum = (struct baum *) malloc( anzahl * sizeof(struct baum));

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
       scanf(" %c",&baum[i].wert);
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

   ZB = zaehl_blaetter(baum,T);

   printf("\nDer Baum besitzt %d Blatt/Blätter.",ZB);

   return 0;

}

int zaehl_blaetter(struct baum *baum, int &T)
{
  int i;
  int vorgaenger, position, zaehler = 1;
    
  if (T == -1)
    return 0;

  position = T;

  for (i=0 ;; i++)
  {
    if (baum[T].lsohn == 0 && baum[T].rsohn == 0)
      return zaehler;

    if (baum[position].lsohn != 0)
      {
        vorgaenger = position;
        position = baum[position].lsohn;
      }
    else if (baum[position].rsohn != 0)
      {
        vorgaenger = position; 
	position = baum[position].rsohn;
      }
    else
      {
        zaehler = zaehler + 1;

        if (baum[vorgaenger].rsohn == position)
          baum[vorgaenger].rsohn = 0;

        if (baum[vorgaenger].lsohn == position)
	  baum[vorgaenger].lsohn = 0;

        if (baum[vorgaenger].lsohn == 0 && baum[vorgaenger].rsohn == 0)
	  zaehler = zaehler - 1;

	position = T;
      }
  }
  return zaehler;
}
            