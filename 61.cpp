#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int getMax(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  multiset<int, std::greater<int>> tmp;
  tmp.insert(a1);
  tmp.insert(a2);
  tmp.insert(a3);
  tmp.insert(a4);
  tmp.insert(a5);
  tmp.insert(a6);
  tmp.insert(a7);
  return *(tmp.begin());
}

int getInd(int m, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  if (m == a1)
    return 0;
  if (m == a2)
    return 1;
  if (m == a3)
    return 2;
  if (m == a4)
    return 3;
  if (m == a5)
    return 4;
  if (m == a6)
    return 5;
  if (m == a7)
    return 6;
  return 0;
}

void three()
{
  ifstream in;
  in.open("input.txt");
  string s1,s2,s3;
  in >> s1 >> s2 >> s3;
  in.close();
  vector<vector<vector<int>>> matrix;
  matrix.resize(s1.length() + 1);
  for (auto i = 0; i < s1.length() + 1; i++)
    matrix[i] = vector<vector<int>>(s2.length() + 1, vector<int>(s3.length() + 1, 0));

  for (auto i = 1; i < s1.length() + 1; i++)
  {
    for (auto j = 1; j < s2.length() + 1; j++)
    {
      for (auto k = 1; k < s3.length() + 1; k++)
      {
	auto x1 = matrix[i - 1][j][k];
	auto x2 = matrix[i][j - 1][k];
	auto x3 = matrix[i][j][k - 1];
	
	auto x12 = matrix[i - 1][j - 1][k];
	auto x13 = matrix[i - 1][j][k - 1];
	auto x23 = matrix[i][j - 1][k - 1];
	auto fl = (s1[i - 1] == s2[j - 1] && s1[i - 1] == s3[k - 1]) ? 1 : 0;
	auto x123 = matrix[i - 1][j - 1][k - 1] + fl;
	
	auto m = getMax(x1, x2, x3, x12, x13, x23, x123);
	matrix[i][j][k] = m;
      }
    }
  }
  string res1, res2, res3;
  auto cur_i = s1.length(), cur_j = s2.length(), cur_k = s3.length();
  cout << matrix[cur_i][cur_j][cur_k] << endl;
  while (cur_i * cur_j * cur_k != 0)
  {
    auto x1 = matrix[cur_i - 1][cur_j][cur_k];
    auto x2 = matrix[cur_i][cur_j - 1][cur_k];
    auto x3 = matrix[cur_i][cur_j][cur_k - 1];
  
    auto x12 = matrix[cur_i - 1][cur_j - 1][cur_k];
    auto x13 = matrix[cur_i - 1][cur_j][cur_k - 1];
    auto x23 = matrix[cur_i][cur_j - 1][cur_k - 1];
    auto fl = (s1[cur_i - 1] == s2[cur_j - 1] && s1[cur_i - 1] == s3[cur_k - 1]) ? 1 : 0;
    auto x123 = matrix[cur_i - 1][cur_j - 1][cur_k - 1] + fl;
	
    auto m = getMax(x1, x2, x3, x12, x13, x23, x123);
    auto ind = getInd(m, x1, x2, x3, x12, x13, x23, x123);
    if (ind == 0)
    {
      res1 = s1[cur_i - 1] + res1;
      res2 = "-" + res2;
      res3 = "-" + res3;
      cur_i--;
    }
    if (ind == 1)
    {
      res1 = "-" + res1;
      res2 = s2[cur_j - 1] + res2;
      res3 = "-" + res3;
      cur_j--;
    }
    if (ind == 2)
    {
      res1 = "-" + res1;
      res2 = "-" + res2;
      res3 = s3[cur_k - 1] + res3;
      cur_k--;
    }
    if (ind == 3)
    {
      res1 = s1[cur_i - 1] + res1;
      res2 = s2[cur_j - 1] + res2;
      res3 = "-" + res3;
      cur_i--;
      cur_j--;
    }
    if (ind == 4)
    {
      res1 = s1[cur_i - 1] + res1;
      res2 = "-" + res2;
      res3 = s3[cur_k - 1] + res3;
      cur_i--;
      cur_k--;
    }
    if (ind == 5)
    {
      res1 = "-" + res1;
      res2 = s2[cur_j - 1] + res2;
      res3 = s3[cur_k - 1] + res3;
      cur_j--;
      cur_k--;
    }
    if (ind == 6)
    {
      res1 = s1[cur_i - 1] + res1;
      res2 = s2[cur_j - 1] + res2;
      res3 = s3[cur_k - 1] + res3;
      cur_i--;
      cur_j--;
      cur_k--;
    }
  }
  while (cur_i != 0)
  {
    res1 = s1[cur_i - 1] + res1;
    res2 = "-" + res2;
    res3 = "-" + res3;
    cur_i--;
  }
  while (cur_j != 0)
  {
    res1 = "-" + res1;
    res2 = s2[cur_j - 1] + res2;
    res3 = "-" + res3;
    cur_j--;
  }
  while (cur_k != 0)
  {
    res1 = "-" + res1;
    res2 = "-" + res2;
    res3 = s3[cur_k - 1] + res3;
    cur_k--;
  }
  cout << res1 << endl;
  cout << res2 << endl;
  cout << res3 << endl;
}

int main()
{
  three();
  return 0;
}