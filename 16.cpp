#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <list>
#include <cmath>

using namespace std;

int check(string dna, string pattern)
{
    int min = pattern.length();
    for (auto i = 0; i <= dna.length() - pattern.length(); i++)
    {
        auto count = 0; 
        for (auto j = 0; j < pattern.length(); j++)
            if (dna[i + j] != pattern[j])
                count++;
        if (count < min)
            min = count;
    }
    return min;
}

void motif()
{
    ifstream in;
    in.open("input.txt");
    int k;
    in >> k;
    string tmp;
    list<string> dnas;
    string res;
    while (in >> tmp)
        dnas.push_back(tmp);
    in.close();
    auto code = 0;
    string kmer(k, 'A');
    auto min = k * dnas.size();
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
        auto sum = 0;
        while (it != dnas.end())
        {
            sum += check(*it, kmer);
            it++;
        }
        if (sum < min)
        {
            res = kmer;
            min = sum;
        }
        code++;
    }
    cout << res << endl;
}


int main()
{
    motif();
    return 0;
}