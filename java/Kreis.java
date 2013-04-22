public class Kreis extends MyPoint
{
    protected double radius;

    public Kreis()
    {
        super();
        radius = 1.0;
    }

    public Kreis(MyPoint p, double rad)
    {
        super(p);
        radius = rad;
    }

    public Kreis(double x, double y, double rad)
    {
        this.x = x;
        this.y = y;
        radius = rad;
    }

    public double getRadius()
    {
        return radius;
    }

    public void setRadius(double rad)
    {
        radius = rad;
    }

    public void multSkalar(double skalar)
    {
        super.multSkalar(skalar);
        radius *= skalar;
    }

    public void stretch(double faktor)
    {
        radius *= faktor;
    }
}
