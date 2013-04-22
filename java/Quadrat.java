public class Quadrat extends Strecke
{
    public Quadrat()
    {
        super();
    }

    public Quadrat(Strecke s)
    {
        super(s);
    }

    public Quadrat(double x, double y, double xx, double yy)
    {
        super(x, y, xx, yy);
    }

    public Quadrat(Quadrat q)
    {
        super(q);
    }

    public void stretch(double faktor)
    {
        Strecke s1 = new Strecke(x, y, xx, y);
        Strecke s2 = new Strecke(x, y, x, yy);

        s1.stretch(faktor);
        s2.stretch(faktor);

        x = s1.x;
        y = s2.y;
        xx = s1.xx;
        yy = s2.yy;
    }
}