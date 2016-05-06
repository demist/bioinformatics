#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
#include <vector>

using namespace std;

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

void frarray(string a, int k)
{
  int max = 0;
  string kmer(k, 'A');
  vector<int> array((int) pow(4, k));
  for (auto code = 0; code < (int) pow(4, k); code++)
  {
    auto tmp = code;
    for (auto i = k - 1; i >= 0; i--)
    {
      int s = tmp / (int) pow(4, i);
      switch (s)
      {
	case 0:
	  kmer[k - i - 1] = 'A';
	  break;
	case 1:
	  kmer[k - i - 1] = 'C';
	  break;
	case 2:
	  kmer[k - i - 1] = 'G';
	  break;
	case 3:
	  kmer[k - i - 1] = 'T';
	  break;
	default:
	  break;
      }
      tmp = tmp - (int) pow(4, i) * s;
    }
    auto c = count(a, kmer, 0);
    array[code] = c;
  }
  for (auto x : array)
    cout << x << " ";
  cout << endl;
}

int main()
{
  string a;
  int k;
  ifstream in;
  in.open("input.txt");
  cin >> a >> k;
  in.close();
  frarray(a, k);
  return 0;
}