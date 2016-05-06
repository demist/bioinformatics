#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void count(string code, string pattern, int d)
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
  ofstream out;
  out.open("output.txt");
  for (auto x : answer)
    out << x << " ";
  out << endl;
  out.close();
}

int main()
{
  string a, b;
  int d;
  ifstream in;
  in.open("input.txt");
  in >> a >> b >> d;
  in.close();
  count(b, a, d);
  return 0;
}