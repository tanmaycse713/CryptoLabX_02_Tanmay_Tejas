#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Account
{
    string username;
    string password;
    string accountNo;
    double balance;
};

vector<Account> accounts = {
    {"Tanmay", "tanmay123", "10001", 10000},
    {"Tejas", "tejas123", "10002", 15000}
};

vector<string> beneficiaries;

int login()
{
    string user, pass;

    cout << "Username: ";
    cin >> user;

    cout << "Password: ";
    cin >> pass;

    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].username == user &&
            accounts[i].password == pass)
        {
            // Sensitive Data Exposure in Logs
            ofstream log("bank.log", ios::app);
            log << "User: " << user
                << " Password: " << pass << endl;
            log.close();

            return i;
        }
    }

    return -1;
}

void checkBalance(int id)
{
    cout << "Balance: Rs. "
         << accounts[id].balance << endl;
}

void transfer(int id)
{
    string account;
    double amount;

    cout << "Enter beneficiary account: ";
    cin >> account;

    cout << "Enter amount: ";
    cin >> amount;

    // Insufficient Input Validation
    if (amount > accounts[id].balance)
    {
        cout << "Insufficient balance\n";
        return;
    }

    // Negative amount is not checked
    accounts[id].balance -= amount;

    cout << "Transfer successful\n";

    // Sensitive Data Exposure in Logs
    ofstream log("bank.log", ios::app);
    log << "Transfer to: " << account
        << " Amount: " << amount << endl;
    log.close();
}

void manageBeneficiary()
{
    string name;

    cout << "Enter beneficiary name: ";
    cin >> name;

    beneficiaries.push_back(name);

    cout << "Beneficiary added\n";
}

void viewAccount()
{
    string accountNo;

    cout << "Enter account number: ";
    cin >> accountNo;

    // Broken Access Control
    // No check whether this account belongs
    // to the logged-in user.

    for (auto &a : accounts)
    {
        if (a.accountNo == accountNo)
        {
            cout << "Owner: " << a.username << endl;
            cout << "Balance: " << a.balance << endl;
        }
    }
}

int main()
{
    int id = login();

    if (id == -1)
    {
        cout << "Login failed\n";
        return 0;
    }

    int choice;

    while (true)
    {
        cout << "\n--- Online Banking ---\n";
        cout << "1. Check Balance\n";
        cout << "2. Transfer Funds\n";
        cout << "3. Manage Beneficiary\n";
        cout << "4. View Account\n";
        cout << "5. Logout\n";

        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
            checkBalance(id);

        else if (choice == 2)
            transfer(id);

        else if (choice == 3)
            manageBeneficiary();

        else if (choice == 4)
            viewAccount();

        else if (choice == 5)
            break;

        else
            cout << "Invalid choice\n";
    }
    return 0;
}

