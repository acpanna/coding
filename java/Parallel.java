import java.applet.Applet;
import java.awt.*;

public class Parallel extends Applet
                      implements Runnable
{
  final int MAX_RUNS = 5; 
  int index_fertig = 0;
  int anzahl_threads = 0;
  int anzahl_run [], prioritaet [], reihenfolge [];
  String taetigkeit [];
  Thread t [];
  
  public void init()
  {
    String param_string = getParameter("anzahl");
    if (param_string == null)
    {
      System.err.println("Parameter \"anzahl\" nicht gesetzt im HTML-File");
      anzahl_run  = null;
      prioritaet  = null;
      reihenfolge = null;
      taetigkeit  = null;
      t = null;
    }
    else
    {
      try
      {
        anzahl_threads = Integer.parseInt(param_string);
        if (anzahl_threads < 0)
        {
          System.err.println("Parameterwert von "
                             + "\"anzahl\" ist negativ!");
          anzahl_threads = 0;
        }
      }
      catch (NumberFormatException exc)
      {
        System.err.println("Umwandlung des Parameterwertes "
                           + "von \"anzahl\" in int-Wert gescheitert!");
        anzahl_threads = 0;
      }

      anzahl_run  = new int[anzahl_threads];
      prioritaet  = new int[anzahl_threads];
      reihenfolge = new int[anzahl_threads];
      taetigkeit  = new String[anzahl_threads];
      t = new Thread[anzahl_threads];  
    }
    
    for (int i = 0; i < anzahl_threads; i++)
    {
      anzahl_run[i]  = 0;
      reihenfolge[i] = 0;
      param_string = getParameter("Taetigkeit" + (i+1));
      if (param_string == null)
      {
        System.err.println("Parameter \"Taetigkeit" + (i+1) 
                           + "\" nicht gesetzt im HTML-File");
        param_string = "Taetigkeit" + (i+1);
      }
      taetigkeit[i] = param_string;
      t[i] = new Thread(this, taetigkeit[i]);

      param_string = getParameter("Prioritaet" + (i+1));
      if (param_string == null)
      {
        System.err.println("Parameter \"Prioritaet" + (i+1) 
                           + "\" nicht gesetzt im HTML-File");
        prioritaet[i] = Thread.NORM_PRIORITY;
      }
      else
      {
        try
        {
          prioritaet[i] = Integer.parseInt(param_string);
          if (prioritaet[i] < 0)
          {
            System.err.println("Parameterwert von \"Prioritaet" + (i+1) 
                           + "\" ist negativ!");
            prioritaet[i] = Thread.NORM_PRIORITY;
          }
          else if (prioritaet[i] > Thread.MAX_PRIORITY)
          {
            System.err.println("Parameterwert von \"Prioritaet" + (i+1) 
                           + "\" ist gr\u00F6\u00DFer als die "
                           + "maximale Priorit\u00E4t!");
            prioritaet[i] = Thread.MAX_PRIORITY;
          }
        }
        catch (NumberFormatException exc)
        {
          System.err.println("Umwandlung des Parameterwertes "
                             + "von \"Prioritaet" + (i+1) 
                             + "\" in int-Wert gescheitert!");
          prioritaet[i] = Thread.NORM_PRIORITY;
        }
      }
    }
  }
  
  public void start()
  {
    // t[0].getThreadGroup().setMaxPriority(Thread.MAX_PRIORITY);

    for (int i = 0; i < anzahl_threads; i++)
    {
      t[i].start();
      t[i].setPriority(prioritaet[i]);
  
      if (prioritaet[i] != t[i].getPriority())
        System.err.println("!!! Achtung! Priorit\u00E4t "
                           + "konnte nicht ver\u00E4ndert werden!");
    }
  }
  
  // implementiert Interface Runnable
  public void run()
  {
    for (int i = 0; i < MAX_RUNS; i++) 
    {
      Thread t_curr = Thread.currentThread();
      System.out.println((i+1) + ".Tag: Am liebsten tue ich " 
                         + t_curr.getName() + ".");

      int index = thread_index(t_curr);
      if (index == anzahl_threads)
        System.err.println("Threadnummer nicht gefunden!");
      else
      {
        anzahl_run[index]++;
        if (anzahl_run[index] == MAX_RUNS)
          ergebnis(index);
      }

      try
      {
        t_curr.sleep(100);
      }
      catch (InterruptedException exc)
      {
        System.err.println("abgebrochen: " + t_curr.getName());
      }
    }       
  }
  
  public void stop()
  {
    for (int i = 0; i < anzahl_threads; i++)
      // t[i].stop(); // unsafe
      t[i] = null;
     
    System.out.print("\nReihenfolge der Abarbeitung:");
    for (int i = 0; i < anzahl_threads; i++)
      System.out.print("  " + (reihenfolge[i]+1));
    System.out.println();
    
    System.out.print("\nPriorit\u00E4t   der Abarbeitung:");
    for (int i = 0; i < anzahl_threads; i++)
      System.out.print("  " + prioritaet[reihenfolge[i]]);
    System.out.println();
  }

  synchronized public void ergebnis(int index)
  {
    reihenfolge[index_fertig] = index;
    System.err.println("### " + index_fertig + ".Thread \"" 
                       + taetigkeit[index] + "\" (Nr. " 
                       + reihenfolge[index_fertig]
                       + ") mit Priorit\u00E4t " + prioritaet[index]
                       + " ist fertig!");
    index_fertig++;
  }
  
  public int thread_index(Thread t)
  {
    boolean found = false;
    int i;
    
    if (t == null)
      return anzahl_threads;
    for (i = 0; i < anzahl_threads && !found; i++)
      if (t.getName().equals(taetigkeit[i]))
        found = true;
    if (found)
      return i-1;
    else
      return anzahl_threads;
  }
}
