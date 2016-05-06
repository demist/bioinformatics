#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

void conv()
{
    ifstream in;
    in.open("input.txt");
    vector<int> spec;
    int tmp;
    while (in >> tmp)
        spec.push_back(tmp);
    in.close();
    map<int, int> dif;
    for (auto x : spec)
    {
        for (auto y : spec)
        {
            auto d = x - y;
            if (d > 0)
            {
                if (dif.find(d) != dif.end())
                    dif[d]++;
                else
                    dif[d] = 1;
            }
        }
    }
    multimap<int, int> revdif;
    for (auto x : dif)
        revdif.insert(make_pair(x.second, x.first));
    auto it = revdif.end();
    it--;
    ofstream o;
    o.open("output.txt");
    while (it != revdif.begin())
    {
        for (auto i = 0; i < it->first; i++)
            o << it->second << " ";
        it--;
    }
    for (auto i = 0; i < it->first - 1; i++)
        o << it->second << " ";
    o << it->second << endl;
    o.close();
}

int main()
{
    conv();
    return 0;
}