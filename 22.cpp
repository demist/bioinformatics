#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int dist(string a, string b)
{
    auto res = 0;
    for (auto i = 0; i < a.length(); i++)
        if (a[i] != b[i])
            res++;
    return res;
}

int distBtwPatternAndStrs()
{
    ifstream in;
    in.open("input.txt");
    string pattern;
    in >> pattern;
    int k = pattern.length();
    vector<string> dna;
    string tmp;
    while(in >> tmp)
        dna.push_back(tmp);
    in.close();
    auto distance = 0;
    for (auto i = 0; i < dna.size(); i++)
    {
        auto hamDist = pattern.length() + 1;
        for (auto j = 0; j <= dna[i].length() - k; j++)
        {
            auto newPattern = dna[i].substr(j, k);
            auto newHamDist = dist(pattern, newPattern);
            if (newHamDist < hamDist)
                hamDist = newHamDist;
        }
        distance += hamDist;
    }
    return distance;
}

int main()
{
    cout << distBtwPatternAndStrs() << endl;
    return 0;
}