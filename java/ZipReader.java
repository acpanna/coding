import java.io.*;
import java.util.*;
import java.util.zip.*;

public class ZipReader
{
  static BufferedReader br;
  static boolean inputOpened = false;
  // Konstanten fuer menue()
  static final int GROESSE = 1, NAMEN = 2, LISTING = 3, 
                   SCHLIESSEN = 4, ENDE = 5;
  
  public static void main(String [] argv) 
  {
    // Oeffnen des ZIP-Archivfiles
    ZipFile archiv = null;
    
    try
    {
      archiv = new ZipFile(argv[0]);
    }
    catch(ArrayIndexOutOfBoundsException exc)
    {
      System.err.println("Es wurde keine ZIP - File in der Kommandozeile mit angegeben   --  Abbruch");
      System.exit(1);
    }
    catch(ZipException exc) 
    {
      System.err.println("ZIP - Format - Fehler  --   Abbruch");
      System.exit(1);
    }
    catch(SecurityException exc) 
    {
      System.err.println("Kein Zugriffsrecht auf dieses File  --   Abbruch");
      System.exit(1);
    }
    catch(IOException exc) 
    {
      System.err.println("I/O - Fehler beim Oeffnen des ZIP - Files  --   Abbruch");
      System.exit(1);
    }
      
    int wahl;
    
    do
    {
      wahl = menue();
      switch(wahl)
      {
        case GROESSE: 
                      System.out.println("Gr\u00F6\u00DFe in Bytes: " 
                                           + "nicht ermittelbar in JDK 1.1");
// JDK 1.2: 
//                                         + archiv.size());
                      break;
        case NAMEN: 
                      System.out.println("Namen des ZIP-Archivs: " 
                                           + archiv.getName());  
                      break;
        case LISTING: 
                      // archiv.entries() liefert eine Aufzaehlung
                      //   der Fileeintraege des ZIP-Files
                      for (Enumeration files = archiv.entries(); 
                           files.hasMoreElements(); ) 
                      {
                        // files.nextElement() gibt das naechste Objekt der
                        // Aufzaehlung zurueck, das hier ein Objekt der 
                        // Klasse ZipEntry ist
                        ZipEntry file = (ZipEntry) files.nextElement();
                        System.out.println("File: " + file);
                        System.out.println("  Filegr\u00F6\u00DFe: " 
                                           + file.getSize() + " Bytes");
                        System.out.println("  Erstellungszeit: " 
                                           + new Date(file.getTime()));
                      }
                      break;
        case SCHLIESSEN: 
                      // Archiv wird geschlossen
                    
                      try
                      {
                        archiv.close();
                      }
                      catch(IOException exc)
                      {
                        System.err.println("Fehler beim Schliessen des Archivs  --  Abbruch");
                        System.exit(1);
                      }
                    
                      break;
      }
       
      System.out.println(); 
    
    } while (wahl != ENDE);
  
    try
    {
      br.close();    
    }
    catch(IOException exc)
    {
      System.err.println("I/O - Fehler beim Schliessen der Eingabe  --  Abbruch");
      System.exit(1);
    }
  
  }
  
  public static int menue()
  {
    // final: steht fuer konstant
    final int [] zahlen = { GROESSE, NAMEN, LISTING, SCHLIESSEN, ENDE };
    final String [] auswahl = { 
                                "Gr\u00F6\u00DFe ermitteln", 
                                "Namen ausgeben", 
                                "Auflisten aller Files im Archiv", 
                                "Schlie\u00DFen des Archivs",
                                "Ende des Programms"
                              };

    if (!inputOpened)
    {
      inputOpened = true;
      InputStreamReader isr = new InputStreamReader(System.in);
      br = new BufferedReader(isr);
    }
    
    // Auswahlen des Menues ausgeben
    for (int i = 0; i < auswahl.length; i++)
      System.out.println(zahlen[i] + ": " + auswahl[i]); 
    System.out.println();
    
    System.out.print("Auswahl: ");
    int result = 0;
    // Eingabe der Auswahl als Zeile (Stringobjekt) einlesen
    
    String zeile = null;
    
    try
    {
      zeile = br.readLine();
    }
    catch (IOException exc)
    {
      System.err.println("I/O - Fehler bei Eingabe  --  Abbruch");
      System.exit(1);
    }
    
    // Umwandeln der Eingabe in int-Wert
    Integer iObj = null;
   
    try
    {
      iObj = new Integer(zeile);
    }
    catch (NumberFormatException exc)
    {
      System.err.println("NumberFormatException, waehle Standartwert 0");
      iObj = new Integer(0);
    }  
    
    result = iObj.intValue();
    return result;
  }
}
