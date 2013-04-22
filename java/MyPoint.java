import java.awt.Color;

public class MyPoint
{
    protected static int anzahl = 0;

    protected double x;
    protected double y;

    protected boolean isVisible;

    public MyPoint()
    {
        x = 0.0;
        y = 0.0;

        isVisible = false;
        anzahl++;
    }

    public MyPoint(double xx, double yy)
    {
        x = xx;
        y = yy;

        isVisible = true;
        anzahl++;
    }

    public MyPoint(MyPoint point)
    {
        x = point.x;
        y = point.y;

        isVisible = true;
        anzahl++;
    }

    public static int getAnzahl()
    {
        return anzahl;
    }

    public double getX()
    {
        return x;
    }

    public double getY()
    {
        return y;
    }

    public boolean getStatus()
    {
        return isVisible;
    }

    public void hide()
    {
        isVisible = false;
    }

    public void show()
    {
        isVisible = true;
    }

    public void setX(double new_x)
    {
        x = new_x;
    }

    public void setY(double new_y)
    {
        y = new_y;
    }

    public void moveTo(double new_x, double new_y)
    {
        x = new_x;
        y = new_y;
    }

    public void addPoint(double xx, double yy)
    {
        x += xx;
        y += yy;
    }

    public void multSkalar(double skalar)
    {
        x *= skalar;
        y *= skalar;
    }

    protected void finalize()
    {
        anzahl--;
    }
}




