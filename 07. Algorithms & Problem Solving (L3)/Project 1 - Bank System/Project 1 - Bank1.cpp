/*
        Project 1: Write A Console-based Bank Management System in C++,
                 (show - add - delete - update - find - exit)
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string FileName = "myFile.txt";

enum enMenu { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6 };

// Struct for client data.
struct stClientData {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.00;
    bool Flag = false;
};

// ======================== 1.Show ========================

// Split line from string to vector of string.
vector<string> SplitLine(string Line, string delmi = "/##/") {
    short pos = 0;
    string sWord;
    vector<string> vString;
    while ((pos = Line.find(delmi)) != std::string::npos) {
        sWord = Line.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);
        Line.erase(0, pos + delmi.length());
    }
    if (Line != "") vString.push_back(Line);
    return vString;
}

// Convert line of string to a record of struct.
stClientData ConvertLineToRecord(string Line) {
    vector<string> vClient;
    stClientData stClient;

    vClient = SplitLine(Line);

    stClient.AccountNumber = vClient[0];
    stClient.PinCode = vClient[1];
    stClient.Name = vClient[2];
    stClient.Phone = vClient[3];
    stClient.AccountBalance = stod(vClient[4]);

    return stClient;
}

// Get all lines from the external file.
vector<stClientData> GetDataFromFile() {
    vector<stClientData> vClient;
    stClientData stClient;
    fstream myFile;

    myFile.open(FileName, ios::in);

    if (myFile.is_open()) {
        string Line;
        while (getline(myFile, Line)) {
            stClient = ConvertLineToRecord(Line);
            vClient.push_back(stClient);
        }
        myFile.close();
    }

    return vClient;
}

// Print each client data.
void PrintClientData(stClientData Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

// Show clients list that contain all clients data.
void ShowClientList() {
    vector<stClientData> vClient = GetDataFromFile();
    cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClientData Client : vClient)
    {
        PrintClientData(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// ======================== 2.Add ========================

// Convert a struct record to string line.
string ConvertRecordToLine(stClientData stClient, string delmi = "/##/") {
    string S;
    S += stClient.AccountNumber + delmi;
    S += stClient.PinCode + delmi;
    S += stClient.Name + delmi;
    S += stClient.Phone + delmi;
    S += to_string(stClient.AccountBalance);
    
    return S;
}

// Push data to the file by write mode with append type.
void PushDataToFile(vector<stClientData> vClient) {
    fstream myFile;

    myFile.open(FileName, ios::out | ios::app);

    if (myFile.is_open()) {
        string Line;
        for (stClientData& C : vClient) {
            if (C.Flag == false) {
                Line = ConvertRecordToLine(C);
                myFile << Line << endl;
            }
        }
        
        myFile.close();
    }
}

// Get client data from the user and save them is a struct.
stClientData GetClientData(string AccountNumber) {
    stClientData stClient;

    stClient.AccountNumber = AccountNumber;
    cout << "\nEnter PIN Code: ";
    getline(cin >> ws, stClient.PinCode);
    cout << "\nEnter Name: ";
    getline(cin, stClient.Name);
    cout << "\nEnter Phone: ";
    getline(cin, stClient.Phone);
    cout << "\nEnter Account Balance: ";
    cin >> stClient.AccountBalance;

    return stClient;
}

// Search for client by the account number.
bool FindClinetByAccNum(string AccountNumber, stClientData& Client) {
    vector<stClientData> vClient = GetDataFromFile();

    for (stClientData& C : vClient) {
        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }

    return false;
}

// Get client account number.
string GetAccountNumber() {
    string S;
    cout << "\nEnter Account Number? ";
    cin >> S;
    return S;
}

// Add new client for the system and send the data to the external file.
void AddNewClient() {
    string AccountNumber = GetAccountNumber();
    stClientData stClient;
    vector<stClientData> vClients;

    while (FindClinetByAccNum(AccountNumber, stClient)) {
        cout << "\nClient With [" << AccountNumber << "] already exist, ";
        cout << "Enter another account number: ";
        AccountNumber = GetAccountNumber();
    }

    stClient = GetClientData(AccountNumber);
    vClients.push_back(stClient);
    PushDataToFile(vClients);
}

// Add client screen and asking for add more.
void AddClient() {
    cout << "----------------------------------------";
    cout << "\n\tAdd New Client";
    cout << "\n----------------------------------------";
    cout << "\nAdding New Client:";

    char choice = 'n';
    do {
        AddNewClient();
        cout << "\nClient Added Successfully,";
        cout << "Do You Want Add More Client? (Y/N)? ";
        cin >> choice;
    } while (toupper(choice) == 'Y');
}

// ======================== 3.Delete ========================

// Print all client details.
void PrintClientDetails(stClientData stClient) {
    cout << "\nThe Following Are The Client Details: ";
    cout << "\n-----------------------------------------";
    cout << "\nAccount Number: " << stClient.AccountNumber;
    cout << "\nPin Code: " << stClient.PinCode;
    cout << "\nName: " << stClient.Name;
    cout << "\nPhone: " << stClient.Phone;
    cout << "\nAccount Balance: " << stClient.AccountBalance;
    cout << "\n-----------------------------------------";
}

// Mark a client by a flag to delete them later.
bool MarkToDelete(vector<stClientData> &vClient, string AccountNumber) {
    for (stClientData& C : vClient) {
        if (C.AccountNumber == AccountNumber) {
            C.Flag = true;
            return true;
        }
    }
    return false;
}

//  Push data to the file by write mode without append mode.
void PushDataToFileWithoutAppend(const vector<stClientData> &vClient) {
    fstream myFile;

    myFile.open(FileName, ios::out);

    if (myFile.is_open()) {
        string Line;
        for (const stClientData C : vClient) {
            if (C.Flag == false) {
                Line = ConvertRecordToLine(C);
                myFile << Line << endl;
            }
        }

        myFile.close();
    }
}

// Progress of deletion client.
void DeletedSuccessfully(string AccountNumber, vector<stClientData>& vClient) {
    MarkToDelete(vClient, AccountNumber);
    PushDataToFileWithoutAppend(vClient); 
}

// Make sure to delete the client.
void SureToDelete(string AccountNumber, vector<stClientData> &vClient) {
    char Answer = 'n';
    cout << "\nAre You Sure You Want To Delete [" << AccountNumber << "] Client ? (Y / N) ? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        DeletedSuccessfully(AccountNumber, vClient);
        cout << "\nClient Deleted Successfully.";
    }
    else {
        cout << "\nWill Not Delete.";
    }
}

// First function for the delete client from the external file.
void DeleteClientFromFile() {
    cout << "----------------------------------------";
    cout << "\n\tDelete Client Screen";
    cout << "\n----------------------------------------";

    vector<stClientData> vClients = GetDataFromFile();

    string AccountNumber = GetAccountNumber();
    stClientData stClient;

    if (FindClinetByAccNum(AccountNumber, stClient)) {
        PrintClientDetails(stClient);
        SureToDelete(AccountNumber, vClients);
    }
    else {
        cout << "\nClient With Account Number [" << AccountNumber << "] Is Not Found!";
    }
}

// ======================== 4.Update ========================

// Update the client data and push them to the file.
void UpdatedSuccessfully(string AccountNumber, vector<stClientData> &vClients) {
    for (stClientData& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C = GetClientData(AccountNumber);
            break;
        }
    }
    PushDataToFileWithoutAppend(vClients);
}

// Make sure to update the client data.
void SureToUpdate(string AccountNumber, vector<stClientData> &vClients) {
    char Answer = 'n';
    cout << "\nAre You Sure You Want To Update [" << AccountNumber << "] Client ? (Y / N) ? ";
    cin >> Answer;    
    if (toupper(Answer) == 'Y') {
        UpdatedSuccessfully(AccountNumber, vClients);
        cout << "\nClient Deleted Successfully.";
    }
    else {
        cout << "\nWill Not Delete.";
    }
}

// Updata the clinet information.
void UpdateClientInfo() {
    cout << "----------------------------------------";
    cout << "\n\tUpdate Client Screen";
    cout << "\n----------------------------------------";

    vector<stClientData> vClients = GetDataFromFile();

    string AccountNumber = GetAccountNumber();
    stClientData stClient;

    if (FindClinetByAccNum(AccountNumber, stClient)) {
        PrintClientDetails(stClient);
        SureToUpdate(AccountNumber, vClients);
    }
    else {
        cout << "\nClient With Account Number [" << AccountNumber << "] Is Not Found!";
    }
}

// ======================== 5.Find ========================

// Search if the client is in the system.
void FindClient() {
    cout << "----------------------------------------";
    cout << "\n\tFind Client Screen";
    cout << "\n----------------------------------------";

    string AccountNumber = GetAccountNumber();
    stClientData stClient;

    if (FindClinetByAccNum(AccountNumber, stClient)) {
        PrintClientDetails(stClient);
    }
    else {
        cout << "\nClient With Account Number [" << AccountNumber << "] Is Not Found!";
    }
}

// ======================== 6.Exit ========================

// Exit from the program
void ExitProgram() {
    cout << "-------------------------------------";
    cout << "\tProgram Ends :-)";
    cout << "\n-------------------------------------";
}

// =================== Start Program ======================

void BackToMenu() {
    cout << "\n\n\nPress any key to go back to the menu...";
    system("pause");
}

void PrintMenu() {
    cout << "===============================\n";
    cout << setw(3) << "Main Menu Screen";
    cout << "\n===============================\n";
    cout << setw(2) << "\n[1] Show Client List.";
    cout << setw(2) << "\n[2] Add New Client.";
    cout << setw(2) << "\n[3] Delete Client.";
    cout << setw(2) << "\n[4] Update Client Info.";
    cout << setw(2) << "\n[5] Find Client.";
    cout << setw(2) << "\n[6] Exit.";
    cout << "\n===============================\n";
}

void StartProgram() {
    bool exit = false;

    do {
        system("cls");  // Clear screen at start
        PrintMenu();

        short choice;
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> choice;

        switch (choice) {
        case enMenu::Show:
            ShowClientList();
            BackToMenu();
            break;
        case enMenu::Add:
            AddClient();
            BackToMenu();
            break;
        case enMenu::Delete:
            DeleteClientFromFile();
            BackToMenu();
            break;
        case enMenu::Update:
            UpdateClientInfo();
            BackToMenu();
            break;
        case enMenu::Find:
            FindClient();
            BackToMenu();
            break;
        case enMenu::Exit:
            ExitProgram();
            exit = true;
            break;
        default:
            system("cls");
            cout << "Invalid choice! Please enter 1-6.\n";
            BackToMenu();
        }
    } while (!exit);
}

int main() {
    StartProgram();
    return 0;
}