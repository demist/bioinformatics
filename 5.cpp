#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>

using namespace std;

bool check(string code, string pattern, int l, int t)
{
  auto count = 0;
  vector<int> apps;
  for (auto i = 0; i <= code.length() - pattern.length(); i++)
  {
    auto flag = true;
    for (auto j = 0; j < pattern.length(); j++)
      if (code[i + j] != pattern[j])
	flag = false;
    if (flag)
      apps.push_back(i);
  }
  if (apps.size() < t)
    return false;
  for (auto i = 0; i <= apps.size() - t; i++)
  {
    if (apps[i + t - 1] - apps[i] <= l)
      return true;
  }
  return false;
}

void clump(string code, int k, int l, int t)
{
  set<string> answer;
  for (auto i = 0; i <= code.length() - k; i++)
  {
    auto pattern = code.substr(i, k);
    auto flag = check(code, pattern, l, t);
    if (flag)
      answer.insert(pattern);
  }
  for (auto x : answer)
    cout << x << " ";
  cout << endl;
}

int main()
{
  string a;
  int k,l,t;
  ifstream in;
  in.open("input.txt");
  in >> a >> k >> l >> t;
  clump(a, k, l, t);
  return 0;
}