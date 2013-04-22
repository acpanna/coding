#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

#define MAXLINE 256

int month_name_to_number(char *name);
bool check(int sd, int d, int rd, int m, int rm, int y, int ry);
bool check_date(int d1, int m1, int y1, int d2, int m2, int y2);

using namespace std;

int main(int argc, char **argv)
{
  // declarations
  int day, month, year, read_day, read_month, read_year, stichtag;
  char buffer2[5];
  struct tm *ptr;
  time_t zeit;
 
  // argumentlist check
  if (argc < 2)
  {
    cerr << "Usage: isdnclearer <stichtag>" << endl;
    return 1;
  }
  else
    stichtag = atoi(argv[1]);

  // set current date
  time(&zeit);
  ptr = localtime(&zeit);
  strftime(buffer2, 3, "%d", ptr);
  day = atoi(buffer2);
  strftime(buffer2, 3, "%m", ptr);
  month = atoi(buffer2);
  strftime(buffer2, 3, "%y", ptr);
  year = atoi(buffer2);
  
  // parse /var/log/isdn.log
  system("cp /var/log/isdn.log /tmp/isdn.log.tmp");

  ifstream fin("/tmp/isdn.log.tmp");
  ofstream fout("/var/log/isdn.log");

  if (fin.fail() || fout.fail())
  {
    cerr << "Beim Lesen/Schreiben der Datei /var/log/isdn.log ist ein Fehler\
	aufgetreten !" << endl;
    return 1;
  }

  while(!fin.eof())
  {
    char buffer[MAXLINE] = {'\0'};
    fin.getline(buffer, MAXLINE, '\n');
  
    buffer2[0] = buffer[0];
    buffer2[1] = buffer[1];
    buffer2[2] = buffer[2];
    buffer2[3] = '\0';

    read_month = month_name_to_number(buffer2); 

    buffer2[0] = buffer[3];
    buffer2[1] = buffer[4];
    buffer2[2] = buffer[5];
    buffer2[3] = buffer[6];
    buffer2[4] = '\0';

    read_day = atoi(buffer2);

    buffer2[0] = buffer[18];
    buffer2[1] = buffer[19];
    buffer2[2] = '\0';

    read_year = atoi(buffer2);

    if (check(stichtag, day, read_day, month, read_month, year, read_year))
      fout << buffer << endl;
  }
    
  fin.close();
  fout.close();

  system("rm /tmp/isdn.log.tmp");
/*
  // parse /winhd/iwatch.txt
  system("cp /winhd/iwatch.txt /tmp/iwatch.txt.tmp");

  ifstream fin2("/tmp/iwatch.txt.tmp");
  ofstream fout2("/winhd/iwatch.txt");

  if (fin2.fail() || fout2.fail())
  {
    cerr << "Beim Lesen/Schreiben der Datei /winhd/iwatch.txt ist ein Fehler\
	aufgetreten !" << endl;
    return 1;
  }
  
  while(!fin2.eof())
  {
    char buffer[MAXLINE] = {'\0'};
    fin2.getline(buffer, MAXLINE, '\n');
    
    buffer2[0] = buffer[9];
    buffer2[1] = buffer[10];
    buffer2[2] = '\0';

    read_day = atoi(buffer2);
    
    buffer2[0] = buffer[12];
    buffer2[1] = buffer[13];
    buffer2[2] = '\0';

    read_month = atoi(buffer2);

    buffer2[0] = buffer[15];
    buffer2[1] = buffer[16];
    buffer2[2] = '\0';

    read_year = atoi(buffer2);
    
    if (check(stichtag, day, read_day, month, read_month, year, read_year))
      fout2 << buffer << endl;
  }

  fin2.close();
  fout2.close();

  system("rm /tmp/iwatch.txt.tmp");
*/
  return 0;
}

int month_name_to_number(char *name)
{
  if (strcmp(name, "Jan") == 0)
    return 1;
  if (strcmp(name, "Feb") == 0)
    return 2;
  if (strcmp(name, "Mar") == 0)
    return 3;
  if (strcmp(name, "Apr") == 0)
    return 4;
  if (strcmp(name, "May") == 0)
    return 5;
  if (strcmp(name, "Jun") == 0)
    return 6;
  if (strcmp(name, "Jul") == 0)
    return 7;
  if (strcmp(name, "Aug") == 0)
    return 8;
  if (strcmp(name, "Sep") == 0)
    return 9;
  if (strcmp(name, "Oct") == 0)
    return 10;
  if (strcmp(name, "Nov") == 0)
    return 11;
  if (strcmp(name, "Dec") == 0)
    return 12;

  return 0;
}

bool check(int sd, int d, int rd, int m, int rm, int y, int ry)
{
  if (d < sd)
  {
    if (m == 1)
    {
      m = 13;
      y = y - 1;
    }
     
    if (check_date(rd, rm, ry, sd, m-1, y))
      return true;
  }
  else
  {
    if (check_date(rd, rm, ry, sd, m, y)) 
      return true;
  }

  return false;
}

// Falls d1:m1:y1 >= d2:m2:y2 
// gebe true zurueck
bool check_date(int d1, int m1, int y1, int d2, int m2, int y2)
{
  if (y1 > y2)
    return true;
  else if (y1 < y2)
    return false;
  else
  {
    if (m1 > m2)
      return true;
    else if (m1 < m2)
      return false;
    else
    {
      if (d1 >= d2)
	return true;
      else
	return false;
    }
  }
}
