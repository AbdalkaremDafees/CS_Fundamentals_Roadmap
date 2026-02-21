/*
        Project 1: Extension for Project 1 In Course 7 'Bank Management System in C++',
                   Manage Users Program To Control The Clients Program.
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

void StartProgram();
void TransactionProgram();
void LoginScreen();
void BackToMainMenu();

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

enum enMenu { enShow = 1, enAdd = 2, enDelete = 3, enUpdate = 4, enFind = 5, enTransaction = 6, enManageUsers = 7, enLogout = 8 };
enum enTransMenu { enDeposit = 1, enWithdraw = 2, enTotalBalance = 3, enMainMenu = 4 };
enum enManageUsersMenu { enShowUser = 1, enAddUser = 2, enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enMainMenuUser = 6 };
enum enMainMenuPermissions { enAll = -1, enListClients = 1, enAddNewClient = 2, enDeleteClient = 4, enUpdateClients = 8, enFindClient = 16, enTranactions = 32, enPerManageUsers = 64 };

// Struct for client data.
struct stClientData {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.00;
    bool Flag = false;
};

// Struct for User data.
struct stUserData {
    string UserName;
    string Password;
    int Permision;
    bool MarkForDelete = false;
};

// Global User Data Struct.
stUserData CurrentUser;

// Check Access Permission for user.
bool CheckAccessPermission(enMainMenuPermissions Permission) {
    if (CurrentUser.Permision == enMainMenuPermissions::enAll) {
        return true;
    }

    if ((Permission & CurrentUser.Permision) == Permission) {
        return true;
    }
    else
        return false;
}

void ShowAccessDeniedMessage() {
    cout << "\n________________________________\n";
    cout << "Access Denied, \nYou Don't Have Permission To Do This.";
    cout << "\n________________________________\n";
}

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
stUserData ConvertUserLineToRecord(string Line) {
    vector<string> vUser;
    stUserData stUser;

    vUser = SplitLine(Line);

    stUser.UserName = vUser[0];
    stUser.Password = vUser[1];
    stUser.Permision = stoi(vUser[2]);

    return stUser;
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
vector<stUserData> GetDataFromUserFile() {
    vector<stUserData> vUser;
    stUserData stUser;
    fstream myFile;

    myFile.open(UsersFileName, ios::in);

    if (myFile.is_open()) {
        string Line;
        while (getline(myFile, Line)) {
            stUser = ConvertUserLineToRecord(Line);
            vUser.push_back(stUser);
        }
        myFile.close();
    }

    return vUser;
}

// Get all lines from the external file.
vector<stClientData> GetDataFromFile() {
    vector<stClientData> vClient;
    stClientData stClient;
    fstream myFile;

    myFile.open(ClientsFileName, ios::in);

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

    if (!CheckAccessPermission(enMainMenuPermissions::enListClients)) {
        ShowAccessDeniedMessage();
        return;
    }

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

    myFile.open(ClientsFileName, ios::out | ios::app);

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
    if (!CheckAccessPermission(enMainMenuPermissions::enAddNewClient)) {
        ShowAccessDeniedMessage();
        return;
    }

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
bool MarkToDelete(vector<stClientData>& vClient, string AccountNumber) {
    for (stClientData& C : vClient) {
        if (C.AccountNumber == AccountNumber) {
            C.Flag = true;
            return true;
        }
    }
    return false;
}

//  Push data to the file by write mode without append mode.
void PushDataToFileWithoutAppend(const vector<stClientData>& vClient) {
    fstream myFile;

    myFile.open(ClientsFileName, ios::out);

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
void SureToDelete(string AccountNumber, vector<stClientData>& vClient) {
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
    if (!CheckAccessPermission(enMainMenuPermissions::enDeleteClient)) {
        ShowAccessDeniedMessage();
        return;
    }

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
void UpdatedSuccessfully(string AccountNumber, vector<stClientData>& vClients) {
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
void SureToUpdate(string AccountNumber, vector<stClientData>& vClients) {
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
    if (!CheckAccessPermission(enMainMenuPermissions::enUpdateClients)) {
        ShowAccessDeniedMessage();
        return;
    }

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

// ========================= 5.Find ============================

// Search if the client is in the system.
void FindClient() {
    if (!CheckAccessPermission(enMainMenuPermissions::enFindClient)) {
        ShowAccessDeniedMessage();
        return;
    }

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

// ================= 6. Transaction Program ====================

// ======================== 6.1 Deposit ========================

// Perform deposit action.
void PerformDeposit(string AccountNumber, vector<stClientData>& vClients, double DepositAmount) {
    for (stClientData& C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            C.AccountBalance += DepositAmount;
            break;
        }
    }
    PushDataToFileWithoutAppend(vClients);
}

// Ask user to make sure to perform deposit.
void SureToDeposit(string AccountNumber, vector<stClientData>& vClients, double DepositAmount) {
    char Answer = 'n';
    cout << "\nAre You Sure You Want To Perform This Transaction? (y/n)? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        PerformDeposit(AccountNumber, vClients, DepositAmount);
        cout << "\nDeposit Added Successfully.";
    }
    else {
        cout << "\nWill Not Add Deposit.";
    }
}

// Read deposit amount.
double ReadDepositAmount() {
    double DepositAmount;
    cout << "\nPlease Enter Deposit Amount? ";
    cin >> DepositAmount;
    return DepositAmount;
}

// Show deposit screen and start deposit program.
void DepositScreen() {
    cout << "----------------------------------------";
    cout << "\n\tDeposit Screen";
    cout << "\n----------------------------------------";

    vector<stClientData> vClients = GetDataFromFile();

    string AccountNumber = GetAccountNumber();
    stClientData stClient;

    bool FindClient = FindClinetByAccNum(AccountNumber, stClient);
    while (!FindClient) {
        cout << "\nClient With Account Number [" << AccountNumber << "] Is Not Exist!";
        AccountNumber = GetAccountNumber();
        FindClient = FindClinetByAccNum(AccountNumber, stClient);
    }

    PrintClientDetails(stClient);
    double DepositAmount = ReadDepositAmount();
    SureToDeposit(AccountNumber, vClients, DepositAmount);
}

// ======================== 6.2 Withdraw =======================

// Perform withdraw action.
void PerformWithdraw(string AccountNumber, vector<stClientData>& vClients, double withdrawAmount) {
    for (stClientData& C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            C.AccountBalance -= withdrawAmount;
            break;
        }
    }
    PushDataToFileWithoutAppend(vClients);
}

// Ask user to make sure to perform withdraw.
void SureToWithdraw(string AccountNumber, vector<stClientData>& vClients, double withdrawAmount) {
    char Answer = 'n';
    cout << "\nAre You Sure You Want To Perform This Transaction? (y/n)? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        PerformWithdraw(AccountNumber, vClients, withdrawAmount);
        cout << "\nWithdraw Performed Successfully.";
    }
    else {
        cout << "\nWill Not Add Withdraw.";
    }
}

//  Check Withdraw Amount.
bool CheckWithdrawAmount(stClientData stClient, double WithdrawAmount) {
    return (stClient.AccountBalance >= WithdrawAmount);
}

// Read withdraw amount.
double ReadWithdrawAmount() {
    double WithdrawAmount;
    cout << "\nPlease Enter Withdraw Amount? ";
    cin >> WithdrawAmount;

    return WithdrawAmount;
}

// withdarw program.
void WithdrawFromClient(stClientData stClient, vector<stClientData>& vClients, string AccountNumber) {
    double WithdrawAmount = ReadWithdrawAmount();

    bool RightAmount = CheckWithdrawAmount(stClient, WithdrawAmount);
    while (!RightAmount) {
        cout << "\nAmount Exceeds The Balance, You Can Withdraw Up to: " << stClient.AccountBalance;
        cout << "\nPlease Enter Another Amount? ";
        cin >> WithdrawAmount;
        RightAmount = CheckWithdrawAmount(stClient, WithdrawAmount);
    }
    SureToWithdraw(AccountNumber, vClients, WithdrawAmount);
}

// Show withdraw screen and start withdraw program.
void WithdrawScreen() {
    cout << "----------------------------------------";
    cout << "\n\tWithdraw Screen";
    cout << "\n----------------------------------------";

    vector<stClientData> vClients = GetDataFromFile();

    string AccountNumber = GetAccountNumber();
    stClientData stClient;

    bool FindClient = FindClinetByAccNum(AccountNumber, stClient);
    while (!FindClient) {
        cout << "\nClient With Account Number [" << AccountNumber << "] Is Not Exist!";
        AccountNumber = GetAccountNumber();
        FindClient = FindClinetByAccNum(AccountNumber, stClient);
    }

    PrintClientDetails(stClient);
    WithdrawFromClient(stClient, vClients, AccountNumber);

}

// ===================== 6.3 Total Balance =====================

// Sum of all clients balance.
double SumOfAllClientsBalance(vector<stClientData>& vClients) {
    double sum = 0;
    for (stClientData& C : vClients) {
        sum += C.AccountBalance;
    }
    return sum;
}

// Show total balance list that contain some clients data.
void ShowTotalBalanceList(vector<stClientData> vClient) {
    cout << "\n\t\t\t\t\tBalance List (" << vClient.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stClientData Client : vClient) {
        cout << "| " << left << setw(15) << Client.AccountNumber;
        cout << "| " << left << setw(40) << Client.Name;
        cout << "| " << left << setw(12) << fixed << setprecision(2) << Client.AccountBalance;
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// Perform total balance.
void PerformTotalBalance() {
    vector<stClientData> vClients = GetDataFromFile();
    ShowTotalBalanceList(vClients);
    double TotalBalane = SumOfAllClientsBalance(vClients);
    cout << setw(15) << "Total Balance = " << fixed << setprecision(2) << TotalBalane << endl;
}

// ====================== 6.4 Transaction Control ===================

// print transaction screen that contain menu.
void PrintTransactionScreen() {
    cout << "===============================\n";
    cout << setw(3) << "Transaction Menu Screen";
    cout << "\n===============================\n";
    cout << setw(2) << "[1] Deposit.";
    cout << setw(2) << "\n[2] Withdraw.";
    cout << setw(2) << "\n[3] Total Balance.";
    cout << setw(2) << "\n[4] Main Menu.";
    cout << "\n===============================\n";
}

// Back to the transaction menu.
void BackToTransMenu() {
    cout << "\n\n\nPress any key to go back to the transaction menu...";
    system("pause");
    system("cls");
    TransactionProgram();
}

// Transaction Program.
void TransactionProgram() {
    if (!CheckAccessPermission(enMainMenuPermissions::enTranactions)) {
        ShowAccessDeniedMessage();
        return;
    }

    bool exitTransaction = false;

    do {
        system("cls");
        PrintTransactionScreen();

        short choice;
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> choice;

        switch (choice) {
        case enTransMenu::enDeposit:
            system("cls");
            DepositScreen();
            BackToTransMenu();
            break;
        case enTransMenu::enWithdraw:
            system("cls");
            WithdrawScreen();
            BackToTransMenu();
            break;
        case enTransMenu::enTotalBalance:
            system("cls");
            PerformTotalBalance();
            BackToTransMenu();
            break;
        case enTransMenu::enMainMenu:
            exitTransaction = true;
            system("cls");
            StartProgram();
            break;
        default:
            system("cls");
            cout << "Invalid choice! Please enter 1-4.\n";
            BackToTransMenu();
        }
    } while (!exitTransaction);
}

// =================== 7.Manage Users Program ======================

// ================ 7.1 Show Manage Users List =====================

// Print Each User Data
void PrintUserData(stUserData User) {
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Password;
    cout << "| " << setw(40) << left << User.Permision;
}

// Show Users list that contain all Users data.
void ShowUsersList() {
    vector<stUserData> vUser = GetDataFromUserFile();
    cout << "\n\t\t\t\t\tUser List (" << vUser.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (stUserData U : vUser)
    {
        PrintUserData(U);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// =================== 7.2 Add Manage Users =========================

// Convert a struct record to string line.
string ConvertRecordToUserLine(stUserData stUser, string delmi = "/##/") {
    string S;
    S += stUser.UserName + delmi;
    S += stUser.Password + delmi;
    S += to_string(stUser.Permision);

    return S;
}

// Push data to the file by write mode with append type.
void PushDataToUserFile(vector<stUserData> vUser) {
    fstream myFile;

    myFile.open(UsersFileName, ios::out | ios::app);

    if (myFile.is_open()) {
        string Line;
        for (stUserData& U : vUser) {
            if (U.MarkForDelete == false) {
                Line = ConvertRecordToUserLine(U);
                myFile << Line << endl;
            }
        }

        myFile.close();
    }
}

// Read user permissions by binary value.
int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full access? y/n? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y') {
        return -1;
    }

    cout << "\nDo you want to give access to : \n ";
    cout << "\nShow Client List? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enListClients;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enAddNewClient;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enDeleteClient;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enUpdateClients;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enFindClient;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enTranactions;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::enPerManageUsers;
    }

    return Permissions;
}

// Get user data from the user and save them is a struct.
stUserData GetUserData(string UserName) {
    stUserData CurrentUser;

    CurrentUser.UserName = UserName;

    cout << "\nEnter Password: ";
    getline(cin >> ws, CurrentUser.Password);

    CurrentUser.Permision = ReadPermissionsToSet();
    
    return CurrentUser;
}

// Search for user by the user name.
bool FindUserByUserName(string UserName, stUserData& stUser) {
    vector<stUserData> vUser = GetDataFromUserFile();

    for (stUserData& U : vUser) {
        if (U.UserName == UserName) {
            stUser = U;
            return true;
        }
    }

    return false;
}

// Get user account number.
string GetUserName() {
    string S;
    cout << "\nEnter User Name? ";
    cin >> S;
    return S;
}

// Add new user for the system and send the data to the external file.
void AddNewUser() {
    string UserName = GetUserName();
    stUserData CurrentUser;
    vector<stUserData> vUser;

    while (FindUserByUserName(UserName, CurrentUser)) {
        cout << "\nUser With [" << UserName << "] already exist, ";
        cout << "Enter another user name: ";
        UserName = GetUserName();
    }

    CurrentUser = GetUserData(UserName);
    vUser.push_back(CurrentUser);
    PushDataToUserFile(vUser);
}

// Add User screen and asking for add more.
void AddUsers() {
    cout << "----------------------------------------";
    cout << "\n\tAdd New User";
    cout << "\n----------------------------------------";
    cout << "\nAdding New User:";

    char choice = 'n';
    do {
        AddNewUser();
        cout << "\nUser Added Successfully,";
        cout << "Do You Want Add More User? (Y/N)? ";
        cin >> choice;
    } while (toupper(choice) == 'Y');
}

// =================== 7.3 Delete Users =========================

// Print all User details.
void PrintUserDetails(stUserData stUser) {
    cout << "\nThe Following Are The User Details: ";
    cout << "\n-----------------------------------------";
    cout << "\nUser Name: " << stUser.UserName;
    cout << "\nPassword: " << stUser.Password;
    cout << "\nPermission: " << stUser.Permision;
    cout << "\n-----------------------------------------";
}

// Mark an user by a flag to delete them later.
bool MarkUserToDelete(string UserName, vector<stUserData>& vUser) {
    for (stUserData& U : vUser) {
        if (U.UserName == UserName) {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

//  Push user data to the file by write mode without append mode.
void PushUserDataToFileWithoutAppend(const vector<stUserData> vUser) {
    fstream myFile;

    myFile.open(UsersFileName, ios::out);

    if (myFile.is_open()) {
        string Line;
        for (const stUserData U : vUser) {
            if (U.MarkForDelete == false) {
                Line = ConvertRecordToUserLine(U);
                myFile << Line << endl;
            }
        }

        myFile.close();
    }
}

// Progress of deletion user.
void DeletedUserSuccessfully(string UserName, vector<stUserData>& vUser) {
    MarkUserToDelete(UserName, vUser);
    PushUserDataToFileWithoutAppend(vUser);
}

// Make sure to delete the user.
void SureToDeleteUser(string UserName, vector<stUserData>& vUser) {
    char Answer = 'n';
    cout << "\nAre You Sure You Want To Delete [" << UserName << "] User ? (Y / N) ? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        DeletedUserSuccessfully(UserName, vUser);
        cout << "\nUser Deleted Successfully.";
    }
    else {
        cout << "\nWill Not Delete.";
    }
}

// First function for the delete user from the external file.
void DeleteUserFromFile() {
    cout << "----------------------------------------";
    cout << "\n\tDelete User Screen";
    cout << "\n----------------------------------------";

    vector<stUserData> vUser = GetDataFromUserFile();

    string UserName = GetUserName();

    if (UserName == "Admin") {
        cout << "\n!!!! You Can't Delete Admin !!!!";
        return;
    }
    
    if (FindUserByUserName(UserName, CurrentUser)) {
        PrintUserDetails(CurrentUser);
        SureToDeleteUser(UserName, vUser);
    }
    else {
        cout << "\nUser With User Name [" << UserName << "] Is Not Found!";
    }
}

// =================== 7.4 Update Users =======================

// Update the user data and push them to the file.
void UpdatedUserInfoSuccessfully(string UserName, vector<stUserData>& vUser) {
    for (stUserData& U : vUser)
    {
        if (U.UserName == UserName)
        {
            U = GetUserData(UserName);
            break;
        }
    }
    PushUserDataToFileWithoutAppend(vUser);
}

// Make sure to update the user data.
void SureToUpdateUserInfo(string UserName, vector<stUserData>& vUser) {
    char Answer = 'n';
    cout << "\nAre You Sure You Want To Update [" << UserName << "] User ? (Y / N) ? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y') {
        UpdatedUserInfoSuccessfully(UserName, vUser);
        cout << "\nUser Deleted Successfully.";
    }
    else {
        cout << "\nWill Not Delete.";
    }
}

// Updata the user information.
void UpdateUserInfo() {
    cout << "----------------------------------------";
    cout << "\n\tUpdate User Screen";
    cout << "\n----------------------------------------";

    vector<stUserData> vUser = GetDataFromUserFile();

    string UserName = GetUserName();
    stUserData CurrentUser;

    if (FindUserByUserName(UserName, CurrentUser)) {
        PrintUserDetails(CurrentUser);
        SureToUpdateUserInfo(UserName, vUser);
    }
    else {
        cout << "\nUser With User Name [" << UserName << "] Is Not Found!";
    }
}

// =================== 7.5 Find Users =========================

// Search if the user is in the system.
void FindUser() {
    cout << "----------------------------------------";
    cout << "\n\tFind User Screen";
    cout << "\n----------------------------------------";

    string UserName = GetUserName();
    stUserData CurrentUser;

    if (FindUserByUserName(UserName, CurrentUser)) {
        PrintUserDetails(CurrentUser);
    }
    else {
        cout << "\nUser With User Name [" << UserName << "] Is Not Found!";
    }
}

// ================ 7.6 Main Manage User Control =====================

void PrintManageUsersMenu() {
    cout << "===============================\n";
    cout << setw(3) << "Manage Users Menu Screen";
    cout << "\n===============================\n";
    cout << setw(2) << "[1] Show Users List.";
    cout << setw(2) << "\n[2] Add New User.";
    cout << setw(2) << "\n[3] Delete User.";
    cout << setw(2) << "\n[4] Update User Info.";
    cout << setw(2) << "\n[5] Find User.";
    cout << setw(2) << "\n[6] Main Menu.";
    cout << "\n===============================\n";
}

void ShowManageUsersMenu() {
    bool exit = false;

    do {
        system("cls");  // Clear screen at start
        PrintManageUsersMenu();

        short choice;
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> choice;

        switch (choice) {
        case enManageUsersMenu::enShowUser:
            ShowUsersList();
            BackToMainMenu();
            break;
        case enManageUsersMenu::enAddUser:
            AddUsers();
            BackToMainMenu();
            break;
        case enManageUsersMenu::enDeleteUser:
            DeleteUserFromFile();
            BackToMainMenu();
            break;
        case enManageUsersMenu::enUpdateUser:
            UpdateUserInfo();
            BackToMainMenu();
            break;
        case enManageUsersMenu::enFindUser:
            FindUser();
            BackToMainMenu();
            break;
        case enManageUsersMenu::enMainMenuUser:
            StartProgram();
            break;
        default:
            system("cls");
            cout << "Invalid choice! Please enter 1-7.\n";
            BackToMainMenu();
        }
    } while (!exit);
}

// ====================== Start Program ==========================

void BackToMainMenu() {
    cout << "\n\n\nPress any key to go back to the menu...";
    system("pause");
}

void PrintMenu() {
    cout << "===============================\n";
    cout << setw(3) << "Main Menu Screen";
    cout << "\n===============================\n";
    cout << setw(2) << "[1] Show Client List.";
    cout << setw(2) << "\n[2] Add New Client.";
    cout << setw(2) << "\n[3] Delete Client.";
    cout << setw(2) << "\n[4] Update Client Info.";
    cout << setw(2) << "\n[5] Find Client.";
    cout << setw(2) << "\n[6] Transaction.";
    cout << setw(2) << "\n[7] Manage Users.";
    cout << setw(2) << "\n[8] Logout.";
    cout << "\n===============================\n";
}

void StartProgram() {
    bool exit = false;

    do {
        system("cls");  // Clear screen at start
        PrintMenu();

        short choice;
        cout << "Choose what do you want to do? [1 to 8]? ";
        cin >> choice;

        switch (choice) {
        case enMenu::enShow:
            ShowClientList();
            BackToMainMenu();
            break;
        case enMenu::enAdd:
            AddClient();
            BackToMainMenu();
            break;
        case enMenu::enDelete:
            DeleteClientFromFile();
            BackToMainMenu();
            break;
        case enMenu::enUpdate:
            UpdateClientInfo();
            BackToMainMenu();
            break;
        case enMenu::enFind:
            FindClient();
            BackToMainMenu();
            break;
        case enMenu::enTransaction:
            TransactionProgram();
            break;
        case enMenu::enManageUsers:
            system("cls");
            ShowManageUsersMenu();
            break;
        case enMenu::enLogout:
            LoginScreen();
            exit = true;
            break;
        default:
            system("cls");
            cout << "Invalid choice! Please enter 1-7.\n";
            BackToMainMenu();
        }
    } while (!exit);
}

// ======================= Login Screen ==========================

bool FindUserByUserNameAndPassword(string UserName, string Password, stUserData& User) {
    vector<stUserData> vUsers = GetDataFromUserFile();

    for (stUserData& U : vUsers) {
        User = U;
        if (U.UserName == UserName && U.Password == Password) {
            User = U;
            return true;
        }
    }

    return false; 
}

bool IsValidUserData(string UserName, string Password) {
    return FindUserByUserNameAndPassword(UserName, Password, CurrentUser);
}

void LoginScreen() {
    bool InvalidLogin = false;

    string UserName, Password;

    do {
        system("cls");
        cout << "----------------------------------------";
        cout << "\n\tLogin Screen";
        cout << "\n----------------------------------------";

        if (InvalidLogin) {
            cout << "\nInvalid User Name or Password!";
        }

        cout << "\nEnter User Name? ";
        cin >> UserName;

        cout << "Enter Password? ";
        cin >> Password;

        InvalidLogin = !IsValidUserData(UserName, Password);
    } while (InvalidLogin);

    StartProgram();
}

int main() {
    LoginScreen();
    return 0;
}