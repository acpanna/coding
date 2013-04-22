// importiert Java-I/O-Klassen
import java.io.*;

public class Aufg6
{
  static BufferedReader br;

  public static void main(String [] argv)
  {
    initInput();

    char b; 
    char c = 'Ä'; 
    short s = (short) (1 << 15); 
    short i = (short) (1 << 15); 
    double d; 
     
    System.out.print("## Test mit ganzzahligen Werten:\n"); 
//  System.out.print(" uninitialisiertes b = " + b + "\n"); 
    b = 127; 
    System.out.print(" b = " + (int) b + "\n"); 
    System.out.print("## nach b++:\n"); 
    b++; 
    System.out.print(" b = " + (int) b + "\n"); 
    System.out.print(" s = " + s + "\n"); 
    System.out.print(" i = " + i + "\n\n"); 
    waitForReturn(); 
 
    System.out.print("## Test mit Zeichen:\n"); 
    System.out.print(" c = " + c + "\n"); 
    if ((int) c >= 128) 
      System.out.print(" ASCII-Code von c = " + (int) c + "\n\n"); 
    else 
    {
      c += 256;
      System.out.print(" ASCII-Code von c = " + c + "\n\n"); 
    }
    waitForReturn();
         
    System.out.print("## Test mit Fließkommawerten:\n"); 
    d = 1e308; 
    System.out.print(" d = " + d + "\n"); 
    System.out.print("## nach d *= 10:\n"); 
    d *= 10; 
    System.out.print(" d = " + d + "\n"); 
    System.out.print("## nach d = -d:\n"); 
    d = -d; 
    System.out.print(" d = " + d + "\n\n"); 
    waitForReturn();
 
    System.out.print("## versehentliches 1/0 bzw. 0/0:\n"); 
    System.out.print("## double/int:\n"); 
    for (i = 5; i > 0; i--) 
    { 
      d = i; 
      System.out.print("d = i = " + i + ", d/(i-1) = " + d/(i-1) + "\n");
    } 
    System.out.print("## setze d auf 0.0:\n"); 
    d = 0.0; 
    System.out.print("d = i = " + i + ", d/i = " + d/i + "\n\n");  
    waitForReturn();
    
    System.out.print("## int/int:\n"); 
/* 
    for (i = 5; i > 1; i--) 
*/ 
    for (i = 5; i > 0; i--) 
      System.out.print("i = " + i + ": i/(i-1) = " + i/(i-1) + "\n");
/* 
    i = 0; 
*/ 
    System.out.print("i/i = " + i/i + "\n");
    
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
