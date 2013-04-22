import java.awt.*;
import java.applet.Applet;

public class PrintJava extends Applet
{
    int rand;
    Dimension dim;    
    
    char buchstaben [];  

    int x_oben_pos [], y_oben_pos [];
    int x_links_pos [], y_links_pos [];
    int x_quer_pos [], y_quer_pos [];
    
    public void init()
    {
        rand = 20;
        setBackground(Color.lightGray);
       
       buchstaben = new char[]{ 'J', 'a', 'v', 'a' };        
       
        y_links_pos = new int[buchstaben.length];
        x_quer_pos = new int[buchstaben.length];
        y_quer_pos = new int[buchstaben.length];
        x_oben_pos = new int[buchstaben.length];
        y_oben_pos =new int[buchstaben.length];       
    }
   
    public void paint(Graphics g) 
    {
        bestimme_positionen();

        g.setColor(Color.red);        
        for (int i = 0; i < buchstaben.length; i++)
          g.drawString("" + buchstaben[i], x_oben_pos[i], y_oben_pos[i]);

        g.setColor(Color.green);
        for (int i = 0; i < buchstaben.length; i++)
          g.drawString("" + buchstaben[i], x_links_pos[i], y_links_pos[i]);
            
        g.setColor(Color.blue);
        for (int i = 0; i < buchstaben.length; i++)
          g.drawString("" + buchstaben[i], x_quer_pos[i], y_quer_pos[i]);
    }   
    
    public void bestimme_positionen()
    {
        dim = getSize();
       
        for (int i = 0; i <buchstaben.length; i++)
        {
          x_oben_pos[i] = rand + (int) (i*(dim.width - 2*rand)/
                                          ((double) x_oben_pos.length - 1));
          y_oben_pos[i] = rand;

          x_quer_pos[i] = rand + (int) (i*(dim.width - 2*rand)/
                                          ((double) x_quer_pos.length - 1));
          y_quer_pos[i] = rand + (int) (i*(dim.height - 2*rand)/
                                          ((double) y_links_pos.length - 1));
          y_links_pos[i] = rand + (int) (i*(dim.height - 2*rand)/
                                          ((double) y_links_pos.length - 1));       
        }
        
        x_links_pos = y_oben_pos;
    }
}
