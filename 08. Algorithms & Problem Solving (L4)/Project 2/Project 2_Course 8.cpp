/*
                    Project 2: ATM System
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

enum enMainMenueOptions {
    eQuickWithdraw = 1, eNormalWithdraw = 2, eDepositMoney = 3,
    eCheckBalance = 4, eLogout = 5
};
enum enQuickWithdrawOptions{e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5,
    e600 = 6, e800 = 7, e1000 = 8, eExit = 9};

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

const string ClientsFileName = "Clients.txt";
sClient CurrentClient;

void ShowMainMenue();
void Login();
void ShowQuickWithdrawScreen();
void ShowDepositScreen();
void ShowNormalWithdrawScreen();
bool DepositBalanceToClientByAccountNumber(string, double, vector<sClient>);
void PrintClientBalance();

vector<string> SplitString(string S1, string Delim) {
    vector<string> vString;
    short pos = 0;
    string sWord;

    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length()); /* erase() until
        positon and move to next word. */
    }

    if (S1 != "") {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "/##/") {
    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "/##/") {
    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

vector <sClient> LoadCleintsDataFromFile(string FileName) {
    vector <sClient> vClients;
    fstream MyFile;

    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }

    return vClients;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client) {
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;

    if (MyFile.is_open()) {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

// =============== 1. Show Quick Withdraw Screen ===============

short GetQuickWithDrawAmount(short QuickWithDrawOption) {
    switch (QuickWithDrawOption) {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }
}

short ReadQuickWithdrawOption() {
    short Choice = 0;
    while (Choice < 1 || Choice > 9)
    {
        cout << "\nChoose what to do from [1] to [9] ? ";
        cin >> Choice;
    }
    return Choice;
}

void PerformQuickWithdrawOptions(short QuickWithDrawOption) {
    if (QuickWithDrawOption == 9) return;

    short WithDrawBalance = GetQuickWithDrawAmount(QuickWithDrawOption);

    if (WithDrawBalance > CurrentClient.AccountBalance) {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Anykey to continue...\n";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithDrawBalance;
}

void ShowQuickWithdrawScreen() {
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 20";
    cout << "\t\t[2] 50\n";
    cout << "\t[3] 100";
    cout << "\t\t[4] 200\n";
    cout << "\t[5] 400";
    cout << "\t\t[6] 600\n";
    cout << "\t[7] 800";
    cout << "\t\t[8] 1000\n";
    cout << "\t[9] Exit.\n";
    cout << "===========================================\n";

    PrintClientBalance();
    PerformQuickWithdrawOptions(ReadQuickWithdrawOption());
}

// =============== 2. Show Normal Withdraw Screen ===============

int ReadWithDrawAmont() {
    int Amount;
    cout << "\nEnter an amount multiple of 5's ? ";
    cin >> Amount;
    while (Amount % 5 != 0) {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> Amount;
    }
    return Amount;
}

void PerfromNormalWithdrawOption() {
    short WithDrawBalance = ReadWithDrawAmont();

    if (WithDrawBalance > CurrentClient.AccountBalance) {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
        return;
    }

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithDrawBalance;
}

void ShowNormalWithdrawScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw\n";
    cout << "===========================================\n";
    PerfromNormalWithdrawOption();
}

// =============== 3. Show Deposit Screen ===============

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> vClients){
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y') {
        for (sClient& C : vClients) {
            if (C.AccountNumber == CurrentClient.AccountNumber) {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }
        }
        return false;
    }

}

double ReadDepositAmount() {
    double Amount;
    cout << "\nEnter a positive Deposit Amount? ";
    cin >> Amount;
    while (Amount <= 0) {
        cout << "\nEnter a positive Deposit Amount? ";
        cin >> Amount;
    }
    return Amount;
}

void PerfromDepositOption() {
    double DepositAmount = ReadDepositAmount();
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);

    CurrentClient.AccountBalance += DepositAmount;
}

void ShowDepositScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tDeposit Money\n";
    cout << "===========================================\n";
    PerfromDepositOption();
}

// =============== 4. Show Check Balance Screen ===============

void PrintClientBalance() {
    cout << "Your Balance is " << CurrentClient.AccountBalance << '\n';
}

void ShowCheckBalanceScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance\n";
    cout << "===========================================\n";
    PrintClientBalance();
}

// =============== Menue And Perform Choices ===============

short ReadMainMenueOption() {
    short Choice = 0;
    cout << "Choose what do you want to do? [1 to 5]? ";
    cin >> Choice;
    return Choice;
}

void GoBackToMainMenue() {
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void PerformMainMenueOption(enMainMenueOptions MainMenueOption) {
    switch (MainMenueOption) {
    case enMainMenueOptions::eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eNormalWithdraw:
        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDepositMoney:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eCheckBalance:
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eLogout:
        system("cls");
        Login();
        break;
    }
}

void ShowMainMenue() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit Money.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";

    PerformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool LoadClientInfo(string AccountNumber, string PINCode) {
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PINCode, CurrentClient))
        return true;
    else
        return false;
}

void Login() {
    bool LoginFaild = false;
    string AccountNumber, PINCode;

    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild) {
            cout << "Invlaid Account Number/PIN Code!\n";
        }

        cout << "Enter Account Number? ";
        cin >> AccountNumber;
        cout << "Enter PIN Code? ";
        cin >> PINCode;

        LoginFaild = !LoadClientInfo(AccountNumber, PINCode);
    } while (LoginFaild);

    ShowMainMenue();
}

int main() {
    Login();

    system("pause>0");
    return 0;
}
