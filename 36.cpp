#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

char getA(string s)
{
    if (s == "AAU" || s == "AAC")
        return 'N';
    if (s == "AAA" || s == "AAG")
        return 'K';
    if (s.substr(0, 2) == "AC")
        return 'T';
    if (s == "AGU" || s == "AGC")
        return 'S';
    if (s == "AGA" || s == "AGG")
        return 'R';
    if (s == "AUU" || s == "AUC" || s == "AUA")
        return 'I';
    if (s == "AUG")
        return 'M';
    if (s == "CAU" || s == "CAC")
        return 'H';
    if (s == "CAA" || s == "CAG")
        return 'Q';
    if (s.substr(0, 2) == "CC")
        return 'P';
    if (s.substr(0, 2) == "CG")
        return 'R';
    if (s.substr(0, 2) == "CU")
        return 'L';
    if (s == "GAU" || s == "GAC")
        return 'D';
    if (s == "GAA" || s == "GAG")
        return 'E';
    if (s.substr(0, 2) == "GC")
        return 'A';
    if (s.substr(0, 2) == "GG")
        return 'G';
    if (s.substr(0, 2) == "GU")
        return 'V';
    if (s == "UAC" || s == "UAU")
        return 'Y';
    if (s.substr(0, 2) == "UC")
        return 'S';
    if (s == "UGU" || s == "UGC")
        return 'C';
    if (s == "UGG")
        return 'W';
    if (s == "UUC" || s == "UUU")
        return 'F';
    if (s == "UUA" || s == "UUG")
        return 'L';
    return '$';
}

void amino()
{
    ifstream in;
    in.open("input.txt");
    string tmp;
    in >> tmp;
    in.close();
    ofstream out;
    out.open("output.txt");
    for (auto i = 0; i <= tmp.length() - 3; i += 3)
    {
        auto sub = tmp.substr(i, 3);
        if (getA(sub) != '$')
            out << getA(sub);
    }
//    out << endl;
    out.close();
}

int main()
{
    amino();
    return 0;
}