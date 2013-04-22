public class KomplexTest
{
  public static void main(String [] argv)
  {
    Komplex z1 = new Komplex(),                                                             	// Komplex() - Konstruktor - Aufruf
	    z2 = new Komplex(3.0),                                                   	    	// Komplex(double x) - Konstruktor - Aufruf 
	    z3;							// Kein Konstruktor - Aufruf, lediglich Definition
    System.out.println("  z1 = new Komplex(): " + z1);
    System.out.println("  z2 = new Komplex(3.0): " + z2);

    z3 = new Komplex(-2.0, 1.0);                              			// Komplex(double x, double y) - Konstruktor - Aufruf
    System.out.println("  z3 = new Komplex(-2.0, 1.0): " + z3);

    z3.add(new Komplex(5.0, -2.0));                                                                    // Komplex(double x, double y) - Konstruktor - Aufruf, danach 
    System.out.println("  z3.add(new Komplex(5.0, -2.0)): " + z3);                // gleich wieder Destruktion des Objekts, weil "anonymes" Objekt
    System.out.println();
    
    Komplex z0;							// Kein Konstruktor - Aufruf, lediglich Definition
    System.out.print("  z0 = Komplex.getOrigin(): ");
    z0 = Komplex.getOrigin();					// Komplex() - Konstruktor - Aufruf in Methode getOrigin()
    System.out.println(z0);
    System.out.println();
    
    System.out.println("  Komplex [] v = new Komplex[2]:");
    Komplex [] v = new Komplex[2];                                                                    // 2-maliger Komplex() - Konstruktor - Aufruf (ist Default - Konstruktor)
    for (int i = 0; i < v.length; i++)
      System.out.println("  v[" + i + "] = " + v[i]); 
    System.out.println();
    
    System.out.println("  Komplex [] w = new Komplex[] { z1, z2 }:");
    Komplex [] w = new Komplex[] { z1, z2 };                                		// 2-maliger Komplex(Komplex z) - Konstruktor - Aufruf (wegen Initialisierung)
    for (int i = 0; i < w.length; i++)
      System.out.println("  w[" + i + "] = " + w[i]);
    System.out.println();
    
    for (int i = 0; i < w.length/2; i++)
    {
      Komplex temp = new Komplex(w[i]);    				// Mit jedem Schleifendurchlauf Komplex(Komplex z) - Konstruktor - Aufruf
      w[i] = w[w.length - 1 - i];					// Destruktion des erzeugten Objekts beim naechsten Schleifendurchlauf.
      w[w.length - 1 - i] = temp;					// Am Ende der Schleife sind alle Objekte wieder zerstoert (wegen Lokalitaet)
    } 								
    for (int i = 0; i < w.length; i++)
      System.out.println("  w[" + i + "] = " + w[i]);
    System.out.println();
    
    System.out.println("  Aufruf von Komplex.zufallObjekt():");
    Komplex.zufallObjekt();						// Komplex(Math.random(), Math.random()) - Konstruktor - Aufruf in Methode zufallObjekt()
    boolean test = z1.imSelbenQuadrant(z2);
    System.out.println("  Aufruf von z1.imSelbenQuadrant(z2):");
    System.out.println("  Ergebnis = " + test);
    System.out.println();
    
    System.out.println("  Komplex zz = z2:");
    Komplex zz = z2;						// Kein Konstruktor Aufruf -- lediglich Referenzierung
    System.out.println("  z2 und z3 auf null-Referenz gesetzt");
    z2 = null;    							// Kein Destruktor - Aufruf, da zz auf altes z2 Objekt referenziert
    z3 = null;							// Destruktor - Aufruf fuer altes z3 Objekt

    System.out.println("  z2 = " + z2);
    System.out.println("  zz = " + zz);
    System.out.println();
    
    System.out.println("  Garbage collection angefordert");
    System.gc();
    System.runFinalization();
    System.runFinalizersOnExit(true);
    System.out.println();
 
    System.out.println("  Ende des Programms");
  }

// Am Ende des Programms werden die Objekte die als letztes erzeugt wurden, als erstes zerstoert.
// Die Objekte die als erstes erzeugt wurden, werden zum Schluß zerstoert.
//
// Grund:  Saemtliche Objekte werden auf dem Stack (vgl. Buecherstapel) erzeugt, 
//               der Stack arbeitet nach dem LIFO - Prinzip, LAST IN FIRST OUT,
//               was zu deutsch heisst: Zuletzt erzeugte Objekte werden als erste zerstoert.
}