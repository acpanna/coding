import java.applet.Applet;
import java.awt.*;

public class Aufg4b extends Applet
{
  public void paint(Graphics g)
  {
    int i = 0;
    int j = 0;

    for (i=0; i<255; i++)
    {
      char zeichen = (char) i;
      g.drawString("" + zeichen + "", ((i+1) % 16) * 20 + 10 , j);
      
      if ((i+1) % 16 == 0)
        j = j + 20;
    }
   
    j += 40;
    
    char zeichen1 = (char) 161;
    char zeichen2 = (char) 241;
    char zeichen3 = (char) 233;
    char zeichen4;  

    g.drawString(zeichen1 + "Paco Pe" + zeichen2 + "a! Je suis l'" + zeichen3 + "tranger!", 10, j);    

    zeichen1 = (char) 188;
    zeichen2 = (char) 189;
    zeichen3 = (char) 190;
    zeichen4 = (char) 178;   

    j += 20;

    g.drawString(zeichen1 + " + " + zeichen2 + " = " + zeichen3 + " , (" + zeichen2 + ")" + zeichen4 + " = " + zeichen1, 10, j);       
    zeichen1 = (char) 169;
    zeichen2 = (char) 229;
    zeichen3 = (char) 246;

    j += 20;

    g.drawString(zeichen1 + " H. R" + zeichen2 + "dstr" + zeichen3 + "m", 10, j);
  }
}    
