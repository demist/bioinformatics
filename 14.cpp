#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <list>

using namespace std;

void find(string a, int d)
{
  list<string> res;
  string kmer(a.length(), 'A');
  int k = a.length();
  for (auto code = 0; code < (int) pow(4, k); code++)
  {
    auto tmp = code;
    for (auto i = k - 1; i >= 0; i--)
    {
      int s = tmp / (int) pow(4, i);
      switch (s)
      {
	case 0:
	  kmer[i] = 'A';
	  break;
	case 1:
	  kmer[i] = 'T';
	  break;
	case 2:
	  kmer[i] = 'C';
	  break;
	case 3:
	  kmer[i] = 'G';
	  break;
	default:
	  break;
      }
      tmp = tmp - (int) pow(4, i) * s;
    }
    auto count = 0;
    for (auto j = 0; j < a.length(); j++)
      if (a[j] != kmer[j])
	count++;
    if (count <= d)
      res.push_back(kmer);
  }
  ofstream out;
  out.open("output.txt");
  for (auto x : res)
    out << x << endl;
  out.close();
}

int main()
{
  string a;
  int d;
  cin >> a >> d;
  find(a, d);
  return 0;
}