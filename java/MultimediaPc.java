public class MultimediaPc extends Pc implements NetWork, Multimedia
{
    String IP;
    String IPName;
    String kamera;
    String kameraAufloesung;

    public MultimediaPc()
    {
        super();
        IP = "000.000.0.0";
        IPName = "NoIPName";
        kamera = "NoKameraName";
        kameraAufloesung = "0x0";
    }

    public MultimediaPc(String name, String typ, String ip, String ipname, String cam, String camview)
    {
        super(name, typ);
        IP = ip;
        IPName = ipname;
        kamera = cam;
        kameraAufloesung = camview;
    }

    public String getIP()
    {
        return IP;
    }

    public String getIPName()
    {
        return IPName;
    }

    public String getKameraModell()
    {
        return kamera;
    }

    public String getKameraAufloesung()
    {
        return kameraAufloesung;
    }

    public String toString()
    {
        return super.toString()+", IP-Adresse: "+IP+", IP-Name: "+IPName+", Kamera-Modell: "+kamera+", Kamera-Aufloesung: "+kameraAufloesung;
    }
}
