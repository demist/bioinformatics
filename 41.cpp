#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

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

int score(string pep, vector<int> spec)
{
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
  auto result = 0;
  for (auto x : spec)
  {
      auto it = res.find(x);
      if (it != res.end())
      {
          result++;
          res.erase(it);
      }
  }
  return result;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    string pep;
    in >> pep;
    vector<int> spec;
    int a;
    while (in >> a)
        spec.push_back(a);
    in.close();
    cout << score(pep, spec) << endl;
    return 0;
}