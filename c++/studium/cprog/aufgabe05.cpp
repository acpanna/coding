#ifdef __GNUC__

#include <climits>
#include <iostream>
using namespace std;

#else

#include <limits.h>
#include <iostream.h>

#endif

int main(void)
{
  int zahl_1, zahl_2;
  short zahl_3, zahl_4, erg_1;
  unsigned short zahl_5, zahl_6, erg_2;

  zahl_1 = INT_MAX/2;
  zahl_2 = 2*zahl_1 + 1;
  cout << "zahl_1 = " << zahl_1 << endl;
  cout << "zahl_2 = 2*zahl_1 + 1 =  " << zahl_2 << endl;

  zahl_2 = 2*zahl_1 + 2;
  cout << "zahl_2 = 2*zahl_1 + 2 = " << zahl_2 << endl << endl;

  zahl_2 = (2*zahl_1 + 2)/2;
  cout << "zahl_2 = (2*zahl_1 + 2)/2 = " << zahl_2 << endl;
  zahl_2 = zahl_1 + 1;
  cout << "zahl_2 =    zahl_1 + 1    = " << zahl_2 << endl << endl;


  if (sizeof(short) != 2)
  {
    cout << "Beispiel funktioniert fuer diesen Compiler nicht!" << endl;
    return 1;
  }

  zahl_3 = 15000;
  zahl_4 = 18000;
  zahl_5 = 15000;
  zahl_6 = 18000;

  cout << "zahl_3 = " << zahl_3 << ", zahl_5 = " << zahl_5 << endl;
  cout << "zahl_4 = " << zahl_4 << ", zahl_6 = " << zahl_6 << endl << endl;

  erg_1 = zahl_3 + zahl_4;
  erg_2 = zahl_5 + zahl_6;

  cout << "1. Summe von zahl_3 und zahl_4: " << erg_1 << endl;
  cout << "2. Summe von zahl_3 und zahl_4:  " << zahl_3 + zahl_4 << endl;
  cout << "1. Summe von zahl_5 und zahl_6:  " << erg_2 << endl;
  cout << "2. Summe von zahl_5 und zahl_6:  " << zahl_5 + zahl_6 << endl;

  return 0;
}
