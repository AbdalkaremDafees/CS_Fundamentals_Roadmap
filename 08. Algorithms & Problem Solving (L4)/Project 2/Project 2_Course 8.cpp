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
void ShowNormalWithDrawScreen();
void ShowDepositScreen();

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

string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
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

void ShowQuickWithdrawScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 50 USD.\n";
    cout << "\t[2] 100 USD.\n";
    cout << "\t[3] 200 USD.\n";
    cout << "\t[4] 500 USD.\n";
    cout << "\t[5] 1000 USD.\n";
    cout << "\t[6] Back to Main Menue.\n";
    cout << "===========================================\n";
}

void ShowNormalWithdrawScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw\n";
    cout << "===========================================\n";
    cout << "Enter amount to withdraw: ";
}

void ShowDepositScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tDeposit Money\n";
    cout << "===========================================\n";
    cout << "Enter amount to deposit: ";
}

void ShowCheckBalanceScreen() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance\n";
    cout << "===========================================\n";
    cout << "Your balance is: 5000 USD\n";
}

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
        if (LoginFaild)
        {
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