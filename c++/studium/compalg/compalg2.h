/* This is  -*- C++ -*-  */
#ifndef COMPALG2_H
#define COMPALG2_H

#include <vector>

using namespace std;

#define INT unsigned long int

#define Permutation vector<INT>

#define Teilmenge vector<bool>

#define Partition vector<INT>

#define Matrix vector<vector<INT> >


//******************************************************************************
//*
//* Folgende Hilfsfunktionen sind schon implementiert und duerfen
//* verwendet werden
//*
//******************************************************************************

INT Binom(INT n, INT k);
// Eingabe: Natuerliche Zahlen n und k.
// Ausgabe: Binomialkoeffizient n ueber k.

INT ggT(INT a, INT b);
// Eingabe: Natuerliche Zahlen a und b.
// Ausgabe: der groesste gemeinsame Teiler von a und b.

//******************************************************************************


//******************************************************************************
//*
//*  THEMA 1
//*
//*  Permutationen - Teil 1
//*
//******************************************************************************
//*
//*  Multiplizieren, Invertieren, Ausgabe in Liste- und Zykelschreibweise
//*  von Permutationen, Konjugation;
//*
//******************************************************************************
//*
//*  Literatur: Kreher, Stinson: COMBINATORIAL ALGORITHMS, S. 195 - 203
//*
//******************************************************************************

void Mult(const Permutation& a, const Permutation& b, Permutation& c);
// Eingabe: Permutationen a und b.
// Ausgabe: Das Produkt c = a * b  (Zuerst b anwenden dann a).

void Inv(const Permutation& a, Permutation& b);
// Eingabe: Permutation a.
// Ausgabe: Das inverse Element b = a^{-1}.

void Conj(const Permutation& a, const Permutation& b, Permutation& c);
// Eingabe: Permutationen a und b.
// Ausgabe: c = a * b * a^{-1}.

void PrintList(const Permutation& a );
// Bildschirmausgabe der Permutation a in Listenschreibweise.

void PrintCycles(const Permutation& a );
// Bildschirmausgabe der Permutation a in Zykelschreibweise.


//******************************************************************************
//*
//*  THEMA 2
//*
//*  Permutationen - Teil 2
//*
//******************************************************************************
//*
//*  Erzeugen aller Elemente einer durch Erzeugern gegebene
//*  Permutationsgruppe -> Dimino-Algorithmus
//*
//******************************************************************************
//*
//*  Literatur: Butler: FUNDAMENTAL ALGORITHMS FOR PERMUTATION GROUPS,
//*             S. 14 - 23
//*
//******************************************************************************

void Dimino(const vector<Permutation>& S, vector<Permutation>& G);
//Eingabe: Menge von Erzeuger S.
//Ausgabe: Menge der Gruppenelemente G.


//******************************************************************************
//*
//*  THEMA 3
//*
//*  Permutationen - Teil 3
//*
//******************************************************************************
//*
//*  Durchlauf von Permutationen -> Johnson-Trotter-Algorithmus
//*
//******************************************************************************
//*
//*  Literatur: Kreher, Stinson: COMBINATORIAL ALGORITHMS, S. 52 - 63
//*
//******************************************************************************

void JohnsonTrotterFirst(INT n, Permutation& a);
// Eingabe: Natuerliche Zahl n
// Ausgabe: Die Permutation a = [0,...,n-1]

void JohnsonTrotterSuccessor(Permutation& a);
// Eingabe: Permutation a.
// Ausgabe: a wird mit seinem Nachfolger ueberschrieben.

INT JohnsonTrotterRank(const Permutation& a);
// Eingabe: Permutation a.
// Ausgabe: Natuerliche Zahl Rang(a).

void JohnsonTrotterUnrank(INT n, INT r, Permutation& a);
// Eingabe: Natuerliche Zahlen n und r.
// Ausgabe: Permutation a mit Rank(a) = r.


//******************************************************************************
//*
//*  THEMA 4
//*
//*  Partitionen
//*
//******************************************************************************
//*
//*  Durchlauf aller Partitionen ->  Lexikographischer Durchlauf
//*
//******************************************************************************
//*
//*  Literatur: Kreher, Stinson: COMBINATORIAL ALGORITHMS, S. 67 - 78
//*
//******************************************************************************

void PartitionLexFirst(INT m, INT n, Partition& a);
// Eingabe: Natuerliche Zahlen m und n.
// Ausgabe: Die lexikographisch kleinste Partition der Zahl m mit n Teilen.

void PartitionLexSuccessor(INT m, Partition& a);
// Eingabe: Natuerliche Zahl m und eine Partition a.
// Ausgabe: a wird mit der naechsten Partitition ueberschrieben.

INT PartitionLexRank(INT m, const Partition& a);
// Eingabe: Natuerliche Zahlen m und eine Partition a.
// Ausgabe: Natuerliche Zahl Rang(a);

void PartitionLexUnrank(INT m, INT n, INT r, Partition& a);
// Eingabe: Natuerliche Zahlen m, n und r.
// Ausgabe: Die Partition a der Zahl m mit n Teilen mit Rang(a) = r



//******************************************************************************
//*
//*  THEMA 5
//*
//*  Abzaehlen von unnummerierten Graphen
//*
//******************************************************************************
//*
//*  Cauchy-Frobenius-Lemma fuer Symmetrieklassen von Abbildungen
//*
//******************************************************************************
//*
//*  Literatur: Kerber: LINEARE ALGEBRA 2002/03
//*
//******************************************************************************

INT NumInducedPermCycles(INT n, const Partition& a);
// Eingabe: Natuerliche Zahl n und eine Partition von n.
// Ausgabe: Ist g eine Permutation mit Partition a, dann wird
//          die Anzahl der Zyklen, der von g auf den 2-Teilmengen von n
//          induzierten Permutation, zurueckgegeben.
// Literatur: APPLIED FINITE GROUP ACTIONS, Kerber, S. 70 - 71


INT NumUnlabelledGraphs(INT n, INT k);
// Eingabe: Natuerliche Zahlen n und k
// Ausgabe: Die Anzahl der unnummerierten k-Multigraphen auf n Knoten.



//******************************************************************************
//*
//*  THEMA 6
//*
//*  alle Teilmengen einer n-elementigen Menge
//*
//******************************************************************************
//*
//*  Durchlauf durch alle Teilmengen -> Gray-Code
//*
//******************************************************************************
//*
//*  Literatur: Kreher, Stinson: COMBINATORIAL ALGORITHMS, S. 31 - 42
//*
//******************************************************************************

void GrayCodeFirst(INT n, Teilmenge& T);
// Eingabe: Natuerliche Zahl n
// Ausgabe: Die erste Teilmenge T von { 0, ..., n-1 } des Gray-Codes.

void GrayCodeSuccessor(Teilmenge& T);
// Eingabe: Teilmenge T.
// Ausgabe: T wird mit seinem Nachfolger ueberschrieben.

INT GrayCodeRank(const Teilmenge& T);
// Eingabe: Teilmenge T.
// Ausgabe: Natuerliche Zahl Rang(T).

void GrayCodeUnrank(INT n, INT r, Teilmenge& T);
// Eingabe: Natuerliche Zahlen n und r.
// Ausgabe: Teilmenge von { 0, ..., n-1 } mit Rank(T) = r.



//******************************************************************************
//*
//*  THEMA 7
//*
//*  Schreier-Erzeuger
//*
//******************************************************************************
//*
//*  Sei eine Permutationsgruppe G < S_n durch Erzeuger gegeben; gesucht ist
//*  die Bahn G(p) eines Punktes p aus { 0, ..., n-1 } und ein
//*  Erzeugendensystem des Stabilisators G_p.
//*
//******************************************************************************
//*
//*  Literatur: noch nicht ausgesucht
//*
//******************************************************************************

void Schreier(const vector<Permutation>& G, INT p,
              vector<INT>& O, vector<Permutation>& S);
// Eingabe: Menge von Erzeuger G=[G[0],...,G[m-1]] und ein Punkt p
// Ausgabe: Die Bahn O von p und eine Menge S von Permutationen, die
//          den Stabilisator G_i erzeugen.


#endif
