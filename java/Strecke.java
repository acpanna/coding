public class Strecke extends MyPoint
{
    protected double xx, yy;

    public Strecke()
    {
        super();
        xx = 1.0;
        yy = 1.0;
    }

    public Strecke(MyPoint p1, MyPoint p2)
    {
        super(p1);
        xx = p2.x;
        yy = p2.y;
    }

    public Strecke(double x1, double y1, double x2, double y2)
    {
        super(x1, y1);
        xx = x2;
        yy = y2;
    }

    public Strecke(Strecke s)
    {
        this(s.x, s.y, s.xx, s.yy);
    }

    public double getXX()
    {
        return xx;
    }

    public double getYY()
    {
        return yy;
    }

    public void setXX(double x2)
    {
        xx = x2;
    }

    public void setYY(double y2)
    {
        yy = y2;
    }

    public void addPoint(double xx, double yy)
    {
        super.addPoint(xx, yy);

        this.xx += xx;
        this.yy += yy;
    }

    public void moveTo(double new_x, double new_y)
    {
        addPoint(new_x - x, new_y - y);
    }

    public void multSkalar(double skalar)
    {
        super.multSkalar(skalar);

        xx *= skalar;
        yy *= skalar;
    }

    public void stretch(double faktor)
    {
        MyPoint sym = new MyPoint(x,y);
        sym.addPoint(xx, yy);
        sym.multSkalar(0.5);
        addPoint(-sym.x,-sym.y);
        multSkalar(faktor);
        addPoint(sym.x, sym.y);
    }
}
