#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string encrypt_text(
    const string &plaintext,
    const string &key)
{
    string result = plaintext;

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

bool verify_solution(
    const string &plaintext,
    const string &ciphertext,
    const string &key)
{
    string generated =
        encrypt_text(plaintext, key);

    return generated == ciphertext;
}

int main()
{
    ifstream plaintextFile(
        "../../../datasets/plaintext.txt");

    ifstream ciphertextFile(
        "../../../outputs/ciphertext.txt");

    if (!plaintextFile)
    {
        cout << "Error opening plaintext.txt\n";
        return 1;
    }

    if (!ciphertextFile)
    {
        cout << "Error opening ciphertext.txt\n";
        return 1;
    }

    string plaintext;
    string ciphertext;
    string line;

    while (getline(plaintextFile, line))
    {
        plaintext += line;
        plaintext += '\n';
    }

    while (getline(ciphertextFile, line))
    {
        ciphertext += line;
        ciphertext += '\n';
    }

    plaintextFile.close();
    ciphertextFile.close();

    string encryptionKey =
        "QWERTYUIOPASDFGHJKLZXCVBNM";

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
