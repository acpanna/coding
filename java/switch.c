#include <stdio.h>

int main(void)
{
    int tag, monat, jahr;

    printf("Beispiel (3):\n\n");
    printf("Eingabe eines Tages (1-31): ");
    scanf("%d", &tag);
    printf("Eingabe einer Monatszahl (1-12): ");
    scanf("%d", &monat);
    printf("Eingabe einer Jahreszahl (00-99): ");
    scanf("%d", &jahr);

    printf("\nEs ist ");
    switch(monat)
    {
        default : printf("eine falsche Eingabe aufgetreten!\n");
                  break;
        case  3 :
        case  4 :
        case  5 : printf("Fruehling!\n");
                  break;
 
        case  7 :
        case  6 :
        case  8 : printf("Sommer!\n");
                  break;
 
        case  9 :
        case 10 :
        case 11 : printf("Herbst!\n");
                  break;
 
        case 12 :
        case  1 :
        case  2 : printf("Winter!\n");
    }

    if (!tag)
    {
      printf("Fehler! Den Tag 0 gibt es nicht!\n");
      tag = 1;
    }

    if (tag == 11 && monat == 11)
      printf("Es ist ausserdem Faschingsanfang!\n");
    else if (monat == 12)
    {
      if (tag == 6)
        printf("Es ist Nikolaus!\n");
      else if (tag == 24)
        printf("Es ist Heilig Abend!\n");
      else if (tag == 31)
        printf("Es ist Silvester!\n");
    }

    if (jahr <= 29)
      printf("Nach der Umrechnung ist das Jahr %d gemeint!\n", 2000 + jahr);
    else if (jahr > 69)
      printf("Nach der Umrechnung ist das Jahr %d gemeint!\n", 1900 + jahr);
    else
    {
      printf("Die Umrechnung laesst die Interpretation \n");
      printf("der zweistelligen Jahresangabe %d undefiniert!\n", jahr);
    }

    return 0;
}
