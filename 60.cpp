#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string s1, s2;
int gap = -5;
vector<vector<int>> matrix(20, vector<int>(20));

ofstream dbg;

class edge
{
public:
  int bt;
  int x;
  int y;
  edge(){}
  edge(int a, int b, int c) :
    x(a), y(b), bt(c) {}
};

int getId(char a)
{
     if (a == 'A')
         return 0;
     if (a == 'C')
         return 1;
     if (a == 'D')
         return 2;
     if (a == 'E')
         return 3;
     if (a == 'F')
         return 4;
     if (a == 'G')
         return 5;
     if (a == 'H')
         return 6;
     if (a == 'I')
         return 7;
     if (a == 'K')
         return 8;
     if (a == 'L')
         return 9;
     if (a == 'M')
         return 10;
     if (a == 'N')
         return 11;
     if (a == 'P')
         return 12;
     if (a == 'Q')
         return 13;
     if (a == 'R')
         return 14;
     if (a == 'S')
         return 15;
     if (a == 'T')
         return 16;
     if (a == 'V')
         return 17;
     if (a == 'W')
         return 18;
     if (a == 'Y')
         return 19;
     return -1;
}

void loadMatrix()
{
    ifstream in;
    in.open("matrix.txt");
    int tmp;
    for (auto i = 0; i < 20; i++)
    {
        for (auto j = 0; j < 20; j++)
        {
            in >> tmp;
            matrix[i][j] = tmp;
        }
    }
    in.close();
}

int getResScore(string a, string b)
{
  int res = 0;
  if (a.length() != b.length())
    return res;
  for (auto i = 0; i < a.length() - 1; i++)
  {
    if (a[i] == '-' || b[i] == '-')
      res += gap;
    else
    {
      res += matrix[getId(a[i])][getId(b[i])];
    }
  }
  return res;
}

void score(string v, string w, vector<int>& last_line, vector<int>& backtrack)
{
    vector<int> cur_line(v.length() + 1, 0);
    vector<int> next_line(v.length() + 1, 0);
    backtrack.resize(v.length() + 1);
    for (auto i = 1; i < cur_line.size(); i++)
        cur_line[i] = cur_line[i - 1] + gap;
    for (auto j = 0; j < w.length(); j++)
    {
	for (auto i = 0; i < cur_line.size(); i++)
        {
            if (i == 0)
            {
                next_line[i] = cur_line[i] + gap;
                backtrack[i] = 2;
                continue;
            }
            auto x1 = cur_line[i - 1] + matrix[getId(v[i - 1])][getId(w[j])]; //i - 1 j -1
            auto x2 = next_line[i - 1] + gap; // i - 1
            auto x3 = cur_line[i] + gap; // j - 1
            if (x1 >= x2 && x1 >= x3)
            {
                next_line[i] = x1;
                backtrack[i] = 0;
                continue;
            }
            if (x2 >= x1 && x2 >= x3)
            {
                next_line[i] = x2;
                backtrack[i] = 1;
                continue;
            }
            if (x3 >= x1 && x3 >= x2)
            {
                next_line[i] = x3;
                backtrack[i] = 2;
                continue;
            }
        }
        cur_line = next_line;
    }
    last_line = cur_line;
}

edge midedge(int x1, int x2, int y1, int y2)
{
    auto v = s1.substr(x1, x2 - x1 + 1);
    auto w = s2.substr(y1, y2 - y1 + 1);
    vector<int> forward, backward, bt1, bt2;
    int m = w.length() / 2;
    score(v, w.substr(0, m), forward, bt1);
    auto s1r = v;
    for (auto i = 0; i < v.length(); i++)
        s1r[s1r.length() - 1 - i] = v[i];
    auto s2r = w.substr(m);
    for (auto i = 0; i < s2r.length(); i++)
        s2r[s2r.length() - 1 - i] = w[m + i];
    score(s1r, s2r, backward, bt2);
    auto best = -1000000;
    int x, b1;
    for (auto i = 0; i < v.length(); i++)
    {
	auto cur = forward[i] + backward[backward.size() - 1 - i];
	if (cur >= best)
        {
            x = i;
	    b1 = bt1[i];
            best = cur;
        }
    }
    //cout << x1 << " " << x2 << " " << y1 << " " << y2 << " " <<  x + x1  << " " << m + y1 << endl;
    return edge(x + x1, m + y1, b1);
}


pair<string, string> align(int x1, int x2, int y1, int  y2)
{
  //cout << s1.substr(x1, x2 - x1 + 1) << " " << s2.substr(y1, y2 - y1 + 1) << endl;
  pair<string, string> res;
  
  if (x1 > x2 && y1 > y2)
    return res;
  if (x1 > x2)
  {
    for (auto i = 0; i <= y2 - y1; i++)
      res.first += "-";
    res.second = s2.substr(y1, y2 - y1 + 1);
    return res;
  }
  if (y1 > y2)
  {
    res.first = s1.substr(x1, x2 - x1 + 1);
    for (auto i = 0; i <= x2 - x1; i++)
      res.second += "-";
    return res;
  }
  if (x1 == x2 && y1 == y2)
  {
    res.first = s1[x1];
    res.second = s2[y1];
    return res;
  }
  if (x1 == x2)
  {
    auto sym = s1[x1];
    int place;
    auto best = -10000;
    for (auto i = y1; i <= y2; i++)
    {
      if (matrix[getId(sym)][getId(s2[i])] > best)
      {
	place = i;
	best = matrix[getId(sym)][getId(s2[i])];
      }
    }
    for (auto i = y1; i <= y2; i++)
    {
      if (i == place)
	res.first += sym;
      else
	res.first += "-";
    }
    res.second = s2.substr(y1, y2 - y1 + 1);
    return res;
  }
  if (y1 == y2)
  {
    res.first = s1.substr(x1, x2 - x1 + 1);
    auto sym = s2[y1];
    int place;
    auto best = -10000;
    for (auto i = x1; i <= x2; i++)
    {
      if (matrix[getId(sym)][getId(s1[i])] > best)
      {
	place = i;
	best = matrix[getId(sym)][getId(s1[i])];
      }
    }
    for (auto i = x1; i <= x2; i++)
    {
      if (i == place)
	res.second += sym;
      else
	res.second += "-";
    }
    return res;
  }
  auto e = midedge(x1, x2, y1, y2);
  if (e.bt == 0)
  {
    res.first += s1[e.x];
    res.second += s2[e.y];
    auto p1 = align(x1, e.x - 1, y1, e.y - 1);
    res.first = p1.first + res.first;
    res.second = p1.second + res.second;
    auto p2 = align(e.x + 1, x2, e.y + 1, y2);
    res.first = res.first + p2.first;
    res.second = res.second + p2.second;
    return res;
  }
  if (e.bt == 1)
  {
    res.first += s1[e.x];
    res.second += "-";
    auto p1 = align(x1, e.x - 1, y1, e.y - 1);
    res.first = p1.first + res.first;
    res.second = p1.second + res.second;
    auto p2 = align(e.x + 1, x2, e.y, y2);
    res.first = res.first + p2.first;
    res.second = res.second + p2.second;
    return res;
  }
  if (e.bt == 2)
  {
    res.first += "-";
    res.second += s2[e.y];
    auto p1 = align(x1, e.x - 1, y1, e.y - 1);
    res.first = p1.first + res.first;
    res.second = p1.second + res.second;
    auto p2 = align(e.x, x2, e.y + 1, y2);
    res.first = res.first + p2.first;
    res.second = res.second + p2.second;
    return res;
  }
  return res;
}

void linear()
{
  ifstream in;
  in.open("input.txt");
  in >> s1 >> s2;
  in.close();
  int level = 0;
  auto res = align(0, s1.length(), 0, s2.length());
  ofstream out;
  out.open("output.txt");
  cout << getResScore(res.first, res.second) << endl;
  cout << res.first.length() << " " << res.second.length() << endl;
  out << getResScore(res.first, res.second) << endl;
  out << res.first.substr(0, res.first.length() - 1) << endl << res.second.substr(0, res.second.length() - 1);
  out.close();
}

int main()
{
  dbg.open("debug.txt");
  loadMatrix();
  linear();
  dbg.close();
  return 0;
}