#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void reconst()
{
    ifstream in;
    in.open("input.txt");
    int k;
    in >> k;
    string tmp;
    multimap<string, string> begs;
    multimap<string, string> ends;
    while (in >> tmp)
    {
        auto sb1 = tmp.substr(0, k - 1);
        auto sb2 = tmp.substr(1, k - 1);
        begs.insert(make_pair(sb1, tmp));
        ends.insert(make_pair(sb2, tmp));
    }
    in.close();
    string res(begs.size() + k - 1, 'A');
    string first;
    for (auto x : begs)
    {
        auto it = ends.find(x.first);
        if (it == ends.end())
            first = x.second;
    }
    for (auto i = 0; i < k; i++)
        res[i] = first[i];
    auto cur = first.substr(1, k - 1);
    for (auto i = 0; i < begs.size() - 1; i++)
    {
        auto newone = begs.find(cur);
        res[k + i] = newone->second[k - 1];
        cur = newone->second.substr(1, k - 1);
    }
    cout << res << endl;
}

int main()
{
    reconst();
    return 0;
}