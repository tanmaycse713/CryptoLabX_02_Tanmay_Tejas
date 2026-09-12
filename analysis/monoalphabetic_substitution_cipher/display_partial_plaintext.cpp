#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string apply_substitution(const string &text, const string &key)
{
    string result = text;

    for (int i = 0; i < result.length(); i++)
    {
        char c = result[i];

        if (isalpha(c))
        {
            char upper = toupper(c);
            char replacement = key[upper - 'A'];

            if (replacement == '?')
                result[i] = '?';
            else if (islower(c))
                result[i] = tolower(replacement);
            else
                result[i] = replacement;
        }
    }

    return result;
}

void display_partial_plaintext(
    const string &ciphertext,
    const string &key)
{
    string plaintext =
        apply_substitution(ciphertext, key);

    cout << "PARTIAL PLAINTEXT:\n";
    cout << plaintext << "\n";
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

    string recoveredKey(26, '?');

    recoveredKey['Q' - 'A'] = 'E';
    recoveredKey['X' - 'A'] = 'T';
    recoveredKey['M' - 'A'] = 'H';

    display_partial_plaintext(
        ciphertext,
        recoveredKey);

    return 0;
}
