public class KreisKurve extends Kurve
{
    public KreisKurve(int N, double mx, double my, double r)
    {
        super(N, mx, my, r, 0);
    }

    public void getKoord()
    {
        double h = 2.0*Math.PI/N;

        for (int i=0; i<N+1; i++)
        {
            x[i] = x1 + x2*Math.cos(i*h);
            y[i] = y1 + x2*Math.sin(i*h);
        }
    }

    public double getMX()
    {
        return x1;
    }

    public double getMY()
    {
        return y1;
    }

    public double getRadius()
    {
        return x2;
    }
}