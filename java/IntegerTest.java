import java.math.*;

public class IntegerTest
{
  static BigInteger test1, test2, test3;

  public static void main(String argv[])
  {
    test1  = new BigInteger("20");
    test2  = new BigInteger("30");
    System.out.println("test1 = " + test1.intValue() + ", test2 = " + test2.intValue() );
 
    test3  = test1.min(test2);
    System.out.println("test3 ( = test1.min(test2) ) = " + test3.intValue() );

    test1  = BigInteger.valueOf(3);
    System.out.println("test1 ( = BigInteger.valueOf(3) ) = " + test1.intValue() );    
   }
}  
  