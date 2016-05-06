#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void skew(string code)
{
  vector<int> res;
  res.resize(code.length() + 1);
  res[0] = 0;
  int sk = 0;
  int min = code.length();
  for (auto i = 0; i < code.length(); i++)
  {
    if (code[i] == 'G')
      sk++;
    if (code[i] == 'C')
      sk--;
    res[i + 1] = sk;
    if (sk < min)
      min = sk;
  }
  for (auto i = 0; i < res.size(); i++)
    if (res[i] == min)
      cout << i << " ";
  cout<< endl;
}

int main()
{
  string a, b;
  ifstream in;
  in.open("input.txt");
  in >> a;
  in.close();
  skew(a);
  return 0;
}