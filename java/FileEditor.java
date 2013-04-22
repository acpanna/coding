// notwendiger Import von Klassen fuer das Fileeinlesen
import java.io.*;

// noetige Datenlemente:

  private File file;
  private FileInputStream f_in;
  private FileOutputStream f_out;
  private StringReader sr;
  private BufferedReader br;
  private PrintWriter pw;

// bereitgestellte Methoden:

  public void oeffne_file_lesen(String filename)
  {
    // Loeschen Sie den angezeigten Text im TextArea-Objekt inhalt

    // Update des TextArea-Objekts inhalt
    update(inhalt);
    
    file = new File(filename);
    if (!file.canRead())
    {
      // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
      ...("Fehler!" + newline + "File \"" + filename 
          + "\" kann nicht zum Lesen ge\u00F6ffnet werden!");
      return;
    }
    if (!file.isFile())
    {
      if (file.isDirectory())
        // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
        ...("Fehler!" + newline + "File \"" + filename 
                       + "\" ist ein Verzeichnis und keine Datei!");
      else
        // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
        ...("Fehler!" + newline + "File \"" + filename 
            + " ist keine normale Datei,"
            + " sondern eine spezielle Betriebssystemdatei,"
            + " die nicht ge\u00F6ffnet werden kann!");
      return;
    }

    try
    {
      f_in = new FileInputStream(file);
      br = new BufferedReader(new InputStreamReader(f_in));

      // Zeigen Sie die Status-Beschreibung in der GUI-Komponente status an
      ...("Status: File ge\u00F6ffnet zum Lesen");

      update(status);
      
      String zeile;
      do
      {
        zeile = br.readLine();
        if (zeile != null)
          // haengen Sie die Zeile und newline 
          // an den Inhalt des TextArea-Objekts inhalt
          ...(zeile + newline);
      }
      while (zeile != null);
      f_in.close();
      br.close();

      // Zeigen Sie die Status-Beschreibung in der GUI-Komponente status an
      ...("Status: Fileeinlesen beendet");
      
      update(status);
      update(inhalt);
    }
    catch (FileNotFoundException exc)
    {
      System.err.println("File mit dem Namen " + filename + " wurde nicht gefunden!");
      System.exit(2);
    }
    catch (IOException exc)
    {
      System.err.println("I/O-Fehler beim Lesen des Files mit dem Namen " 
                         + filename + "!");
      System.err.println(exc);
      System.exit(3);
    }
  }
  
  public void oeffne_file_schreiben(String filename)
  {
    file = new File(filename);
    if (file.exists() && !file.canWrite())
    {
      // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
      ...("Fehler!" + newline + "File \"" + filename 
          + "\" existiert, kann aber nicht zum Schreiben"
          + " ge\u00F6ffnet werden!");

      update(inhalt);
      return;
    }
    if (file.exists() && !file.isFile())
    {
      if (file.isDirectory())
        // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
        ...("Fehler!" + newline + "File \"" + filename 
            + "\" ist ein Verzeichnis und keine Datei!");
      else
        // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
        ...("Fehler!" + newline + "File \"" + filename 
            + " existiert und ist keine normale Datei,"
            + " sondern eine spezielle Betriebssystemdatei,"
            + " die nicht ge\u00F6ffnet werden kann!");

      update(inhalt);
      return;
    }

    try
    {
      // speichern Sie hier in fileInhalt den Inhalt des TextArea-Objekts
      // inhalt als String
      String fileInhalt = ...;

      sr = new StringReader(fileInhalt);
      br = new BufferedReader(sr);

      f_out = new FileOutputStream(file);
      pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(f_out)));
    
      // Zeigen Sie die Status-Beschreibung in der GUI-Komponente status an
      ...("Status: File ge\u00F6ffnet zum Schreiben");

      update(status);

      String zeile;
      do
      {
        zeile = br.readLine();
        if (zeile != null)
          pw.println(zeile);
      }
      while (zeile != null);
      
      sr.close();
      pw.close();

      // Zeigen Sie die Status-Beschreibung in der zugeh. GUI-Komponente an
      ...("Status: Fileschreiben beendet");

      update(status);
    }
    catch (IOException exc)
    {
      System.err.println("I/O-Fehler beim Schreiben des Files mit dem Namen " 
                         + filename);
      System.err.println(exc);
      System.exit(3);
    }
  }

  public void update(Component comp)
  {
    comp.invalidate();
    // Update des aktuellen Containers, der comp beinhaltet
    validate();
  }
