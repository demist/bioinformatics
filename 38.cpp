#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cmath>

using namespace std;

int mass(char c)
{
  if (c == 'G')
    return 57;
  if (c == 'A')
    return 71;
  if (c == 'S')
    return 87;
  if (c == 'P')
    return 97;
  if (c == 'V')
    return 99;
  if (c == 'T')
    return 101;
  if (c == 'C')
    return 103;
  if (c == 'I')
    return 113;
  if (c == 'L')
    return 113;
  if (c == 'N')
    return 114;
  if (c == 'D')
    return 115;
  if (c == 'K')
    return 128;
  if (c == 'Q')
    return 128;
  if (c == 'E')
    return 129;
  if (c == 'M')
    return 131;
  if (c == 'H')
    return 137;
  if (c == 'F')
    return 147;
  if (c == 'R')
    return 156;
  if (c == 'Y')
    return 163;
  if (c == 'W')
    return 186;
  return 0;
}

void cyclo()
{
  ifstream in;
  in.open("input.txt");
  string pep;
  in >> pep;
  in.close();
  multiset<int> res;
  res.insert(0);
  for (auto len = 1; len <= pep.length(); len++)
  {
    for (auto pos = 0; pos < pep.length(); pos++)
    {
      string sub;
      if (pos <= pep.length() - len)
	sub = pep.substr(pos, len);
      else 
      {
	auto beg = pep.substr(pos);
	sub = beg + pep.substr(0, len - beg.length());
      }
      int pmass = 0;
      for (auto i = 0; i < sub.length(); i++)
	pmass += mass(sub[i]);
      res.insert(pmass);
      //cout << sub << " " << pmass << endl;
      if (len == pep.length())
	break;
    }
  }
  ofstream out;
  out.open("output.txt");
  for (auto x : res)
    out << x << " ";
  out << endl;
  out.close();
}

int main()
{
  cyclo();
  return 0;
}