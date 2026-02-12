/*
         Problem #51: Write a program to find a client data by
    account number and delete the data then update and upload them to file.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct ClientsData {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool Flag = false;
};

// Split words and add them to vector.
vector<string> SplitWords(string S, string delmi = "/##") {
    int pos = 0;
    string sWord = "";
    vector<string> vString;

    while ((pos = S.find(delmi)) != std::string::npos) {
        sWord = S.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);
        S.erase(0, pos + delmi.length());
    }

    if (S != "") vString.push_back(S);
    return vString;
}

// Convert string line to record.
ClientsData ConvertLineToRecord(string S) {
    vector<string> vClient;
    vClient = SplitWords(S);

    ClientsData stClient;
    stClient.AccountNumber = vClient[0];
    stClient.PinCode = vClient[1];
    stClient.Name = vClient[2];
    stClient.Phone = vClient[3];
    stClient.AccountBalance = stod(vClient[4]);
    return stClient;
}

// Get Data from external file and save them in vector.
vector<ClientsData> GetLineFromFile(string FileName) {
    vector<ClientsData> vClients;

    fstream myFile;
    myFile.open(FileName, ios::in);

    if (myFile.is_open()) {

        string Line;
        ClientsData stClient;
        while (getline(myFile, Line)) {
            stClient = ConvertLineToRecord(Line);
            vClients.push_back(stClient);
        }

        myFile.close();
    }
    return vClients;
}

// Print all clients data if we find them.
void PrintAllClientsData(ClientsData Client) {
    cout << "\nThe following are the client details:\n";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
}

// Check if the client is in the system by his account number.
bool FindClientByAccNum(vector<ClientsData> vClients, string target, ClientsData& stClient) {
    for (ClientsData& V : vClients) {
        if (V.AccountNumber == target) {
            stClient = V;
            return true;
        }
    }
    return false;
}

// Mark a flag for the target client to delete.
bool MarkClientToDelete(string accountNumber, vector<ClientsData>& vClient) {
    for (ClientsData& V : vClient) {
        if (V.AccountNumber == accountNumber) {
            V.Flag = true;
            return true;
        }
    }
    return false;
}

// Convert vector of struct that contain record for clients to string line.
string ConvertRecordToLine(ClientsData vClient, string delmi = "/##") {
    string S;
    S += vClient.AccountNumber + delmi;
    S += vClient.PinCode + delmi;
    S += vClient.Name + delmi;
    S += vClient.Phone + delmi;
    S += to_string(vClient.AccountBalance) + delmi;
    return S;
}

// Write and save data on external file.
void SaveClientDataToFile(string fileName, vector<ClientsData> vClient) {
    fstream myFile;
    myFile.open(fileName, ios::out);
    if (myFile.is_open()) {
        for (ClientsData& V : vClient) {
                string Line = ConvertRecordToLine(V);
                myFile << Line << endl;
        }
        myFile.close();
    }
}

// Update data for client.
void GetUpdatedData(vector<ClientsData> &vClient) {
    for (ClientsData& V : vClient) {
        if(V.Flag == true) {
            cout << "\nEnter PinCode: ";
            getline(cin >> ws, V.PinCode);
            cout << "\nEnter Name: ";
            getline(cin, V.Name);
            cout << "\nEnter Phone: ";
            getline(cin, V.Phone);
            cout << "\nEnter Account Balance: ";
            cin >> V.AccountBalance;
            return;
        }
    }
}

// Updat account slect by user from file.
void UpdateAccount(vector<ClientsData> vClients, string target) {
    ClientsData stClient;
    char choice = 'N';

    if (FindClientByAccNum(vClients, target, stClient)) {

        PrintAllClientsData(stClient);

        cout << "\n\nAre you sure you want to update this client? Y/N? ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            MarkClientToDelete(target, vClients);
            GetUpdatedData(vClients);
            SaveClientDataToFile("myFile.txt", vClients);
            vClients = GetLineFromFile("myFile.txt");
            cout << "\nClient Updated Successfully";
            return;
        }
        else {
            cout << "\nOkay. Not Deleted.";
            return;
        }
    }
    cout << '\n' << target << " Not Fond.";
}

// Read client account number.
string ReadClientAccNum() {
    string target;
    cout << "Please Enter Account Number? ";
    cin >> target;
    return target;
}

int main()
{
    vector<ClientsData> vClients = GetLineFromFile("myFile.txt");
    string target = ReadClientAccNum();
    UpdateAccount(vClients, target);
    return 0;
}
