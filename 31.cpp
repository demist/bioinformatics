#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <cmath>

using namespace std;

string getStr(int a, int k)
{
    string res(k, '0');
    for (int i = k - 1; i >=0 ; i--)
    {
        if (a >= (int) pow(2, i))
        {
            res[i] = '1';
            a-=(int) pow(2, i);
        }
    }
    auto res2 = res;
    for (auto i = 0; i < res.length(); i++)
        res2[i] = res[res.length() - i - 1];
    return res2;
}

int getInt(string a)
{
    int res = 0;
    auto k = a.length();
    for (auto i = 0; i < k; i++)
        res += a[i] == '1' ? pow(2, k - i - 1) : 0;
    return res;
}

void eulerian()
{
    ifstream in;
    in.open("input.txt");
    int k;
    in >> k;
    k -= 1;
    in.close();
    map<int, set<int>> gr;
    map<int, int> indeg;
    for (auto i = 0; i < (int) pow(2, k); i++)
    {
        auto cur = getStr(i, k);
        auto v1 = cur.substr(1, k - 1) + "0";
        auto v2 = cur.substr(1, k - 1) + "1";
        gr[i].insert(getInt(v1));
        gr[i].insert(getInt(v2));
        //cout << cur << " " << v1 << " " << v2 << endl;
        auto it1 = indeg.find(getInt(v1));
        if (it1 == indeg.end())
            indeg[getInt(v1)] = 1;
        else
            indeg[getInt(v1)]++;

        auto it2 = indeg.find(getInt(v2));
        if (it2 == indeg.end())
            indeg[getInt(v2)]++;
        else
            indeg[getInt(v2)]++;
    }
    list<int> res;
    int v = 0;
    stack<int> st;
    st.push(v);
    while (!st.empty())
    {
        auto w = st.top();
        for (auto u : gr)
        {
            auto it = gr[w].find(u.first);
            if (it != gr[w].end())
            {
                st.push(u.first);
                gr[w].erase(it);
                break;
            }
        }
        if (w == st.top())
        {
            st.pop();
            res.push_back(w);
        }
    }
    auto cnt = 0;
    auto it = res.end();
    it--;
    list<string> verts;
    //cout << "verts:" << endl;
    while (it != res.begin())
    {
        verts.push_back(getStr(*it, k));
        //cout << *it << "->";
        it--;
    }
    //verts.push_back(getStr(*it,k));
    //cout << endl;
    auto it2 = verts.begin();
    while (it2 != verts.end())
    {
        cout << (*it2)[k - 1];
        it2++;
    }
    cout << endl;
}

int main()
{
    eulerian();
    return 0;
}