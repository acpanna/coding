public class TestPc
{
    public static void main(String [] argv)
    {
        MultimediaPc pc1 = new MultimediaPc();
        MultimediaPc pc2 = new MultimediaPc("IBM", "486", "129.130.16.2", "myPC.subnetz.uni-bayreuth.de", "Canon", "300x300");

        System.out.println("\nToString - Ausgabe:");
        System.out.println("===================\n\n");
        System.out.println("pc1 = new MultimediaPc()\n\n"+pc1);
        System.out.println("\n\npc2 = new MultimediaPc(.., .., .., .., .., ..)\n\n"+pc2);
        System.out.println("\n\n\ngetXXXX - Ausgabe:");
        System.out.println("==================\n\n");
        System.out.println("pc1.getModell(): "+pc1.getModell());
        System.out.println("pc1.getCpu(): "+pc1.getCpu());
        System.out.println("pc1.getIP(): "+pc1.getIP());
        System.out.println("pc1.getIPName(): "+pc1.getIPName());
        System.out.println("pc1.getKameraModell(): "+pc1.getKameraModell());
        System.out.println("pc1.getKameraAufloesung(): "+pc1.getKameraAufloesung());
        System.out.println("\npc2.getModell(): "+pc2.getModell());
        System.out.println("pc2.getCpu(): "+pc2.getCpu());
        System.out.println("pc2.getIP(): "+pc2.getIP());
        System.out.println("pc2.getIPName(): "+pc2.getIPName());
        System.out.println("pc2.getKameraModell(): "+pc2.getKameraModell());
        System.out.println("pc2.getKameraAufloesung(): "+pc2.getKameraAufloesung());
    }
}