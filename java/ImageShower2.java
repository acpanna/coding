import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class ImageShower2 extends Applet implements AdjustmentListener
{
    private int imgID;
    private Image img;
    private Scrollbar scrollh, scrollv;
    private BildCanvas context;
    private MediaTracker tracker;

    public void init()
    {
        img = getImage(getDocumentBase(), "pinguin.gif");

        imgID = 1;
        tracker = null;

        try
        {
            tracker = new MediaTracker(this);
            tracker.addImage(img, imgID);
            tracker.waitForID(imgID);
        }
        catch (InterruptedException exc)
        {
            showStatus("Bildladen unterbrochen !");
            System.err.println(exc);
        }

        if (tracker.isErrorAny())
            showStatus("Bildladen hat NICHT geklappt !");
        else
            showStatus("Bildladen hat geklappt !");

        while (tracker.checkID(imgID) == false)
            showStatus("Sorry, Bildladen noch nicht fertig !");

        Dimension size = getSize();

        context = new BildCanvas(img);
        scrollh = new Scrollbar(Scrollbar.HORIZONTAL, 0, 260 - (260 - size.width + 20), 0, 260);
        scrollv = new Scrollbar(Scrollbar.VERTICAL, 0, 310 - (310 - size.height + 20), 0, 310);

        scrollh.setUnitIncrement(2);
        scrollv.setUnitIncrement(2);
        scrollh.setBlockIncrement(20);
        scrollv.setBlockIncrement(20);

        setLayout(new BorderLayout());

        add(context, "Center");
        add(scrollh, "South");
        add(scrollv, "East");

        scrollh.addAdjustmentListener(this);
        scrollv.addAdjustmentListener(this);
    }

    public void adjustmentValueChanged(AdjustmentEvent evt)
    {
        if (evt.getAdjustable() == scrollh)
        {
            showStatus("Horizontales Scrolling, neue Position: " + evt.getValue());
            context.x = -evt.getValue();
            context.repaint();
        }
        else if (evt.getAdjustable() == scrollv)
        {
            showStatus("Vertikales Scrolling, neue Position: " + evt.getValue());
            context.y = -evt.getValue();
            context.repaint();
        }
    }
}

class BildCanvas extends Canvas
{
    private Image img;
    protected int x, y;

    public BildCanvas(Image show)
    {
        super();

        img = show;
        x = y = 0;
        setSize(260, 310);
   }

    public void paint(Graphics g)
    {
        g.drawImage(img, x, y, this);
    }
}
