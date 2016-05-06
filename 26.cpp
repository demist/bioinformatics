#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>

using namespace std;

void debruijn()
{
    ifstream in;
    in.open("input.txt");
    int k;
    in >> k;
    k--;
    string text;
    in >> text;
    in.close();

    map<string, list<string>> res;
    for (auto i = 0; i < text.length() - k; i++)
    {
        auto kmer = text.substr(i, k);
        auto next = text.substr(i + 1, k);
        res[kmer].push_back(next);
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
    debruijn();
    return 0;
}