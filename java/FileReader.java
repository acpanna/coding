import java.io.*;
import java.awt.*;
import java.awt.event.*;

public class FileReader
{
    public static void main(String [] argv)
    {
        MyFrame fenster = new MyFrame("FileReader");

        fenster.setSize(400,400);
        fenster.setBackground(Color.lightGray);

        fenster.setVisible(true);
    }
}

class MyFrame extends Frame implements WindowListener, ActionListener, ItemListener
{
    private Label labelVerz, labelDatei, labelInhalt;
    private Choice selectVerz;
    private TextField showDateiName;
    private TextArea ta_inhalt;
    private String os, separator;

    public MyFrame()
    {
        this("");
    }

    public MyFrame(String titel)
    {
        super(titel);

        labelVerz = new Label("Verzeichnisname:");
        labelDatei = new Label("Dateiname:");
        labelInhalt = new Label("Dateiinhalt:");
        selectVerz = new Choice();
        showDateiName = new TextField();
        ta_inhalt = new TextArea();

        showDateiName.setEditable(false);
        ta_inhalt.setEditable(false);

        os = System.getProperty("os.name");

        if (os.equals("Windows 95"))
        {
            selectVerz.add("c:\\");
            selectVerz.add("c:\\Windows");
            selectVerz.add("c:\\Programme");
            separator = "\\";
        }

        else
        {
            selectVerz.add("/usr/lib/java/lib");
            selectVerz.add("/home/heiko");
            selectVerz.add("/home/heiko/java");
            separator = "/";
        }

        setLayout(new GridLayout(3,2));

        add(labelVerz);
        add(selectVerz);
        add(labelDatei);
        add(showDateiName);
        add(labelInhalt);
        add(ta_inhalt);

        addWindowListener(this);
        selectVerz.addItemListener(this);
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
    }

    public void itemStateChanged(ItemEvent evt)
    {
        if (evt.getSource() == selectVerz)
        {
            FileDialog dlg = new FileDialog(this, "Bitte gewuenschtes File auswaehlen ...", FileDialog.LOAD);
            dlg.setDirectory(selectVerz.getSelectedItem());
            dlg.setModal(true);
            dlg.show();

            String file = dlg.getFile();

            if (file != null)
            {
                showDateiName.setText(file);
                oeffne_file_lesen(dlg.getDirectory() + separator + file);
            }
        }
    }

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
}

