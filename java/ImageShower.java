import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;

public class ImageShower extends Applet implements AdjustmentListener
{
    private int imgID;
    private Image img;
    private ScrollPane scroller;
    private BildCanvas context;
    private MediaTracker tracker;
    private Adjustable barh, barv;

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

        context = new BildCanvas(img);
        scroller = new ScrollPane();

        scroller.setSize(getSize());

        scroller.add(context);
        add(scroller, "Center");

        barh = scroller.getHAdjustable();
        barv = scroller.getVAdjustable();

        barh.addAdjustmentListener(this);
        barv.addAdjustmentListener(this);
    }

    public void adjustmentValueChanged(AdjustmentEvent evt)
    {
        if (evt.getAdjustable() == barh)
            showStatus("Horizontales Scrolling, neue Position: " + barh.getValue());
        else if (evt.getAdjustable() == barv)
            showStatus("Vertikales Scrolling, neue Position: " + barv.getValue());
    }
}

class BildCanvas extends Canvas
{
    private Image img;

    public BildCanvas(Image show)
    {
        super();

        img = show;
        setSize(260, 310);
   }

    public void paint(Graphics g)
    {
        g.drawImage(img, 0, 0, this);
    }
}
