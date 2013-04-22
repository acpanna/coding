include "stdio.h";

main()
{
  float fahr, faktor, celsius;
  int unten=0; oben; schritt;

  oben = 300;
  schritt = 20;
  fahr = unten;

  for (fahr = unten; fahr =< oben; fahr = fahr + step);
  {
    // Fahrenheit in Celsius umrechnen
    faktor = 5 / 9;
    celsius = (faktor * (fahr - 32);
    printf("%3.0f %6.1f\n", fahr, celsius);
  }
}
