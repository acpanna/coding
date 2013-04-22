import java.applet.Applet;
import java.awt.*;
import java.net.*;

public class ParamApplet extends Applet
{

  int i;
  String [] pos; 
  String [] titel;

 // pos und titel als Array von String-Objekten definieren
  MyLabel [] label;
  Bild bild;
  FrameCanvas c;
  
  public void init()
  {
    pos = new String[]{ "North", "South", "West", "East"};  
    titel = new String[4];   
    
    // Anlegen des Arrays pos mit den Werten "North", "South", "West", "East"
    // Anlegen des Arrays titel mit passender Laenge
    
    label = new MyLabel[4];
    
    for (i = 0; i < 4; i++)
    {
      titel[i] = getParameter(pos[i]);

      if (titel[i] == null)
      {
        System.err.println("Parameter \"" + pos[i] + "\" nicht gesetzt im HTML-File");
        titel[i] = "(nicht gesetzt)";
      }
    } 
    // Besetzen der Komponenten von titel mit den HTML-Parametern fuer die Titel
    // Beachten des Sonderfalls, dass HTML-Parameter vergessen wurde in HTML-File
    // ggf. sinnvollen Defaultwert definieren
    
    String bild_namen;
    
   bild_namen = getParameter("url");

   if (bild_namen == null)
   {
     System.err.println("Es wurde keine gueltige bzw. keine URL fuer den Bildpfad im HTML-File festgelegt");
     bild_namen = "file:///";  
   }

    // Besetzen der Variable bild_namen mit dem HTML-Parameter fuer URL des Bildes
    // Beachten des Sonderfalls, dass HTML-Parameter vergessen wurde in HTML-File
    // ggf. sinnvollen Defaultwert definieren

    bild = new Bild(bild_namen);
      
    setLayout(new BorderLayout());
    for (i = 0; i < 4; i++)
    {
      label[i] = new MyLabel(titel[i], pos[i]);
      add(label[i], pos[i]);
    }
    
    System.out.println("[init] Appletgr\u00F6\u00DFe: " + getSize());
    addImage(bild, "Center");
  }

  public void addImage(Bild im, Object constraints)
  {
    c = new FrameCanvas(im.getImage());
    add(c, constraints);
  }
  
  public void paint(Graphics g)
  {
    System.out.println("Appletgr\u00F6\u00DFe: " + getSize());
    c.paint(g);
  }
}

class MyLabel extends Panel
{
  private Label label;
  String north;  
  String south; 

  public MyLabel(String titel, String pos)
  {
    super();
    label = new Label(titel, Label.CENTER);
    label.setBackground(new Color(titel.hashCode()));
    
    north = new String("North");
    south = new String("South");

    // Falls pos denselben Stringinhalt wie "North" oder "South" hat

    if ( pos.compareTo(north) == 0 || pos.compareTo(south) == 0  )
    {
      setLayout(new FlowLayout());
      add(label);
    }
    else
    {
      setLayout(new BorderLayout());
      add(label, "Center");
    }
  }
}

class Bild extends Component
{
  private Image im;
  private URL urlBild;
  
  public Bild(String url_namen)
  {
    try
    {
      /* Laden des Bildes unter Aufsicht eines Medientrackers */
      urlBild = new URL(url_namen);
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
                         + " (" + url_namen + ")");
      System.exit(2);
    }
    catch (InterruptedException exc)
    {
      System.err.println("Bildladen wurde abgebrochen!");
      System.exit(3);
    }
  }
  
  public Image getImage()
  {
    return im;
  }
}

class FrameCanvas extends Canvas
{
  private Image im;
  private Dimension dim, im_dim;
  
  public FrameCanvas(Image im)
  {
    super();
    this.im = im;
    im_dim = new Dimension(im.getWidth(null), im.getHeight(null));
  }
  
  public void paint(Graphics g)
  {
    super.paint(g);
    dim = getSize();
    System.out.println("Canvasgr\u00F6\u00DFe: " + dim);

// zentriert, Originalgroesse
    g.drawImage(im, (dim.width - im_dim.width)/2, 
                (dim.height - im_dim.height)/2, null);
  }

  public Dimension getPreferredSize()
  {
    return im_dim;
  }

  public Dimension getMinimumSize()
  {
    return im_dim;
  }
}

