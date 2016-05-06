#include <iostream>
#include <cmath>
#include <string>

using namespace std;

long long int patternToNumber(string s)
{
  long long int res = 0;
  for (auto i = 0; i < s.length(); i++)
  {
    int sym;
    switch (s[i])
    {
      case 'A':
	sym = 0;
	break;
      case 'C':
	sym = 1;
	break;
      case 'G':
	sym = 2;
	break;
      case 'T':
	sym = 3;
	break;
      default:
	break;
    }
    res += sym * pow(4, s.length() - i - 1);
  }
  return res;
}

int main()
{
  string s;
  cin >> s;
  cout << patternToNumber(s) << endl;
  return 0;
}