#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

using namespace std;

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

int dist(string a, string b)
{
    auto res = 0;
    for (auto i = 0; i < a.length(); i++)
        if (a[i] != b[i])
            res++;
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

void greedy()
{
    ifstream in;
    in.open("input.txt");
    int k,t;
    in >> k >> t;
    vector<string> dna;
    string tmp;
    while (in >> tmp)
        dna.push_back(tmp);
    in.close();

    vector<string> bestMotifs;
    for (auto i = 0; i < dna.size(); i++)
        bestMotifs.push_back(dna[i].substr(0, k));
    for (auto i = 0; i <= dna[0].length() - k; i++)
    {
        vector<string> motifs;
        motifs.push_back(dna[0].substr(i, k));
        for (auto j = 1; j <= dna.size() - 1; j++)
        {
            vector<vector<double>> profile;
            profile.resize(4);
            for (auto q = 0; q < 4; q++)
                profile[q].resize(k);
            for (auto q = 0; q < k; q++)
            {
                auto cA = 0, cC = 0, cT = 0, cG = 0;
                auto it = motifs.begin();
                while (it != motifs.end())
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
                profile[0][q] = (double) (cA + 1) / (motifs.size() + 4);
                profile[1][q] = (double) (cC + 1) / (motifs.size() + 4);
                profile[2][q] = (double) (cG + 1) / (motifs.size() + 4);
                profile[3][q] = (double) (cT + 1) / (motifs.size() + 4);
            }
            auto newMotif = probability(dna[j], k, profile);
            motifs.push_back(newMotif);
        }
        if (score(motifs) < score(bestMotifs))
        {
            bestMotifs.clear();
            bestMotifs = motifs;
        }
    }
    for (auto x : bestMotifs)
        cout << x << " ";
    cout << endl;
}

int main()
{
    greedy();
    return 0;
}