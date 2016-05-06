#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;

int dist(string a, string b)
{
    auto res = 0;
    for (auto i = 0; i < a.length(); i++)
        if (a[i] != b[i])
            res++;
    return res;
}

string probability(string dna, int k, vector<vector<double>> matrix)
{
    string res;
    auto maxc = -1.;
    for (auto i = 0; i <= dna.length() - k; i++)
    {
        auto cur = 1.;
        for (auto j = 0; j < k; j++)
        {
            switch (dna[i + j])
            {
                case 'A':
                    cur *= matrix[0][j];
                    break;
                case 'C':
                    cur *= matrix[1][j];
                    break;
                case 'G':
                    cur *= matrix[2][j];
                    break;
                case 'T':
                    cur *= matrix[3][j];
                    break;
                default:
                    break;
            }
        }
        if (cur > maxc)
        {
            res = dna.substr(i, k);
            maxc = cur;
        }
    }
    return res;
}

int score(vector<string> motifs)
{
    list<string> tr;
    for (auto i = 0; i < motifs[0].length(); i++)
    {
        string tmp(motifs.size(), 'A');
        for (auto j = 0; j < motifs.size(); j++)
            tmp[j] = motifs[j][i];
        tr.push_back(tmp);
    }
    string tests[4];
    tests[0] = string(motifs.size(), 'A');
    tests[1] = string(motifs.size(), 'C');
    tests[2] = string(motifs.size(), 'G');
    tests[3] = string(motifs.size(), 'T');
    auto score = 0;
    auto it = tr.begin();
    while (it != tr.end())
    {
        auto min = motifs.size();
        for (auto i = 0; i < 4; i++)
            if (dist(*it, tests[i]) < min)
                min = dist(*it, tests[i]);
        score += min;
        it++;
    }
    return score;
}

vector<string> gibbsSampler()
{
    ifstream in;
    in.open("input.txt");
    int k,t,N;
    in >> k >> t >> N;
    vector<string> dna(t);
    string tmp;
    for (auto i = 0; i < t; i++)
    {
        in >> tmp;
        dna[i] = tmp;
    }
    vector<string> motifs(t);
    for (auto i = 0; i < t; i++)
    {
        auto pos = (int) rand() % (dna[i].length() - k + 1);
        motifs[i] = dna[i].substr(pos, k);
    }
    vector<string> bestMotifs = motifs;
    for (auto j = 1; j < N; j++)
    {
        auto ir = (int) rand() % t;
        vector<string> withoutI(t - 1);
        for (auto q = 0; q < t; q++)
        {
            if (q < ir)
                withoutI[q] = motifs[q];
            if (q > ir)
                withoutI[q - 1] = motifs[q];
        }
        vector<vector<double>> profile;
        profile.resize(4);
        for (auto q = 0; q < 4; q++)
            profile[q].resize(k);
        for (auto q = 0; q < k; q++)
        {
            auto cA = 0, cC = 0, cT = 0, cG = 0;
            auto it = withoutI.begin();
            while (it != withoutI.end())
            {
                auto current = *it;
                switch (current[q])
                {
                    case 'A':
                        cA++;
                        break;
                    case 'C':
                        cC++;
                        break;
                    case 'G':
                        cG++;
                        break;
                    case 'T':
                        cT++;
                        break;
                    default:
                        break;
                }
                it++;
            }
            profile[0][q] = (double) (cA + 1) / (withoutI.size() + 4);
            profile[1][q] = (double) (cC + 1) / (withoutI.size() + 4);
            profile[2][q] = (double) (cG + 1) / (withoutI.size() + 4);
            profile[3][q] = (double) (cT + 1) / (withoutI.size() + 4);
        }
        motifs[ir] = probability(dna[ir], k, profile);
        if (score(motifs) < score(bestMotifs))
        {
            bestMotifs.clear();
            bestMotifs = motifs;
        }
    }
    return bestMotifs;
}

int main()
{
    vector<string> res = gibbsSampler();
    for (auto i = 0; i < 19; i++)
    {
        auto res2 = gibbsSampler();
        if (score(res2) < score(res))
        {
            res.clear();
            res = res2;
        }
    }
    ofstream out;
    out.open("res.txt");
    for (auto x : res)
        out << x << endl;
    out.close();
    return 0;
}