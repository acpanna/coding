#ifndef _KANTE_H_
#define _KANTE_H_

class Kante
{
  public:
    Kante() { ziel = 0; bewertung = 0.0; }
    Kante(int zielknoten, double weight = 0.0) 
    { ziel = zielknoten; bewertung = weight; }	

    int getZiel() const { return ziel; }
    double getBewertung() const { return bewertung; }
    
    void setZiel(const int &newziel) { ziel = newziel; }
    void setBewertung(const double &newweight) { bewertung = newweight; }

  private:
    int ziel;  // Zielknoten der Kante
    double bewertung; // Kantenbewertung
};

#endif
