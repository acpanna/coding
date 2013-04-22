import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class UmRechner extends Applet implements ActionListener, ItemListener, KeyListener
{
    protected Label waehrung;
    protected Label betrag;
    protected TextField eingabe;
    protected TextField ausgabe;
    protected Button rechne;
    protected List liste;

    protected boolean selected;
    protected boolean typed;

    public void init()
    {
        setLayout(new GridLayout(3,2));

        waehrung = new Label("gewünschte Währung:");
        betrag = new Label("DM-Betrag:");
        eingabe = new TextField();
        ausgabe = new TextField();
        rechne = new Button("ausrechnen");
        liste = new List();
        ausgabe.setEditable(false);
        selected = false;
        typed = false;

        eingabe.addKeyListener(this);
        rechne.addActionListener(this);
        liste.addItemListener(this);

        liste.add("Euro");
        liste.add("Lire");
        liste.add("österreichische Schilling");
        liste.add("französische Francs");

        add(betrag);
        add(eingabe);
        add(waehrung);
        add(liste);
        add(rechne);
        add(ausgabe);
    }

    public void actionPerformed(ActionEvent evt)
    {
        if (evt.getSource() == rechne)
        {
            if (selected == true && typed == true)
            {
                double betrag;
                Double betrag2;

                try
                {
                    betrag2 = new Double(eingabe.getText());
                }

                catch(NumberFormatException exc)
                {
                    ausgabe.setText("");
                    ausgabe.invalidate();
                    ausgabe.validate();

                    return;
                }

                betrag = betrag2.doubleValue();

                switch(liste.getSelectedIndex())
                {
                    case 0:
                      betrag = betrag * 0.5112918;  //Euro
                      break;
                    case 1:
                      betrag = betrag * 990.002;    //Lire
                      break;
                    case 2:
                      betrag = betrag * 7.03552;    //Schiling
                      break;
                    case 3:
                      betrag = betrag * 3.35386;    // Franc
                }

                ausgabe.setText(""+betrag);
                ausgabe.invalidate();
                ausgabe.validate();
            }
        }
    }

    public void itemStateChanged(ItemEvent evt)
    {
        selected = true;
        showStatus("Bitte nun auf >Ausrechnen< drücken !!!");
    }

    public void keyPressed(KeyEvent evt)
    {
    }

    public void keyReleased(KeyEvent evt)
    {
    }

    public void keyTyped(KeyEvent evt)
    {
        typed = true;
    }
}
