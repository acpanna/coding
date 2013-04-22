// importiert Java-I/O-Klassen
import java.io.*;

public class Aufgabe
{
  static BufferedReader br;

  public static void main(String [] argv)
  {
    int n;

    // initialisiert Eingabe
    initInput();

    // hier kommt das eigentliche Programm ...

    // wartet auf ein RETURN (und ueberliest alle vorigen Zeichen)
    waitForReturn();

    // liest int-Wert ein aus einer Zeile, die mit RETURN abgeschlossen wurde
    n = getIntValue();

    // schliesst Eingabe
    closeInput();
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
