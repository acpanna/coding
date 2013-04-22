import java.applet.*;
import java.awt.*;

public class MyButton extends Applet
{
  Button button1;
  Button button2;
  
  public void init()
  {
    button1 = new Button("Drueck mich !");   // dies sind die einzigen Möglichkeiten 
    button2 = new Button();                               // einen Button anzulegen

    add(button1);
    add(button2);
  }

  public void paint(Graphics g)
  {
  }
} 