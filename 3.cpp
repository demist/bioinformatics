#include <iostream>
#include <fstream>
#include <string>

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

int main()
{
  string a;
  ifstream in;
  in.open("input.txt");
  in >> a;
  in.close();
  ofstream out;
  out.open("output.txt");
  out << reverse(a) << endl;
  out.close();
}