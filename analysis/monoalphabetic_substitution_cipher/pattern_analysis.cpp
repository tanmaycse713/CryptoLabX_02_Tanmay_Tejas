#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

string getPattern(const string &word)
{
    map<char, int> mapping;
    string pattern = "";
    int nextNumber = 0;

    for (char c : word)
    {
        if (mapping.find(c) == mapping.end())
        {
            mapping[c] = nextNumber++;
        }

        pattern += char('0' + mapping[c]);
    }

    return pattern;
}

void pattern_analysis(const string &text)
{
    map<string, vector<string>> patterns;
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
                string pattern = getPattern(word);
                patterns[pattern].push_back(word);
                word = "";
            }
        }
    }

    if (!word.empty())
    {
        string pattern = getPattern(word);
        patterns[pattern].push_back(word);
    }

    cout << "PATTERN ANALYSIS\n\n";

    for (auto &p : patterns)
    {
        if (p.second.size() > 1)
        {
            cout << "Pattern "
                 << p.first
                 << " : ";

            for (const string &word : p.second)
            {
                cout << word << " ";
            }

            cout << "\n";
        }
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

    pattern_analysis(ciphertext);

    return 0;
}
