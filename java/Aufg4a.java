public class Aufg4a 
{
  public static void main (String [] argv)
  {
    System.out.print("\n");

    for (int i=0; i<255; i++)
    {
      char zeichen = (char) i;
      System.out.print(zeichen + " ");
      
      if ((i+1) % 16 == 0)
        System.out.print("\n");
    }

    System.out.print("\n\n"); 
    
    char zeichen1 = (char) 161;
    char zeichen2 = (char) 241;
    char zeichen3 = (char) 233;
 
    System.out.print(zeichen1 + "Paco Pe" + zeichen2 + "a! Je suis l'" + zeichen3 + "tranger!");    

    zeichen1 = (char) 188;
    zeichen2 = (char) 189;
    zeichen3 = (char) 190;
   
    System.out.print("\n" + zeichen1 + " + " + zeichen2 + " = " + zeichen3 + " , (" + zeichen2 + ")");
   
    zeichen2 = (char) 178;

    System.out.print(zeichen2 + " = " + zeichen1);    

    zeichen1 = (char) 169;
    zeichen2 = (char) 229;
    zeichen3 = (char) 246;

    System.out.print("\n" + zeichen1 + " H. R" + zeichen2 + "dstr" + zeichen3 + "m");
    System.out.print("\n\n");
  }
}   
