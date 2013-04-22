public class Komplex
{
  public double re, im;

  private int id;

  private static int nextID = 0;

  private static int anzahl = 0;

  public Komplex()
  {
    re = im = 0.0;
    id = Komplex.nextID;
    Komplex.anzahl++;
    Komplex.nextID++;
    ausgabe();
  }

  public Komplex(double x)
  {
    re = x;
    im = 0.0;
    id = Komplex.nextID;
    Komplex.anzahl++;
    Komplex.nextID++;
    ausgabe();
  }

  public Komplex(double x, double y)
  {
    re = x;
    im = y;
    id = Komplex.nextID;
    Komplex.anzahl++;
    Komplex.nextID++;
    ausgabe();
  }

  public Komplex(Komplex z)
  {
    re = z.re;
    im = z.im;
    id = Komplex.nextID;
    Komplex.anzahl++;
    Komplex.nextID++;
    ausgabe();
   }
  
  public void add(Komplex z)
  {
    re += z.re;
    im += z.im;
  }

  public void scale(double r)
  {
    re *= r;
    im *= r;
  }

  public static void zufallObjekt()
  {
    Komplex z = new Komplex(Math.random(), Math.random());
    System.out.println("  zuf\u00E4lliges Komplex-Objekt: " + z);
  }
  
  public boolean imSelbenQuadrant(Komplex vgl)
  {
    if (re >= 0.0 && vgl.re >= 0.0 && im >= 0.0 && vgl.im >= 0.0)
      return true;
    else if (re >= 0.0 && vgl.re >= 0.0 && im < 0.0 && vgl.im < 0.0)
      return true;
    else if (re < 0.0 && vgl.re < 0.0 && im >= 0.0 && vgl.im >= 0.0)
      return true;
    else if (re < 0.0 && vgl.re < 0.0 && im < 0.0 && vgl.im < 0.0)
      return true;
    else 
      return false;
  }
  
  public static Komplex getOrigin()
  {
    return new Komplex();
  }

  public String toString()
  {
    String res = "";
    res += "(" + re + "," + im + ")";
    return res;
  }

  public static int getAnzahl()
  {
    return Komplex.anzahl;
  }

  public void ausgabe()
  {
    System.out.println("\nKomplexe Zahl mit ID: "+ id +" wurde erzeugt/zerstoert.");
    System.out.println("Es sind "+ Komplex.getAnzahl() +" komplexe Objekte vorhanden.");
  }      

  protected void finalize() throws Throwable
  {
     Komplex.anzahl--;
    ausgabe();
  }
}
