import java.io.*;

public class Calcul
{
  static double erg;
  static BufferedReader br; 
  
  public static void main(String [] argv)
  {
    /* Simulation eines einfachen Taschenrechners */

    int wahl;
    double op = 0.0;
    erg = 0.0;
  
    // initialisiert Eingabe
    InputStreamReader isr = new InputStreamReader(System.in);
    br = new BufferedReader(isr);

    do
    {
        System.out.println();
        System.out.println("Speicherinhalt: " + erg);
        System.out.println();
        menue();
        System.out.println();
        System.out.println("Wahl: ");
        
        wahl =(int) getValue();

        if (wahl >= 1 && wahl <= 4)
        {
             System.out.println();
             System.out.println("  2. Zahl: ");
                   
             op = getValue();
        }

        try
        {
          switch (wahl)
          {
              case 0:  erg = 0.0;
                       System.out.println("  Speicher gel\u00f6scht!");
                       break;
              case 1:  erg += op;
                       break;
              case 2:  erg -= op;
                       break;
              case 3:  erg *= op;
                       break;
              case 4:  if (op == 0.0)
                       {
                         if (erg > 0)
                           throw new ArithmeticException();
                        else if (erg < 0)
                            throw new ArithmeticException();
                        else
                          throw new IllegalArgumentException();
                       }
                       else
                         erg /= op;
                       break;
              case 5:  if (erg < 0.0)
                              throw new IllegalArgumentException();
                       else if (erg == 0)
                          throw new ArithmeticException();
                       else
                         erg = Math.log(erg);
                       break;
              case 6:  double fx  = f_eigen(erg);
                       if (fx  == Double.POSITIVE_INFINITY)
                         throw new ArithmeticException();
                       else
                         erg = fx;
                       break;
              case 99: System.out.println("  Ende!");
                       break;
              default: System.out.println("  Falsche Eingabe!");
          }
        }
        catch(ArithmeticException exc)
        {
          System.out.println("\nErgebnis ist  (+) bzw. (-) Unendlich !\n");
        }
        catch(IllegalArgumentException exc)
        {
          System.out.println("\nErgebnis dieser Operation ist nicht definiert !\n");
          erg = 0.0;
        }
    }
    while (wahl != 99);

    // schliesst Eingabe
   closeInput();
  }

  public static void menue()
  {
    System.out.println("   0: Speicher l\u00f6schen");
    System.out.println("   1: Addition");
    System.out.println("   2: Subtraktion");
    System.out.println("   3: Multiplikation");
    System.out.println("   4: Division");
    System.out.println("   5: Logarithmus");
    System.out.println("   6: eigene Funktion");
    System.out.println("  99: Ende");
  }

  public static double f_eigen(double x)
  {
    if (x == 0.0)
      return Double.POSITIVE_INFINITY;
    else
      return 1.0/x;
  }

  public static double getValue()
  {
    Double dObj = null;
    String zeile = "";

    try
    {
      zeile = br.readLine();
      dObj = new Double(zeile);
    }
    catch (IOException exc)
    {
      System.err.println("\nFehler beim Einlesen!\n");
      System.exit(1);
    }
    catch (NumberFormatException exc)
    {
      System.err.println("\nFehler beim Umwandeln von \"" + zeile
                         + "\" in int bzw. double - Wert !\n");
      System.exit(2);
    }
    return dObj.doubleValue();
  }

  public static void closeInput()
  {
    try
    {

     br.close();
    }
    catch (IOException exc)
    {
      System.err.println("\nFehler beim Schlie\u00DFen der Eingabe !\n");
      System.exit(1);
    }
  }
}

