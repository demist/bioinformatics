#include <iostream>
#include <fstream>
#include <string>
#include <list>

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

bool check(string a, string b)
{
  for (auto i = 0, j = 0; i < a.length() - 2; i += 3, j++)
  {
    auto sub = a.substr(i, 3);
    for (auto k = 0; k < sub.length(); k++)
      if (sub[k] == 'T')
	sub[k] = 'U';
    if (getA(sub) != b[j])
      return false;
  }
  return true;
}

char tr(char b)
{
  if (b == 'A')
    return 'T';
  if (b == 'T')
    return 'A';
  if (b == 'C')
    return 'G';
  if (b == 'G')
    return 'C';
  return '$';
}

void trans()
{
  ifstream in;
  in.open("input.txt");
  string dna, peptide;
  in >> dna;
  in >> peptide;
  in.close();
  auto dna_rev = dna;
  for (auto i = 0; i < dna.length(); i++)
    dna_rev[dna_rev.length() - i - 1] = dna[i];
  auto rdna = dna;
  auto rdna_rev = dna_rev;
  for (auto i = 0; i < dna.length(); i++)
  {
    rdna[i] = tr(dna[i]);
    rdna_rev[i] = tr(dna_rev[i]);
  }
  ofstream out;
  out.open("output.txt");
  for (auto i = 0; i <= dna.length() - 3 * peptide.length(); i++)
  {
    auto sub = dna.substr(i, 3 * peptide.length());
    if (check(sub, peptide))
      out << sub << endl;
    sub = rdna.substr(i, 3 * peptide.length());
    if (check(sub, peptide))
      out << dna.substr(i, sub.length()) << endl;
    sub = dna_rev.substr(i, 3 * peptide.length());
    if (check(sub, peptide))
      out << dna.substr(dna.length() - i - sub.length(), sub.length()) << endl;
    sub = rdna_rev.substr(i, 3 * peptide.length());
    if (check(sub, peptide))
      out << dna.substr(dna.length() - i - sub.length(), sub.length()) << endl;
  }
  out.close();
}

int main()
{
  trans();
  return 0;
}