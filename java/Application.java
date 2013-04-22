import java.awt.*;
import java.awt.event.*;

public class ApplicationApplet
{
    public static void main(String [] argv)
    {
        MyFrame fenster = new MyFrame("ApplicationApplet by Heiko Vogel");
        fenster.setVisible(true);
    }
}

class MyFrame extends Frame implements WindowListener, ActionListener
{
    public MyFrame()
    {
        this("");
    }

    public MyFrame(String titel)
    {
        super(titel);

        addWindowListener(fenster);
    }

    public void windowActivated(WindowEvent e)
    {}
    public void windowClosed(WindowEvent e)
    {}
    public void windowClosing(WindowEvent e)
    {
        setVisible(false);
        dispose();
        System.exit(0);
    }
    public void windowDeactivated(WindowEvent e)
    {}
    public void windowDeiconified(WindowEvent e)
    {}
    public void windowIconified(WindowEvent e)
    {}
    public void windowOpened(WindowEvent e)
    {}
    public void actionPerformed(ActionEvent e)
    {}
}
