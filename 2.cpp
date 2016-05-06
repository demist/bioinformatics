#include <iostream>
#include <string>
#include <set>

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

void kmer(string code, int k)
{
  set<string> answer;
  auto max = 0;
  for (auto i = 0; i <= code.length() - k; i++)
  {
    auto pattern = code.substr(i, k);
    auto freq = count(code, pattern);
    if (freq == max)
      answer.insert(pattern);
    if (freq > max)
    {
      answer.clear();
      answer.insert(pattern);
      max = freq;
    }
  }
  for (auto x : answer)
    cout << x << " ";
  cout << endl;
}

int main()
{
  string a;
  int k;
  cin >> a >> k;
  kmer(a, k);
  return 0;
}