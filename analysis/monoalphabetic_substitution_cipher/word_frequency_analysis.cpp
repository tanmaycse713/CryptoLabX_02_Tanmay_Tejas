#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

void word_frequency_analysis(const string &text)
{
    map<string, int> words;
    string word = "";

    for (char c : text)
    {
        if (isalpha(c))
        {
            word += toupper(c);
        }
        else
        {
            if (!word.empty())
            {
                words[word]++;
                word = "";
            }
        }
    }

    if (!word.empty())
        words[word]++;

    vector<pair<string, int>> frequency(
        words.begin(),
        words.end());

    sort(frequency.begin(), frequency.end(),
         [](const pair<string, int> &a,
            const pair<string, int> &b)
         {
             return a.second > b.second;
         });

    cout << "WORD FREQUENCY ANALYSIS\n\n";

    cout << "ALL WORDS\n";

    for (auto p : frequency)
    {
        cout << p.first
             << " -> "
             << p.second << "\n";
    }

    cout << "\nONE LETTER WORDS\n";

    for (auto p : frequency)
    {
        if (p.first.length() == 1)
        {
            cout << p.first
                 << " -> "
                 << p.second << "\n";
        }
    }

    cout << "\nTWO LETTER WORDS\n";

    for (auto p : frequency)
    {
        if (p.first.length() == 2)
        {
            cout << p.first
                 << " -> "
                 << p.second << "\n";
        }
    }

    cout << "\nTHREE LETTER WORDS\n";

    for (auto p : frequency)
    {
        if (p.first.length() == 3)
        {
            cout << p.first
                 << " -> "
                 << p.second << "\n";
        }
    }
}

int main()
{
    ifstream input("../../../outputs/ciphertext.txt");

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

    word_frequency_analysis(ciphertext);

    return 0;
}
