public class AnlageTest
{
	public static void main (String argv[])
	{
		BankAnlage test = new BankAnlage("Max Muster",10000.0,10,3.0);

		System.out.println("Name: " + test.getName() + ", Kontostand : " + test.getKonto() + ", Laufzeit: " + test.getLaufzeit() + ", Zinssatz: " + test.getZins());
                                
                                System.out.println("Zinsen im 1. Jahr: " + test.getZinsenImJahr(1) + ", Zinsen im 6. Jahr: " + test.getZinsenImJahr(6));
                              
                                System.out.println("Gesamtzinsen nach 1 Jahr: " + test.getZinsenBisJahr(1) +" , Gesamtzinsen nach 10 Jahren: " + test.getZinsenBisJahr(10));
                               
                                System.out.println("Kontostand nach 1 Jahr: " + test.getKontoImJahr(1) + ", Kontostand nach 5 Jahren: " + test.getKontoImJahr(5));
                               
                                test.setKontoToEuro();
                                
                                System.out.println("Akt. Kontostand nach Umstellung des Konto auf Euro: " + test.getKonto());
	}

}
