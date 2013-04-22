import java.io.*;
import java.util.Date;
import java.util.Calendar;
import java.awt.*;
import java.awt.event.*;

public class Diary
{
    protected static MyFrame fenster;

    public static void main(String [] argv)
    {
        fenster = new MyFrame("Tagebuch");
    }
}

class MyFrame extends Frame implements WindowListener, ActionListener
{
    private String passfile = "c:\\windows\\diary.pas";
    private String diaryfile = "c:\\windows\\diary.txt";

    private MenuBar menubar;
    private Menu menu;
    private MenuItem pitem;
    private MenuItem sitem;

    private Dialog dlg, suche;
    private String pass;
    private boolean settype;
    private TextField dlg_pwd, tag, monat, jahr;
    private BufferedReader br;
    private FileInputStream f_in;
    private Panel [] panelSeiten;
    private Panel center, bottom;
    private CardLayout cardlayout;
    private Button dlg_ok, eingabe, next, prev, search;

    protected File file;
    protected PrintWriter pw;
    protected int diarylength;
    protected TextField date [];
    protected TextArea [] textSeiten;
    protected FileOutputStream f_out;

    public MyFrame()
    {
        this("");
    }

    public MyFrame(String titel)
    {
        super(titel);

        setBackground(Color.lightGray);
        setSize(400,400);

        menubar = new MenuBar();
        menu = new Menu("Menue");
        sitem = new MenuItem("Suche nach Eintrag");
        pitem = new MenuItem("Passwort aendern");

        menubar.add(menu);
        menu.add(sitem);
        menu.add(pitem);
        setMenuBar(menubar);

        addWindowListener(this);

        file = new File(passfile);
        settype = false;
        diarylength = 0;

        if (file.isFile())
        {
            try
            {
                f_in = new FileInputStream(file);
                br = new BufferedReader(new InputStreamReader(f_in));

                pass = br.readLine();

                f_in.close();
                br.close();
            }

            catch (FileNotFoundException exc)
            {
                System.err.println("PassFile wurde nicht gefunden !!!");
                System.exit(1);
            }

            catch (IOException exc)
            {
                System.err.println("Einlesefehler aufgetreten !!!");
                System.exit(1);
            }

            passDialog();
        }

        else
        {
            settype = true;
            passDialog();
        }

        center = new Panel();
        bottom = new Panel();

        eingabe = new Button("Eintrag hinzufuegen");
        next = new Button("Naechster Eintrag");
        prev = new Button("Vorheriger Eintrag");

        eingabe.addActionListener(this);
        next.addActionListener(this);
        prev.addActionListener(this);

        bottom.add(prev);
        bottom.add(eingabe);
        bottom.add(next);

        add(center,"Center");
        add(bottom,"South");

        pitem.addActionListener(this);
        sitem.addActionListener(this);

        cardlayout = new CardLayout();
        center.setLayout(cardlayout);

        setVisible(true);

        getDiary();
    }

    private void passDialog()
    {
        file = new File(passfile);

        if (settype == true)
            dlg = new Dialog(this, "Festlegen des Passworts ...", true);
        else
            dlg = new Dialog(this, "Eingabe des Passworts ...", true);

        dlg.setSize(220,80);

        dlg_pwd = new TextField(8);
        dlg_pwd.setEchoChar('*');

        dlg_ok = new Button("OK");

        dlg.add(dlg_pwd,"North");
        dlg.add(dlg_ok,"South");

        dlg_pwd.addActionListener(this);
        dlg_ok.addActionListener(this);

        dlg.setVisible(true);
    }

    protected void getDiary()
    {
        file = new File(diaryfile);

        center.removeAll();

        if (file.isFile())
        {
            try
            {
                f_in = new FileInputStream(file);
                br = new BufferedReader(new InputStreamReader(f_in));

                Integer myInt = new Integer(br.readLine());
                diarylength = myInt.intValue();

                textSeiten = new TextArea[diarylength];
                panelSeiten = new Panel[diarylength];
                date = new TextField[diarylength];

                for (int i=0; i<diarylength; i++)
                {
                    textSeiten[i] = new TextArea();
                    textSeiten[i].setEditable(false);
                    panelSeiten[i] = new Panel();
                    date[i] = new TextField();
                    date[i].setEditable(false);

                    String zeile = br.readLine();
                    date[i].setText(zeile);

                    zeile = br.readLine();

                    while (zeile != null && !zeile.equals("$%&"))
                    {
                        textSeiten[i].append(zeile);
                        textSeiten[i].append("\n");
                        zeile = br.readLine();
                    }

                    panelSeiten[i].setLayout(new BorderLayout());

                    Panel tmp = new Panel();
                    tmp.add(date[i]);

                    panelSeiten[i].add(tmp,"North");
                    panelSeiten[i].add(textSeiten[i],"Center");

                    center.add("Seite" + i, panelSeiten[i]);
                }

                invalidate();
                validate();

                f_in.close();
                br.close();
            }

            catch (FileNotFoundException exc)
            {
                System.err.println("DiaryFile wurde nicht gefunden !!!");
                System.exit(1);
            }

            catch (IOException exc)
            {
                System.err.println("Einlesefehler aufgetreten !!!");
                System.exit(1);
            }

            catch (NumberFormatException exc)
            {
                System.err.println("Einlesefehler (NumberFormatException) aufgetreten !!!");
                System.exit(1);
            }
        }
    }

    private void setDiary()
    {
        file = new File(diaryfile);

        MyDialog set = new MyDialog(this, "Neuer Tagebucheintrag ...", true);
        set.setVisible(true);

        getDiary();
    }

    public void windowActivated(WindowEvent e)
    {}
    public void windowClosed(WindowEvent e)
    {}
    public void windowClosing(WindowEvent e)
    {
        if (e.getSource() == this)
        {
            setVisible(false);
            dispose();

            System.exit(0);
        }

        else if (e.getSource() == suche)
        {
            suche.setVisible(false);
            suche.dispose();
        }
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
        if (e.getSource() == dlg_pwd || e.getSource() == dlg_ok)
        {
            if (settype == true)
            {
                pass = dlg_pwd.getText();
                dlg.setVisible(false);
                dlg.dispose();

                try
                {
                    f_out = new FileOutputStream(file);
                    pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(f_out)));

                    pw.println(pass);
                    pw.close();
                }

                catch (IOException exc)
                {
                    System.err.println("Schreibfehler aufgetreten !!!");
                    System.exit(1);
                }
            }

            else
            {
                dlg.setVisible(false);
                dlg.dispose();

                if (!pass.equals(dlg_pwd.getText()))
                {
                    System.err.println("Fehlerhaftes Passwort !!!");
                    setVisible(false);
                    dispose();
                    System.exit(1);
                }
            }
        }

        else if (e.getSource() == prev)
        {
            cardlayout.previous(center);
        }

        else if (e.getSource() == next)
        {
            cardlayout.next(center);
        }

        else if (e.getSource() == eingabe)
        {
            setDiary();
        }

        else if (e.getSource() == pitem)
        {
            settype = true;
            passDialog();
        }

        else if (e.getSource() == sitem)
        {
            suche = new Dialog(this, "Suche nach Eintrag ...", true);
            suche.setSize(200,100);

            tag = new TextField(3);
            monat = new TextField(3);
            jahr = new TextField(4);
            search = new Button("Suche starten");

            Panel zentrum = new Panel(new GridLayout(3,2));
            zentrum.add(new Label("Tag :", Label.CENTER));
            zentrum.add(tag);
            zentrum.add(new Label("Monat :", Label.CENTER));
            zentrum.add(monat);
            zentrum.add(new Label("Jahr :", Label.CENTER));
            zentrum.add(jahr);

            suche.add(zentrum,"Center");
            suche.add(search,"South");

            search.addActionListener(this);
            suche.addWindowListener(this);

            suche.setVisible(true);
        }

         else if (e.getSource() == search)
         {
            for (int i=0; i<diarylength; i++)
                if (date[i].getText().equals(tag.getText()+". "+monat.getText()+". "+jahr.getText()))
                    cardlayout.show(center, "Seite"+i);

            suche.setVisible(false);
            suche.dispose();
         }
    }
}

class MyDialog extends Dialog implements WindowListener, ActionListener
{
    private Date date;
    private TextField datum;
    private Button ok, cancel;
    private Panel center, bottom;
    private TextArea ta_wetter, ta_tag, ta_was;
    private Label wetter, tagesablauf, vorkommnisse;

    public MyDialog(Frame own, String titel, boolean which)
    {
        super(own, titel, which);

        setSize(400, 400);
        setBackground(Color.lightGray);
        addWindowListener(this);

        date = new Date();

        datum = new TextField();
        datum.setEditable(false);
        datum.setText("" + date.getDate() + ". " + (date.getMonth() + 1) +". " + (date.getYear() + 1900));

        ta_wetter = new TextArea();
        ta_tag = new TextArea();
        ta_was = new TextArea();
        wetter = new Label("Wetter :",Label.CENTER);
        tagesablauf = new Label("Tagesablauf :",Label.CENTER);
        vorkommnisse = new Label("Besondere Vorkommnisse :",Label.CENTER);
        ok = new Button("Eintragung machen");
        cancel = new Button("Eintrag verwerfen");
        center = new Panel(new GridLayout(3,2));
        bottom = new Panel();

        center.add(wetter);
        center.add(ta_wetter);
        center.add(tagesablauf);
        center.add(ta_tag);
        center.add(vorkommnisse);
        center.add(ta_was);
        bottom.add(ok);
        bottom.add(cancel);

        Panel tmp = new Panel();
        tmp.add(datum);

        ok.addActionListener(this);
        cancel.addActionListener(this);

        add(tmp,"North");
        add(center,"Center");
        add(bottom,"South");
    }

    public void windowActivated(WindowEvent e)
    {}
    public void windowClosed(WindowEvent e)
    {}
    public void windowClosing(WindowEvent e)
    {
         setVisible(false);
         dispose();
    }
    public void windowDeactivated(WindowEvent e)
    {}
    public void windowDeiconified(WindowEvent e)
    {}
    public void windowIconified(WindowEvent e)
    {}
    public void windowOpened(WindowEvent e)
    {
        ta_wetter.requestFocus();
    }
    public void actionPerformed(ActionEvent e)
    {
        if (e.getSource() == cancel)
        {
            setVisible(false);
            dispose();
        }

        if (e.getSource() == ok)
        {
            TextArea tmp = new TextArea();
            tmp.append(datum.getText() + "\n");

            StringBuffer text = new StringBuffer(ta_wetter.getText());

            for (int i=text.length() - 1; i>=0; i--)
                if (text.charAt(i) == '\n' || text.charAt(i) == ' ')
                    text.deleteCharAt(i);
                else
                    break;

            tmp.append("Wetter:\n" + text + "\n\n");

            text = new StringBuffer(ta_tag.getText());

            for (int i=text.length() - 1; i>=0; i--)
                if (text.charAt(i) == '\n' || text.charAt(i) == ' ')
                    text.deleteCharAt(i);
                else
                    break;

            tmp.append("Tagesablauf:\n" + text + "\n\n");

            text = new StringBuffer(ta_was.getText());

            for (int i=text.length() - 1; i>=0; i--)
                if (text.charAt(i) == '\n' || text.charAt(i) == ' ')
                    text.deleteCharAt(i);
                else
                    break;

            tmp.append("Besondere Vorkommnisse:\n" + text);

            try
            {
                Diary.fenster.f_out = new FileOutputStream(Diary.fenster.file);
                Diary.fenster.pw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(Diary.fenster.f_out)));

                Diary.fenster.pw.println( "" + (Diary.fenster.diarylength + 1) );

                for (int i=0; i<Diary.fenster.diarylength; i++)
                    Diary.fenster.pw.println( Diary.fenster.date[i].getText() + "\n" + Diary.fenster.textSeiten[i].getText() + "\n$%&" );

                Diary.fenster.pw.println(  tmp.getText() );

                Diary.fenster.pw.close();
            }

            catch (IOException exc)
            {
                System.err.println("Schreibfehler augetreten !!!");
                System.exit(1);
            }

            setVisible(false);
            dispose();
        }
    }
}
