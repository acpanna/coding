public class Funktion
{
  public static void main(String [] argv)
  {
    String frage = new String("suhtragin\u00F6khcarpssaw");
    StringBuffer antwort = new StringBuffer("fpmaknednifua");
    char [] fazit = { 'l', 'e', 'z', 't', 'e', 'm', 'e', 'g', 's', 
                      'e', 's', 'o', 'l', 'n', 'n', 'i', 's' };
    String [] alleWoerter = new String[3];
    
    alleWoerter[0] = new String(frage);
    alleWoerter[1] = new String(antwort);
    alleWoerter[2] = new String(fazit);          
    
    System.out.println("falsche Reihenfolge:");
    System.out.println("  Frage:   " + frage);
    System.out.println("  Antwort: " + antwort);
    System.out.println("  Fazit:   " + fazit);
    for (int i = 0; i < alleWoerter.length; i++)
      System.out.println("  " + (i+1) + ". Wort: " + alleWoerter[i]);
    System.out.println();
    
    frage = reverse(frage);
    reverse(antwort);
    reverse(fazit);
    reverse(alleWoerter);
    
    // 2. Alternative zur Invertierung eines Strings : 
    // StringBuffer Objekt mit String im Konstruktor anlegen 
    // StringBuffer reverse() - Funktion aufrufen, 
    // String Objekt mit "invertiertem" StringBuffer anlegen
    // und dem altem String Objekt zuweisen.
    //
    // Bsp:
    //
    // String str = new String("streawkceur");
    // StringBuffer strbuf = new StringBuffer(str);
    // reverse(strbuf);
    // str = new String(strbuf);
        
    System.out.println("richtige Reihenfolge:");
    System.out.println("  Frage:   " + frage);
    System.out.println("  Antwort: " + antwort);
    System.out.println("  Fazit:   " + fazit);
    for (int i = 0; i < alleWoerter.length; i++)
      System.out.println("  " + (i+1) + ". Wort: " + alleWoerter[i]);
  }

  // die naechsten 3 Varianten von reverse() sollen einfach die verwaltete
  // Zeichenkette rueckwaerts wieder in den uebergebenen Parameter abspeichern
  
  // Variante fuer String
  public static String reverse(String src)
  {
    StringBuffer tmp = new StringBuffer(src);
    tmp.reverse();
    return new String(tmp); 
  }

  // Variante fuer StringBuffer
  public static void reverse(StringBuffer src)
  {
    src.reverse();
  }

  // Variante fuer char-Array
  public static void reverse(char [] src)
  {
    for (int i=0; i<src.length/2; i++)
    {
      char tmp = src[i];
      src[i] = src[src.length - 1 - i];
      src[src.length - 1 - i] = tmp;
    }
  }

  // diese Variante von reverse() soll einfach alle im Array verwalteten
  // Zeichenketten rueckwaerts wieder in die Arraykomponenten abspeichern

  // Variante fuer String-Array
  public static void reverse(String [] src)
  {
    for (int i=0; i<src.length; i++)
      src[i] = reverse(src[i]);
  }
}

