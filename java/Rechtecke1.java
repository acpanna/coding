import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.lang.Math;

// Klasse Rechtecke implementiert alle Methode, 
// die das Interface MouseListener vorgibt

public class Rechtecke1 extends Applet implements MouseListener
{
  static private int anzahl = 10;
  static private Color selected = Color.red;
  private Rechteck [] rechteck;
  private int clicked_rechteck, moved_rechteck;
  private Color alte_farbe;
  private Point anfang, ende;
  
  public void init()
  {
    // Groesse des Appletbereichs ermitteln
    Dimension dim = getSize();
    
    // Array initialisieren
    rechteck = new Rechteck[anzahl];
    
    for (int i = 0; i < anzahl; i++)
    {
      // zufaelligen Punkt (x, y) im Appletbereich bestimmen
      int x = zufallszahl(dim.width),
          y = zufallszahl(dim.width);
      // zufaellige Hoehe und Breite so bestimmen, dass das Rechteck noch
      // gezeichnet werden kann
      rechteck[i] = new Rechteck(x, y, 
                                 zufallszahl(dim.width - x),
                                 zufallszahl(dim.height - y));
      // zufaellige Farbe bestimmen
      rechteck[i].setFarbe(zufallszahl(255), zufallszahl(255), zufallszahl(255));
    }
    
    // eigentlich ueberfluessige Initialisierungen
    clicked_rechteck = moved_rechteck = 0;
    alte_farbe = rechteck[clicked_rechteck].getFarbe();
    anfang = ende = new Point();
    
    // aktuelles Applet reagiert auf MouseEvents
    addMouseListener(this);
  }
  
  public void paint(Graphics g)
  {
    // alle Rechtecke werden gezeichnet
    for (int i = 0; i < anzahl; i++)
    {
      rechteck[i].zeichneRechteck(g);
    }
  }
  
  // Hilfsmethode: ganzzahlige Zufallszahl zwischen 0 und limit wird bestimmt
  private int zufallszahl(int limit)
  {
    double r = Math.random();
    return (int) (r*limit);
  }
  
  // immer, wenn mit der Mouse geclickt wird, wird diese Methode aufgerufen
  public void mouseClicked(MouseEvent e)
  {
    boolean found;
    int nr = anzahl - 1;
    // bestimme (x,y)-Position des Mouseclicks
    Point mouse_p = e.getPoint();
  
    // suche Rechteck, das angeclickt wurde (von hinter her, da die
    // zuletzt gezeichneten Rechtecke die am ehesten sichtbaren sind)
    do
    {
      found = rechteck[nr].contains(mouse_p);
      if (!found)
        nr--;
    }
    while (!found && nr >= 0);
    
    if (found)
    {
      // stelle alte Farbe des zuletzt selektierten Rechtecks wieder her
      rechteck[clicked_rechteck].setFarbe(alte_farbe);
      
      // vermerke das angeclickte Rechteck und speichere dessen Farbe
      clicked_rechteck = nr;
      alte_farbe = rechteck[clicked_rechteck].getFarbe();
      
      // zeichne selektiertes Rechteck in spezieller Farbe
      rechteck[nr].setFarbe(selected);
      
      // fordere Applet auf, sich neu zu zeichnen
      repaint();
    }
  }
  
  // immer, wenn die linke Mousetaste gedrueckt gehalten wird, wird diese Methode 
  // zu Anfang des Drueckens aufgerufen
  public void mousePressed(MouseEvent e)
  {
    boolean found;
    int nr = anzahl - 1;
    // bestimme (x,y)-Anfangsposition der Mousebewegung
    anfang = e.getPoint();
  
    // suche Rechteck, das selektiert wurde (von hinter her, da die
    // zuletzt gezeichneten Rechtecke die am ehesten sichtbaren sind)
    do
    {
      found = rechteck[nr].contains(anfang);
      if (!found)
        nr--;
    }
    while (!found && nr >= 0);
    
    if (found)
    {
      // selektiertes Rechteck fuer Verschieben merken
      moved_rechteck = nr;
    }
  }
  
  // immer, wenn die linke Mousetaste gedrueckt gehalten wurde und dann ausgelassen 
  // wurde, wird diese Methode am Ende des Drueckens aufgerufen
  public void mouseReleased(MouseEvent e)
  {
    // bestimme (x,y)-Endposition der Mousebewegung
    ende = e.getPoint();
    // bestimme Verschiebungsvektor
    Point translation = new Point(ende.x - anfang.x, ende.y - anfang.y);
    
    // verschiebe die erste Ecke um diesen Vektor
    rechteck[moved_rechteck].setErsteEckeX(
      rechteck[moved_rechteck].getErsteEckeX() + translation.x);
    rechteck[moved_rechteck].setErsteEckeY(
      rechteck[moved_rechteck].getErsteEckeY() + translation.y);
    
    // fordere Applet auf, sich neu zu zeichnen
    repaint();
  }
  
  // die naechsten beiden MouseEvents werden ignoriert
  public void mouseEntered(MouseEvent e)
  {
  }
  
  public void mouseExited(MouseEvent e)
  {
  }
}


class Rechteck
{
	int eckex, eckey;
	int hoehe, breite;
                Color farbe; 

	public Rechteck()
	{
		eckex = eckey = 0;
		hoehe = breite = 1;
		farbe = Color.green;
	}

	public Rechteck(int width, int height)
	{
		eckex = 0;
		eckey = 0;
		hoehe = Math.abs(height);
		breite = Math.abs(width);
		farbe = Color.green;
	}

	public Rechteck(int corner1x, int corner1y, int corner2x, int corner2y)
	{
		eckex = Math.abs(corner1x);
		eckey = Math.abs(corner1y);
		breite = Math.abs(corner1x - corner2x);
		hoehe  = Math.abs(corner1y - corner2y);
		farbe = Color.green;
	}

	public int getErsteEckeX()
	{
		return eckex;
	}

	public int getErsteEckeY()
	{
		return eckey;
	}

	public int getZweiteEckeX()
	{
		return (eckex + breite);
	}

	public int getZweiteEckeY()
	{
		return (eckey + hoehe);
	}

	public void setErsteEckeX(int neu)
	{
		eckex = Math.abs(neu);
	}

	public void setErsteEckeY(int neu)
	{
		eckey = Math.abs(neu);
	}

	public void setZweiteEckeX(int neu)
	{
		breite = Math.abs(neu - eckex);
	}

	public void setZweiteEckeY(int neu)
	{
		hoehe = Math.abs(neu - eckey);
	}

	public void setFarbe(int red, int green, int blue)
	{
		farbe = new Color(Math.abs(red), Math.abs(green), Math.abs(blue));
	}

	public void setFarbe(Color neu)
	{
		farbe = neu;
	}

	public Color getFarbe()
	{
		return  farbe;
	}
               
                public void zeichneRechteck(Graphics g)
	{
	                Color akt_farbe = g.getColor();
        
                                g.setColor(farbe);
         
                                g.fillRect(eckex, eckey, breite, hoehe);
        
                                g.setColor(akt_farbe);
	}
  
	public boolean contains(Point p)
	{
		if ( (p.x >= eckex) && (p.x <= (eckex + breite)) && (p.y >= eckey) && (p.y <= (eckey + hoehe)) )
			return true;
		else
			return false;
	}
}



