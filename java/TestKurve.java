public class TestKurve
{
    public static void main(String [] argv)
    {
        KreisKurve kk1 = new KreisKurve(6,0,0,1);
        StreckeKurve sk1 = new StreckeKurve(6,1,1,2,2);

        System.out.println("KreisKurve kk1 = new KreisKurve(6,0,0,3): ");
        for (int i=0; i<= kk1.getN(); i++)
        {
            System.out.println(""+ i +": x(t"+ i +") = "+ kk1.getXAt(i) +", y(t"+ i +") = "+ kk1.getYAt(i));
        }

        kk1.move(1.0, 1.0);
        System.out.println("\nkk1.move(1.0, 1.0): ");
        for (int i=0; i<= kk1.getN(); i++)
        {
            System.out.println(""+ i +": x(t"+ i +") = "+ kk1.getXAt(i) +", y(t"+ i +") = "+ kk1.getYAt(i));
        }

        kk1.scale(4.0);
        System.out.println("\nkk1.scale(4.0): ");
        for (int i=0; i<= kk1.getN(); i++)
        {
            System.out.println(""+ i +": x(t"+ i +") = "+ kk1.getXAt(i) +", y(t"+ i +") = "+ kk1.getYAt(i));
        }

        System.out.println("\nStreckeKurve sk1 = new StreckeKurve(6,1,1,2,2): ");
        for (int i=0; i<= sk1.getN(); i++)
        {
            System.out.println(""+ i +": x(t"+ i +") = "+ sk1.getXAt(i) +", y(t"+ i +") = "+ sk1.getYAt(i));
        }

        sk1.move(1.0, 2.0);
        System.out.println("\nsk1.move(1.0, 2.0): ");
        for (int i=0; i<= sk1.getN(); i++)
        {
            System.out.println(""+ i +": x(t"+ i +") = "+ sk1.getXAt(i) +", y(t"+ i +") = "+ sk1.getYAt(i));
        }

        sk1.scale(-1.0);
        System.out.println("\nsk1.scale(-1.0): ");
        for (int i=0; i<= sk1.getN(); i++)
        {
            System.out.println(""+ i +": x(t"+ i +") = "+ sk1.getXAt(i) +", y(t"+ i +") = "+ sk1.getYAt(i));
        }
    }
}