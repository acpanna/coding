

public class Test
{
    public static void main(String [] argv)
    {
        MyPoint p1 = new MyPoint();
        MyPoint p2 = new MyPoint(1.0, 2.0);

        Kreis k1 = new Kreis();
        Kreis k2 = new Kreis(p2, 3.0);

        Strecke s1 = new Strecke();
        Strecke s2 = new Strecke(0.0, -2.0, 1.0, 1.0);
        Strecke s3 = new Strecke(p1, p2);

        Quadrat q1 = new Quadrat();
        Quadrat q2 = new Quadrat(q1);
        Quadrat q3 = new Quadrat(1.0, 2.0, 3.0, 4.0);

        System.out.println("MyPoint p1 = new MyPoint(): X="+p1.getX()+", Y="+p1.getY()+"");
        System.out.println("MyPoint p2 = new MyPoint(1.0, 2.0): X="+p2.getX()+", Y="+p2.getY()+"");

        System.out.println("Kreis k1 = new Kreis(): X="+k1.getX()+", Y="+k1.getY()+", RADIUS="+k1.getRadius()+"");
        System.out.println("Kreis k2 = new Kreis(p2, 3.0): X="+k2.getX()+", Y="+k2.getY()+", RADIUS="+k2.getRadius()+"");

        System.out.println("Strecke s1 = new Strecke(): X="+s1.getX()+", Y="+s1.getY()+", XX="+s1.getXX()+", YY="+s1.getYY()+"");
        System.out.println("Strecke s2 = new Strecke(0.0, -2.0, 1.0, 1.0): X="+s2.getX()+", Y="+s2.getY()+", XX="+s2.getXX()+", YY="+s2.getYY()+"");
        System.out.println("Strecke s3 = new Strecke(p1, p2): X="+s3.getX()+", Y="+s3.getY()+", XX="+s3.getXX()+", YY="+s3.getYY()+"");

        System.out.println("Quadrat q1 = new Quadrat(): X="+q1.getX()+", Y="+q1.getY()+", XX="+q1.getXX()+", YY="+q1.getYY()+"");
        System.out.println("Quadrat q2 = new Quadrat(q1): X="+q2.getX()+", Y="+q2.getY()+", XX="+q2.getXX()+", YY="+q2.getYY()+"");
        System.out.println("Quadrat q3 = new Quadrat(1.0, 2.0, 3.0, 4.0): X="+q3.getX()+", Y="+q3.getY()+", XX="+q3.getXX()+", YY="+q3.getYY()+"");

        p1.moveTo(1.5, 2.5);
        System.out.println("p1.moveTo(1.5, 2.5): X="+p1.getX()+", Y="+p1.getY()+"");
        p2.addPoint(2.0, 4.0);
        System.out.println("p2.addPoint(2.0, 4.0): X="+p2.getX()+", Y="+p2.getY()+"");

        k1.moveTo(1.0, 1.0);
        System.out.println("k1.moveTo(1.0, 1.0): X="+k1.getX()+", Y="+k1.getY()+", RADIUS="+k1.getRadius()+"");
        k1.addPoint(1.0, 2.0);
        System.out.println("k1.addPoint(1.0, 2.0): X="+k1.getX()+", Y="+k1.getY()+", RADIUS="+k1.getRadius()+"");
        k2.multSkalar(3.0);
        System.out.println("k2.multSkalar(3.0): X="+k2.getX()+", Y="+k2.getY()+", RADIUS="+k2.getRadius()+"");
        k2.stretch(2.5);
        System.out.println("k2.stretch(2.5): X="+k2.getX()+", Y="+k2.getY()+", RADIUS="+k2.getRadius()+"");

        s1.moveTo(0.0, 3.0);
        System.out.println("s1.moveTo(0.0, 3.0): X="+s1.getX()+", Y="+s1.getY()+", XX="+s1.getXX()+", YY="+s1.getYY()+"");
        s2.addPoint(1.0, 1.0);
        System.out.println("s2.addPoint(1.0, 1.0): X="+s2.getX()+", Y="+s2.getY()+", XX="+s2.getXX()+", YY="+s2.getYY()+"");
        s2.multSkalar(4.0);
        System.out.println("s2.multSkalar(4.0): X="+s2.getX()+", Y="+s2.getY()+", XX="+s2.getXX()+", YY="+s2.getYY()+"");
        s3.stretch(0.5);
        System.out.println("s3.stretch(0.5): X="+s3.getX()+", Y="+s3.getY()+", XX="+s3.getXX()+", YY="+s3.getYY()+"");

        q1.moveTo(2.0, 3.0);
        System.out.println("q1.moveTo(2.0, 3.0): X="+q1.getX()+", Y="+q1.getY()+", XX="+q1.getXX()+", YY="+q1.getYY()+"");
        q2.addPoint(2.0, 1.0);
        System.out.println("q2.addPoint(2.0, 1.0): X="+q2.getX()+", Y="+q2.getY()+", XX="+q2.getXX()+", YY="+q2.getYY()+"");
        q2.multSkalar(-3.0);
        System.out.println("q2.multSkalar(-3.0): X="+q2.getX()+", Y="+q2.getY()+", XX="+q2.getXX()+", YY="+q2.getYY()+"");
        q3.stretch(1.5);
        System.out.println("q3.stretch(1.5): X="+q3.getX()+", Y="+q3.getY()+", XX="+q3.getXX()+", YY="+q3.getYY()+"");
    }
}
