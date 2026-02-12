/*
       Problem #49: Write a program to find a client by
          account number and print it to the screen
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
void FindClientByAccNum(vector<ClientsData> vClients, string target) {
    for (ClientsData& V : vClients) {
        if (V.AccountNumber == target) {
            PrintAllClientsData(V);
            return;
        }
    }
    cout << "\nNot Fond.";
    return;
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
    FindClientByAccNum(vClients, target);
    return 0;
}
