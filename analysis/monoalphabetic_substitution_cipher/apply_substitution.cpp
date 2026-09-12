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

    string key(26, '?');

    key['Q' - 'A'] = 'E';
    key['X' - 'A'] = 'T';

    string result =
        apply_substitution(ciphertext, key);

    cout << "CIPHERTEXT:\n";
    cout << ciphertext << "\n";

    cout << "PARTIAL PLAINTEXT:\n";
    cout << result << "\n";

    return 0;
}
