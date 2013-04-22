import java.io.*;
import java.awt.*;
import java.awt.event.*;

public class NotePad
{
    public static void main(String [] argv)
    {
        if (argv.length != 1)
        {
            System.err.println("Fehlerhafter Interpreter - Aufruf (Syntax: java NotePad test.txt) !!!");
            System.exit(1);
        }

        MyFrame fenster = new MyFrame("NotePad", argv[0]);

        fenster.setSize(500,500);
        fenster.setBackground(Color.lightGray);
        fenster.setVisible(true);
    }
}

class MyFrame extends Frame implements WindowListener, ActionListener
{
    protected Button b_Load;
    protected Button b_Save;
    protected Label l_File;
    protected Label status;
    protected TextArea inhalt;
    protected String file_name;

    protected static String newline = System.getProperty("line.separator");

    protected File file;
    protected FileInputStream f_in;
    protected BufferedReader br;
    protected StringReader sr;
    protected FileOutputStream f_out;
    protected PrintWriter pw;

    public MyFrame(String titel, String filename)
    {
        super(titel);

        b_Load = new Button("load file");
        b_Save = new Button("save file");
        l_File = new Label("File: "+filename, Label.CENTER);
        status = new Label("",Label.CENTER);
        inhalt = new TextArea();
        file_name = filename;

        b_Load.addActionListener(this);
        b_Save.addActionListener(this);
        addWindowListener(this);

        add(l_File,"North");
        add(b_Load,"West");
        add(b_Save,"East");
        add(status,"South");
        add(inhalt,"Center");
    }

    public void windowActivated(WindowEvent e)
    {}
    public void windowClosed(WindowEvent e)
    {}
    public void windowClosing(WindowEvent e)
    {
         dispose();
         System.exit(0);
    }
    public void windowDeactivated(WindowEvent e)
    {}
    public void windowDeiconified(WindowEvent e)
    {}
    public void windowIconified(WindowEvent e)
    {}
    public void windowOpened(WindowEvent e)
    {}

    public void actionPerformed(ActionEvent e)
    {
        if (e.getSource() == b_Load)
        {
            oeffne_file_lesen(file_name);
        }

        else if (e.getSource() == b_Save)
        {
            oeffne_file_schreiben(file_name);
        }
    }

    public void oeffne_file_lesen(String filename)
    {
        // Loeschen Sie den angezeigten Text im TextArea-Objekt inhalt
        inhalt.setText("");
        // Update des TextArea-Objekts inhalt
        update(inhalt);

        file = new File(filename);
        if (!file.canRead())
        {
            // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
            inhalt.append("Fehler!" + newline + "File \"" + filename
            + "\" kann nicht zum Lesen ge\u00F6ffnet werden!");
            return;
        }
        if (!file.isFile())
        {
            if (file.isDirectory())
                // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
                inhalt.append("Fehler!" + newline + "File \"" + filename
                + "\" ist ein Verzeichnis und keine Datei!");
            else
                // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
                inhalt.append("Fehler!" + newline + "File \"" + filename
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
            status.setText("Status: File ge\u00F6ffnet zum Lesen");

            update(status);

          String zeile;
          do
          {
            zeile = br.readLine();
            if (zeile != null)
              // haengen Sie die Zeile und newline
              // an den Inhalt des TextArea-Objekts inhalt
              inhalt.append(zeile + newline);
          }
          while (zeile != null);
          f_in.close();
          br.close();

          // Zeigen Sie die Status-Beschreibung in der GUI-Komponente status an
          status.setText("Status: Fileeinlesen beendet");

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
          inhalt.append("Fehler!" + newline + "File \"" + filename
              + "\" existiert, kann aber nicht zum Schreiben"
              + " ge\u00F6ffnet werden!");

          update(inhalt);
          return;
        }
        if (file.exists() && !file.isFile())
        {
          if (file.isDirectory())
            // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
            inhalt.append("Fehler!" + newline + "File \"" + filename
                + "\" ist ein Verzeichnis und keine Datei!");
          else
            // Zeigen Sie den Fehler im TextArea-Objekt inhalt an
            inhalt.append("Fehler!" + newline + "File \"" + filename
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
          String fileInhalt = inhalt.getText();

          sr = new StringReader(fileInhalt);
          br = new BufferedReader(sr);

          f_out = new FileOutputStream(file);
          pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(f_out)));

          // Zeigen Sie die Status-Beschreibung in der GUI-Komponente status an
          status.setText("Status: File ge\u00F6ffnet zum Schreiben");

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
          status.setText("Status: Fileschreiben beendet");

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
}


