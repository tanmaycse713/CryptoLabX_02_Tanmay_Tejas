#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

void frequency_analysis(const string &text)
{
    int freq[26] = {0};
    int total = 0;

    for (char c : text)
    {
        if (isalpha(c))
        {
            c = toupper(c);
            freq[c - 'A']++;
            total++;
        }
    }

    vector<pair<char, int>> frequency;

    for (int i = 0; i < 26; i++)
    {
        frequency.push_back({char('A' + i), freq[i]});
    }

    sort(frequency.begin(), frequency.end(),
         [](const pair<char, int> &a,
            const pair<char, int> &b)
         {
             return a.second > b.second;
         });

    cout << "LETTER FREQUENCY ANALYSIS\n";
    cout << "Letter\tCount\tPercentage\n";

    for (auto p : frequency)
    {
        double percentage = 0;

        if (total > 0)
            percentage = (double)p.second * 100 / total;

        cout << p.first << "\t"
             << p.second << "\t"
             << percentage << "%\n";
    }

    cout << "\nMOST FREQUENT LETTERS\n";

    for (int i = 0; i < 5; i++)
    {
        cout << frequency[i].first
             << " -> "
             << frequency[i].second << "\n";
    }
}

int main()
{
    ifstream input("outputs/ciphertext.txt");

    if (!input)
    {
        cout << "Error opening ciphertext.txt\n";
        return 1;
    }

    string ciphertext;
    string line;

    while (getline(input, line))
    {
        ciphertext += line;
        ciphertext += '\n';
    }

    input.close();

    frequency_analysis(ciphertext);

    return 0;
}
