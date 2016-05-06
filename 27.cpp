#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>

using namespace std;

void debruj()
{
    ifstream in;
    in.open("input.txt");
    list<string> kmers;
    string tmp;
    while (in >> tmp)
        kmers.push_back(tmp);
    in.close();
    map<string, list<string>> res;
    for (auto x : kmers)
    {
        auto t1 = x.substr(0, x.length() - 1);
        auto t2 = x.substr(1, x.length() - 1);
        res[t1].push_back(t2);
    }
    ofstream out;
    out.open("output.txt");
    for (auto x : res)
    {
        out << x.first << " -> ";
        auto cnt = 0;
        for (auto y : x.second)
        {
            out << y;
            if (cnt != x.second.size() - 1)
                out << ",";
            cnt++;
        }
        out << endl;
    }
    out.close();
}

int main()
{
    debruj();
    return 0;
}