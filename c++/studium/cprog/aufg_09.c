#include <math.h>

/* exp-Berechnung im float-Fall */
float float_exp(float wert)
{
  return (float) exp(wert);
}

/* Wenn Sie zur Berechnung von 10^(-i) die Funktion pow() verwendet haben,
   nehmen Sie fuer float die Funktion float_pow() */
float float_pow(float x, float y)
{
  return (float) pow(x, y);
}
