#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

void count(string code, string pattern)
{
  list<int> answer;
  for (auto i = 0; i <= code.length() - pattern.length(); i++)
  {
    auto flag = true;
    for (auto j = 0; j < pattern.length(); j++)
      if (code[i + j] != pattern[j])
	flag = false;
    if (flag)
      answer.push_back(i);
  }
  for (auto x : answer)
    cout << x << " ";
  cout << endl;
}

int main()
{
  string a, b;
  ifstream in;
  in.open("input.txt");
  in >> a >> b;
  count(b,a);
  return 0;
}