public class BankAnlage
{
	private String besitzer;
	
	private double kontostand;
	private double zins;
	
	private long laufzeit;

	public BankAnlage(String name)
	{
		besitzer = name;
		kontostand = 0.0;
		laufzeit = 0;
		zins = 0.0;
	}
	
	public BankAnlage(String name, double guthaben)
	{
		besitzer = name;
		kontostand = guthaben;
		laufzeit = 0;
		zins = 0.0;
	}

	public BankAnlage(String name, double guthaben, long wielang)
	{
		besitzer = name;
		kontostand = guthaben;
		laufzeit = Math.abs(wielang);
		zins = 0.0;
	}
	
	public BankAnlage(String name, double guthaben, long wielang, double gewinn)
	{
		besitzer = name;
		kontostand = guthaben;
		laufzeit = Math.abs(wielang);
		zins = Math.abs(gewinn);
	}

                public double getZinsenImJahr(long jahr)
	{
		double erg = 0.0;
		double neukonto = kontostand;

		for (long i=1; i<=jahr; i++)
		{
			erg = (neukonto * zins) / 100.0;
			neukonto += erg;
		}
    
		return erg;
	}

	public double getZinsenBisJahr(long jahr)
	{
                    double erg = 0.0;
	    double neukonto = kontostand;

		for (long i=1; i<=jahr; i++)
		{
			erg += (neukonto * zins) / 100.0;
			neukonto += (neukonto * zins) / 100.0;
		}
    
		return erg;
	}

	public double getKontoImJahr(long jahr)
	{
		double neukonto = kontostand;
	
		for (long i=1; i<=jahr; i++)
			neukonto += (neukonto * zins) / 100.0;
	
		return neukonto;
	}
	

	public void setKontoToEuro()
	{
		kontostand = kontostand / 1.99554;    //Ungefaehrer EURO - Wechselkurs
	}

	public String getName()
	{
		return new String(besitzer);
	}

	public double getKonto()
	{
		return kontostand;
	}

	public long getLaufzeit()
	{
		return laufzeit;
	}

	public double getZins()
	{
		return zins;
	}

                public void setKonto(double neu)
                {
                                kontostand = neu;
                }

                public void setLaufzeit(long neu)
                {
                                laufzeit = Math.abs(neu);
                }

                public void setZins(double neu)
                {
                                zins = Math.abs(neu);
                }
}

