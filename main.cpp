#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <ctime>
#include <cctype>

using namespace std;

void writeLog(int choice)
{
    ofstream log("outputs/log.txt", ios::app);

    time_t now = time(0);
    char *dt = ctime(&now);

    string option;

    switch(choice)
    {
        case 1: option = "Encrypt"; break;
        case 2: option = "Decrypt"; break;
        case 3: option = "Attack"; break;
        case 4: option = "Analyze"; break;
        case 5: option = "Exit"; break;
        default: option = "Invalid Choice";
    }

    log << dt << "Option : " << option << endl;
    log << "-----------------------------" << endl;

    log.close();
}

void analyzeFile()
{
    string filename;

    cout << "\nEnter file name (Example: sample1.txt): ";
    cin >> filename;

    ifstream file("datasets/" + filename);

    if(!file)
    {
        cout << "File not found!\n";
        return;
    }

    string line;
    string text = "";

    int lines = 0;

    while(getline(file,line))
    {
        text += line;
        text += '\n';
        lines++;
    }

    file.close();

    int characters = text.length();

    int words = 0;
    bool insideWord = false;

    for(char ch : text)
    {
        if(isspace(ch))
        {
            insideWord = false;
        }
        else if(!insideWord)
        {
            words++;
            insideWord = true;
        }
    }

    set<char> uniqueCharacters;
    map<char,int> frequency;

    for(char ch : text)
    {
        uniqueCharacters.insert(ch);

        if(isalpha(ch))
        {
            ch = tolower(ch);
            frequency[ch]++;
        }
    }

    cout << "\n===== Analysis Result =====\n";
    cout << "Characters        : " << characters << endl;
    cout << "Words             : " << words << endl;
    cout << "Lines             : " << lines << endl;
    cout << "Unique Characters : " << uniqueCharacters.size() << endl;

    cout << "\nLetter Frequency\n";

    for(auto x : frequency)
    {
        cout << x.first << " : " << x.second << endl;
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n========== CryptoLabX ==========\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. Attack\n";
        cout << "4. Analyze\n";
        cout << "5. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        writeLog(choice);

        switch(choice)
        {
            case 1:
                cout << "\nEncrypt - Coming Soon\n";
                break;

            case 2:
                cout << "\nDecrypt - Coming Soon\n";
                break;

            case 3:
                cout << "\nAttack - Coming Soon\n";
                break;

            case 4:
                analyzeFile();
                break;

            case 5:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 5);

    return 0;
}