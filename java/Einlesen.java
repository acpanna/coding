// noetiger Import der I/O-Klassen
import java.io.*;

  // Oeffnen des Files und Anzeige im TextArea-Objekt ta_inhalt
  //    ggf. Namen ta_inhalt austauschen!

  public void oeffne_file_lesen(String filename)
  {
    File file;
    FileInputStream f_in;
    StringReader sr;
    BufferedReader br;
    String newline = System.getProperty("line.separator");
    
    ta_inhalt.setText("");
    update(ta_inhalt);
    
    file = new File(filename);
    if (!file.canRead())
    {
      ta_inhalt.setText("Fehler!" + newline + "File \"" + filename 
                        + "\" kann nicht zum Lesen ge\u00F6ffnet werden!");
      return;
    }
    if (!file.isFile())
    {
      if (file.isDirectory())
        ta_inhalt.setText("Fehler!" + newline + "File \"" + filename 
                          + "\" ist ein Verzeichnis und keine Datei!");
      else
        ta_inhalt.setText("Fehler!" + newline + "File \"" + filename 
                          + " ist keine normale Datei, sondern eine spezielle Betriebssystemdatei,"
                          + " die nicht ge\u00F6ffnet werden kann!");
      return;
    }

    try
    {
      f_in = new FileInputStream(file);
      br = new BufferedReader(new InputStreamReader(f_in));
      
      String zeile;
      do
      {
        zeile = br.readLine();
        if (zeile != null)
          ta_inhalt.append(zeile + newline);
      }
      while (zeile != null);

      f_in.close();
      br.close();

      update(ta_inhalt);
    }
    catch (FileNotFoundException exc)
    {
      System.err.println("File mit dem Namen " + filename + " wurde nicht gefunden!");
      System.err.println(exc);
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
  
  public void update(Component c)
  {
    c.invalidate();
    c.getParent().validate();
  }
