#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>

using namespace std;

string reverse(string a)
{
  string res = a;
  for (auto i = 0; i < a.length(); i++)
  {
    switch (a[i])
    {
      case 'A':
	res[a.length() - i - 1] = 'T';
	break;
      case 'T':
	res[a.length() - i - 1] = 'A';
	break;
      case 'C':
	res[a.length() - i - 1] = 'G';
	break;
      case 'G':
	res[a.length() - i - 1] = 'C';
	break;
      default:
	break;
    }
  }
  return res;
}

int count(string code, string pattern, int d)
{
  list<int> answer;
  for (auto i = 0; i <= code.length() - pattern.length(); i++)
  {
    auto dis = 0;
    for (auto j = 0; j < pattern.length(); j++)
      if (code[i + j] != pattern[j])
	dis++;
    if (dis <= d)
      answer.push_back(i);
  }
  return answer.size();
}

void find(string a, int k, int d)
{
  int max = 0;
  list<string> res;
  string kmer(k, 'A');
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
    auto rev = reverse(kmer);
    auto c = count(a, kmer, d) + count(a, rev, d);
    if (c == max)
      res.push_back(kmer);
    if (c > max)
    {
      res.clear();
      max = c;
      res.push_back(kmer);
    }
  }
  for (auto x : res)
    cout << x << " ";
  cout << endl;
}

int main()
{
  string a;
  int k, d;
  ifstream in;
  in.open("input.txt");
  cin >> a >> k >> d;
  in.close();
  find(a, k, d);
  return 0;
}