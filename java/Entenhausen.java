import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;

public class Entenhausen extends Applet implements ActionListener
{
  String url_namen; 
  String [] bild_namen;
  Button [] button;
  Bild [] bilder;
  
  public void init()
  {
    setLayout(new FlowLayout());

    url_namen = getParameter("url_basis");
    if (url_namen == null)
    {
      System.err.println("Parameter \"url_basis\" nicht im HTML-File definiert!");
      url_namen = "http://www.uni-bayreuth.de/departments/math/~rbaier/lectures/java/uebung/blatt_01/";
    }

    button = new Button[3];
    bild_namen = new String[3];
    
    button[0] = new Button(" Tick, Trick und Track ");
    bild_namen[0] = "tick_trick_track.jpg";
    add(button[0]);
    button[0].addActionListener(this);
    
    button[1] = new Button(" Donald ");
    bild_namen[1] = "donald.gif";
    add(button[1]);
    button[1].addActionListener(this);
    
    button[2] = new Button(" Dagobert ");
    bild_namen[2] = "dagobert.gif";
    add(button[2]);
    button[2].addActionListener(this);

    bilder = new Bild[] { 
                          new Bild(url_namen, bild_namen[0], button[0].getLabel()), 
                          new Bild(url_namen, bild_namen[1], button[1].getLabel()), 
                          new Bild(url_namen, bild_namen[2], button[2].getLabel())
                        };

    setSize(300, 300);
    setVisible(true);
  }

  public void actionPerformed(ActionEvent ev)
  {
    Object src = ev.getSource();
    
    if (src == button[0])
    {
      if (bilder[0].isVisible())
        bilder[0].setVisible(false);
      else
        bilder[0].setVisible(true);
    }
    else if (src == button[1])
    {
      if (bilder[1].isVisible())
        bilder[1].setVisible(false);
      else
        bilder[1].setVisible(true);
    }
    else if (src == button[2])
    {
      if (bilder[2].isVisible())
        bilder[2].setVisible(false);
      else
        bilder[2].setVisible(true);
    }
    else
    {
      System.err.println("Fehler: getSource() = " + src);
    }
  }
}

class Bild extends Frame
{
  private Image im;
  private URL urlBild;
  
  public Bild(String url_namen, String bild_namen, String bild_titel)
  {
    super(bild_titel);
    try
    {
      /* Laden des Bildes unter Aufsicht eines Medientrackers */
      urlBild = new URL(url_namen + bild_namen);
      MediaTracker med_track = new MediaTracker(this);
      im = Toolkit.getDefaultToolkit().getImage(urlBild);
      med_track.addImage(im, 0);
      med_track.waitForID(0);      /* Warten, bis Bild komplett geladen */
      System.out.println("Bild geladen");
      System.out.println("Bildgr\u00F6\u00DFe: "
                         + im.getWidth(this) + " x "
                         + im.getHeight(this));
    }
    catch (MalformedURLException exc)
    {
      System.err.println("Fehler beim \u00D6ffnen der URL " + urlBild 
                         + " (" + bild_namen + ")");
      System.exit(2);
    }
    catch (InterruptedException exc)
    {
      System.err.println("Bildladen wurde abgebrochen!");
      System.exit(3);
    }
    setSize(300, 300);
    FrameCanvas c = new FrameCanvas(im);
    add(c);
  }
}

class FrameCanvas extends Canvas
{
  private Image im;
  
  public FrameCanvas(Image im)
  {
    super();
    this.im = im;
  }
  
  public void paint(Graphics g)
  {
    g.drawImage(im, 0, 0, null);
  }
}
