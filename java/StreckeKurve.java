public class StreckeKurve extends Kurve
{
    public StreckeKurve(int N, double px, double py, double qx, double qy)
    {
        super(N, px, py, qx, qy);
    }

    public void getKoord()
    {
        double h = 1.0/N;

        for (int i=0; i<N+1; i++)
        {
            x[i] = x1 + (i*h) * (x2 - x1);
            y[i] = y1 + (i*h) * (y2 - y1);
        }
    }

    public double getPX()
    {
        return x1;
    }

    public double getPY()
    {
        return y1;
    }

    public double getQX()
    {
        return x2;
    }

    public double getQY()
    {
        return y2;
    }
}