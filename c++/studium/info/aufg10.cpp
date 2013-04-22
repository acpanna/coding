#include <stdio.h>
#include <stdlib.h>

int sstart;
int tstart;

struct zeichenkette {
  int zeiger;
  char zeichen;
} *s, *t;

int sfind(int &sstart, int &tstart);
 
int main(void)
{
  int i, zeiger;
  int laenges, laenget;

  printf("\nBitte geben Sie die Länge der Zeichenkette S ein : ");
  scanf("%d",&laenges);
  printf("Bitte geben Sie die Länge der Zeichenkette T ein : ");
  scanf("%d",&laenget);
  
  s = (struct zeichenkette *) malloc((laenges+1) * sizeof(struct zeichenkette));
  t = (struct zeichenkette *) malloc((laenget+1) * sizeof(struct zeichenkette));
      
  printf("\n");

  if (laenges != 0)
    {

      for(i=1; i<=laenges; i++)
        {
          printf("Bitte geben Sie das %2d.-te Zeichen von S ein : ",i);
	  scanf(" %c",&s[i].zeichen);
          s[i].zeiger = i+1;
        }

      s[laenges].zeiger = 0;
      sstart = 1;
    }
  else
    {
      sstart = 0;
    }

  printf("\n");

  if (laenget != 0)
    {

      for(i=1; i<=laenget; i++)
        {
          printf("Bitte geben Sie das %2d.-te Zeichen von T ein : ",i);
          scanf(" %c",&t[i].zeichen);
          t[i].zeiger = i+1;
        }

      t[laenget].zeiger = 0;
      tstart = 1;
    }
  else
    {
      tstart = 0;
    }

  zeiger = sfind(sstart,tstart);

  printf("\n\n\t\tZeigerwert: %d",zeiger);

  return 0;
}

int sfind(int &sstart, int &tstart)
{
  int i, j, temp;
  int positions, positiont;

  if ((sstart == 0) || (tstart == 0))
    return 0;
    
  positions = sstart;
  positiont = tstart;

  for (i=0 ;; i++)
    {
      if (t[positiont].zeichen == s[positions].zeichen)
	{
          temp = positions;

	  if (t[positiont].zeiger == 0)
	    return temp;

	  if (t[positiont].zeiger != 0 && s[positions].zeiger == 0)
	    return 0;

	  for (j=0 ;; j++)
	    {
	      positiont = t[positiont].zeiger;
	      positions = s[positions].zeiger;

              if (t[positiont].zeichen == s[positions].zeichen)
		{
		  if (t[positiont].zeiger == 0)
	            return temp;

	          if (t[positiont].zeiger != 0 && s[positions].zeiger == 0)
	            return 0;
		}

	      if (t[positiont].zeichen != s[positions].zeichen)
		{
		  positiont = tstart;

		  if (s[temp].zeiger != 0)
                    positions = s[temp].zeiger;
		  else
		    return 0;
                  break;
                }
            }
	}

      else
        {

	  if (s[positions].zeiger != 0)
	    positions = s[positions].zeiger;

	  else
            return 0;
	}
    }	      
}


  