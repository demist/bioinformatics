#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<int, list<int>> gr;
unordered_map<int, bool> used;
vector<int> ans;

void dfs(int v)
{
  used[v] = true;
  if (gr.find(v) != gr.end())
  {
    for (auto x : gr[v])
    {
      if (!used[x])
	dfs(x);
    }
  }
  ans.push_back(v);
}

void topsort()
{
  ifstream in;
  in.open("input.txt");
  int tmp1, tmp2;
  char lane[256];
  while (in.getline(lane, 256))
  {
    istringstream tmp(lane);
    tmp >> tmp1;
    used[tmp1] = false;
    while (tmp >> tmp2)
    {
      used[tmp2] = false;
      gr[tmp1].push_back(tmp2);
    }
  }
  in.close();
  for (auto x : used)
  {
    if (!x.second)
      dfs(x.first);
  }
  ofstream out;
  out.open("output.txt");
  for (auto i = ans.size() - 1; i > 0; i--)
    out << ans[i] << ", ";
  out << ans[0] << endl;
  out.close();
}

int main()
{
  topsort();
  return 0;
}