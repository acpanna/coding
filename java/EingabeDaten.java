import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class EingabeDaten extends Applet 
                          implements ActionListener, MouseMotionListener
                          // Frage a)
{
  private Label labelName, labelMatrikelNr;
  private TextField textName, textMatrikelNr;
  private Button buttonOK, buttonLoeschen;
  private Panel panelLabelName, panelLabelMatrikelNr,
                panelName, panelMatrikelNr, panelOK, panelLoeschen;
  
  // Frage h)
  public void init()
  {
    // Frage b)

    labelName = new Label("Name:");
    labelMatrikelNr = new Label("Matrikelnummer:");
    textName = new TextField(15);
    textMatrikelNr = new TextField(8);
    buttonOK = new Button("OK");
    buttonLoeschen = new Button("L\u00F6schen");

    // Frage c)
    labelName.setBackground(Color.yellow);
    labelMatrikelNr.setBackground(Color.yellow);
    textName.setBackground(Color.white);
    textMatrikelNr.setBackground(Color.white);
    buttonOK.setBackground(Color.green);
    buttonLoeschen.setBackground(Color.red);

    panelLabelName = new Panel(new FlowLayout(FlowLayout.LEFT));
    panelLabelMatrikelNr = new Panel(new FlowLayout(FlowLayout.LEFT));
    panelName = new Panel(new FlowLayout(FlowLayout.LEFT));
    panelMatrikelNr = new Panel(new FlowLayout(FlowLayout.LEFT));
    panelOK = new Panel();
    panelLoeschen = new Panel();

    // Frage d)
    setBackground(Color.gray);
    setLayout(new GridLayout(3, 2));

    panelLabelName.add(labelName);
    panelName.add(textName);
    panelLabelMatrikelNr.add(labelMatrikelNr);
    panelMatrikelNr.add(textMatrikelNr);
    // Frage e)
    panelOK.add(buttonOK);
    panelLoeschen.add(buttonLoeschen);

    add(panelLabelName);
    add(panelName);
    add(panelLabelMatrikelNr);
    add(panelMatrikelNr);
    // Frage e)
    add(panelOK);
    add(panelLoeschen);

    // Frage f)
    buttonOK.addActionListener(this);
    buttonLoeschen.addActionListener(this);

    // Frage f)
    buttonOK.addMouseMotionListener(this);
    buttonLoeschen.addMouseMotionListener(this);
  }
  
  public void actionPerformed(ActionEvent evt)
  {
    // Frage g)
    Object quelle = evt.getSource();
    if (quelle == buttonOK)
    {
      System.out.println("eingegebener Name: " + textName.getText());
      System.out.println("Matrikelnummer: " + textMatrikelNr.getText());
    }
    else if (quelle == buttonLoeschen)
    {
      textName.setText("");
      textMatrikelNr.setText("");
      textName.invalidate();
      textMatrikelNr.invalidate();
      validate();
    }
  }

  public void mouseDragged(MouseEvent evt)
  {
  }

  public void mouseMoved(MouseEvent evt)
  {
    // Frage g)
    Object quelle = evt.getSource();

    // Frage h)
    if (quelle == buttonOK)
      showStatus("Eingabe best\u00E4tigen");
    else if (quelle == buttonLoeschen)
      showStatus("Eingabe l\u00F6schen");
    else
      showStatus("                              ");
  }
}
