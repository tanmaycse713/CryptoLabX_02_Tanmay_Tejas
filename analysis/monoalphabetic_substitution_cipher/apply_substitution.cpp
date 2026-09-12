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

            if (islower(c))
                result[i] = tolower(replacement);
            else
                result[i] = replacement;
        }
    }

    return result;
}

int main()
{
    ifstream input("datasets/plaintext.txt");

    if (!input)
    {
        cout << "Error opening plaintext.txt\n";
        return 1;
    }

    string plaintext;
    string line;

    while (getline(input, line))
    {
        plaintext += line;
        plaintext += '\n';
    }

    input.close();

    string key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    string ciphertext =
        apply_substitution(plaintext, key);

    ofstream output("outputs/ciphertext.txt");

    if (!output)
    {
        cout << "Error creating ciphertext.txt\n";
        return 1;
    }

    output << ciphertext;
    output.close();

    cout << "Ciphertext generated successfully.\n";

    return 0;
}
