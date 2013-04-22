import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class BildAnalyse extends Applet implements ActionListener, MouseListener, MouseMotionListener
{
  protected MediaTracker mt;
  protected String bildName;
  protected Image bild;
  protected int bildID;
  protected Polygon rahmen_pinguin, rahmen_nase,
                    rahmen_auge_li, rahmen_auge_re;
  protected Polygon [] alleRahmen;
  protected Button auswert;
  protected int [] clicked, entered;
  protected boolean [] rahmenEntered;
  protected String [] rahmenNamen;

  public void init()
  {
    bild = getImage(getDocumentBase(), "pinguin.gif");
    bildID = 1;
    mt = null;

    try
    {
      mt = new MediaTracker(this);
      mt.addImage(bild, bildID);
      mt.waitForID(bildID);
    }
    catch (InterruptedException exc)
    {
      System.err.println("Bildladen unterbrochen!");
      System.err.println(exc);
    }
    System.out.println("Bildladen hat geklappt!");

    int [] pinguin_x = new int []
      { 106, 88, 83, 86, 58, 35, 35, 26, 1, 2, 77, 94,
        114, 165, 169, 178, 197, 259, 233, 233, 206,
        180, 173, 152, 124
      };
    int [] pinguin_y = new int []
      { 7, 18, 57, 102, 137, 193, 208, 225, 231, 277, 303, 292,
        287, 288, 296, 302, 303, 256, 233, 185, 130,
        84, 33, 5, 1
      };
    int [] nase_x = new int []
      { 117, 90, 91, 110, 123, 152, 154, 127 };
    int [] nase_y = new int []
      { 58, 79, 90, 108, 108, 90, 76, 66 };
    int [] auge_li_x = new int []
      { 135, 125, 125, 150, 155, 154, 149 };
    int [] auge_li_y = new int []
      { 41, 48, 65, 75, 68, 59, 47 };
    int [] auge_re_x = new int []
      { 99, 90, 90, 94, 111, 112, 109, 100 };
    int [] auge_re_y = new int []
      { 42, 52, 63, 75, 64, 55, 47, 43 };

    rahmen_pinguin = new Polygon(pinguin_x, pinguin_y, pinguin_x.length);
    rahmen_nase = new Polygon(nase_x, nase_y, nase_x.length);
    rahmen_auge_li = new Polygon(auge_li_x, auge_li_y, auge_li_x.length);
    rahmen_auge_re = new Polygon(auge_re_x, auge_re_y, auge_re_x.length);
    alleRahmen = new Polygon [] { rahmen_pinguin, rahmen_nase,
                                  rahmen_auge_li, rahmen_auge_re };
    rahmenNamen = new String [] { "Pinguin", "Nase", "linkes Auge",
                                  "rechtes Auge" };

    clicked = new int [alleRahmen.length];
    entered = new int [alleRahmen.length];
    rahmenEntered = new boolean [alleRahmen.length];

    auswert = new Button("Statistik");
    add(auswert);

    auswert.addActionListener(this);
    addMouseListener(this);
    addMouseMotionListener(this);
  }

  public void paint(Graphics g)
  {
    if (mt.checkID(bildID))
      g.drawImage(bild, 0, 0, this);
    else
      System.out.println("Sorry, Bildladen noch nicht fertig");

    g.setColor(Color.red);
    for (int i = 0; i < alleRahmen.length; i++)
      g.drawPolygon(alleRahmen[i]);
  }
   public void actionPerformed(ActionEvent e)
   {
      System.out.println("MouseClicks :: Pinguin : "+ clicked[0] +", Nase : "+ clicked[1] +", AugeLinks : "+ clicked[2] +", AugeRechts : "+ clicked[3] +"");
      System.out.println("MouseMoves :: Pinguin : "+ entered[0] +", Nase : "+ entered[1] +", AugeLinks : "+ entered[2] +", AugeRechts : "+ entered[3] +"\n");
   }

   public void mouseDragged(MouseEvent e)
   {
   }

   public void mouseMoved(MouseEvent e)
   {
        int i;

        for (i=alleRahmen.length-1; i>=0; i--)
        {
            if (alleRahmen[i].contains(e.getPoint())== true && rahmenEntered[i] == false)
            {
                entered[i]++;
                rahmenEntered[i] = true;
            }
            else if (alleRahmen[i].contains(e.getPoint())== false)
                rahmenEntered[i] = false;
        }
   }

   public void mouseClicked(MouseEvent e)
   {
   }

   public void mouseEntered(MouseEvent e)
   {
   }

   public void mouseExited(MouseEvent e)
   {
   }

   public void mousePressed(MouseEvent e)
   {
     for (int i=alleRahmen.length-1; i>=0; i--)
        if (alleRahmen[i].contains(e.getPoint()))
        {
            clicked[i]++;
            break;
        }
   }

   public void mouseReleased(MouseEvent e)
   {
   }
}
