public abstract class Kurve
{
    protected int N;

    protected double [] x;
    protected double [] y;

    protected double x1;  // Hier wird mx bzw. px gespeichert
    protected double x2;  // Hier wird my bzw. py gespeichert
    protected double y1;  // Hier wird r bzw. qx gespeichert
    protected double y2;  // Hier wird 0 bzw. qy gespeichert

    Kurve(int N, double x1, double y1, double x2, double y2)
    {
        if (N == 0)
            N = 1;        // Falls N gleich Null, setze N gleich 1, weil sonst Kurve aus 1 Punkt !!!

        this.N = N;

        this.x = new double[N+1];
        this.y = new double[N+1];

        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;

        getKoord();
    }

    public Object move(double xx, double yy)
    {
        for (int i=0; i<N+1; i++)
        {
            x[i] += xx;
            y[i] += yy;
        }

        return this;
    }

    public Object scale(double sk)
    {
        for (int i=0; i<N+1; i++)
        {
            x[i] *= sk;
            y[i] *= sk;
        }

        return this;
    }

    public int getN()
    {
        return N;
    }

    public double getXAt(int index)
    {
        try
        {
            return x[index];
        }

        catch(IndexOutOfBoundsException exc)
        {
            if (index < 0)
              return x[0];
            else
              return x[N];
        }
    }

    public double getYAt(int index)
    {
        try
        {
            return y[index];
        }

        catch(IndexOutOfBoundsException exc)
        {
            if (index < 0)
              return y[0];
            else
              return y[N];
        }
    }

    public abstract void getKoord();
}





