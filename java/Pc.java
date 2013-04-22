public class Pc
{
    protected String modell;
    protected String cpu;

    public Pc()
    {
        modell = "NoName";
        cpu = "Unknown";
    }

    public Pc(String name, String typ)
    {
        modell = name;
        cpu = typ;
    }

    public String getModell()
    {
        return modell;
    }

    public String getCpu()
    {
        return cpu;
    }

    public String toString()
    {
        return "Modellbezeichnung: "+modell+", Prozessor: "+cpu;
    }
}
