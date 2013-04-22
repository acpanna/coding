public class Abs
{
  public static void main(String argv[])
  {
    int izahl = -5;
    long lzahl = -354677874;
    float fzahl = -5.0f;
    double dzahl = -11330.5467;

    izahl = Math.abs(izahl);           // abs() - Methode der Klasse Math ist "ueberladen",
    lzahl = Math.abs(lzahl);           // d.h. abs() kann mit verschiedenen Parametern 
    fzahl = Math.abs(fzahl);          // (int, long, float, double - Werten) aufgerufen werden.
    dzahl = Math.abs(dzahl);

    System.out.println("abs() einer Integer-Zahl: "+ izahl +", long-Zahl: "+ lzahl +", float-Zahl: "+ fzahl +", double-Zahl: "+ dzahl);
  }
} 