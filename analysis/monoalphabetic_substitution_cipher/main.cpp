#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void frequency_analysis(const string &text);
void word_frequency_analysis(const string &text);
void pattern_analysis(const string &text);

string apply_substitution(
    const string &text,
    const string &key);

void display_partial_plaintext(
    const string &ciphertext,
    const string &key);

bool verify_solution(
    const string &plaintext,
    const string &ciphertext,
    const string &key);

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

    string encryptionKey =
        "QWERTYUIOPASDFGHJKLZXCVBNM";

    string ciphertext =
        apply_substitution(
            plaintext,
            encryptionKey);

    ofstream output(
        "outputs/ciphertext.txt");

    if (!output)
    {
        cout << "Error creating ciphertext.txt\n";
        return 1;
    }

    output << ciphertext;
    output.close();

    cout << "MONOALPHABETIC SUBSTITUTION CIPHER\n";

    cout << "\n1. FREQUENCY ANALYSIS\n";
    frequency_analysis(ciphertext);

    cout << "\n2. WORD FREQUENCY ANALYSIS\n";
    word_frequency_analysis(ciphertext);

    cout << "\n3. PATTERN ANALYSIS\n";
    pattern_analysis(ciphertext);

    cout << "\n4. APPLY SUBSTITUTION\n";

    string recoveredKey(26, '?');

    recoveredKey['Q' - 'A'] = 'E';
    recoveredKey['X' - 'A'] = 'T';

    string partialPlaintext =
        apply_substitution(
            ciphertext,
            recoveredKey);

    cout << "Partial plaintext generated.\n";

    cout << "\n5. DISPLAY PARTIAL PLAINTEXT\n";

    display_partial_plaintext(
        ciphertext,
        recoveredKey);

    cout << "\n6. VERIFY SOLUTION\n";

    if (verify_solution(
            plaintext,
            ciphertext,
            encryptionKey))
    {
        cout << "Verification Successful\n";
    }
    else
    {
        cout << "Verification Failed\n";
    }

    return 0;
}
