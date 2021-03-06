#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <list>
#include <cmath>

using namespace std;

bool check(string dna, string pattern, int d)
{
    for (auto i = 0; i <= dna.length() - pattern.length(); i++)
    {
        auto count = 0; 
        for (auto j = 0; j < pattern.length(); j++)
            if (dna[i + j] != pattern[j])
                count++;
        if (count <= d)
            return true;
    }
    return false;
}

void motif()
{
    ifstream in;
    in.open("input.txt");
    int k, d;
    in >> k >> d;
    string tmp;
    list<string> dnas;
    set<string> res;
    while (in >> tmp)
        dnas.push_back(tmp);
    in.close();
    auto code = 0;
    string kmer(k, 'A');
    while (code < (int) pow(4, k))
    {
        auto tmp = code;
        for (auto i = k - 1; i >= 0; i--)
        {
            auto sym = tmp / (int) pow(4, i);
            tmp = tmp - sym * (int) pow(4, i);
            switch (sym)
            {
                case 0:
                    kmer[i] = 'A';
                    break;
                case 1:
                    kmer[i] = 'C';
                    break;
                case 2:
                    kmer[i] = 'G';
                    break;
                case 3:
                    kmer[i] = 'T';
                    break;
                default:
                    break;
            }
        }
        auto it = dnas.begin();
        auto flag = true;
        while (it != dnas.end())
        {
            if (!check(*it, kmer, d))
                flag = false;
            it++;
        }
        if (flag)
            res.insert(kmer);
        code++;
    }
    for (auto x : res)
        cout << x << " ";
    cout << endl;
}


int main()
{
    motif();
    return 0;
}