#include <iostream>
#include <cmath>
#include <string>

using namespace std;

string numberToPattern(int s, int k)
{
  string res(k, 'A');
  for (auto i = k - 1; i >= 0; i--)
  {
    int sym = s / (int) pow(4, i);
    switch(sym)
    {
      case 0:
	res[k - i - 1] = 'A';
	break;
      case 1:
	res[k - i - 1] = 'C';
	break;
      case 2:
	res[k - i - 1] = 'G';
	break;
      case 3:
	res[k - i - 1] = 'T';
	break;
      default:
	break;
    }
    s = s - sym * (int) pow(4, i);
  }
  return res;
}

int main()
{
  long long int s, k;
  cin >> s >> k;
  cout << numberToPattern(s, k) << endl;
  return 0;
}