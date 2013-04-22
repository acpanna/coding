// importiert Java-I/O-Klassen
import java.io.*;

public class Aufg5
{
  static BufferedReader br;

  public static void main(String [] argv)
  {
    initInput();

    int tag, monat, jahr; 
 
    System.out.print("\nBeispiel (3):\n\n"); 
    System.out.print("Eingabe eines Tages (1-31): "); 
    
    tag = getIntValue(); 
 
    System.out.print("Eingabe einer Monatszahl (1-12): "); 
    
    monat = getIntValue(); 

    System.out.print("Eingabe einer Jahreszahl (00-99): "); 
    
    jahr = getIntValue(); 
    
    closeInput();
 
    System.out.print("\nEs ist "); 
    switch(monat) 
    { 
        default : System.out.print("eine falsche Eingabe aufgetreten!\n"); 
                  break; 
        case  3 : 
        case  4 : 
        case  5 : System.out.print("Fruehling!\n"); 
                  break; 
  
        case  7 : 
        case  6 : 
        case  8 : System.out.print("Sommer!\n"); 
                  break; 
  
        case  9 : 
        case 10 : 
        case 11 : System.out.print("Herbst!\n"); 
                  break; 
  
        case 12 : 
        case  1 : 
        case  2 : System.out.print("Winter!\n"); 
    } 
 
    if (tag == 0) 
    { 
      System.out.print("Fehler! Den Tag 0 gibt es nicht!\n"); 
      tag = 1; 
    } 
 
    if (tag == 11 && monat == 11) 
      System.out.print("Es ist ausserdem Faschingsanfang!\n"); 
    else if (monat == 12) 
    { 
      if (tag == 6) 
        System.out.print("Es ist Nikolaus!\n"); 
      else if (tag == 24) 
        System.out.print("Es ist Heilig Abend!\n"); 
      else if (tag == 31) 
        System.out.print("Es ist Silvester!\n"); 
    } 
 
    if (jahr <= 29) 
    {
      jahr += 2000;
      System.out.print("Nach der Umrechnung ist das Jahr " + jahr + " gemeint!\n");
    }
    else if (jahr > 69) 
    { 
       jahr += 1900;
       System.out.print("Nach der Umrechnung ist das Jahr " + jahr + " gemeint!\n");
    }
    else
    {
      System.out.print("Die Umrechnung laesst die Interpretation \n");       
      System.out.print("der zweistelligen Jahresangabe " + jahr + " undefiniert!\n");
    }  
    
    System.out.print("\n");
  }

  public static void initInput()
  {
    InputStreamReader isr = new InputStreamReader(System.in);
    br = new BufferedReader(isr);
  }

  public static void waitForReturn()
  {
    try
    {
      br.readLine();
    }
    catch (IOException exc)
    {
      System.err.println(exc);
      System.err.println("Fehler beim Einlesen!");
      System.exit(1);
    }
  }

  public static int getIntValue()
  {
    Integer iObj = null;
    String zeile = "";

    try
    {
      zeile = br.readLine();
      iObj = new Integer(zeile);
    }
    catch (IOException exc)
    {
      System.err.println(exc);
      System.err.println("Fehler beim Einlesen!");
      System.exit(1);
    }
    catch (NumberFormatException exc)
    {
      System.err.println(exc);
      System.err.println("Fehler beim Umwandeln von \"" + zeile
                         + "\" in int-Wert!");
      System.exit(2);
    }
    return iObj.intValue();
  }

  public static void closeInput()
  {
    try
    {
      br.close();
    }
    catch (IOException exc)
    {
      System.err.println(exc);
      System.err.println("Fehler beim Schlie\u00DFen der Eingabe!");
      System.exit(1);
    }
  }
}
