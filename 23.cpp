#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void generate()
{
  ifstream in;
  in.open("input.txt");
  int k;
  in >> k;
  string text;
  in >> text;
  in.close();
  
  map<string, int> kmers;
  for (auto i = 0; i <= text.length() - k; i++)
  {
    auto tmp = text.substr(i, k);
    auto it = kmers.find(tmp);
    if (it == kmers.end())
      kmers[tmp] = 1;
    else
      kmers[tmp]++;
  }
  ofstream out;
  out.open("output.txt");
  auto it = kmers.begin();
  while (it != kmers.end())
  {
    auto count = it->second;
    for (auto i = 0; i < count; i++)
      out << it->first << endl;
    it++;
  }
  out.close();
}

int main()
{
  generate();
  return 0;
}