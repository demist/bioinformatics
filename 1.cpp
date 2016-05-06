#include <iostream>
#include <string>

using namespace std;

int count(string code, string pattern)
{
  auto count = 0;
  for (auto i = 0; i <= code.length() - pattern.length(); i++)
  {
    auto flag = true;
    for (auto j = 0; j < pattern.length(); j++)
      if (code[i + j] != pattern[j])
	flag = false;
    if (flag)
      count++;
  }
  return count;
}

int main()
{
  string a, b;
  cin >> a >> b;
  cout << count(a, b) << endl;
  return 0;
}