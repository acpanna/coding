import java.applet.Applet;
import java.awt.*;

public class RandApplet extends Applet
                        implements Runnable
{
  Dimension dim;
  int anzahl;                          // hier: Anzahl der Farben definieren, nicht initialisieren!
  int farben [][];                   // hier: Arrays definieren, nicht initialisieren!
  Thread t;

  public void init()
  {
    anzahl = getIntParameter("anzahl");    // hier: Wert fuer Anzahl der Farben zuweisen mit getIntParameter()
    farben = new int[anzahl][3];                  // hier: Arrays dynamisch erzeugen
    
    for (int i=0; i<anzahl; i++)
   {
     farben[i][0] = getIntParameter("rot" + (i+1));
     farben[i][1] = getIntParameter("gruen" + (i+1));      // hier: Komponenten der Arrays zuweisen mit Werten von getIntParameter()
     farben[i][2] = getIntParameter("blau" + (i+1));
   }                                                              
  }

  public void start()
  {
    t = new Thread(this, "Update Rand");
    t.start();
    
    // hier: Arrays in Ausgangssituation bringen
  }
  
  public void run()
  {
    while (t != null)
    {
      try
      {
        // Pause
        t.sleep(1000);
      }
      catch (InterruptedException exc)
      {
        System.err.println("abgebrochener Thread: " + t.getName());
      }
      // Aufruf fuer einen Update der Arrays, um Wandern der Farben zu erzeugen
      update_rand();
    }
  }

  public void paint(Graphics g)
  {
    dim = getSize();               // hier: Variable dim mit Wert besetzen
    
    g.setColor(Color.red);
    g.drawRect(0, 0, dim.width - 1, dim.height - 1);

    int posx = 0, posy = 0;
  
    while (posy < dim.height-20 || posx < dim.width)
    {
      for (int i=0; i<anzahl; i++)
      {
        if (posx  > dim.width)
        {
          posx = 0;
          posy = dim.height-20;
          drawRectangle(g, posx, posy, 100, 20, farben[i][0], farben[i][1], farben[i][2]); 
          posx += 100;
        }

        else
        {
          drawRectangle(g, posx, posy, 100, 20, farben[i][0], farben[i][1], farben[i][2]); 
          posx += 100;
        }
      }
    }

    posx = 0;                                                                                     // Zeichnen von oberen, unteren, linken und rechten Rand
    posy = 0;                                                                                    //   mit drawRectangle() mit den Farbwerten aus den Arrays    

    while (posx < dim.width-20 || posy < dim.height)
    {
       for (int i=0; i<anzahl; i++)
       {
         if (posy  > dim.height)
         {
           posy = 0;
           posx = dim.width-20;
           drawRectangle(g, posx, posy, 20, 100, farben[i][0], farben[i][1], farben[i][2]);
           posy += 100;
         }
     
         else
         {
           drawRectangle(g, posx, posy, 20, 100, farben[i][0], farben[i][1], farben[i][2]);
           posy += 100;
         }
       }
    }
  }

  public void stop()
  {
    // t.stop(); // unsafe
    t = null;
  }
  
  public void update_rand()
  {
    int i;

    int temp0 = farben[0][0];
    int temp1 = farben[0][1];
    int temp2 = farben[0][2];
    
    for (i=0; i<anzahl-1; i++)
    {
      farben[i][0] = farben[i+1][0];
      farben[i][1] = farben[i+1][1];                      // hier: Aendern der Arrays fuer die Farbwerte durchfuehren
      farben[i][2] = farben[i+1][2];
    }

    farben[i][0] = temp0;
    farben[i][1] = temp1;
    farben[i][2] = temp2;

    
    repaint();                                                         // schlage das Wiederzeichnen vor
  }
  
  // ein Rechteck mit linker oberer Ecke (x, y) 
  //   und Dimension (width+1) x (height+1) 
  //   in der RGB-Farbe (red, green, blue) wird gezeichnet
  
  public void drawRectangle(Graphics g, 
                            int x, int y, int width, int height, 
                            int red, int green, int blue)
  {
    Color curr_col = g.getColor();
    g.setColor(new Color(red, green, blue));
    g.fillRect(x, y, width, height);
    g.setColor(curr_col);
  }
  
  // lese Wert des Parameters mit uebergebenem Namen param_name
  //   aus dem HTML-File und wandle diesen String in einen int-Wert um
  
  public int getIntParameter(String param_name)
  {
    String param_value = getParameter(param_name);
    if (param_value == null)
    {
      System.err.println("Parameter \"" + param_name 
                         + "\" nicht gesetzt im HTML-File");
      return 0;
    }
    
    Integer iObj = null;
    try
    {
      iObj = new Integer(param_value);
      return iObj.intValue();
    }
    catch (NumberFormatException exc)
    {
      System.err.println("Fehler beim Umwandeln von \"" + param_value
                         + "\" in int-Wert!");
      return 0;
    }
  }
}
