import java.awt.*;
import java.awt.event.*;
import java.applet.Applet;

public class PaintApplet extends Applet implements ActionListener, ItemListener, MouseListener, MouseMotionListener
{
    private Label status;
    private Panel menu;
    private MyCanvas canvas;
    private Choice farbe;
    private Color color;
    private Checkbox filled;
    private Button button [];
    private String namen [];
    private String farben [];

    private byte type;
    private Point start, end;

    public void init()
    {
        status = new Label("", Label.CENTER);
        menu = new Panel();
        canvas = new MyCanvas();
        farbe = new Choice();
        color = Color.blue;
        filled = new Checkbox("ausgefuellt");
        namen = new String[]{ "Rechteck", "Kreis", "Ellipse" };
        farben = new String[]{ "blau", "gelb", "gruen", "rot", "schwarz", "weiss" };
        button = new Button[namen.length];

        type = -1;

        for (int i=0; i<namen.length; i++)
        {
            button[i] = new Button(namen[i]);
            button[i].addActionListener(this);
            menu.add(button[i]);
        }

        for (int i=0; i<farben.length; i++)
            farbe.add(farben[i]);

        filled.addItemListener(this);
        farbe.addItemListener(this);
        canvas.addMouseListener(this);
        canvas.addMouseMotionListener(this);

        menu.add(filled);
        menu.add(farbe);

        setLayout(new BorderLayout());
        setBackground(Color.lightGray);

        add(menu, "North");
        add(canvas, "Center");
        add(status, "South");
    }

    public void actionPerformed(ActionEvent evt)
    {
        if (evt.getSource() == button[0])
        {
            status.setText("Rechtecke zeichnen");
            type = 0;
        }

        if (evt.getSource() == button[1])
        {
            status.setText("Kreise zeichnen");
            type = 1;
        }

        if (evt.getSource() == button[2])
        {
            status.setText("Ellipsen zeichnen");
            type = 2;
        }
    }

    public void itemStateChanged(ItemEvent evt)
    {
        if (evt.getSource() == farbe)
        {
            status.setText("Farbe " + farben[farbe.getSelectedIndex()] + " ausgewaehlt");

            switch(farbe.getSelectedIndex())
            {
                case 0: color = Color.blue;
                        break;
                case 1: color = Color.yellow;
                        break;
                case 2: color = Color.green;
                        break;
                case 3: color = Color.red;
                        break;
                case 4: color = Color.black;
                        break;
                case 5: color = Color.white;
            }
        }

        else if (evt.getSource() == filled)
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

    public void mouseMoved(MouseEvent evt)
    {}
    public void mouseClicked(MouseEvent evt)
    {}
    public void mouseEntered(MouseEvent evt)
    {}
    public void mouseExited(MouseEvent evt)
    {}
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