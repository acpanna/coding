import java.awt.*;
import java.awt.event.*;

public class PaintApplikation
{
    public static void main(String [] argv)
    {
        MyFrame fenster = new MyFrame("PaintApplikation");

        fenster.setSize(400, 400);
        fenster.setBackground(Color.lightGray);
        fenster.setVisible(true);
    }
}

class MyFrame extends Frame implements ActionListener, ItemListener, MouseListener, MouseMotionListener, WindowListener
{
    private Label status;
    private MenuBar menubar;
    private Menu menuGrafik, menuZeichen, menuFarben;
    private MenuItem form [], farbe [];
    private MenuShortcut shortcut [];
    private CheckboxMenuItem filled;
    private MyCanvas canvas;
    private Color color;

    private String namen [];
    private String farben [];

    private byte type;
    private Point start, end;

    public MyFrame(String titel)
    {
        super(titel);

        status = new Label("", Label.CENTER);
        menubar = new MenuBar();
        menuGrafik = new Menu("Grafikobjekte");
        menuZeichen = new Menu("Zeichenstil");
        menuFarben = new Menu("Zeichenfarbe");

        filled = new CheckboxMenuItem("ausgefuellt");
        canvas = new MyCanvas();
        color = Color.blue;

        namen = new String[]{ "Rechteck", "Kreis", "Ellipse" };
        farben = new String[]{ "blau", "gelb", "gruen", "rot", "schwarz", "weiss" };

        form = new MenuItem[namen.length];
        farbe = new MenuItem[farben.length];
        shortcut = new MenuShortcut[namen.length + farben.length];

        type = -1;

        for (int i=0; i<namen.length; i++)
        {
            shortcut[i] = new MenuShortcut((int) namen[i].charAt(0));
            form[i] = new MenuItem(namen[i], shortcut[i]);
            menuGrafik.add(form[i]);
            form[i].addActionListener(this);
        }

        for (int i=0; i<farben.length; i++)
        {
            shortcut[namen.length + i] = new MenuShortcut((int) farben[i].charAt(farben[i].length() - 1));
            farbe[i] = new MenuItem(farben[i], shortcut[namen.length + i]);
            menuFarben.add(farbe[i]);
            farbe[i].addActionListener(this);
        }

        menuZeichen.add(filled);
        menuZeichen.add(menuFarben);

        menubar.add(menuGrafik);
        menubar.add(menuZeichen);

        filled.addItemListener(this);
        canvas.addMouseListener(this);
        canvas.addMouseMotionListener(this);

        setLayout(new BorderLayout());

        setMenuBar(menubar);

        add(canvas, "Center");
        add(status, "South");

        addWindowListener(this);
    }

    public void actionPerformed(ActionEvent evt)
    {
        if (evt.getSource() == form[0])
        {
            status.setText("Rechtecke zeichnen");
            type = 0;
        }

        if (evt.getSource() == form[1])
        {
            status.setText("Kreise zeichnen");
            type = 1;
        }

        if (evt.getSource() == form[2])
        {
            status.setText("Ellipsen zeichnen");
            type = 2;
        }

        if (evt.getSource() == farbe[0])
        {
            status.setText("Farbe " + farbe[0].getLabel() + " ausgewaehlt");
            color = Color.blue;
        }

        if (evt.getSource() == farbe[1])
        {
            status.setText("Farbe " + farbe[1].getLabel() + " ausgewaehlt");
            color = Color.yellow;
        }

        if (evt.getSource() == farbe[2])
        {
            status.setText("Farbe " + farbe[2].getLabel() + " ausgewaehlt");
            color = Color.green;
        }

        if (evt.getSource() == farbe[3])
        {
            status.setText("Farbe " + farbe[3].getLabel() + " ausgewaehlt");
            color = Color.red;
        }

        if (evt.getSource() == farbe[4])
        {
            status.setText("Farbe " + farbe[4].getLabel() + " ausgewaehlt");
            color = Color.black;
        }

        if (evt.getSource() == farbe[5])
        {
            status.setText("Farbe " + farbe[5].getLabel() + " ausgewaehlt");
            color = Color.white;
        }
    }

    public void itemStateChanged(ItemEvent evt)
    {
        if (evt.getSource() == filled)
        {
            if (filled.getState() == true)
                status.setText("Ausgefuellt zeichnen");
            else
                status.setText("Rahmen zeichnen");
        }
    }

    public void mouseDragged(MouseEvent evt)
    {
        Graphics g = canvas.getGraphics();
        g.setColor(color);

        if (type == 0)
        {
            g.setXORMode(canvas.getBackground());
            g.drawRect(start.x, start.y, end.x - start.x, end.y - start.y);
            end = evt.getPoint();
            g.drawRect(start.x, start.y, end.x - start.x, end.y - start.y);
        }

        else if (type == 1)
        {
            int radius;

            g.setXORMode(canvas.getBackground());

            radius = (int) Math.sqrt(Math.pow(end.x - start.x, 2) + Math.pow(end.y - start.y, 2));

            g.drawOval(start.x-radius, start.y-radius, 2 * radius, 2 * radius);
            end = evt.getPoint();

            radius = (int) Math.sqrt(Math.pow(end.x - start.x, 2) + Math.pow(end.y - start.y, 2));

            g.drawOval(start.x - radius, start.y - radius, 2 * radius, 2 * radius);
        }

        else if (type == 2)
        {
            g.setXORMode(canvas.getBackground());
            g.drawOval(start.x, start.y, end.x - start.x, end.y - start.y);
            end = evt.getPoint();
            g.drawOval(start.x, start.y, end.x - start.x, end.y - start.y);
        }
    }

    public void mousePressed(MouseEvent evt)
    {
        start = end = evt.getPoint();

        if ( type == -1)
            status.setText("Keine Form ausgewaehlt");
        else if ( type == 0 )
            status.setText("1. Ecke des Rechtecks festgelegt");
        else if ( type == 1 )
            status.setText("Mittelpunkt des Kreises festgelegt");
        else if ( type == 2 )
            status.setText("Zentrum der Ellipse festgelegt");
    }

    public void mouseReleased(MouseEvent evt)
    {
        Graphics g = canvas.getGraphics();
        g.setColor(color);
        g.setPaintMode();
        end = evt.getPoint();

        if (type == 0)
        {
            g.drawRect(start.x, start.y, end.x - start.x, end.y - start.y);

            if (filled.getState() == true)
                g.fillRect(start.x, start.y, end.x - start.x, end.y - start.y);

            status.setText("2. Ecke des Rechtecks festgelegt");
        }

        else if (type == 1)
        {
            int radius;

            radius = (int) Math.sqrt(Math.pow(end.x - start.x, 2) + Math.pow(end.y - start.y, 2));

            g.drawOval(start.x - radius, start.y - radius, 2 * radius, 2 * radius);

            if (filled.getState() == true)
                g.fillOval(start.x - radius, start.y - radius, 2 * radius, 2 * radius);

            status.setText("Radius des Kreises festgelegt");
        }

        else if (type == 2)
        {
            g.drawOval(start.x, start.y, end.x - start.x, end.y - start.y);

            if (filled.getState() == true)
                g.fillOval(start.x, start.y, end.x - start.x, end.y - start.y);

            status.setText("Radius der Ellipse festgelegt");
        }
    }

    public void windowClosing(WindowEvent e)
    {
         dispose();
         System.exit(0);
    }

    public void mouseMoved(MouseEvent evt)
    {}
    public void mouseClicked(MouseEvent evt)
    {}
    public void mouseEntered(MouseEvent evt)
    {}
    public void mouseExited(MouseEvent evt)
    {}
    public void windowActivated(WindowEvent e)
    {}
    public void windowClosed(WindowEvent e)
    {}
    public void windowDeactivated(WindowEvent e)
    {}
    public void windowDeiconified(WindowEvent e)
    {}
    public void windowIconified(WindowEvent e)
    {}
    public void windowOpened(WindowEvent e)
    {}
}

class MyCanvas extends Canvas
{
    int width, height;

    public MyCanvas()
    {
        this(new Dimension(200, 200));
    }

    public MyCanvas(Dimension dim)
    {
        super();
        width = dim.width;
        height = dim.height;
    }

    public void paint(Graphics g)
    {
    }

    public Dimension getPreferredSize()
    {
        return new Dimension(width, height);
    }
}
