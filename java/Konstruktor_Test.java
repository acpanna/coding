public class Konstruktor_Test
{
  public static void main(String [] argv)
  {
    test();
    System.out.println();

    System.out.println("Garbage collection angefordert");
    System.gc();
    System.runFinalization();
    System.runFinalizersOnExit(true);
  }

  public static void test()
  {
    System.out.println("Quadrat q = new Quadrat();");
    Quadrat q = new Quadrat();
    System.out.println("Quadrat q: " + q);
    System.out.println();

    System.out.println("Quadrat q2 = new Quadrat(-2.0, 3.0, 4.0);");
    Quadrat q2 = new Quadrat(-2.0, 3.0, 4.0);
    System.out.println("Quadrat q2: " + q2);
    System.out.println();

    System.out.println("Rechteck r = new Rechteck();");
    Rechteck r = new Rechteck();
    System.out.println("Rechteck r: " + r);
    System.out.println();

    System.out.println("Rechteck r2 = new Rechteck(q2, 5.0);");
    Rechteck r2 = new Rechteck(q2, 5.0);
    System.out.println("Rechteck r2: " + r2);
    System.out.println();

    System.out.println("Rechteck r3 = new Rechteck(-2.0, 3.0, 4.0, 5.0);");
    Rechteck r3 = new Rechteck(-2.0, 3.0, 4.0, 5.0);
    System.out.println("Rechteck r3: " + r3);
    System.out.println();

    System.out.println("Rechteck2 rr = new Rechteck2();");
    Rechteck2 rr = new Rechteck2();
    System.out.println("Rechteck2 rr: " + rr);
    System.out.println();

    System.out.println("Rechteck3 rrr = new Rechteck3(1.0, 2.0, 4.0, 5.0);");
    Rechteck3 rrr = new Rechteck3(1.0, 2.0, 4.0, 5.0);
    System.out.println("Rechteck rrr: " + rrr);
  }
}

class Quadrat
{
  protected double px, py, breite;
  private int id;
  private static int lastID = 0;

  public Quadrat()
  {
    this(0.0, 0.0, 0.0);
    System.out.println("Quadrat() - Konstruktor wurde aufgerufen ...");
    System.out.println("Aktuelle Quadrat - Objekt - ID : " + id);
  }

  public Quadrat(Quadrat q)
  {
    id = ++lastID;
    px = q.px;
    py = q.py;
    breite = q.breite;
    System.out.println("Quadrat(Quadrat q) - Konstruktor wurde aufgerufen ...");
    System.out.println("Aktuelle Quadrat - Objekt - ID : " + id);
  }

  public Quadrat(double x, double y, double seite)
  {
    id = ++lastID;
    px = x;
    py = y;
    breite = seite;
    System.out.println("Quadrat(double x, double y, double seite) - Konstruktor wurde aufgerufen ...");
    System.out.println("Aktuelle Quadrat - Objekt - ID : " + id);
  }

  public void scale(double s)
  {
    px *= s;
    py *= s;
    breite *= s;
  }

  public String toString()
  {
    return "Ecke = (" + px + "," + py + "), Seitenl\u00E4nge: "
           + breite;
  }

  protected void finalize() throws Throwable
  {
    System.out.println("Quadrat - finalize() - Methode wurde aufgerufen,\nQuadrat - Objekt mit ID : "+ id +" wird freigegeben ...");
  }
}

class Rechteck extends Quadrat
{
  protected double hoehe;
  private int id;
  private static int lastID = 0;

  public Rechteck()
  {
    this(0.0, 0.0, 0.0, 0.0);
    System.out.println("Rechteck() - Konstruktor wurde aufgerufen ...");
    System.out.println("Aktuelle Rechteck - Objekt - ID : " + id);
  }

  public Rechteck(Quadrat q, double h)
  {
    super(q);
    id = ++lastID;
    hoehe = h;
    System.out.println("Rechteck(Quadrat q, double h) - Konstruktor wurde aufgerufen ...");
    System.out.println("Aktuelle Rechteck - Objekt - ID : " + id);
  }

  public Rechteck(double x, double y, double br, double h)
  {
    super(x, y, br);
    id = ++lastID;
    hoehe = h;
    System.out.println("Rechteck(double x, double y, double br, double h) - Konstruktor wurde aufgerufen ...");
    System.out.println("Aktuelle Rechteck - Objekt - ID : " + id);
  }

  public void scale(double s)
  {
    super.scale(s); // Aufruf von scale() von Quadrat
    hoehe *= s;
  }

  public String toString()
  {
    return "Ecke = (" + px + "," + py + "), Breite: "
           + breite + ", H\u00F6he: " + hoehe;
  }

  protected void finalize() throws Throwable
  {
    super.finalize();
    System.out.println("Rechteck - finalize() - Methode wurde aufgerufen,\nRechteck - Objekt mit ID : "+ id +" wird freigegeben ...");
  }
}

class Rechteck2 extends Quadrat
{
  protected double hoehe = 0.0;

  public void scale(double s)
  {
    super.scale(s); // Aufruf von scale() von Quadrat
    hoehe *= s;
  }

  public String toString()
  {
    return "Ecke = (" + px + "," + py + "), Breite: "
           + breite + ", H\u00F6he: " + hoehe;
  }

  protected void finalize() throws Throwable
  {
    super.finalize();
    System.out.println("Rechteck2 - finalize() - Methode wurde aufgerufen ...");
  }
}

class Rechteck3 extends Quadrat
{
  protected double hoehe = 0.0;

  public Rechteck3(double x, double y, double br, double h)
  {
    px = x;
    py = y;
    breite = br;
    hoehe = h;
    System.out.println("Rechteck3(double x, double y, double br, double h) - Konstruktor wurde aufgerufen ...");
  }

  public void scale(double s)
  {
    super.scale(s); // Aufruf von scale() von Quadrat
    hoehe *= s;
  }

  public String toString()
  {
    return "Ecke = (" + px + "," + py + "), Breite: "
           + breite + ", H\u00F6he: " + hoehe;
  }

  protected void finalize() throws Throwable
  {
    super.finalize();
    System.out.println("Rechteck3 - finalize() - Methode wurde aufgerufen ...");
  }
}
