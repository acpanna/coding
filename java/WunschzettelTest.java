public class WunschzettelTest
{
	public static void main(String [] argv)
                {
                               String [] want = new String[3];
                               want[0] = "Fahrrad";
                               want[1] = "Auto";
                               want[2] = "Yacht";
                               
                               float [] price = new float[3];
                               price[0] = 200.0f;
                               price[1] = 30000.0f;
                               price[2] = 100000.0f;
 
                               String wish = "Fusswaermer";
                               float cash = 10.0f;

                               Wunschzettel [] test = new Wunschzettel[5];
                               test[0] = new Wunschzettel();
                               test[1] = new Wunschzettel(want);
                               test[2] = new Wunschzettel(want, price);
                               test[3] = new Wunschzettel(wish);
                               test[4] = new Wunschzettel(wish, cash);

                               for (int i=0; i<test.length; i++)
                                       System.out.print("" + (i+1) + ". ter Wunschzettel: \n" + test[i] + "\n");
                }
}
               