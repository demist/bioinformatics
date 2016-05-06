#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int count(string code1, string code2)
{
  auto count = 0;
  for (auto i = 0; i <= code1.length(); i++)
  {
    if (code1[i] != code2[i])
      count++;
  }
  return count;
}

int main()
{
  string a, b;
  ifstream in;
  in.open("input.txt");
  in >> a >> b;
  in.close();
  cout << count(a, b) << endl;
  return 0;
}