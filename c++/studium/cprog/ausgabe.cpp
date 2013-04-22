/*
    NICHT vergessen:
      #include <iomanip.h> (veraltet)
    bzw.
      #include <iomanip>   (neuer C++-Standard)
*/

// ab jetzt: Ausgabe in Exponentialschreibweise, vgl. "%e" 
void ausgabe_exponent(void)
{
  cout.setf(ios::scientific, ios::floatfield);
}

// ab jetzt: Ausgabe in Festpunktschreibweise, vgl. "%f" 
void ausgabe_festpunkt(void)
{
  cout.setf(ios::fixed, ios::floatfield);
}

// ab jetzt: Ausgabe in variabler Schreibweise (Standard), vgl. "%g" 
void ausgabe_variabel(void)
{
  cout.setf(0, ios::floatfield);
}
