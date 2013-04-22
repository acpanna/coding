#include <stdio.h>

int main(int argc, char * argv[])
{
    signed char b;
    char c = 'Ä';
    short s = 1 << 15;
    unsigned short i = 1 << 15;
    double d;
    
    printf("## Test mit ganzzahligen Werten:\n");
    printf(" uninitialisiertes b = %d\n", b);
    b = 127;
    printf(" b = %d\n", b);
    printf("## nach b++:\n");
    b++;
    printf(" b = %d\n", b);
    printf(" s = %hd\n", s);
    printf(" i = %d\n\n", i);
    fflush(stdin);
    getchar();

    printf("## Test mit Zeichen:\n");
    printf(" c = %c\n", c);
    if ((int) c >= 128)
      printf(" ASCII-Code von c = %d\n\n", (int) c);
    else
      printf(" ASCII-Code von c = %d\n\n", 256 + c);
    fflush(stdin);
    getchar();
    
    printf("## Test mit Fließkommawerten:\n");
    d = 1e308;
    printf(" d = %e\n", d);
    printf("## nach d *= 10:\n");
    d *= 10;
    printf(" d = %e\n", d);
    printf("## nach d = -d:\n");
    d = -d;
    printf(" d = %e\n\n", d);
    fflush(stdin);
    getchar();

    printf("## versehentliches 1/0 bzw. 0/0:\n");
    printf("## double/int:\n");
    for (i = 5; i > 0; i--)
    {
      d = i;
      printf("d = i = %d: d/(i-1) = %e\n", i, d/(i-1));
    }
    printf("## setze d auf 0.0:\n");
    d = 0.0;
    printf("d = i = %d, d/i = %f\n\n", i, d/i);    
    fflush(stdin);
    getchar();

    printf("## int/int:\n");
/*
    for (i = 5; i > 1; i--)
*/
    for (i = 5; i > 0; i--)
      printf("i = %d: i/(i-1) = %d\n", i, i/(i-1));
/*
    i = 0;
*/
    printf("i/i = %d\n", i/i);
    
    return 0;
}

