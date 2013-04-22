public class Matrix 
{
  public static void main(String [] argv)
  {
    int [][] A_voll = new int [][]{ {  4,  -2,  0,  0,  0 }, 
                                                       { -1,  4, -2,  0,  0 },
                                                       {  0, -1,  4, -2,  0 },
                                                       {  0,  0, -1,  4, -2 },
                                                       {  0,  0,  0, -1,  4 } };
    int [][] B_voll = new int[5][5];

    int [][] C_voll = new int[][]{ { 1, 2, 3, 4, 5},
                                                     { 5, 4, 3, 2, 1},
                                                     { 0, 0, 1, 2, 0},
                                                     { 1, 2, 3, 4, 5},
                                                     { 5, 4, 3, 2, 1}};

    int [] elements1 = new int[numberOfNonZeros(A_voll)];
    int [] i1 = new int[numberOfNonZeros(A_voll)];
    int [] j1 = new int[numberOfNonZeros(A_voll)];
   
    int [] elements2 = new int [numberOfNonZeros(C_voll)];
    int [] i2 = new int[numberOfNonZeros(C_voll)]; 
    int [] j2 = new int[numberOfNonZeros(C_voll)];

    int [] elements3 = new int [elements1.length + elements2.length];
    int [] i3 = new int[i1.length + i2.length]; 
    int [] j3 = new int[j1.length + j2.length];  

    matVollInDuenn(A_voll, i1, j1, elements1);
    matVollInDuenn(C_voll, i2, j2, elements2);
    matDuennInVoll(B_voll, i1, j1, elements1);

   show1(B_voll);
   show2(i1, j1, elements1); 

    matAdd(i1, j1, elements1, i2, j2, elements2, i3, j3, elements3);
    show2(i3, j3, elements3);
  }

  public static int numberOfNonZeros( int [][] matrix)
  {
    int counter = 0;

    for (int i=0; i<matrix.length; i++)
      for (int j=0; j<matrix[i].length; j++)
       if (matrix[i][j] != 0)
         counter++;
   
    return counter;
  }   

  public static void matVollInDuenn( int [][] matrix, int [] zeile, int [] spalte, int [] eintraege ) 
  {
    int counter = 0;

    for (int i=0; i<matrix.length; i++)
      for (int j=0; j<matrix[i].length; j++)
        if (matrix[i][j] != 0)
        {
          eintraege[counter] = matrix[i][j];
          zeile[counter] = i;
          spalte[counter] = j;
          counter++;
        }
  }
        
  public static void matDuennInVoll( int [][] matrix, int [] zeile, int [] spalte, int [] eintraege )  
  {
    for (int i=0; i<eintraege.length; i++)
      matrix[zeile[i]][spalte[i]] = eintraege[i];
  }
 
  public static void show1( int [][] matrix)
  {
    for (int i=0; i<matrix.length; i++)
    {
      for (int j=0; j<matrix[i].length; j++)
        System.out.print(" " + matrix[i][j]);
     
      System.out.print("\n");
    }
  }

  public static void show2( int [] zeile, int [] spalte, int [] eintraege )
  {
    System.out.print("\n\nZeilenArray :   ");
    for (int i=0; i< zeile.length; i++)
      System.out.print(" " + zeile[i]);
    System.out.print("\nSpaltenArray :  ");
    for (int i=0; i< spalte.length; i++)
      System.out.print(" " + spalte[i]);
    System.out.print("\nEintragsArray : ");
    for (int i=0; i< eintraege.length; i++)
      System.out.print(" " + eintraege[i]);
  }

  public static void matAdd( int [] zeile1, int [] spalte1, int [] eintraege1, int [] zeile2, int [] spalte2, int [] eintraege2, int [] zeile3, int [] spalte3, int [] eintraege3 )
  {
    int counter1 = 0, counter2 = 0, counter3 = 0;

    while(counter1 < eintraege1.length && counter2 < eintraege2.length)
    {
      if (zeile1[counter1] == zeile2[counter2] && spalte1[counter1] == spalte2[counter2])
      {
        zeile3[counter3] = zeile1[counter1];
        spalte3[counter3] = spalte1[counter1];
        eintraege3[counter3] = eintraege1[counter1] + eintraege2[counter2];
        counter1++;
        counter2++;
        
        if (eintraege3[counter3]  !=  0)
          counter3++;
      }
      else if(zeile1[counter1] == zeile2[counter2] && spalte1[counter1] < spalte2[counter2])
      { 
        zeile3[counter3] = zeile1[counter1];
        spalte3[counter3] = spalte1[counter1];
        eintraege3[counter3] = eintraege1[counter1];
        counter1++;
        counter3++;
      } 
      else if(zeile1[counter1] == zeile2[counter2] && spalte1[counter1] > spalte2[counter2])
      { 
        zeile3[counter3] = zeile2[counter2];
        spalte3[counter3] = spalte2[counter2];
        eintraege3[counter3] = eintraege2[counter2];
        counter2++;
        counter3++;
      } 
      else if(zeile1[counter1]  < zeile2[counter2])
      { 
        zeile3[counter3] = zeile1[counter1];
        spalte3[counter3] = spalte1[counter1];
        eintraege3[counter3] = eintraege1[counter1];
        counter1++;
        counter3++;
      } 
      else if(zeile1[counter1]  > zeile2[counter2])
      { 
        zeile3[counter3] = zeile2[counter2];
        spalte3[counter3] = spalte2[counter2];
        eintraege3[counter3] = eintraege2[counter2];
        counter2++;
        counter3++;
      } 
    }

    if  (counter1 < eintraege1.length)
    {
      for (int i=counter1; i<eintraege1.length; i++)
      {
        zeile3[counter3] = zeile1[i];
        spalte3[counter3] = spalte1[i];
        eintraege3[counter3] = eintraege1[i];
        counter3++;
      }
    }
    else if (counter2 < eintraege2.length)
    {
      for (int i=counter2; i<eintraege2.length; i++)
      {
        zeile3[counter3] = zeile2[i];
        spalte3[counter3] = spalte2[i];
        eintraege3[counter3] = eintraege2[i];
        counter3++;
      }  
    }    
  
    //  Leider ist mir momentan nicht bekannt, wie ich einen Java - Array  
    //  innerhalb einer Funktion verkuerzen koennte, deshalb kann  
    //  es zur Ausgabe ueberfluessiger Nullen kommen.

  }     
}
