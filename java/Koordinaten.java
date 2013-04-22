       import java.applet.Applet;
       import java.awt.*;
       import java.awt.event.*;

       public class Koordinaten extends Applet implements MouseListener
       {
         int x, y, width, height;
         Dimension groesse;
         FontMetrics fm;
         String ausgabe;

         public void init()
         {
           groesse = new Dimension(getBounds().width, getBounds().height);
           fm = getFontMetrics(getFont());
           addMouseListener(this);
         }

         public void mousePressed(MouseEvent evt)
         {
           x = evt.getX();
           y = evt.getY();
           ausgabe = "Koordinaten: (x,y) = (" + x + "," + y + ")";
           height = fm.getHeight();
           width  = fm.stringWidth(ausgabe);

           if (x + width > groesse.width)
             x = x - width;
           if (y - height < 0)
             y = y + height;
           setForeground(Color.blue);
           getGraphics().drawString(ausgabe, x, y);
         }

         public void mouseReleased(MouseEvent evt)
         {
           setForeground(getBackground());
           getGraphics().drawString(ausgabe, x, y);
         }

         // notwendige Definitionen fuer MouseListener
         // da keine Reaktion auf diese Events, leere Funktionen
         public void mouseClicked(MouseEvent evt)
         {
         }

         public void mouseEntered(MouseEvent evt)
         {
         }

         public void mouseExited(MouseEvent evt)
         {
         }
       }
