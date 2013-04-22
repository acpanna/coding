#include "stdafx.h"
#include "Zinsenfkt.h"

double ErtragOhneZinsen( double startKapital,
							 double prozZins,
							 double laufzeit )
{
	return startKapital * ( 1+ prozZins/100.0 * laufzeit);
}