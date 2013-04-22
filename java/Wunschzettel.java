public class Wunschzettel
{
	String [] wuensche;
	float [] preise;

                public Wunschzettel()
                {
		this("Wunschlos gluecklich");
	}

	public Wunschzettel(String [] w)
                {
		this(w,new float[w.length]);
	}
	
	public Wunschzettel(String [] w, float [] p)
	{
                                wuensche = new String[w.length];
		preise = new float[w.length];

                                try
                                {

		          for (int i=0; i<w.length; i++)
		         {
			wuensche[i] = new String(w[i]);
			preise[i] = Math.abs(p[i]);                                                                             
		         }
	                }

                                catch(NullPointerException exc)
                                {
                                         wuensche[0] = "";
                                         preise[0] = 0.0f;
                                }  
                }

	public Wunschzettel(String einzigerWunsch)
	{
		this(einzigerWunsch, 0.0f);
	}

                public Wunschzettel(String einzigerWunsch, float zugeh_preis)
	{
		this(new String[1], new float[1]);

		wuensche[0] = new String(einzigerWunsch);
		preise[0] = zugeh_preis;
	}

                public String toString()
                {
                              String res = new String();
                              for (int i=0; i<wuensche.length; i++)
                                     res += "\tWunsch "+(i+1)+": "+wuensche[i]+", Preis: "+preise[i]+"\n";
                              return res;
                } 
}