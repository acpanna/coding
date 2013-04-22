#include <math.h>
#include <stdio.h>

/* Kleiner Taschenrechner fuer komplexe Zahlen
   Version mit Prozeduren */

struct komplex {
                 double re, im;
               };

struct komplex add(struct komplex x, struct komplex y);
struct komplex sub(struct komplex x, struct komplex y);
struct komplex mult(struct komplex x, struct komplex y);
struct komplex divi(struct komplex x, struct komplex y);
struct komplex komplement(struct komplex x);
double real_teil(struct komplex x);
double imag_teil(struct komplex x);
double betrag(struct komplex x);

int main(void)
{
  int wahl;
  struct komplex x = { 0.0, 0.0}, y;  

  printf("Speicherinhalt: %g\n", x.re);

  do
  {
    printf("\n  0: Speicher loeschen\n");
    printf("  1: Addition einer Zahl zur gespeicherten Zahl\n");
    printf("  2: Subtraktion einer Zahl von der gespeicherten Zahl\n");
    printf("  3: Multiplikation einer Zahl zur gespeicherten Zahl\n");
    printf("  4: Division der gespeicherten Zahl durch eine Zahl\n");
    printf("  5: Komplement der gespeicherten Zahl\n");
    printf("  6: Realteil der gespeicherten Zahl\n");
    printf("  7: Imaginaerteil der gespeicherten Zahl\n");
    printf("  8: Betrag der gespeicherten Zahl\n");
    printf("  9: Ende\n");

    printf("\nWahl der Operation: ");
    scanf("%d", &wahl);

    if ((wahl >= 1) && (wahl <= 4))
    {
      printf("Zahl: \n");
      printf("  Realteil: ");
      scanf("%lf", &y.re);
      printf("  Imaginaerteil: ");
      scanf("%lf", &y.im);
    }

    switch (wahl)
    {
      case 0 : x.re = 0.0;
               x.im = 0.0;
               break;
      case 1 : x = add(x, y);
               break;
      case 2 : x = sub(x, y);
               break;
      case 3 : x = mult(x, y);
               break;
      case 4 : x = divi(x, y);
               break;
      case 5 : x = komplement(x);
               break;
      case 6 : x.re = real_teil(x); x.im = 0.0;
               break;
      case 7 : x.re = imag_teil(x); x.im = 0.0;
               break;
      case 8 : x.re = betrag(x); x.im = 0.0;
               break;
      case 9 : break;
      default: printf("\n  Falsche Eingabe!\n");
               continue;   /* Ueberspringe Rest der do-while-Schleife */
    }

    if (wahl == 9)
      printf("\nEndergebnis: %g", x.re);
    else
      printf("\nZwischenergebnis: %g", x.re);
    
    if (x.im > 0)
      printf(" + %g i\n", x.im);
    else
      if (x.im == 0)
        printf("\n");
      else
        printf(" - %g i\n", -x.im);
  }
  while (wahl != 9);

  return 0;
}

struct komplex add(struct komplex x, struct komplex y)
{
  x.re += y.re;
  x.im += y.im;
  return x;
}

struct komplex sub(struct komplex x, struct komplex y)
{
  x.re -= y.re;
  x.im -= y.im;
  return x;
}

struct komplex mult(struct komplex x, struct komplex y)
{
  struct komplex z;

  z.re = x.re*y.re - x.im*y.im;
  z.im = x.re*y.im + x.im*y.re;
  return z;
}

struct komplex divi(struct komplex x, struct komplex y)
{
  double abs_val_squared;
  struct komplex z;

  abs_val_squared = betrag(y);
  abs_val_squared *= abs_val_squared;
  if (abs_val_squared == 0.0)
  {
    printf("Division durch Null nicht erlaubt! Keine Operation!\n");
    z = x;
  }
  else
  {
    z.re = ( x.re*y.re + x.im*y.im)/abs_val_squared;
    z.im = (-x.re*y.im + x.im*y.re)/abs_val_squared;
  }
  return z;
}

struct komplex komplement(struct komplex x)
{
  x.im = -x.im;
  return x;
}

double real_teil(struct komplex x)
{
  return x.re;
}

double imag_teil(struct komplex x)
{
  return x.im;
}

double betrag(struct komplex x)
{
  return sqrt(pow(x.re, 2) + pow(x.im, 2));
}
